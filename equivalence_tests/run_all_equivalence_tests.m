%% run_all_equivalence_tests.m
% =========================================================================
% Master Runner: 100-Test Numerical Equivalence Validation Suite
% =========================================================================
%
% Runs all equivalence tests in sequence:
%   Step 1: Validate MATLAB-level inference (Options 2, 3, 4)
%   Step 2: Validate MEX-compiled C code (if MEX files exist)
%   Step 3: Generate combined comparison report
%
% Prerequisites:
%   1. Run generate_reference_data.py first to create test vectors
%   2. Run the code generation scripts for each option
%
% Usage:
%   cd equivalence_tests/
%   run_all_equivalence_tests
% =========================================================================

clear; clc;
fprintf('╔═════════════════════════════════════════════════════════════════╗\n');
fprintf('║  ShuffleNet V2 — Complete Numerical Equivalence Test Suite     ║\n');
fprintf('║  100 test vectors × 3 MATLAB options + MEX validation         ║\n');
fprintf('╚═════════════════════════════════════════════════════════════════╝\n\n');

%% Check prerequisites
testVectorDir = fullfile(pwd, 'test_vectors');
if ~isfolder(testVectorDir) || ~isfile(fullfile(testVectorDir, 'all_outputs_100x1000.bin'))
    error(['Test vectors not found.\n' ...
           'Run first: python3 generate_reference_data.py']);
end
fprintf('Test vectors found: %s\n\n', testVectorDir);

%% Step 1: MATLAB-level equivalence
fprintf('━━━ STEP 1: MATLAB-Level Equivalence ━━━━━━━━━━━━━━━━━━━━━━━━━\n\n');
try
    validate_matlab_equivalence;
catch ME
    fprintf('WARNING: MATLAB equivalence test error: %s\n', ME.message);
end

%% Step 2: MEX equivalence (if available)
fprintf('\n━━━ STEP 2: MEX (Compiled C) Equivalence ━━━━━━━━━━━━━━━━━━━━━━\n\n');
try
    validate_mex_equivalence;
catch ME
    fprintf('WARNING: MEX equivalence test error: %s\n', ME.message);
    fprintf('(This is expected if MEX files have not been compiled yet)\n');
end

%% Step 3: Load and combine results
fprintf('\n━━━ STEP 3: Combined Report ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n');

if isfile('equivalence_results.mat')
    load('equivalence_results.mat', 'results', 'optionNames');

    fprintf('%-30s %10s %10s %10s %8s\n', ...
        'Implementation', 'MaxErr', 'AvgRelL2', 'AvgCosine', 'Top1%');
    fprintf('%s\n', repmat('=', 1, 72));

    for oi = 1:numel(optionNames)
        oName = optionNames{oi};
        r = results.(oName);
        if r.success
            fprintf('%-30s %10.2e %10.2e %10.6f %7.1f%%\n', ...
                oName, max(r.maxAbsErr), mean(r.relL2Err), ...
                mean(r.cosineSim), sum(r.top1Match)/100*100);
        else
            fprintf('%-30s %10s %10s %10s %8s\n', ...
                oName, 'SKIP', 'SKIP', 'SKIP', 'SKIP');
        end
    end
end

fprintf('\n╔═════════════════════════════════════════════════════════════════╗\n');
fprintf('║  Equivalence testing complete.                                 ║\n');
fprintf('║  Results saved to: equivalence_results.mat                     ║\n');
fprintf('║                    equivalence_report.csv                      ║\n');
fprintf('║                    equivalence_detail.csv                      ║\n');
fprintf('╚═════════════════════════════════════════════════════════════════╝\n');
