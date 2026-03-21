function out = mInvoke_shufflenet(input) %#codegen
%MINVOKE_SHUFFLENET Entry-point function for ShuffleNet V2 inference via PyTorch Coder.
%
%   OUT = MINVOKE_SHUFFLENET(INPUT) runs inference on the exported
%   PyTorch ShuffleNet V2 model using the given INPUT tensor.
%
%   The model path is hardcoded as a compile-time constant, which is
%   required by the PyTorch Coder codegen pipeline.
%
%   Inputs:
%       input   - Single-precision input tensor of size [1 x 3 x 224 x 224]
%                 following PyTorch NCHW format
%
%   Outputs:
%       out     - Network output (class scores), size [1 x 1000] for
%                 ImageNet classification
%
%   Requirements:
%       - MATLAB R2026a or later
%       - Deep Learning Toolbox
%       - MATLAB Coder Support Package for PyTorch and LiteRT Models
%
%   See also: loadPyTorchExportedProgram, generate_code_pytorch_coder

%   Copyright 2026. Generated for ARM Cortex-A embedded platform deployment.

persistent net;
if isempty(net)
    % Model path must be a compile-time constant for code generation.
    % Update this path to match your deployment environment.
    modelPath = '/Users/arkadiyturevskiy/Documents/Claude/PyTorch_Import_2/Shufflenet/shufflenet_exported.pt2';
    net = loadPyTorchExportedProgram(modelPath);
end
out = net.invoke(input);

end
