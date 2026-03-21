%% validate_mex_equivalence.m
% =========================================================================
% 100-Test Numerical Equivalence for MEX-Compiled C Code
% =========================================================================
%
% After code generation, each option produces a MEX function. This script
% validates that the MEX (compiled C) output matches PyTorch reference
% across all 100 test vectors.
%
% This tests the ACTUAL GENERATED C code (compiled as MEX), not the
% MATLAB-level inference. Combined with validate_matlab_equivalence.m,
% it provides full coverage:
%   1) MATLAB inference == PyTorch reference  (validate_matlab_equivalence.m)
%   2) MEX (C code)     == PyTorch reference  (this script)
%   3) MEX (C code)     == MATLAB inference   (derived from 1 & 2)
%
% Usage:
%   cd equivalence_tests/
%   validate_mex_equivalence
% =========================================================================

clear; clc;
fprintf('=================================================================\n');
fprintf(' ShuffleNet V2 — 100-Test MEX Equivalence Validation\n');
fprintf('=================================================================\n\n');

%% Configuration
NUM_TESTS   = 100;
INPUT_SHAPE = [3, 224, 224];
OUTPUT_SIZE = 1000;

testVectorDir = fullfile(pwd, 'test_vectors');
projectDir    = fileparts(pwd);

%% Load reference data
fprintf('Loading reference data...\n');
refOutputFile = fullfile(testVectorDir, 'all_outputs_100x1000.bin');
refInputFile  = fullfile(testVectorDir, 'all_inputs_100x3x224x224.bin');

fid = fopen(refOutputFile, 'r', 'l');
refOutputs = fread(fid, [OUTPUT_SIZE, NUM_TESTS], 'float32')';
fclose(fid);

fid = fopen(refInputFile, 'r', 'l');
refInputsRaw = fread(fid, [prod(INPUT_SHAPE), NUM_TESTS], 'float32');
fclose(fid);
fprintf('  Loaded %d reference test vectors\n', NUM_TESTS);

%% Helper: compute metrics (same as validate_matlab_equivalence.m)
    function metrics = computeMetrics(yRef, yTest)
        diff = double(yTest(:)) - double(yRef(:));
        metrics.maxAbsErr  = max(abs(diff));
        metrics.meanAbsErr = mean(abs(diff));
        metrics.rmsErr     = sqrt(mean(diff.^2));
        refNorm = norm(double(yRef(:)));
        if refNorm > 0
            metrics.relL2Err = norm(diff) / refNorm;
        else
            metrics.relL2Err = norm(diff);
        end
        a = double(yRef(:)); b = double(yTest(:));
        metrics.cosineSim = dot(a, b) / (norm(a) * norm(b) + eps);
        [~, ref1]  = max(yRef);   [~, test1] = max(yTest);
        metrics.top1Match = (ref1 == test1);
        [~, rI] = sort(double(yRef(:)),'descend');
        [~, tI] = sort(double(yTest(:)),'descend');
        inter = numel(intersect(rI(1:5), tI(1:5)));
        uni   = numel(union(rI(1:5), tI(1:5)));
        metrics.top5Jaccard = inter / uni;
    end

%% Test each MEX function that exists
mexTests = {};

% Option 2: PyTorch Coder MEX
opt2Mex = fullfile(projectDir, 'option2_pytorch_coder', ...
    ['mInvoke_shufflenet_mex.' mexext]);
if isfile(opt2Mex)
    mexTests{end+1} = struct('name', 'Option2_PyTorchCoder_MEX', ...
        'dir', fullfile(projectDir, 'option2_pytorch_coder'), ...
        'func', @(x) mInvoke_shufflenet_mex( ...
            fullfile(projectDir, 'shufflenet_exported.pt2'), x), ...
        'inputFormat', 'BCHW');
end

% Option 3: importNetworkFromPyTorch MEX
opt3Mex = fullfile(projectDir, 'option3_import_pytorch', ...
    ['predict_shufflenet_mex.' mexext]);
if isfile(opt3Mex)
    mexTests{end+1} = struct('name', 'Option3_importPyTorch_MEX', ...
        'dir', fullfile(projectDir, 'option3_import_pytorch'), ...
        'func', @(x) predict_shufflenet_mex(x), ...
        'inputFormat', 'SSCB');
end

% Option 4: ONNX import MEX
opt4Mex = fullfile(projectDir, 'option4_onnx_import', ...
    ['predict_shufflenet_onnx_mex.' mexext]);
if isfile(opt4Mex)
    mexTests{end+1} = struct('name', 'Option4_importONNX_MEX', ...
        'dir', fullfile(projectDir, 'option4_onnx_import'), ...
        'func', @(x) predict_shufflenet_onnx_mex(x), ...
        'inputFormat', 'SSCB');
end

if isempty(mexTests)
    fprintf('\nNo MEX files found. Generate MEX first using:\n');
    fprintf('  Option 2: run generate_code_pytorch_coder.m\n');
    fprintf('  Option 3: run import_and_generate.m\n');
    fprintf('  Option 4: run import_onnx_and_generate.m\n');
    fprintf('\nAlternatively, run validate_matlab_equivalence.m to test\n');
    fprintf('MATLAB-level inference without MEX compilation.\n');
    return;
end

%% Run tests for each MEX
summaryResults = {};

for mi = 1:numel(mexTests)
    mt = mexTests{mi};
    fprintf('\n─────────────────────────────────────────────────────────────\n');
    fprintf(' %s\n', mt.name);
    fprintf('─────────────────────────────────────────────────────────────\n');

    addpath(mt.dir);

    maxErrs   = nan(NUM_TESTS, 1);
    relL2Errs = nan(NUM_TESTS, 1);
    cosines   = nan(NUM_TESTS, 1);
    top1s     = false(NUM_TESTS, 1);
    inferMs   = nan(NUM_TESTS, 1);
    success   = true;

    try
        for i = 1:NUM_TESTS
            inputCHW = reshape(refInputsRaw(:, i), INPUT_SHAPE);

            % Format input per MEX expectations
            if strcmp(mt.inputFormat, 'BCHW')
                testInput = reshape(inputCHW, [1, INPUT_SHAPE]);
            else  % SSCB
                testInput = dlarray(single(permute(inputCHW, [2,3,1])), 'SSCB');
            end

            tic;
            outTest = mt.func(testInput);
            inferMs(i) = toc * 1000;

            outTest = squeeze(double(extractdata(outTest)));
            yRef = refOutputs(i, :);
            m = computeMetrics(yRef, outTest);

            maxErrs(i)   = m.maxAbsErr;
            relL2Errs(i) = m.relL2Err;
            cosines(i)   = m.cosineSim;
            top1s(i)     = m.top1Match;

            if mod(i, 25) == 0
                fprintf('  Test %3d/100: maxErr=%.2e, relL2=%.2e, top1=%s\n', ...
                    i, m.maxAbsErr, m.relL2Err, mat2str(m.top1Match));
            end
        end
    catch ME
        fprintf('  FAILED at test %d: %s\n', i, ME.message);
        success = false;
    end

    if success
        worstMax = max(maxErrs);
        avgRel   = mean(relL2Errs);
        avgCos   = mean(cosines);
        top1Pct  = sum(top1s) / NUM_TESTS * 100;
        avgMs    = mean(inferMs);

        if worstMax < 1e-3
            status = 'PASS';
        elseif worstMax < 1e-1
            status = 'MARGINAL';
        else
            status = 'FAIL';
        end

        fprintf('\n  Summary:\n');
        fprintf('    Worst max|err|: %.2e\n', worstMax);
        fprintf('    Avg rel L2:     %.2e\n', avgRel);
        fprintf('    Avg cosine:     %.8f\n', avgCos);
        fprintf('    Top-1 match:    %.1f%%\n', top1Pct);
        fprintf('    Avg inference:  %.1f ms\n', avgMs);
        fprintf('    Status:         [%s]\n', status);

        summaryResults{end+1} = struct('name', mt.name, ...
            'worstMax', worstMax, 'avgRel', avgRel, 'avgCos', avgCos, ...
            'top1Pct', top1Pct, 'avgMs', avgMs, 'status', status);
    end

    rmpath(mt.dir);
end

%% Final summary
fprintf('\n=================================================================\n');
fprintf(' MEX EQUIVALENCE SUMMARY\n');
fprintf('=================================================================\n');
fprintf('%-32s %12s %12s %8s %8s\n', 'MEX Function', 'WorstMaxErr', 'AvgRelL2', 'Top1%', 'Status');
fprintf('%s\n', repmat('-', 1, 76));
for si = 1:numel(summaryResults)
    s = summaryResults{si};
    fprintf('%-32s %12.2e %12.2e %7.1f%% %8s\n', ...
        s.name, s.worstMax, s.avgRel, s.top1Pct, s.status);
end
fprintf('=================================================================\n');
