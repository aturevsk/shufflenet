%% Import ShuffleNet V2 from PyTorch and Generate Embedded C Code
% This script imports a ShuffleNet V2 model from PyTorch format using
% importNetworkFromPyTorch, validates it, and generates embedded C code
% for the STM32F746G-Discovery board (ARM Cortex-M7).
%
% Workflow:
%   1. Import model using importNetworkFromPyTorch
%   2. Display and analyze network architecture
%   3. Check code generation readiness
%   4. Test inference with a sample image
%   5. Save dlnetwork to .mat file
%   6. Generate MEX for host validation
%   7. Configure embedded deployment (library-free + ARM Compute Library)
%   8. Generate embedded C code
%   9. Report metrics
%
% Prerequisites:
%   - MATLAB R2026a or later
%   - Deep Learning Toolbox
%   - Deep Learning Toolbox Converter for PyTorch Models
%   - MATLAB Coder
%   - Embedded Coder
%
% Model file: ../shufflenet_exported.pt2 (relative to this script)

%   Copyright 2026. Generated for STM32F746G-Discovery deployment.

%% Setup
clear; clc; close all;
fprintf('=============================================================\n');
fprintf(' ShuffleNet V2 Import from PyTorch & Embedded Code Generation\n');
fprintf(' Target: STM32F746G-Discovery (ARM Cortex-M7)\n');
fprintf('=============================================================\n\n');

% Resolve model path
scriptDir = fileparts(mfilename('fullpath'));
modelPath = fullfile(scriptDir, '..', 'shufflenet_exported.pt2');
modelPath = char(java.io.File(modelPath).getCanonicalPath());

if ~isfile(modelPath)
    error('import_pytorch:modelNotFound', ...
        'Model file not found: %s', modelPath);
end
fprintf('Model file: %s\n\n', modelPath);

% Output directories
outputDir = fullfile(scriptDir, 'codegen_output');
if ~isfolder(outputDir)
    mkdir(outputDir);
end

% Mat file for the saved network
matFilePath = fullfile(scriptDir, 'shufflenet_dlnetwork.mat');

%% Step 1: Import Model Using importNetworkFromPyTorch
fprintf('--- Step 1: Importing Model from PyTorch ---\n');
try
    tStart = tic;

    % Import with explicit input size specification
    % PyTorchInputSizes expects NCHW format: [Batch x Channels x Height x Width]
    % NaN for batch dimension allows variable batch size
    net = importNetworkFromPyTorch(modelPath, ...
        'PyTorchInputSizes', [NaN 3 224 224]);

    importTime = toc(tStart);
    fprintf('Model imported successfully in %.2f seconds.\n', importTime);
    fprintf('Network class: %s\n', class(net));

    % Display basic network info
    if isa(net, 'dlnetwork')
        fprintf('Number of layers: %d\n', numel(net.Layers));
        fprintf('Number of connections: %d\n', height(net.Connections));
        fprintf('Number of learnables: %d\n', numel(net.Learnables));

        % Count total parameters
        totalParams = 0;
        for i = 1:numel(net.Learnables.Value)
            totalParams = totalParams + numel(net.Learnables.Value{i});
        end
        fprintf('Total parameters: %s (%.2f M)\n', ...
            num2str(totalParams), totalParams / 1e6);
    end
catch ME
    fprintf(2, 'ERROR: Failed to import model from PyTorch.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '\nPossible solutions:\n');
    fprintf(2, '  - Install: Deep Learning Toolbox Converter for PyTorch Models\n');
    fprintf(2, '  - Ensure model was exported with torch.export (not torch.jit)\n');
    fprintf(2, '  - Try exporting to ONNX first (see option4_onnx_import)\n');
    rethrow(ME);
end

%% Step 2: Display Network Architecture
fprintf('\n--- Step 2: Network Architecture ---\n');
try
    tStart = tic;

    % Display layer graph
    fprintf('Network layers:\n');
    disp(net.Layers);

    % Analyze network architecture with detailed visualization
    fprintf('\nOpening network analyzer...\n');
    analyzeNetwork(net);

    analysisTime = toc(tStart);
    fprintf('Architecture analysis completed in %.2f seconds.\n', analysisTime);
catch ME
    fprintf('Warning: Could not display full architecture: %s\n', ME.message);
end

%% Step 3: Check Code Generation Readiness
fprintf('\n--- Step 3: Code Generation Readiness Check ---\n');
try
    tStart = tic;

    % analyzeNetworkForCodegen checks for unsupported layers and provides
    % recommendations for making the network codegen-compatible
    result = analyzeNetworkForCodegen(net);

    codegenCheckTime = toc(tStart);
    fprintf('Code generation readiness check completed in %.2f seconds.\n', codegenCheckTime);

    % Display results
    if isprop(result, 'IsSupported') || isfield(result, 'IsSupported')
        if result.IsSupported
            fprintf('  Result: PASS - Network is ready for code generation.\n');
        else
            fprintf(2, '  Result: FAIL - Network has unsupported layers.\n');
            fprintf(2, '  Review the analyzeNetworkForCodegen report for details.\n');
        end
    else
        fprintf('  Check the generated report for detailed results.\n');
    end
catch ME
    fprintf('Warning: Code generation readiness check failed: %s\n', ME.message);
    fprintf('  Continuing anyway; codegen may still work.\n');
end

%% Step 4: Test Inference with a Sample Image
fprintf('\n--- Step 4: Test Inference ---\n');
try
    tStart = tic;

    % Create a sample input image
    % MATLAB dlnetwork expects SSCB format (Height x Width x Channels x Batch)
    % after import from PyTorch
    inputSize = [224, 224, 3]; % HWC for MATLAB
    sampleInput = single(randn(inputSize(1), inputSize(2), inputSize(3), 1));
    sampleDlarray = dlarray(sampleInput, 'SSCB');

    fprintf('Input size: [%s] (SSCB format)\n', num2str(size(sampleDlarray)));
    fprintf('Input type: %s (%s)\n', class(sampleDlarray), dims(sampleDlarray));

    % Run inference
    dlOutput = predict(net, sampleDlarray);
    inferenceTime = toc(tStart);

    % Extract and display results
    outputData = extractdata(dlOutput);
    fprintf('Inference completed in %.4f seconds.\n', inferenceTime);
    fprintf('Output size: [%s]\n', num2str(size(outputData)));

    % Apply softmax to get probabilities
    probabilities = exp(outputData) ./ sum(exp(outputData(:)));
    [sortedProbs, sortedIdx] = sort(probabilities(:), 'descend');

    fprintf('\nTop-5 predicted class indices (random input):\n');
    for k = 1:min(5, numel(sortedIdx))
        fprintf('  Class %4d: probability = %.6f\n', sortedIdx(k), sortedProbs(k));
    end

    % Try with a real image if available
    try
        testImagePath = fullfile(scriptDir, '..', 'test_image.jpg');
        if isfile(testImagePath)
            fprintf('\nTesting with real image: %s\n', testImagePath);
            img = imread(testImagePath);
            img = imresize(img, [224 224]);
            img = single(img) / 255.0;
            % ImageNet normalization
            meanVals = reshape(single([0.485, 0.456, 0.406]), 1, 1, 3);
            stdVals  = reshape(single([0.229, 0.224, 0.225]), 1, 1, 3);
            img = (img - meanVals) ./ stdVals;
            imgDl = dlarray(img, 'SSCB');
            realOutput = predict(net, imgDl);
            realProbs = exp(extractdata(realOutput));
            realProbs = realProbs ./ sum(realProbs(:));
            [topProb, topIdx] = max(realProbs(:));
            fprintf('  Top prediction: class %d (prob = %.4f)\n', topIdx, topProb);
        end
    catch
        % No test image available; skip
    end
catch ME
    fprintf(2, 'ERROR: Inference test failed.\n');
    fprintf(2, '  %s\n', ME.message);
    rethrow(ME);
end

%% Step 5: Expand Layers and Save dlnetwork
fprintf('\n--- Step 5: Expanding Layers and Saving dlnetwork ---\n');
try
    % Expand nested network layers for code generation compatibility.
    % MATLAB Coder requires flat (non-nested) layer structures.
    fprintf('Expanding nested network layers...\n');
    net = expandLayers(net);
    fprintf('Network expanded. New layer count: %d\n', numel(net.Layers));

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

%% Step 6: Generate MEX Code for Validation
fprintf('\n--- Step 6: MEX Code Generation ---\n');
mexOutputDir = fullfile(outputDir, 'mex');
if ~isfolder(mexOutputDir)
    mkdir(mexOutputDir);
end

try
    tStart = tic;

    % Configure MEX
    mexCfg = coder.config('mex');
    mexCfg.TargetLang = 'C';
    mexCfg.GenerateReport = true;

    % Deep learning configuration for MEX
    % Use library-free for code generation (MKL-DNN not supported on macOS ARM)
    dlcfg = coder.DeepLearningConfig('none');
    mexCfg.DeepLearningConfig = dlcfg;

    % Input type: single [224 x 224 x 3 x 1] in SSCB format
    inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

    fprintf('Generating MEX code...\n');
    codegen -config mexCfg ...
            -d mexOutputDir ...
            predict_shufflenet ...
            -args {inputArg} ...
            -report

    mexTime = toc(tStart);
    fprintf('MEX generation completed in %.2f seconds.\n', mexTime);

    % Validate MEX
    fprintf('\nValidating MEX output...\n');
    mexResult = predict_shufflenet_mex(sampleInput);
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

%% Step 7: Configure Embedded Deployment
fprintf('\n--- Step 7: Embedded Deployment Configuration ---\n');

% --- Configuration A: Library-free C code ---
fprintf('\n  [Config A] Library-free C code (no external dependencies)\n');
try
    cfgA = coder.config('lib', 'ecoder', true);
    cfgA.TargetLang = 'C';
    cfgA.GenerateReport = true;

    % Library-free deep learning: pure C implementation with no external
    % library dependencies. Best for constrained embedded targets.
    dlcfgA = coder.DeepLearningConfig('none');
    cfgA.DeepLearningConfig = dlcfgA;

    % STM32 target configuration
    % Use coder.hardware('STM32F746G-Discovery') if STM32 support package
    % is installed. Otherwise, generate code only (no build).
    try
        cfgA.Hardware = coder.hardware('STM32F746G-Discovery');
    catch
        fprintf('    STM32 support package not installed. Using GenCodeOnly.\n');
        cfgA.GenCodeOnly = true;
    end

    % Embedded optimization settings
    cfgA.StackUsageMax = 65536; % 64 KB
    cfgA.EnableMemcpy = true;
    cfgA.MemcpyThreshold = 64;
    cfgA.EnableOpenMP = false;
    cfgA.SupportNonFinite = false;
    cfgA.BuildConfiguration = 'Faster Runs';
    % cfgA.OptimizeBlockIOStorage = true; % Not available in EmbeddedCodeConfig

    fprintf('    Target: STM32F746G-Discovery (ARM Cortex-M7)\n');
    fprintf('    Deep Learning Library: none (pure C)\n');
    fprintf('    Stack limit: 64 KB\n');
    fprintf('    Constants: kept in source files\n');
catch ME
    fprintf(2, '    ERROR configuring library-free: %s\n', ME.message);
end

% --- Configuration B: ARM Compute Library ---
fprintf('\n  [Config B] ARM Compute Library\n');
try
    cfgB = coder.config('lib', 'ecoder', true);
    cfgB.TargetLang = 'C';
    cfgB.GenerateReport = true;

    % ARM Compute Library for optimized Cortex-M/A inference
    dlcfgB = coder.DeepLearningConfig('arm-compute');
    dlcfgB.ArmArchitecture = 'armv7';
    dlcfgB.ArmComputeVersion = '24.02';
    cfgB.DeepLearningConfig = dlcfgB;

    % STM32 target
    try
        cfgB.Hardware = coder.hardware('STM32F746G-Discovery');
    catch
        cfgB.GenCodeOnly = true;
    end
    cfgB.StackUsageMax = 65536;
    cfgB.EnableOpenMP = false;
    cfgB.SupportNonFinite = false;
    cfgB.BuildConfiguration = 'Faster Runs';

    fprintf('    Target: STM32F746G-Discovery (ARM Cortex-M7)\n');
    fprintf('    Deep Learning Library: ARM Compute Library\n');
    fprintf('    ARM Architecture: armv7\n');

    armConfigAvailable = true;
catch ME
    fprintf('    ARM Compute Library config not available: %s\n', ME.message);
    fprintf('    Falling back to library-free only.\n');
    armConfigAvailable = false;
end

%% Step 8: Generate Embedded C Code
fprintf('\n--- Step 8: Embedded C Code Generation ---\n');

% Input specification for embedded codegen
inputArg = coder.typeof(single(0), [224, 224, 3, 1], [false, false, false, false]);

% --- Generate with library-free configuration ---
embeddedDirA = fullfile(outputDir, 'embedded_libfree');
if ~isfolder(embeddedDirA)
    mkdir(embeddedDirA);
end

fprintf('\n  Generating library-free C code...\n');
try
    tStart = tic;
    codegen -config cfgA ...
            -d embeddedDirA ...
            predict_shufflenet ...
            -args {inputArg} ...
            -report
    codegenTimeA = toc(tStart);
    fprintf('  Library-free code generation completed in %.2f seconds.\n', codegenTimeA);
    fprintf('  Output: %s\n', embeddedDirA);
catch ME
    fprintf(2, '  ERROR: Library-free code generation failed.\n');
    fprintf(2, '    %s\n', ME.message);
    codegenTimeA = NaN;
end

% --- Generate with ARM Compute Library configuration ---
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
                predict_shufflenet ...
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

%% Step 9: Report Metrics
fprintf('\n--- Step 9: Code Generation Metrics ---\n');

% Helper function to report directory metrics
reportDirMetrics = @(dirPath, label) reportCodeMetrics(dirPath, label);

if isfolder(embeddedDirA)
    reportCodeMetrics(embeddedDirA, 'Library-free');
end

if armConfigAvailable && isfolder(embeddedDirB)
    reportCodeMetrics(embeddedDirB, 'ARM Compute Library');
end

% Summary
fprintf('\n=============================================================\n');
fprintf(' Summary\n');
fprintf('=============================================================\n');
if exist('importTime', 'var')
    fprintf('  Model import time:         %.2f s\n', importTime);
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
fprintf('Code generation workflow complete.\n');
fprintf('Next steps:\n');
fprintf('  1. Review the code generation reports in codegen_output/\n');
fprintf('  2. Import generated code into STM32CubeIDE project\n');
fprintf('  3. Map weights to Flash, activations to SDRAM\n');
fprintf('  4. Implement camera input and display output on LCD\n');
fprintf('  5. Build, flash, and test on STM32F746G-Discovery\n');
fprintf('=============================================================\n');


%% Local Functions
function reportCodeMetrics(dirPath, label)
%REPORTCODEMETRICS Report file sizes and counts for generated code directory.
    fprintf('\n  [%s] Generated code in: %s\n', label, dirPath);
    cFiles = dir(fullfile(dirPath, '**', '*.c'));
    hFiles = dir(fullfile(dirPath, '**', '*.h'));

    if isempty(cFiles) && isempty(hFiles)
        fprintf('    No C/H files found.\n');
        return;
    end

    totalCSize = sum([cFiles.bytes]);
    totalHSize = sum([hFiles.bytes]);

    fprintf('    C source files:  %d (%.2f KB)\n', numel(cFiles), totalCSize / 1024);
    fprintf('    Header files:    %d (%.2f KB)\n', numel(hFiles), totalHSize / 1024);
    fprintf('    Total code size: %.2f KB (%.2f MB)\n', ...
        (totalCSize + totalHSize) / 1024, (totalCSize + totalHSize) / 1e6);

    % List largest files
    allFiles = [cFiles; hFiles];
    [~, sizeIdx] = sort([allFiles.bytes], 'descend');
    fprintf('    Largest files:\n');
    for k = 1:min(5, numel(sizeIdx))
        f = allFiles(sizeIdx(k));
        fprintf('      %8.1f KB  %s\n', f.bytes / 1024, f.name);
    end
end
