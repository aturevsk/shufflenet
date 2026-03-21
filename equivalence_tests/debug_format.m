%% debug_format.m — Diagnose input format for imported networks
cd(fileparts(mfilename('fullpath')));
projectDir = fileparts(pwd);
addpath(fullfile(projectDir,'option3_import_pytorch'));
addpath(fullfile(projectDir,'option4_onnx_import'));

fid = fopen('test_vectors/input_001.bin','r','l');
x_flat = fread(fid, 150528, 'float32'); fclose(fid);
fid = fopen('test_vectors/output_001.bin','r','l');
ref = fread(fid, 1000, 'float32'); fclose(fid);

S = load(fullfile(projectDir,'option3_import_pytorch','shufflenet_dlnetwork.mat'),'net');
net = S.net;
fprintf('Network class: %s\n', class(net));
fprintf('Input layer: %s\n', class(net.Layers(1)));
disp(net.Layers(1));

% Format A: CHW -> HWC with SSCB
x_chw = reshape(x_flat, [3,224,224]);
x_hwc = permute(x_chw, [2,3,1]);
dl_a = dlarray(single(x_hwc), 'SSCB');
y_a = predict(net, dl_a);
y_a = squeeze(double(extractdata(y_a)));
err_a = max(abs(y_a(:) - ref));
[~,ta] = max(y_a); [~,tr] = max(ref);
fprintf('A (CHW->HWC SSCB): maxErr=%.4e top1=%d ref=%d\n', err_a, ta, tr);

% Format B: raw x_flat reshaped as [224,224,3] directly
x_raw = reshape(x_flat, [224,224,3]);
dl_b = dlarray(single(x_raw), 'SSCB');
y_b = predict(net, dl_b);
y_b = squeeze(double(extractdata(y_b)));
err_b = max(abs(y_b(:) - ref));
[~,tb] = max(y_b);
fprintf('B (raw 224x224x3 SSCB): maxErr=%.4e top1=%d ref=%d\n', err_b, tb, tr);

% Compare ref top-5
[~,ridx] = sort(ref,'descend');
fprintf('Ref top-5: %s\n', mat2str(ridx(1:5)'));
[~,aidx] = sort(y_a(:),'descend');
fprintf('FmtA top-5: %s\n', mat2str(aidx(1:5)'));
[~,bidx] = sort(y_b(:),'descend');
fprintf('FmtB top-5: %s\n', mat2str(bidx(1:5)'));

% Check cosine similarities
cos_a = dot(y_a(:),ref) / (norm(y_a(:))*norm(ref));
cos_b = dot(y_b(:),ref) / (norm(y_b(:))*norm(ref));
fprintf('Cosine A: %.8f\n', cos_a);
fprintf('Cosine B: %.8f\n', cos_b);
fprintf('Done\n');
