%% benchmark_speed.m — Rigorous inference speed benchmark
% 7 independent trials, 100 iterations each, with 10 warmup iterations.
% Reports mean, std, min, max, and median latency per inference.
%
% Methodology matches the LSTM Forecaster project benchmark protocol.
cd(fileparts(mfilename('fullpath')));
projectDir = fileparts(pwd);
addpath(fullfile(projectDir,'option3_import_pytorch'));
addpath(fullfile(projectDir,'option4_onnx_import'));

NUM_TRIALS = 7;
NUM_ITERS  = 100;
NUM_WARMUP = 10;

%% Create a fixed test input (ImageNet-normalized random image)
rng(42);
x = single(randn(224,224,3));

fprintf('================================================================\n');
fprintf(' ShuffleNet V2 — Rigorous Speed Benchmark\n');
fprintf(' %d trials x %d iterations (+ %d warmup)\n', NUM_TRIALS, NUM_ITERS, NUM_WARMUP);
fprintf('================================================================\n\n');

%% Option 3: importNetworkFromPyTorch
fprintf('--- Option 3: importNetworkFromPyTorch (dlnetwork) ---\n');
S = load(fullfile(projectDir,'option3_import_pytorch','shufflenet_dlnetwork.mat'),'net');
net3 = S.net;
dl_in = dlarray(x, 'SSCB');

% Warmup
fprintf('  Warming up (%d iters)...\n', NUM_WARMUP);
for w = 1:NUM_WARMUP
    predict(net3, dl_in);
end

% Timed trials
trial_means3 = zeros(NUM_TRIALS, 1);
all_times3 = zeros(NUM_TRIALS, NUM_ITERS);
for t = 1:NUM_TRIALS
    times = zeros(NUM_ITERS, 1);
    for i = 1:NUM_ITERS
        tic;
        predict(net3, dl_in);
        times(i) = toc * 1000;
    end
    trial_means3(t) = mean(times);
    all_times3(t,:) = times';
    fprintf('  Trial %d/%d: mean=%.2f ms, std=%.2f ms, min=%.2f ms\n', ...
        t, NUM_TRIALS, mean(times), std(times), min(times));
end

flat3 = all_times3(:);
fprintf('\n  RESULT (Option 3):\n');
fprintf('    Mean:   %.2f ms\n', mean(flat3));
fprintf('    Std:    %.2f ms\n', std(flat3));
fprintf('    Median: %.2f ms\n', median(flat3));
fprintf('    Min:    %.2f ms\n', min(flat3));
fprintf('    Max:    %.2f ms\n', max(flat3));
fprintf('    Trial means:'); fprintf(' %.2f', trial_means3); fprintf(' ms\n');

%% Option 4: importNetworkFromONNX
fprintf('\n--- Option 4: importNetworkFromONNX (dlnetwork) ---\n');
S = load(fullfile(projectDir,'option4_onnx_import','shufflenet_onnx_dlnetwork.mat'),'net');
net4 = S.net;

% Warmup
fprintf('  Warming up (%d iters)...\n', NUM_WARMUP);
for w = 1:NUM_WARMUP
    predict(net4, dl_in);
end

% Timed trials
trial_means4 = zeros(NUM_TRIALS, 1);
all_times4 = zeros(NUM_TRIALS, NUM_ITERS);
for t = 1:NUM_TRIALS
    times = zeros(NUM_ITERS, 1);
    for i = 1:NUM_ITERS
        tic;
        predict(net4, dl_in);
        times(i) = toc * 1000;
    end
    trial_means4(t) = mean(times);
    all_times4(t,:) = times';
    fprintf('  Trial %d/%d: mean=%.2f ms, std=%.2f ms, min=%.2f ms\n', ...
        t, NUM_TRIALS, mean(times), std(times), min(times));
end

flat4 = all_times4(:);
fprintf('\n  RESULT (Option 4):\n');
fprintf('    Mean:   %.2f ms\n', mean(flat4));
fprintf('    Std:    %.2f ms\n', std(flat4));
fprintf('    Median: %.2f ms\n', median(flat4));
fprintf('    Min:    %.2f ms\n', min(flat4));
fprintf('    Max:    %.2f ms\n', max(flat4));
fprintf('    Trial means:'); fprintf(' %.2f', trial_means4); fprintf(' ms\n');

%% Summary comparison
fprintf('\n================================================================\n');
fprintf(' SPEED BENCHMARK SUMMARY\n');
fprintf('================================================================\n');
fprintf('%-35s %10s %10s %10s %10s\n', 'Implementation', 'Mean(ms)', 'Std(ms)', 'Min(ms)', 'Speedup');
fprintf('%s\n', repmat('-', 1, 78));
fprintf('%-35s %10.2f %10.2f %10.2f %10.2fx\n', ...
    'Opt 3: importNetworkFromPyTorch', mean(flat3), std(flat3), min(flat3), mean(flat4)/mean(flat3));
fprintf('%-35s %10.2f %10.2f %10.2f %10.2fx\n', ...
    'Opt 4: importNetworkFromONNX', mean(flat4), std(flat4), min(flat4), 1.0);
fprintf('================================================================\n');

%% Save results
save('benchmark_speed_results.mat', ...
    'trial_means3', 'all_times3', 'trial_means4', 'all_times4', ...
    'NUM_TRIALS', 'NUM_ITERS', 'NUM_WARMUP');
fprintf('\nSaved to benchmark_speed_results.mat\n');
