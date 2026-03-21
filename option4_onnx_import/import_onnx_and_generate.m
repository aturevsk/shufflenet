%% Import ShuffleNet V2 from ONNX and Generate Embedded C Code
% This script provides a fallback pathway for deploying ShuffleNet V2 to
% the ARM Cortex-A embedded platform board by first exporting from PyTorch to ONNX,
% then importing the ONNX model into MATLAB for code generation.
%
% This approach is useful when:
%   - Direct PyTorch import (importNetworkFromPyTorch) encounters issues
%   - The PyTorch Coder Support Package is not available
%   - You need maximum compatibility with MATLAB's code generation tools
%
% Workflow:
%   1. Import ONNX model using importNetworkFromONNX
%   2. Display and analyze network architecture
%   3. Test inference with a sample image
%   4. Save dlnetwork to .mat file
%   5. Generate MEX for host validation
%   6. Configure embedded deployment (library-free + ARM Compute Library)
%   7. Generate embedded C code
%   8. Report metrics
%
% Prerequisites:
%   - Run export_to_onnx.py first to generate shufflenet_v2.onnx
%   - MATLAB R2026a or later
%   - Deep Learning Toolbox
%   - Deep Learning Toolbox Converter for ONNX Model Format
%   - MATLAB Coder
%   - Embedded Coder
%
% Note on R2026a: Auto-generated custom layers from ONNX imports now
% support code generation, enabling direct codegen from ONNX-imported
% networks without manual layer replacement.

%   Copyright 2026. Generated for ARM Cortex-A embedded platform deployment.

%% Setup
clear; clc; close all;
fprintf('=============================================================\n');
fprintf(' ShuffleNet V2 ONNX Import & Embedded Code Generation\n');
fprintf(' Target: ARM Cortex-A embedded platform (ARM Cortex-A53)\n');
fprintf('=============================================================\n\n');

% Resolve paths
scriptDir = fileparts(mfilename('fullpath'));
onnxPath = fullfile(scriptDir, 'shufflenet_v2.onnx');
matFilePath = fullfile(scriptDir, 'shufflenet_onnx_dlnetwork.mat');

% Check that ONNX file exists
if ~isfile(onnxPath)
    error('onnx_import:onnxNotFound', ...
        ['ONNX model not found: %s\n' ...
         'Run export_to_onnx.py first:\n' ...
         '  cd %s\n' ...
         '  python export_to_onnx.py'], onnxPath, scriptDir);
end

onnxInfo = dir(onnxPath);
fprintf('ONNX model: %s\n', onnxPath);
fprintf('ONNX file size: %.2f MB\n\n', onnxInfo.bytes / 1e6);

% Output directory
outputDir = fullfile(scriptDir, 'codegen_output');
if ~isfolder(outputDir)
    mkdir(outputDir);
end

%% Step 1: Import ONNX Model
fprintf('--- Step 1: Importing ONNX Model ---\n');
try
    tStart = tic;

    % Import the ONNX model into a dlnetwork
    % InputDataFormats: 'BCSS' maps ONNX NCHW to MATLAB's internal format
    %   B = Batch, C = Channel, S = Spatial (Height), S = Spatial (Width)
    % OutputDataFormats: 'BC' maps ONNX output (Batch, Classes) format
    % GenerateCoderFiles: true generates codegen-compatible custom layer
    %   files (new in R2026a - custom layers from ONNX now support codegen)
    net = importNetworkFromONNX(onnxPath, ...
        'InputDataFormats', 'BCSS', ...
        'OutputDataFormats', 'BC', ...
        'GenerateCoderFiles', true);

    importTime = toc(tStart);
    fprintf('ONNX model imported successfully in %.2f seconds.\n', importTime);
    fprintf('Network class: %s\n', class(net));

    % Display network summary
    if isa(net, 'dlnetwork')
        fprintf('Number of layers: %d\n', numel(net.Layers));
        fprintf('Number of connections: %d\n', height(net.Connections));

        % Count parameters
        totalParams = 0;
        for i = 1:numel(net.Learnables.Value)
            totalParams = totalParams + numel(net.Learnables.Value{i});
        end
        fprintf('Total parameters: %s (%.2f M)\n', ...
            num2str(totalParams), totalParams / 1e6);

        % List layer types
        layerTypes = arrayfun(@(l) class(l), net.Layers, 'UniformOutput', false);
        uniqueTypes = unique(layerTypes);
        fprintf('Layer types (%d unique):\n', numel(uniqueTypes));
        for i = 1:numel(uniqueTypes)
            count = sum(strcmp(layerTypes, uniqueTypes{i}));
            % Extract short name (remove package prefix)
            parts = strsplit(uniqueTypes{i}, '.');
            shortName = parts{end};
            fprintf('  %3d x %s\n', count, shortName);
        end
    end
catch ME
    fprintf(2, 'ERROR: Failed to import ONNX model.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '\nPossible solutions:\n');
    fprintf(2, '  - Install: Deep Learning Toolbox Converter for ONNX Model Format\n');
    fprintf(2, '  - Re-export ONNX with a lower opset version (try 13 or 11)\n');
    fprintf(2, '  - Check for unsupported ONNX operators in the model\n');
    rethrow(ME);
end

%% Step 2: Display and Analyze Network
fprintf('\n--- Step 2: Network Architecture Analysis ---\n');
try
    tStart = tic;

    % Display layer list
    fprintf('Layer summary:\n');
    disp(net.Layers);

    % Open interactive network analyzer
    fprintf('Opening network analyzer...\n');
    analyzeNetwork(net);

    % Check code generation readiness
    fprintf('\nChecking code generation readiness...\n');
    codegenResult = analyzeNetworkForCodegen(net);

    if isprop(codegenResult, 'IsSupported') || isfield(codegenResult, 'IsSupported')
        if codegenResult.IsSupported
            fprintf('  Code generation readiness: PASS\n');
        else
            fprintf(2, '  Code generation readiness: FAIL\n');
            fprintf(2, '  Review the report for unsupported layers.\n');
            fprintf(2, '  Note: R2026a supports codegen for ONNX auto-generated custom layers.\n');
        end
    end

    analysisTime = toc(tStart);
    fprintf('Analysis completed in %.2f seconds.\n', analysisTime);
catch ME
    fprintf('Warning: Network analysis encountered issues: %s\n', ME.message);
end

%% Step 3: Test Inference
fprintf('\n--- Step 3: Test Inference ---\n');
try
    tStart = tic;

    % Create sample input
    % After ONNX import with 'BCSS' format, the network expects MATLAB's
    % standard SSCB (Height x Width x Channels x Batch) dlarray format
    inputSize = [224, 224, 3, 1]; % HWC batch=1
    sampleInput = single(randn(inputSize));
    sampleDlarray = dlarray(sampleInput, 'SSCB');

    fprintf('Input size: [%s] (SSCB format)\n', num2str(size(sampleDlarray)));

    % Run inference
    dlOutput = predict(net, sampleDlarray);
    inferenceTime = toc(tStart);

    outputData = extractdata(dlOutput);
    fprintf('Inference completed in %.4f seconds.\n', inferenceTime);
    fprintf('Output size: [%s]\n', num2str(size(outputData)));

    % Show top predictions
    probabilities = exp(outputData) ./ sum(exp(outputData(:)));
    [sortedProbs, sortedIdx] = sort(probabilities(:), 'descend');
    fprintf('\nTop-5 predicted class indices (random input):\n');
    for k = 1:min(5, numel(sortedIdx))
        fprintf('  Class %4d: probability = %.6f\n', sortedIdx(k), sortedProbs(k));
    end

    % Timing benchmark (multiple runs)
    fprintf('\nBenchmark (10 inference runs):\n');
    times = zeros(1, 10);
    for r = 1:10
        tRun = tic;
        predict(net, sampleDlarray);
        times(r) = toc(tRun);
    end
    fprintf('  Mean: %.4f s, Std: %.4f s, Min: %.4f s, Max: %.4f s\n', ...
        mean(times), std(times), min(times), max(times));

catch ME
    fprintf(2, 'ERROR: Inference test failed.\n');
    fprintf(2, '  %s\n', ME.message);
    rethrow(ME);
end

%% Step 4: Save dlnetwork
fprintf('\n--- Step 4: Saving dlnetwork ---\n');
try
    tStart = tic;
    save(matFilePath, 'net');
    saveTime = toc(tStart);

    fileInfo = dir(matFilePath);
    fprintf('Network saved to: %s\n', matFilePath);
    fprintf('File size: %.2f MB\n', fileInfo.bytes / 1e6);
    fprintf('Save time: %.2f seconds.\n', saveTime);
catch ME
    fprintf(2, 'ERROR: Failed to save network.\n');
    fprintf(2, '  %s\n', ME.message);
    rethrow(ME);
end

%% Step 5: Generate MEX for Validation
fprintf('\n--- Step 5: MEX Code Generation ---\n');
mexOutputDir = fullfile(outputDir, 'mex');
if ~isfolder(mexOutputDir)
    mkdir(mexOutputDir);
end

try
    tStart = tic;

    mexCfg = coder.config('mex');
    mexCfg.TargetLang = 'C';
    mexCfg.GenerateReport = true;
    mexCfg.SIMDAcceleration = 'Full'; % AVX2 SIMD for host MEX

    % Use MKL-DNN for efficient host-side MEX inference
    dlcfg = coder.DeepLearningConfig('mkldnn');
    mexCfg.DeepLearningConfig = dlcfg;

    % Input: single [224 x 224 x 3 x 1]
    inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

    fprintf('Generating MEX code...\n');
    codegen -config mexCfg ...
            -d mexOutputDir ...
            predict_shufflenet_onnx ...
            -args {inputArg} ...
            -report

    mexTime = toc(tStart);
    fprintf('MEX generation completed in %.2f seconds.\n', mexTime);

    % Validate
    fprintf('Validating MEX output...\n');
    mexResult = predict_shufflenet_onnx_mex(sampleInput);
    maxDiff = max(abs(double(outputData(:)) - double(mexResult(:))));
    fprintf('  Max difference (MATLAB vs MEX): %.2e\n', maxDiff);
    if maxDiff < 1e-4
        fprintf('  PASS: Results match within tolerance.\n');
    else
        fprintf('  WARNING: Results differ beyond tolerance.\n');
    end
catch ME
    fprintf('Warning: MEX generation failed: %s\n', ME.message);
    fprintf('  Continuing with embedded code generation...\n');
end

%% Step 6: Configure Embedded Deployment
fprintf('\n--- Step 6: Embedded Deployment Configuration ---\n');

% --- Configuration A: Library-free C code ---
fprintf('\n  [Config A] Library-free C code (no external dependencies)\n');
try
    cfgA = coder.config('lib', 'ecoder', true);
    cfgA.TargetLang = 'C';
    cfgA.GenerateReport = true;

    % Library-free: pure C code with no external DNN library dependencies
    % This produces standalone C code that can run on any ARM Cortex-M target
    dlcfgA = coder.DeepLearningConfig('none');
    dlcfgA.LearnablesCompression = 'bfloat16'; % ~50% weight memory reduction
    cfgA.DeepLearningConfig = dlcfgA;

    % Raspberry Pi target
    try
        cfgA.Hardware = coder.hardware('Raspberry Pi');
    catch
        fprintf('    ARM Cortex-A support package not installed. Using GenCodeOnly.\n');
        cfgA.GenCodeOnly = true;
    end

    % Memory and optimization settings
    cfgA.StackUsageMax = 65536; % 64 KB
    cfgA.EnableMemcpy = true;
    cfgA.MemcpyThreshold = 64;
    cfgA.EnableOpenMP = true; % Cortex-A53 is multi-core (up to 4 cores)
    cfgA.SupportNonFinite = false;
    cfgA.InstructionSetExtensions = 'Neon v7'; % SIMD for Cortex-A53
    cfgA.OptimizeReductions = true; % SIMD for sum/product reductions
    cfgA.InstructionSetExtensionsConfig.FMA = 'on'; % Fused multiply-add SIMD instructions
    cfgA.LargeConstantThreshold = 0;
    cfgA.BuildConfiguration = 'Faster Runs';
    cfgA.OptimizeBlockIOStorage = true;

    fprintf('    Target: ARM Cortex-A embedded platform (ARM Cortex-A53)\n');
    fprintf('    Deep Learning Library: none (pure C)\n');
    fprintf('    Stack limit: 64 KB\n');
catch ME
    fprintf(2, '    ERROR: %s\n', ME.message);
end

% --- Configuration B: ARM Compute Library ---
fprintf('\n  [Config B] ARM Compute Library\n');
try
    cfgB = coder.config('lib', 'ecoder', true);
    cfgB.TargetLang = 'C';
    cfgB.GenerateReport = true;

    % ARM Compute Library provides NEON-optimized DNN operations
    dlcfgB = coder.DeepLearningConfig('arm-compute');
    dlcfgB.ArmArchitecture = 'armv7';
    dlcfgB.ArmComputeVersion = '24.02';
    cfgB.DeepLearningConfig = dlcfgB;

    try
        cfgB.Hardware = coder.hardware('Raspberry Pi');
    catch
        cfgB.GenCodeOnly = true;
    end
    cfgB.StackUsageMax = 65536;
    cfgB.EnableOpenMP = true; % Cortex-A53 is multi-core (up to 4 cores)
    cfgB.SupportNonFinite = false;
    cfgB.InstructionSetExtensions = 'Neon v7'; % SIMD for Cortex-A53
    cfgB.OptimizeReductions = true; % SIMD for sum/product reductions
    cfgB.InstructionSetExtensionsConfig.FMA = 'on'; % Fused multiply-add SIMD instructions
    cfgB.LargeConstantThreshold = 0;
    cfgB.BuildConfiguration = 'Faster Runs';

    fprintf('    Target: ARM Cortex-A embedded platform (ARM Cortex-A53)\n');
    fprintf('    Deep Learning Library: ARM Compute Library\n');
    fprintf('    ARM Architecture: armv7\n');

    armConfigAvailable = true;
catch ME
    fprintf('    ARM Compute Library not available: %s\n', ME.message);
    armConfigAvailable = false;
end

%% Step 7: Generate Embedded C Code
fprintf('\n--- Step 7: Embedded C Code Generation ---\n');

inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

% --- Library-free code generation ---
embeddedDirA = fullfile(outputDir, 'embedded_libfree');
if ~isfolder(embeddedDirA)
    mkdir(embeddedDirA);
end

fprintf('\n  Generating library-free C code...\n');
try
    tStart = tic;
    codegen -config cfgA ...
            -d embeddedDirA ...
            predict_shufflenet_onnx ...
            -args {inputArg} ...
            -report
    codegenTimeA = toc(tStart);
    fprintf('  Library-free code generation completed in %.2f seconds.\n', codegenTimeA);
    fprintf('  Output: %s\n', embeddedDirA);
catch ME
    fprintf(2, '  ERROR: Library-free code generation failed.\n');
    fprintf(2, '    %s\n', ME.message);
    fprintf(2, '  Common causes for ONNX-imported models:\n');
    fprintf(2, '    - Custom layers may need manual codegen support\n');
    fprintf(2, '    - Unsupported ONNX operators in the model\n');
    fprintf(2, '    - R2026a auto-generated custom layers should work;\n');
    fprintf(2, '      ensure GenerateCoderFiles=true was used during import\n');
    codegenTimeA = NaN;
end

% --- ARM Compute Library code generation ---
if armConfigAvailable
    embeddedDirB = fullfile(outputDir, 'embedded_arm_compute');
    if ~isfolder(embeddedDirB)
        mkdir(embeddedDirB);
    end

    fprintf('\n  Generating ARM Compute Library C code...\n');
    try
        tStart = tic;
        codegen -config cfgB ...
                -d embeddedDirB ...
                predict_shufflenet_onnx ...
                -args {inputArg} ...
                -report
        codegenTimeB = toc(tStart);
        fprintf('  ARM Compute Library code generation completed in %.2f seconds.\n', codegenTimeB);
        fprintf('  Output: %s\n', embeddedDirB);
    catch ME
        fprintf(2, '  ERROR: ARM Compute Library code generation failed.\n');
        fprintf(2, '    %s\n', ME.message);
        codegenTimeB = NaN;
    end
end

%% Step 8: Report Metrics
fprintf('\n--- Step 8: Code Generation Metrics ---\n');

if isfolder(embeddedDirA)
    reportCodeMetrics(embeddedDirA, 'Library-free');
end

if armConfigAvailable && isfolder(embeddedDirB)
    reportCodeMetrics(embeddedDirB, 'ARM Compute Library');
end

% Final summary
fprintf('\n=============================================================\n');
fprintf(' Summary\n');
fprintf('=============================================================\n');
if exist('importTime', 'var')
    fprintf('  ONNX import time:          %.2f s\n', importTime);
end
if exist('inferenceTime', 'var')
    fprintf('  MATLAB inference time:     %.4f s\n', inferenceTime);
end
if exist('saveTime', 'var')
    fprintf('  Network save time:         %.2f s\n', saveTime);
end
if exist('mexTime', 'var')
    fprintf('  MEX generation time:       %.2f s\n', mexTime);
end
if exist('codegenTimeA', 'var') && ~isnan(codegenTimeA)
    fprintf('  Lib-free codegen time:     %.2f s\n', codegenTimeA);
end
if exist('codegenTimeB', 'var') && ~isnan(codegenTimeB)
    fprintf('  ARM Compute codegen time:  %.2f s\n', codegenTimeB);
end
fprintf('=============================================================\n');
fprintf('ONNX import and code generation workflow complete.\n');
fprintf('\nNext steps:\n');
fprintf('  1. Review code generation reports in codegen_output/\n');
fprintf('  2. Import generated C code into ARM Cortex-ACubeIDE project\n');
fprintf('  3. Place weight arrays in Flash memory sections\n');
fprintf('  4. Map activation buffers to SDRAM\n');
fprintf('  5. Implement preprocessing (camera capture, resize, normalize)\n');
fprintf('  6. Build and deploy to ARM Cortex-A embedded platform\n');
fprintf('=============================================================\n');


%% Local Functions
function reportCodeMetrics(dirPath, label)
%REPORTCODEMETRICS Report file sizes and counts for generated code.
    fprintf('\n  [%s] Generated code in: %s\n', label, dirPath);
    cFiles = dir(fullfile(dirPath, '**', '*.c'));
    hFiles = dir(fullfile(dirPath, '**', '*.h'));

    if isempty(cFiles) && isempty(hFiles)
        fprintf('    No C/H files found.\n');
        return;
    end

    totalCSize = sum([cFiles.bytes]);
    totalHSize = sum([hFiles.bytes]);
    totalSize  = totalCSize + totalHSize;

    fprintf('    C source files:  %d (%.2f KB)\n', numel(cFiles), totalCSize / 1024);
    fprintf('    Header files:    %d (%.2f KB)\n', numel(hFiles), totalHSize / 1024);
    fprintf('    Total code size: %.2f KB (%.2f MB)\n', totalSize / 1024, totalSize / 1e6);

    % Largest files
    allFiles = [cFiles; hFiles];
    [~, sizeIdx] = sort([allFiles.bytes], 'descend');
    fprintf('    Largest files:\n');
    for k = 1:min(5, numel(sizeIdx))
        f = allFiles(sizeIdx(k));
        fprintf('      %8.1f KB  %s\n', f.bytes / 1024, f.name);
    end
end
