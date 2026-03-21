%% Master Script: Run All MATLAB Code Generation Options
% This script sequentially runs Options 2, 3, and 4 for generating
% embedded C code from ShuffleNet V2 for ARM Cortex-A embedded platform.
%
% Prerequisites:
%   - MATLAB R2026a
%   - Deep Learning Toolbox
%   - MATLAB Coder + Embedded Coder
%   - Deep Learning Toolbox Converter for PyTorch Models
%   - Deep Learning Toolbox Converter for ONNX Model Format
%   - MATLAB Coder Support Package for PyTorch and LiteRT Models
%   - ARM cross-compilation toolchain (optional, for on-target deployment)
%
% Before running:
%   1. Ensure shufflenet_exported.pt2 is in this directory
%   2. For Option 4: run export_to_onnx.py first to create the ONNX file
%
% Usage:
%   >> run_all_codegen

clear; clc; close all;
fprintf('=============================================================\n');
fprintf(' ShuffleNet V2 — Master Code Generation Script\n');
fprintf(' Running Options 2, 3, and 4 sequentially\n');
fprintf('=============================================================\n\n');

projectDir = fileparts(mfilename('fullpath'));
results = struct();
totalStart = tic;

%% Option 2: PyTorch Coder Support Package
fprintf('\n###########################################################\n');
fprintf('# OPTION 2: PyTorch Coder Support Package                 #\n');
fprintf('###########################################################\n\n');

try
    cd(fullfile(projectDir, 'option2_pytorch_coder'));
    opt2Start = tic;
    generate_code_pytorch_coder;
    results.opt2_time = toc(opt2Start);
    results.opt2_status = 'SUCCESS';
    fprintf('\nOption 2 completed in %.1f seconds.\n', results.opt2_time);
catch ME
    results.opt2_time = toc(opt2Start);
    results.opt2_status = 'FAILED';
    results.opt2_error = ME.message;
    fprintf(2, '\nOption 2 FAILED: %s\n', ME.message);
    fprintf(2, 'Continuing with Option 3...\n');
end
cd(projectDir);

%% Option 3: importNetworkFromPyTorch + MATLAB Coder
fprintf('\n###########################################################\n');
fprintf('# OPTION 3: importNetworkFromPyTorch + MATLAB Coder       #\n');
fprintf('###########################################################\n\n');

try
    cd(fullfile(projectDir, 'option3_import_pytorch'));
    opt3Start = tic;
    import_and_generate;
    results.opt3_time = toc(opt3Start);
    results.opt3_status = 'SUCCESS';
    fprintf('\nOption 3 completed in %.1f seconds.\n', results.opt3_time);
catch ME
    results.opt3_time = toc(opt3Start);
    results.opt3_status = 'FAILED';
    results.opt3_error = ME.message;
    fprintf(2, '\nOption 3 FAILED: %s\n', ME.message);
    fprintf(2, 'Continuing with Option 4...\n');
end
cd(projectDir);

%% Option 4: ONNX Import + MATLAB Coder
fprintf('\n###########################################################\n');
fprintf('# OPTION 4: ONNX Import + MATLAB Coder                   #\n');
fprintf('###########################################################\n\n');

% Check if ONNX file exists
onnxFile = fullfile(projectDir, 'option4_onnx_import', 'shufflenet_v2.onnx');
if ~isfile(onnxFile)
    fprintf('ONNX file not found. Attempting to generate it...\n');
    fprintf('Running: python3 option4_onnx_import/export_to_onnx.py\n');
    [status, cmdout] = system('python3 option4_onnx_import/export_to_onnx.py');
    if status ~= 0
        fprintf(2, 'Failed to generate ONNX file:\n%s\n', cmdout);
        fprintf(2, 'Please run export_to_onnx.py manually first.\n');
        results.opt4_status = 'SKIPPED';
    else
        fprintf('%s\n', cmdout);
    end
end

if ~isfield(results, 'opt4_status') || ~strcmp(results.opt4_status, 'SKIPPED')
    try
        cd(fullfile(projectDir, 'option4_onnx_import'));
        opt4Start = tic;
        import_onnx_and_generate;
        results.opt4_time = toc(opt4Start);
        results.opt4_status = 'SUCCESS';
        fprintf('\nOption 4 completed in %.1f seconds.\n', results.opt4_time);
    catch ME
        results.opt4_time = toc(opt4Start);
        results.opt4_status = 'FAILED';
        results.opt4_error = ME.message;
        fprintf(2, '\nOption 4 FAILED: %s\n', ME.message);
    end
end
cd(projectDir);

%% Summary
totalTime = toc(totalStart);
fprintf('\n=============================================================\n');
fprintf(' CODE GENERATION SUMMARY\n');
fprintf('=============================================================\n');
fprintf('  Option 2 (PyTorch Coder):     %s', results.opt2_status);
if isfield(results, 'opt2_time')
    fprintf(' (%.1f s)', results.opt2_time);
end
fprintf('\n');
fprintf('  Option 3 (PT Import + Coder): %s', results.opt3_status);
if isfield(results, 'opt3_time')
    fprintf(' (%.1f s)', results.opt3_time);
end
fprintf('\n');
fprintf('  Option 4 (ONNX + Coder):      %s', results.opt4_status);
if isfield(results, 'opt4_time')
    fprintf(' (%.1f s)', results.opt4_time);
end
fprintf('\n');
fprintf('  Total time: %.1f seconds\n', totalTime);
fprintf('=============================================================\n');

% Save results
save(fullfile(projectDir, 'codegen_results.mat'), 'results');
fprintf('Results saved to codegen_results.mat\n');
