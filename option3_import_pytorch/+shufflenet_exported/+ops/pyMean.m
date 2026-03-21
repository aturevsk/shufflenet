function [Yval, Yrank] = pyMean(Xval, dim, keepdim, Xrank)
%#codegen
%PYMEAN Calculates the mean of the input tensor along dimension dim.
%   Copyright 2025 The MathWorks, Inc.
import shufflenet_exported.ops.*
if iscell(dim)
    dim = [dim{:}];
end
% If dim is empty, get all dims
if isempty(dim)
    dim = 0:Xrank-1; % 0-indexed, as in PyTorch
elseif (dim < 0)
    dim = Xrank + dim;
end
mlDims = Xrank - dim;
% Compute the mean
Yval = mean(Xval, mlDims);
% If keepdim is false (the default), squeeze out dims
if ~keepdim
    % Get size vector (including singletons up to rank)
    sz = ones(1, Xrank);
    ySz = size(Yval);
    sz(1:numel(ySz)) = ySz;
    % Remove dims that were averaged across
    for i=1:numel(mlDims)
        sz(mlDims(i)) = [];
    end
    % If sz has less than 2 elements, append trailing singletons
    if numel(sz) < 2
        sz = [sz ones(1, 2-numel(sz))];
    end
    % Reshape to remove dims
    Yrank = Xrank - numel(dim);
    Yval = dlarray(reshape(Yval, sz));
else
    Yrank = Xrank;
end
Yval = dlarray(Yval, repmat('U', 1, max(Yrank, 2)));
end