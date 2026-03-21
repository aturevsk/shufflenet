%% quick_test.m — Run 100-test equivalence for Options 3 and 4
cd(fileparts(mfilename('fullpath')));
projectDir = fileparts(pwd);
addpath(fullfile(projectDir, 'option3_import_pytorch'));
addpath(fullfile(projectDir, 'option4_onnx_import'));

NUM_TESTS = 100;
OUTPUT_SIZE = 1000;
INPUT_SHAPE = [3, 224, 224];

fid = fopen('test_vectors/all_outputs_100x1000.bin','r','l');
refOut = fread(fid,[OUTPUT_SIZE, NUM_TESTS],'float32')';
fclose(fid);
fid = fopen('test_vectors/all_inputs_100x3x224x224.bin','r','l');
refIn = fread(fid,[prod(INPUT_SHAPE), NUM_TESTS],'float32');
fclose(fid);
fprintf('Loaded %d reference test vectors\n', NUM_TESTS);

%% Option 3
fprintf('\n=== Option 3: importNetworkFromPyTorch ===\n');
try
    S = load(fullfile(projectDir,'option3_import_pytorch','shufflenet_dlnetwork.mat'),'net');
    net3 = S.net;
    maxErrs3 = zeros(NUM_TESTS,1);
    cosines3 = zeros(NUM_TESTS,1);
    top1s3 = zeros(NUM_TESTS,1);
    times3 = zeros(NUM_TESTS,1);
    for i = 1:NUM_TESTS
        x = reshape(refIn(:,i), INPUT_SHAPE);
        x = permute(x,[2,3,1]);
        dl = dlarray(single(x),'SSCB');
        tic;
        y = predict(net3,dl);
        times3(i) = toc*1000;
        y = squeeze(double(extractdata(y)));
        ref = refOut(i,:)';
        maxErrs3(i) = max(abs(y(:)-ref));
        cosines3(i) = dot(y(:),ref) / (norm(y(:))*norm(ref)+eps);
        [~,r1] = max(ref); [~,t1] = max(y);
        top1s3(i) = (r1==t1);
        if mod(i,25)==0
            fprintf('  %3d/100: maxErr=%.2e cos=%.6f top1=%d\n', i, maxErrs3(i), cosines3(i), top1s3(i));
        end
    end
    fprintf('  SUMMARY: worst=%.2e mean=%.2e cos=%.6f top1=%.0f%% avgMs=%.1f\n', ...
        max(maxErrs3), mean(maxErrs3), mean(cosines3), sum(top1s3), mean(times3));
catch ME
    fprintf('  FAILED: %s\n', ME.message);
    maxErrs3 = nan; cosines3 = nan; top1s3 = nan; times3 = nan;
end

%% Option 4
fprintf('\n=== Option 4: importNetworkFromONNX ===\n');
try
    S = load(fullfile(projectDir,'option4_onnx_import','shufflenet_onnx_dlnetwork.mat'),'net');
    net4 = S.net;
    maxErrs4 = zeros(NUM_TESTS,1);
    cosines4 = zeros(NUM_TESTS,1);
    top1s4 = zeros(NUM_TESTS,1);
    times4 = zeros(NUM_TESTS,1);
    for i = 1:NUM_TESTS
        x = reshape(refIn(:,i), INPUT_SHAPE);
        x = permute(x,[2,3,1]);
        dl = dlarray(single(x),'SSCB');
        tic;
        y = predict(net4,dl);
        times4(i) = toc*1000;
        y = squeeze(double(extractdata(y)));
        ref = refOut(i,:)';
        maxErrs4(i) = max(abs(y(:)-ref));
        cosines4(i) = dot(y(:),ref) / (norm(y(:))*norm(ref)+eps);
        [~,r1] = max(ref); [~,t1] = max(y);
        top1s4(i) = (r1==t1);
        if mod(i,25)==0
            fprintf('  %3d/100: maxErr=%.2e cos=%.6f top1=%d\n', i, maxErrs4(i), cosines4(i), top1s4(i));
        end
    end
    fprintf('  SUMMARY: worst=%.2e mean=%.2e cos=%.6f top1=%.0f%% avgMs=%.1f\n', ...
        max(maxErrs4), mean(maxErrs4), mean(cosines4), sum(top1s4), mean(times4));
catch ME
    fprintf('  FAILED: %s\n', ME.message);
    maxErrs4 = nan; cosines4 = nan; top1s4 = nan; times4 = nan;
end

%% Option 2 (PyTorch Coder)
fprintf('\n=== Option 2: PyTorch Coder Support Package ===\n');
try
    ptModel = fullfile(projectDir, 'shufflenet_exported.pt2');
    net2 = loadPyTorchExportedProgram(ptModel);
    maxErrs2 = zeros(NUM_TESTS,1);
    cosines2 = zeros(NUM_TESTS,1);
    top1s2 = zeros(NUM_TESTS,1);
    times2 = zeros(NUM_TESTS,1);
    for i = 1:NUM_TESTS
        x = reshape(refIn(:,i), [1 INPUT_SHAPE]);
        tic;
        y = net2.invoke(x);
        times2(i) = toc*1000;
        y = squeeze(double(y));
        ref = refOut(i,:)';
        maxErrs2(i) = max(abs(y(:)-ref));
        cosines2(i) = dot(y(:),ref) / (norm(y(:))*norm(ref)+eps);
        [~,r1] = max(ref); [~,t1] = max(y);
        top1s2(i) = (r1==t1);
        if mod(i,25)==0
            fprintf('  %3d/100: maxErr=%.2e cos=%.6f top1=%d\n', i, maxErrs2(i), cosines2(i), top1s2(i));
        end
    end
    fprintf('  SUMMARY: worst=%.2e mean=%.2e cos=%.6f top1=%.0f%% avgMs=%.1f\n', ...
        max(maxErrs2), mean(maxErrs2), mean(cosines2), sum(top1s2), mean(times2));
catch ME
    fprintf('  FAILED: %s\n', ME.message);
    maxErrs2 = nan; cosines2 = nan; top1s2 = nan; times2 = nan;
end

%% Save results
save('quick_test_results.mat', 'maxErrs2','cosines2','top1s2','times2', ...
    'maxErrs3','cosines3','top1s3','times3', ...
    'maxErrs4','cosines4','top1s4','times4');
fprintf('\nResults saved to quick_test_results.mat\n');
fprintf('Done!\n');
