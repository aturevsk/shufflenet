function [Y, YRank] = pyTranspose(X, dim0, dim1, XRank)
%#codegen
% at::transpose(const at::Tensor &self, int64_t dim0, int64_t dim1)
% Swaps the dimensions dim0 and dim1 in X
%Copyright 2025 The MathWorks, Inc.
import shufflenet_exported.ops.*
% Perform Transpose only if input rank >= 2
if XRank >= 2
    mlDim0 = transformDim(dim0, XRank);
    mlDim1 = transformDim(dim1, XRank);
    % Create permutation vector
    perm = 1:XRank;
    perm(mlDim0) = mlDim1;
    perm(mlDim1) = mlDim0;
    Y = permute(X, perm);
else
    Y = X;
end
YRank = XRank;
end
function revPTDim = transformDim(dimRef ,XRank)
if dimRef < 0
    revPTDim = -dimRef;
else
    revPTDim = XRank - dimRef;
end
end