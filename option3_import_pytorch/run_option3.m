%% Option 3: Import, Fix Custom Layers, Then Generate Code
% This script orchestrates the full Option 3 workflow:
%   1. Import model (which generates custom layers)
%   2. Fix custom layers for codegen compatibility (add %#codegen)
%   3. Re-save the network and generate C code

scriptDir = fileparts(mfilename('fullpath'));
projectDir = fullfile(scriptDir, '..');
matFilePath = fullfile(scriptDir, 'shufflenet_dlnetwork.mat');
modelPath = fullfile(projectDir, 'shufflenet_exported.pt2');

fprintf('=============================================================\n');
fprintf(' Option 3: importNetworkFromPyTorch + MATLAB Coder\n');
fprintf('=============================================================\n\n');

%% Phase 1: Import and Expand
fprintf('--- Phase 1: Import Model ---\n');
tStart = tic;
net = importNetworkFromPyTorch(modelPath, PyTorchInputSizes=[NaN 3 224 224]);
importTime = toc(tStart);
fprintf('Import completed in %.1f seconds. Layers: %d\n', importTime, numel(net.Layers));

% Test inference
sampleInput = dlarray(single(randn(224, 224, 3, 1)), 'SSCB');
dlOut = predict(net, sampleInput);
outData = extractdata(dlOut);
fprintf('Inference OK. Output size: [%s]\n', num2str(size(outData)));

% Expand network layers (required for codegen)
fprintf('Expanding layers...\n');
net = expandLayers(net);
fprintf('Expanded to %d layers.\n', numel(net.Layers));

% Save
save(matFilePath, 'net');
fprintf('Network saved to: %s\n\n', matFilePath);

%% Phase 2: Fix Custom Layer Codegen Pragmas
fprintf('--- Phase 2: Fix Custom Layers for Codegen ---\n');
fix_codegen_pragmas;

%% Phase 3: Generate C Code
fprintf('\n--- Phase 3: Generate C Code ---\n');
outputDir = fullfile(scriptDir, 'codegen_output');
if ~isfolder(outputDir); mkdir(outputDir); end

embeddedDir = fullfile(outputDir, 'embedded_libfree');
if ~isfolder(embeddedDir); mkdir(embeddedDir); end

% Configure Embedded Coder (library-free)
cfg = coder.config('lib', 'ecoder', true);
cfg.TargetLang = 'C';
cfg.GenerateReport = true;
cfg.GenCodeOnly = true;

dlcfg = coder.DeepLearningConfig('none');
cfg.DeepLearningConfig = dlcfg;

cfg.EnableMemcpy = true;
cfg.MemcpyThreshold = 64;
cfg.EnableOpenMP = false;
cfg.SupportNonFinite = false;
cfg.BuildConfiguration = 'Faster Runs';
cfg.PurelyIntegerCode = false;

% Input spec: [224 x 224 x 3 x 1] single
inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

fprintf('Generating library-free embedded C code...\n');
tStart = tic;
try
    codegen -config cfg ...
            -d embeddedDir ...
            predict_shufflenet ...
            -args {inputArg} ...
            -report
    codegenTime = toc(tStart);
    fprintf('Code generation SUCCESS in %.1f seconds.\n', codegenTime);

    % Report metrics
    cFiles = dir(fullfile(embeddedDir, '**', '*.c'));
    hFiles = dir(fullfile(embeddedDir, '**', '*.h'));
    totalSize = sum([cFiles.bytes]) + sum([hFiles.bytes]);
    fprintf('Generated %d .c files, %d .h files (%.1f KB total)\n', ...
        numel(cFiles), numel(hFiles), totalSize/1024);
catch ME
    codegenTime = toc(tStart);
    fprintf(2, 'Code generation FAILED: %s\n', ME.message);
end

%% Summary
fprintf('\n=============================================================\n');
fprintf(' Option 3 Summary\n');
fprintf('=============================================================\n');
fprintf('  Import time:    %.1f s\n', importTime);
fprintf('  Codegen time:   %.1f s\n', codegenTime);
fprintf('  Output dir:     %s\n', embeddedDir);
fprintf('=============================================================\n');
