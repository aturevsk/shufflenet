%% Option 4: ONNX Import + MATLAB Coder
% Import ShuffleNet V2 from ONNX and generate embedded C code.
% R2026a: auto-generated custom layers from ONNX support code generation.
%
% Prerequisites: Run export_to_onnx.py first to generate shufflenet_v2.onnx

scriptDir = fileparts(mfilename('fullpath'));
onnxPath = fullfile(scriptDir, 'shufflenet_v2.onnx');
matFilePath = fullfile(scriptDir, 'shufflenet_onnx_dlnetwork.mat');

fprintf('=============================================================\n');
fprintf(' Option 4: ONNX Import + MATLAB Coder\n');
fprintf('=============================================================\n\n');

if ~isfile(onnxPath)
    error('ONNX file not found: %s\nRun export_to_onnx.py first.', onnxPath);
end
fprintf('ONNX file: %s (%.2f MB)\n\n', onnxPath, dir(onnxPath).bytes/1e6);

%% Phase 1: Import ONNX Model
fprintf('--- Phase 1: Import ONNX Model ---\n');
tStart = tic;
net = importNetworkFromONNX(onnxPath, ...
    'InputDataFormats', 'BCSS', ...
    'OutputDataFormats', 'BC', ...
    'GenerateCoderFiles', true);
importTime = toc(tStart);
fprintf('Imported in %.1f seconds. Layers: %d\n', importTime, numel(net.Layers));

% Print layer summary
fprintf('\nNetwork layers:\n');
disp(net.Layers);

%% Phase 2: Test Inference
fprintf('\n--- Phase 2: Test Inference ---\n');
% ONNX import with BCSS format expects SSCB input in MATLAB
sampleInput = dlarray(single(randn(224, 224, 3, 1)), 'SSCB');
tStart = tic;
dlOut = predict(net, sampleInput);
infTime = toc(tStart);
outData = extractdata(dlOut);
fprintf('Inference OK (%.3f s). Output size: [%s]\n', infTime, num2str(size(outData)));

% Top-5
probs = exp(outData) ./ sum(exp(outData(:)));
[sortedP, sortedI] = sort(probs(:), 'descend');
fprintf('Top-5 classes: ');
for k = 1:5
    fprintf('%d(%.3f) ', sortedI(k), sortedP(k));
end
fprintf('\n');

%% Phase 3: Expand Layers and Save
fprintf('\n--- Phase 3: Expand and Save ---\n');
try
    net = expandLayers(net);
    fprintf('Expanded to %d layers.\n', numel(net.Layers));
catch ME
    fprintf('expandLayers not needed or failed: %s\n', ME.message);
end
save(matFilePath, 'net');
fprintf('Saved to: %s (%.2f MB)\n', matFilePath, dir(matFilePath).bytes/1e6);

%% Phase 4: Check Code Generation Readiness
fprintf('\n--- Phase 4: Code Generation Readiness ---\n');
try
    codegenResult = analyzeNetworkForCodegen(net);
    disp(codegenResult);
catch ME
    fprintf('analyzeNetworkForCodegen: %s\n', ME.message);
end

%% Phase 5: Generate Embedded C Code (Library-Free)
fprintf('\n--- Phase 5: Generate Embedded C Code ---\n');
outputDir = fullfile(scriptDir, 'codegen_output');
embeddedDir = fullfile(outputDir, 'embedded_libfree');
if ~isfolder(embeddedDir); mkdir(embeddedDir); end

cfg = coder.config('lib', 'ecoder', true);
cfg.TargetLang = 'C';
cfg.GenerateReport = true;
cfg.GenCodeOnly = true;
cfg.EnableMemcpy = true;
cfg.SupportNonFinite = false;
cfg.BuildConfiguration = 'Faster Runs';
cfg.PurelyIntegerCode = false;

% Expert-reviewed performance settings
cfg.EnableOpenMP = true;           % Expert fix #5: multi-core Cortex-A53
cfg.LargeConstantThreshold = 0;   % Expert fix #4: weights in binary files

% Deep learning config (library-free)
dlcfg = coder.DeepLearningConfig('none');
cfg.DeepLearningConfig = dlcfg;

% Expert fix #1: NEON SIMD intrinsics (property of cfg, not dlcfg)
cfg.InstructionSetExtensions = 'Neon v7';

% Target hardware: Raspberry Pi (expert fix #2)
try
    cfg.Hardware = coder.hardware('Raspberry Pi');
catch
    fprintf('  (Raspberry Pi support package not installed, using GenCodeOnly)\n');
end

fprintf('  SIMD: NEON v7 | OpenMP: ON | Weights: binary files\n');

inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

fprintf('Generating library-free embedded C code...\n');
tStart = tic;
try
    codegen -config cfg ...
            -d embeddedDir ...
            predict_shufflenet_onnx ...
            -args {inputArg} ...
            -report
    codegenTime = toc(tStart);
    fprintf('Code generation SUCCESS in %.1f seconds.\n', codegenTime);

    cFiles = dir(fullfile(embeddedDir, '**', '*.c'));
    hFiles = dir(fullfile(embeddedDir, '**', '*.h'));
    totalSize = sum([cFiles.bytes]) + sum([hFiles.bytes]);
    fprintf('Generated %d .c, %d .h files (%.1f KB total)\n', ...
        numel(cFiles), numel(hFiles), totalSize/1024);

    % List largest files
    allFiles = [cFiles; hFiles];
    if ~isempty(allFiles)
        [~, idx] = sort([allFiles.bytes], 'descend');
        fprintf('Largest files:\n');
        for k = 1:min(10, numel(idx))
            f = allFiles(idx(k));
            fprintf('  %8.1f KB  %s\n', f.bytes/1024, f.name);
        end
    end
catch ME
    codegenTime = toc(tStart);
    fprintf(2, 'Code generation FAILED: %s\n', ME.message);
end

%% Summary
fprintf('\n=============================================================\n');
fprintf(' Option 4 Summary\n');
fprintf('=============================================================\n');
fprintf('  Import time:    %.1f s\n', importTime);
fprintf('  Inference time: %.3f s\n', infTime);
if exist('codegenTime', 'var')
    fprintf('  Codegen time:   %.1f s\n', codegenTime);
end
fprintf('  Output dir:     %s\n', embeddedDir);
fprintf('=============================================================\n');
