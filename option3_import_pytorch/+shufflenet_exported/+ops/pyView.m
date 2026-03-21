function [Y, YRank] = pyView(X, shape, ~)
%#codegen
%PYVIEW Reshapes the input tensor into the dimensions given by shape.
% The final input, XRank, is not used.
%   Copyright 2025 The MathWorks, Inc.
import shufflenet_exported.ops.*
% Extract the shape
if isdlarray(shape)
    shape = extractdata(shape);
elseif iscell(shape)
    shape = [shape{:}];
end
% Set the rank of Y to the number of dimensions in the original
% shape vector
YRank = numel(shape);
% Prepend the shape vector with ones so that it always contains at least
% two elements
shape = [ones(1, 2-numel(shape)) shape];
newShape = num2cell(shape);
if any(shape == -1)
    % Replace -1 with []
    i = shape == -1;
    newShape{i} = [];
end
revPythonShape = fliplr(newShape);
Y = reshape(X, revPythonShape{:});
end
