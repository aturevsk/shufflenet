function out = predict_shufflenet(in) %#codegen
%PREDICT_SHUFFLENET Entry-point function for ShuffleNet V2 inference.
%
%   OUT = PREDICT_SHUFFLENET(IN) runs inference on a pre-saved dlnetwork.
%
%   Inputs:
%       in  - Input image as single array [224 x 224 x 3] (HWC, MATLAB convention)
%
%   Outputs:
%       out - Network output (class scores), size [1 x 1000]
%
%   See also: import_and_generate, coder.loadDeepLearningNetwork, dlarray

%   Copyright 2026. Generated for ARM Cortex-A embedded platform deployment.

persistent net;
if isempty(net)
    net = coder.loadDeepLearningNetwork('shufflenet_dlnetwork.mat');
end

% Wrap input as dlarray with SSCB format for the network
dlIn = dlarray(in, 'SSCB');
dlOut = predict(net, dlIn);

% Extract numeric output
out = extractdata(dlOut);

end
