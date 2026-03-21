%% run_full_100.m — 100-test equivalence with proper format and all metrics
cd(fileparts(mfilename('fullpath')));
projectDir = fileparts(pwd);
addpath(fullfile(projectDir,'option3_import_pytorch'));
addpath(fullfile(projectDir,'option4_onnx_import'));

NUM_TESTS = 100;
fid = fopen('test_vectors/all_outputs_100x1000.bin','r','l');
refOut = fread(fid,[1000,NUM_TESTS],'float32')'; fclose(fid);
fid = fopen('test_vectors/all_inputs_100x3x224x224.bin','r','l');
refIn = fread(fid,[150528,NUM_TESTS],'float32'); fclose(fid);
fprintf('Loaded %d test vectors\n\n', NUM_TESTS);

%% Option 3
fprintf('=== Option 3: importNetworkFromPyTorch ===\n');
S = load(fullfile(projectDir,'option3_import_pytorch','shufflenet_dlnetwork.mat'),'net');
net3 = S.net;
m3 = struct('maxErr',zeros(100,1),'meanErr',zeros(100,1),'cos',zeros(100,1),...
    'top1',zeros(100,1),'top5j',zeros(100,1),'ms',zeros(100,1),'relL2',zeros(100,1));
for i = 1:NUM_TESTS
    x = reshape(refIn(:,i),[3,224,224]);
    x = permute(x,[2,3,1]);
    dl = dlarray(single(x),'SSCB');
    tic; y = predict(net3,dl); m3.ms(i)=toc*1000;
    y = squeeze(double(extractdata(y)));
    ref = refOut(i,:)';
    d = abs(y(:)-ref);
    m3.maxErr(i) = max(d);
    m3.meanErr(i) = mean(d);
    m3.relL2(i) = norm(y(:)-ref)/norm(ref);
    m3.cos(i) = dot(y(:),ref)/(norm(y(:))*norm(ref)+eps);
    [~,r1]=max(ref); [~,t1]=max(y); m3.top1(i)=(r1==t1);
    [~,ri]=sort(ref,'descend'); [~,ti]=sort(y(:),'descend');
    m3.top5j(i) = numel(intersect(ri(1:5),ti(1:5)))/numel(union(ri(1:5),ti(1:5)));
    if mod(i,25)==0
        fprintf('  %3d/100: maxErr=%.2e relL2=%.2e cos=%.6f top1=%d\n',...
            i, m3.maxErr(i), m3.relL2(i), m3.cos(i), m3.top1(i));
    end
end
fprintf('  SUMMARY: worstMax=%.2e meanMax=%.2e avgRelL2=%.2e avgCos=%.6f top1=%.0f%% top5J=%.4f avgMs=%.1f\n',...
    max(m3.maxErr), mean(m3.maxErr), mean(m3.relL2), mean(m3.cos),...
    sum(m3.top1), mean(m3.top5j), mean(m3.ms));

%% Option 4
fprintf('\n=== Option 4: importNetworkFromONNX ===\n');
S = load(fullfile(projectDir,'option4_onnx_import','shufflenet_onnx_dlnetwork.mat'),'net');
net4 = S.net;
m4 = struct('maxErr',zeros(100,1),'meanErr',zeros(100,1),'cos',zeros(100,1),...
    'top1',zeros(100,1),'top5j',zeros(100,1),'ms',zeros(100,1),'relL2',zeros(100,1));
for i = 1:NUM_TESTS
    x = reshape(refIn(:,i),[3,224,224]);
    x = permute(x,[2,3,1]);
    dl = dlarray(single(x),'SSCB');
    tic; y = predict(net4,dl); m4.ms(i)=toc*1000;
    y = squeeze(double(extractdata(y)));
    ref = refOut(i,:)';
    d = abs(y(:)-ref);
    m4.maxErr(i) = max(d);
    m4.meanErr(i) = mean(d);
    m4.relL2(i) = norm(y(:)-ref)/norm(ref);
    m4.cos(i) = dot(y(:),ref)/(norm(y(:))*norm(ref)+eps);
    [~,r1]=max(ref); [~,t1]=max(y); m4.top1(i)=(r1==t1);
    [~,ri]=sort(ref,'descend'); [~,ti]=sort(y(:),'descend');
    m4.top5j(i) = numel(intersect(ri(1:5),ti(1:5)))/numel(union(ri(1:5),ti(1:5)));
    if mod(i,25)==0
        fprintf('  %3d/100: maxErr=%.2e relL2=%.2e cos=%.6f top1=%d\n',...
            i, m4.maxErr(i), m4.relL2(i), m4.cos(i), m4.top1(i));
    end
end
fprintf('  SUMMARY: worstMax=%.2e meanMax=%.2e avgRelL2=%.2e avgCos=%.6f top1=%.0f%% top5J=%.4f avgMs=%.1f\n',...
    max(m4.maxErr), mean(m4.maxErr), mean(m4.relL2), mean(m4.cos),...
    sum(m4.top1), mean(m4.top5j), mean(m4.ms));

%% Option 3 vs Option 4 (inter-agreement)
fprintf('\n=== Opt3 vs Opt4 (inter-agreement) ===\n');
interMax = zeros(100,1); interCos = zeros(100,1);
for i = 1:NUM_TESTS
    x = reshape(refIn(:,i),[3,224,224]);
    x = permute(x,[2,3,1]);
    dl = dlarray(single(x),'SSCB');
    y3 = squeeze(double(extractdata(predict(net3,dl))));
    y4 = squeeze(double(extractdata(predict(net4,dl))));
    interMax(i) = max(abs(y3(:)-y4(:)));
    interCos(i) = dot(y3(:),y4(:))/(norm(y3(:))*norm(y4(:))+eps);
end
fprintf('  Max inter-error: %.2e\n', max(interMax));
fprintf('  Mean inter-error: %.2e\n', mean(interMax));
fprintf('  Avg inter-cosine: %.10f\n', mean(interCos));

%% Save
save('full_100_results.mat','m3','m4','interMax','interCos');
fprintf('\nSaved to full_100_results.mat\n');
