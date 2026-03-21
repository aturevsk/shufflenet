%% run_codegen_only.m — Just do code generation for Option 5
cd(fileparts(mfilename('fullpath')));
addpath(pwd);  % ChannelShuffleLayer, ChannelSplitLayer
fprintf('--- Attempting Embedded C codegen for Option 5 ---\n');

inputType = coder.typeof(single(0), [224 224 3 1]);

cfg = coder.config('lib', 'ecoder', true);
cfg.TargetLang = 'C';
dlcfg = coder.DeepLearningConfig('none');
dlcfg.LearnablesCompression = 'bfloat16'; % ~50% weight memory reduction
cfg.DeepLearningConfig = dlcfg;
cfg.GenerateReport = true;
cfg.GenCodeOnly = true;
cfg.EnableOpenMP = true; % Cortex-A53 is multi-core (up to 4 cores)
cfg.EnableMemcpy = true;
cfg.MemcpyThreshold = 64;
cfg.SupportNonFinite = false;
cfg.InstructionSetExtensions = 'Neon v7'; % SIMD for Cortex-A53
cfg.OptimizeReductions = true; % SIMD for sum/product reductions
cfg.InstructionSetExtensionsConfig.FMA = 'on'; % Fused multiply-add SIMD instructions
cfg.LargeConstantThreshold = 0;
cfg.BuildConfiguration = 'Faster Runs';

try
    tStart = tic;
    codegen -config cfg ...
        -d embeddedDir ...
        predict_shufflenet_v5 ...
        -args {inputType} ...
        -report
    codegenTime = toc(tStart);
    fprintf('SUCCESS in %.1f seconds!\n', codegenTime);

    cFiles = dir(fullfile('embeddedDir', '**', '*.c'));
    hFiles = dir(fullfile('embeddedDir', '**', '*.h'));
    totalSize = sum([cFiles.bytes]) + sum([hFiles.bytes]);
    fprintf('Generated %d .c files, %d .h files (%.1f KB)\n', ...
        numel(cFiles), numel(hFiles), totalSize/1024);

    % List C files
    fprintf('\nGenerated C files:\n');
    for i = 1:numel(cFiles)
        fprintf('  %s (%d lines)\n', cFiles(i).name, ...
            numel(regexp(fileread(fullfile(cFiles(i).folder, cFiles(i).name)), '\n')));
    end
catch ME
    codegenTime = toc(tStart);
    fprintf('FAILED (%.1f s): %s\n', codegenTime, ME.message);
end
