function out = predict_shufflenet_v5(in) %#codegen
%predict_shufflenet_v5  Codegen entry point for Option 5 rebuilt ShuffleNet V2.
%
%   out = predict_shufflenet_v5(in)
%
%   Input:  in  - single-precision [224 x 224 x 3 x N] image (SSCB)
%   Output: out - single-precision [1000 x N] class scores
%
%   The persistent network is loaded once from the saved .mat file.
%   All custom layers (ChannelShuffleLayer, ChannelSplitLayer) are
%   codegen-compatible, inheriting from nnet.layer.Layer directly.

persistent net;
if isempty(net)
    net = coder.loadDeepLearningNetwork('shufflenet_v5_dlnetwork.mat');
end

% Wrap input as dlarray with SSCB format for the network
dlIn = dlarray(in, 'SSCB');
dlOut = predict(net, dlIn);
out = extractdata(dlOut);
end
