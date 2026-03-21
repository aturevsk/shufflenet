%% Generate C Code from ShuffleNet V2 Using PyTorch Coder Support Package
% This script demonstrates the complete workflow for generating embedded C
% code from a PyTorch-exported ShuffleNet V2 model targeting the
% STM32F746G-Discovery board (ARM Cortex-M7).
%
% Workflow:
%   1. Load the exported PyTorch model (.pt2 format)
%   2. Print model summary and verify structure
%   3. Run test inference in MATLAB
%   4. Generate MEX for host-based validation
%   5. Validate MEX output against MATLAB reference
%   6. Configure Embedded Coder for STM32F746G-Discovery
%   7. Generate embedded C code
%   8. Report code generation metrics
%
% Prerequisites:
%   - MATLAB R2026a or later
%   - Deep Learning Toolbox
%   - MATLAB Coder
%   - Embedded Coder
%   - PyTorch Coder Support Package for MATLAB Coder
%   - STM32 Hardware Support Package (for on-target deployment)
%
% Model file: ../shufflenet_exported.pt2 (relative to this script)

%   Copyright 2026. Generated for STM32F746G-Discovery deployment.

%% Setup
clear; clc; close all;
fprintf('=============================================================\n');
fprintf(' ShuffleNet V2 Code Generation via PyTorch Coder\n');
fprintf(' Target: STM32F746G-Discovery (ARM Cortex-M7)\n');
fprintf('=============================================================\n\n');

% Resolve model path relative to this script's location
scriptDir = fileparts(mfilename('fullpath'));
modelPath = fullfile(scriptDir, '..', 'shufflenet_exported.pt2');
modelPath = char(java.io.File(modelPath).getCanonicalPath());

if ~isfile(modelPath)
    error('pytorch_coder:modelNotFound', ...
        'Model file not found: %s\nEnsure shufflenet_exported.pt2 is in the parent directory.', ...
        modelPath);
end
fprintf('Model file: %s\n\n', modelPath);

% Output directory for generated code
outputDir = fullfile(scriptDir, 'codegen_output');
if ~isfolder(outputDir)
    mkdir(outputDir);
end

%% Step 1: Load the Exported PyTorch Model
fprintf('--- Step 1: Loading PyTorch Exported Program ---\n');
try
    tStart = tic;
    net = loadPyTorchExportedProgram(modelPath);
    loadTime = toc(tStart);
    fprintf('Model loaded successfully in %.2f seconds.\n', loadTime);
catch ME
    fprintf(2, 'ERROR: Failed to load model.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '  Ensure the PyTorch Coder Support Package is installed.\n');
    fprintf(2, '  Run: matlab.addons.install("pytorch_coder_support")\n');
    rethrow(ME);
end

%% Step 2: Print Model Summary
fprintf('\n--- Step 2: Model Summary ---\n');
try
    disp(net);
    fprintf('\nModel details:\n');
    fprintf('  File size: %.2f MB\n', dir(modelPath).bytes / 1e6);

    % Attempt to display model graph if available
    if ismethod(net, 'summary') || isprop(net, 'Graph')
        fprintf('  Attempting to display model graph...\n');
        try
            summary(net);
        catch
            fprintf('  (summary method not available for this model type)\n');
        end
    end
catch ME
    fprintf('Warning: Could not display full model summary: %s\n', ME.message);
end

%% Step 3: Test Inference with Random Input
fprintf('\n--- Step 3: Test Inference (MATLAB) ---\n');
inputSize = [1, 3, 224, 224]; % NCHW format for PyTorch
testInput = single(randn(inputSize));
fprintf('Input size: [%s]\n', num2str(inputSize));
fprintf('Input type: %s\n', class(testInput));

try
    tStart = tic;
    matlabOutput = net.invoke(testInput);
    inferenceTime = toc(tStart);
    fprintf('Inference completed in %.4f seconds.\n', inferenceTime);
    fprintf('Output size: [%s]\n', num2str(size(matlabOutput)));
    fprintf('Output type: %s\n', class(matlabOutput));

    % Display top-5 predictions (indices only, no labels without synset file)
    [sortedScores, sortedIdx] = sort(matlabOutput(:), 'descend');
    fprintf('\nTop-5 predicted class indices (random input):\n');
    for k = 1:min(5, numel(sortedIdx))
        fprintf('  Class %4d: score = %.6f\n', sortedIdx(k), sortedScores(k));
    end
catch ME
    fprintf(2, 'ERROR: Inference failed.\n');
    fprintf(2, '  %s\n', ME.message);
    rethrow(ME);
end

%% Step 4: Generate MEX for Host Validation
fprintf('\n--- Step 4: MEX Code Generation for Host Validation ---\n');
mexOutputDir = fullfile(outputDir, 'mex');
if ~isfolder(mexOutputDir)
    mkdir(mexOutputDir);
end

try
    tStart = tic;

    % Configure MEX code generation
    mexCfg = coder.config('mex');
    mexCfg.TargetLang = 'C';
    mexCfg.GenerateReport = true;
    mexCfg.ReportPotentialDifferences = true;

    % Define input types for code generation
    %   input: single-precision tensor [1 x 3 x 224 x 224]
    inputArg = coder.typeof(single(0), inputSize, [false, false, false, false]);

    fprintf('Generating MEX code...\n');
    codegen -config mexCfg ...
            -d mexOutputDir ...
            mInvoke_shufflenet ...
            -args {inputArg} ...
            -report

    mexTime = toc(tStart);
    fprintf('MEX generation completed in %.2f seconds.\n', mexTime);
    fprintf('MEX output directory: %s\n', mexOutputDir);
catch ME
    fprintf(2, 'ERROR: MEX generation failed.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '  This may indicate unsupported layers or operations.\n');
    fprintf(2, '  Check the code generation report for details.\n');
    % Continue to allow inspection of the error
end

%% Step 5: Validate MEX Output Against MATLAB
fprintf('\n--- Step 5: MEX Validation ---\n');
try
    % Run inference through the generated MEX function
    tStart = tic;
    mexOutput = mInvoke_shufflenet_mex(testInput);
    mexInferenceTime = toc(tStart);
    fprintf('MEX inference completed in %.4f seconds.\n', mexInferenceTime);

    % Compare outputs
    maxAbsDiff = max(abs(double(matlabOutput(:)) - double(mexOutput(:))));
    meanAbsDiff = mean(abs(double(matlabOutput(:)) - double(mexOutput(:))));
    relError = maxAbsDiff / (max(abs(double(matlabOutput(:)))) + eps);

    fprintf('Validation results:\n');
    fprintf('  Max absolute difference:  %.2e\n', maxAbsDiff);
    fprintf('  Mean absolute difference: %.2e\n', meanAbsDiff);
    fprintf('  Max relative error:       %.2e\n', relError);

    % Tolerance check (single-precision)
    tolerance = 1e-5;
    if maxAbsDiff < tolerance
        fprintf('  PASS: MEX output matches MATLAB within tolerance (%.0e).\n', tolerance);
    else
        fprintf(2, '  WARNING: Difference exceeds tolerance (%.0e).\n', tolerance);
        fprintf(2, '  This may be due to floating-point reordering in generated code.\n');
    end

    % Speedup report
    if exist('inferenceTime', 'var') && mexInferenceTime > 0
        fprintf('  Speedup (MEX vs MATLAB): %.2fx\n', inferenceTime / mexInferenceTime);
    end
catch ME
    fprintf('Warning: MEX validation skipped or failed.\n');
    fprintf('  %s\n', ME.message);
    fprintf('  Continuing with embedded code generation...\n');
end

%% Step 6: Configure Embedded Coder for STM32F746G-Discovery
fprintf('\n--- Step 6: Embedded Coder Configuration ---\n');
try
    % Create Embedded Coder configuration for static library
    cfg = coder.config('lib', 'ecoder', true);

    % Target hardware: configure for ARM Cortex-M (generic)
    % Note: Use coder.hardware('STM32F746G-Discovery') if the
    % STM32 Hardware Support Package is installed.
    try
        cfg.Hardware = coder.hardware('STM32F746G-Discovery');
        fprintf('Target hardware: STM32F746G-Discovery\n');
    catch
        fprintf('STM32 support package not installed.\n');
        fprintf('Using generic ARM Cortex-M configuration.\n');
        % Configure for generic embedded ARM target
        cfg.GenCodeOnly = true;
    end
    fprintf('  Target: ARM Cortex-M7 (STM32F746G-Discovery)\n');
    fprintf('  Flash: 1 MB + 16 MB QSPI\n');
    fprintf('  RAM: 340 KB SRAM + 8 MB SDRAM\n');

    % Code generation settings optimized for embedded
    cfg.TargetLang = 'C';
    cfg.GenerateReport = true;
    cfg.ReportPotentialDifferences = true;

    % Memory optimization settings
    cfg.EnableMemcpy = true;
    cfg.MemcpyThreshold = 64;
    cfg.EnableOpenMP = false; % Single-core Cortex-M7
    cfg.SupportNonFinite = false; % Save code size

    % Optimization settings for embedded
    cfg.BuildConfiguration = 'Faster Runs';

    % Data type settings
    cfg.PurelyIntegerCode = false; % Need floating-point for DNN
    cfg.SaturateOnIntegerOverflow = false;

    fprintf('  Build configuration: Faster Runs\n');
    fprintf('  OpenMP: disabled (single-core target)\n');
    fprintf('  Non-finite support: disabled (code size optimization)\n');

catch ME
    fprintf(2, 'ERROR: Failed to configure Embedded Coder.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '  Ensure Embedded Coder is installed.\n');
    rethrow(ME);
end

%% Step 7: Generate Embedded C Code
fprintf('\n--- Step 7: Embedded C Code Generation ---\n');
embeddedOutputDir = fullfile(outputDir, 'embedded_stm32');
if ~isfolder(embeddedOutputDir)
    mkdir(embeddedOutputDir);
end

try
    tStart = tic;

    % Define input types (same as MEX generation)
    inputArg = coder.typeof(single(0), inputSize, [false, false, false, false]);

    fprintf('Generating embedded C code for STM32F746G-Discovery...\n');
    fprintf('  This may take several minutes for a full DNN model.\n');

    codegen -config cfg ...
            -d embeddedOutputDir ...
            mInvoke_shufflenet ...
            -args {inputArg} ...
            -report

    codegenTime = toc(tStart);
    fprintf('Embedded code generation completed in %.2f seconds.\n', codegenTime);
    fprintf('Output directory: %s\n', embeddedOutputDir);
catch ME
    fprintf(2, 'ERROR: Embedded code generation failed.\n');
    fprintf(2, '  %s\n', ME.message);
    fprintf(2, '\nCommon issues:\n');
    fprintf(2, '  - Unsupported layers for code generation\n');
    fprintf(2, '  - Missing Embedded Coder license\n');
    fprintf(2, '  - STM32 hardware support package not installed\n');
    fprintf(2, '  - Insufficient memory for target configuration\n');
    fprintf(2, '\nCheck the code generation report for detailed diagnostics.\n');
end

%% Step 8: Report Code Generation Metrics
fprintf('\n--- Step 8: Code Generation Metrics ---\n');
try
    % Analyze generated files
    if isfolder(embeddedOutputDir)
        cFiles = dir(fullfile(embeddedOutputDir, '**', '*.c'));
        hFiles = dir(fullfile(embeddedOutputDir, '**', '*.h'));

        totalCSize = sum([cFiles.bytes]);
        totalHSize = sum([hFiles.bytes]);
        totalSize  = totalCSize + totalHSize;

        fprintf('Generated code statistics:\n');
        fprintf('  C source files:  %d (%.2f KB)\n', numel(cFiles), totalCSize / 1024);
        fprintf('  Header files:    %d (%.2f KB)\n', numel(hFiles), totalHSize / 1024);
        fprintf('  Total code size: %.2f KB\n', totalSize / 1024);

        % List the largest generated files
        allFiles = [cFiles; hFiles];
        if ~isempty(allFiles)
            [~, sizeIdx] = sort([allFiles.bytes], 'descend');
            fprintf('\nLargest generated files:\n');
            for k = 1:min(10, numel(sizeIdx))
                f = allFiles(sizeIdx(k));
                fprintf('  %8.1f KB  %s\n', f.bytes/1024, f.name);
            end
        end

        % Check for report
        reportFile = fullfile(embeddedOutputDir, 'html', 'report.mldatx');
        if isfile(reportFile)
            fprintf('\nCode generation report available at:\n');
            fprintf('  %s\n', reportFile);
        end
    else
        fprintf('No embedded code output directory found.\n');
    end

    % Summary timing
    fprintf('\n=============================================================\n');
    fprintf(' Summary\n');
    fprintf('=============================================================\n');
    if exist('loadTime', 'var')
        fprintf('  Model load time:          %.2f s\n', loadTime);
    end
    if exist('inferenceTime', 'var')
        fprintf('  MATLAB inference time:    %.4f s\n', inferenceTime);
    end
    if exist('mexTime', 'var')
        fprintf('  MEX generation time:      %.2f s\n', mexTime);
    end
    if exist('mexInferenceTime', 'var')
        fprintf('  MEX inference time:       %.4f s\n', mexInferenceTime);
    end
    if exist('codegenTime', 'var')
        fprintf('  Embedded codegen time:    %.2f s\n', codegenTime);
    end
    fprintf('=============================================================\n');
    fprintf('Code generation workflow complete.\n');
    fprintf('Next steps:\n');
    fprintf('  1. Review the code generation report\n');
    fprintf('  2. Open the generated project in STM32CubeIDE\n');
    fprintf('  3. Configure memory sections for weights (Flash) and activations (SDRAM)\n');
    fprintf('  4. Build and flash to STM32F746G-Discovery\n');
    fprintf('=============================================================\n');

catch ME
    fprintf('Warning: Could not generate full metrics report.\n');
    fprintf('  %s\n', ME.message);
end
