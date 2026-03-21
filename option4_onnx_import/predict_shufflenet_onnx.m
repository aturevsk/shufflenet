function out = predict_shufflenet_onnx(in) %#codegen
%PREDICT_SHUFFLENET_ONNX Entry-point for ShuffleNet V2 inference (ONNX import).
%
%   OUT = PREDICT_SHUFFLENET_ONNX(IN) runs inference on a pre-saved
%   dlnetwork imported from ONNX.
%
%   Inputs:
%       in  - Input image [224 x 224 x 3] single (HWC format)
%
%   Outputs:
%       out - Network output class scores [1 x 1000]

%   Copyright 2026. Generated for ARM Cortex-A embedded platform deployment.

persistent net;
if isempty(net)
    net = coder.loadDeepLearningNetwork('shufflenet_onnx_dlnetwork.mat');
end

% Wrap as dlarray for network that expects SSCB format
dlIn = dlarray(in, 'SSCB');
dlOut = predict(net, dlIn);
out = extractdata(dlOut);

end
