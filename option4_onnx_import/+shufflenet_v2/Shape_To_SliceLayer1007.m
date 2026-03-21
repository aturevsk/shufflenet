classdef Shape_To_SliceLayer1007 < nnet.layer.Layer & nnet.layer.Formattable
    % A custom layer auto-generated while importing an ONNX network.

    %#ok<*PROPLC>
    %#ok<*NBRAK>
    %#ok<*INUSL>
    %#ok<*VARARG>
    properties (Learnable)
    end

    properties (State)
    end

    properties
        Vars
        NumDims
    end


    methods(Static, Hidden)
        % Specify the path to the class that will be used for codegen
        function name = matlabCodegenRedirect(~)
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1007';
        end
    end


    methods
        function this = Shape_To_SliceLayer1007(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_4_Sl', 'x_stage3_stage3_4_61'};
        end

        function [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61] = predict(this, x_stage3_stage3_3__6)
            if isdlarray(x_stage3_stage3_3__6)
                x_stage3_stage3_3__6 = stripdims(x_stage3_stage3_3__6);
            end
            x_stage3_stage3_3__6NumDims = 4;
            x_stage3_stage3_3__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_3__6, [4 3 1 2], 4);

            [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61, x_stage3_stage3_4_SlNumDims, x_stage3_stage3_4_61NumDims] = Shape_To_SliceGraph1027(this, x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, false);
            x_stage3_stage3_4_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_4_Sl, [3 4 2 1], 4);
            x_stage3_stage3_4_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_4_61, [3 4 2 1], 4);

            x_stage3_stage3_4_Sl = dlarray(single(x_stage3_stage3_4_Sl), 'SSCB');
            x_stage3_stage3_4_61 = dlarray(single(x_stage3_stage3_4_61), 'SSCB');
        end

        function [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61] = forward(this, x_stage3_stage3_3__6)
            if isdlarray(x_stage3_stage3_3__6)
                x_stage3_stage3_3__6 = stripdims(x_stage3_stage3_3__6);
            end
            x_stage3_stage3_3__6NumDims = 4;
            x_stage3_stage3_3__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_3__6, [4 3 1 2], 4);

            [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61, x_stage3_stage3_4_SlNumDims, x_stage3_stage3_4_61NumDims] = Shape_To_SliceGraph1027(this, x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, true);
            x_stage3_stage3_4_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_4_Sl, [3 4 2 1], 4);
            x_stage3_stage3_4_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_4_61, [3 4 2 1], 4);

            x_stage3_stage3_4_Sl = dlarray(single(x_stage3_stage3_4_Sl), 'SSCB');
            x_stage3_stage3_4_61 = dlarray(single(x_stage3_stage3_4_61), 'SSCB');
        end

        function [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61, x_stage3_stage3_4_SlNumDims1029, x_stage3_stage3_4_61NumDims1030] = Shape_To_SliceGraph1027(this, x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_3_Sh, x_stage3_stage3_3_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, 0, x_stage3_stage3_3__6NumDims+1);

            % Gather:
            [x_stage3_stage3_3_Ga, x_stage3_stage3_3_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_3_Sh, this.Vars.x_stage3_stage3_3_14, 0, x_stage3_stage3_3_ShNumDims, this.NumDims.x_stage3_stage3_3_14);

            % Shape:
            [x_stage3_stage3_3_52, x_stage3_stage3_3_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, 0, x_stage3_stage3_3__6NumDims+1);

            % Gather:
            [x_stage3_stage3_3_37, x_stage3_stage3_3_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_3_52, this.Vars.x_stage3_stage3_3_15, 0, x_stage3_stage3_3_52NumDims, this.NumDims.x_stage3_stage3_3_15);

            % Shape:
            [x_stage3_stage3_3_53, x_stage3_stage3_3_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, 0, x_stage3_stage3_3__6NumDims+1);

            % Gather:
            [x_stage3_stage3_3_38, x_stage3_stage3_3_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_3_53, this.Vars.x_stage3_stage3_3_16, 0, x_stage3_stage3_3_53NumDims, this.NumDims.x_stage3_stage3_3_16);

            % Shape:
            [x_stage3_stage3_3_54, x_stage3_stage3_3_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, 0, x_stage3_stage3_3__6NumDims+1);

            % Gather:
            [x_stage3_stage3_3_39, x_stage3_stage3_3_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_3_54, this.Vars.x_stage3_stage3_3_17, 0, x_stage3_stage3_3_54NumDims, this.NumDims.x_stage3_stage3_3_17);

            % Div:
            x_stage3_stage3_3_Di = fix(x_stage3_stage3_3_37 ./ this.Vars.x_stage3_stage3_3__7);
            x_stage3_stage3_3_DiNumDims = max(x_stage3_stage3_3_37NumDims, this.NumDims.x_stage3_stage3_3__7);

            % Cast:
            x_stage3_stage3_3__2 = cast(int64(extractdata(x_stage3_stage3_3_Di)), 'like', x_stage3_stage3_3_Di);
            x_stage3_stage3_3__2NumDims = x_stage3_stage3_3_DiNumDims;

            % Cast:
            x_stage3_stage3_3_Ca = cast(int64(extractdata(x_stage3_stage3_3__2)), 'like', x_stage3_stage3_3__2);
            x_stage3_stage3_3_CaNumDims = x_stage3_stage3_3__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_3_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ga, this.Vars.onnx__Unsqueeze_799, x_stage3_stage3_3_GaNumDims);
            x_stage3_stage3_3_71 = reshape(x_stage3_stage3_3_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ca, this.Vars.onnx__Unsqueeze_803, x_stage3_stage3_3_CaNumDims);
            x_stage3_stage3_3_Un = reshape(x_stage3_stage3_3_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_38, this.Vars.onnx__Unsqueeze_805, x_stage3_stage3_3_38NumDims);
            x_stage3_stage3_3_65 = reshape(x_stage3_stage3_3_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_39, this.Vars.onnx__Unsqueeze_807, x_stage3_stage3_3_39NumDims);
            x_stage3_stage3_3_66 = reshape(x_stage3_stage3_3_39, shape);

            % Concat:
            [x_stage3_stage3_3_Co, x_stage3_stage3_3_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_3_71, this.Vars.x_stage3_stage3_3__8, x_stage3_stage3_3_Un, x_stage3_stage3_3_65, x_stage3_stage3_3_66}, [x_stage3_stage3_3_71NumDims, this.NumDims.x_stage3_stage3_3__8, x_stage3_stage3_3_UnNumDims, x_stage3_stage3_3_65NumDims, x_stage3_stage3_3_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_3_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_3__6, x_stage3_stage3_3_Co, x_stage3_stage3_3__6NumDims, 0);
            x_stage3_stage3_3_49 = reshape(x_stage3_stage3_3__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_3_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1028, x_stage3_stage3_3_49NumDims);
            if isempty(perm)
                x_stage3_stage3_3_Tr = x_stage3_stage3_3_49;
            else
                x_stage3_stage3_3_Tr = permute(x_stage3_stage3_3_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_3_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ga, this.Vars.onnx__Unsqueeze_812, x_stage3_stage3_3_GaNumDims);
            x_stage3_stage3_3_67 = reshape(x_stage3_stage3_3_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_37, this.Vars.onnx__Unsqueeze_814, x_stage3_stage3_3_37NumDims);
            x_stage3_stage3_3_68 = reshape(x_stage3_stage3_3_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_38, this.Vars.onnx__Unsqueeze_816, x_stage3_stage3_3_38NumDims);
            x_stage3_stage3_3_69 = reshape(x_stage3_stage3_3_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_3_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_39, this.Vars.onnx__Unsqueeze_818, x_stage3_stage3_3_39NumDims);
            x_stage3_stage3_3_70 = reshape(x_stage3_stage3_3_39, shape);

            % Concat:
            [x_stage3_stage3_3__5, x_stage3_stage3_3__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_3_67, x_stage3_stage3_3_68, x_stage3_stage3_3_69, x_stage3_stage3_3_70}, [x_stage3_stage3_3_67NumDims, x_stage3_stage3_3_68NumDims, x_stage3_stage3_3_69NumDims, x_stage3_stage3_3_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_3_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_3_Tr, x_stage3_stage3_3__5, x_stage3_stage3_3_TrNumDims, 0);
            x_stage3_stage3_3_Re = reshape(x_stage3_stage3_3_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_4_55, x_stage3_stage3_4_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_3_Re, x_stage3_stage3_3_ReNumDims, 0, x_stage3_stage3_3_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_4_40, x_stage3_stage3_4_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_4_55, this.Vars.x_stage3_stage3_4_18, 0, x_stage3_stage3_4_55NumDims, this.NumDims.x_stage3_stage3_4_18);

            % Add:
            x_stage3_stage3_4_Ad = x_stage3_stage3_4_40 + this.Vars.x_stage3_stage3_4_10;
            x_stage3_stage3_4_AdNumDims = max(x_stage3_stage3_4_40NumDims, this.NumDims.x_stage3_stage3_4_10);

            % Div:
            x_stage3_stage3_4_34 = fix(x_stage3_stage3_4_Ad ./ this.Vars.x_stage3_stage3_4_11);
            x_stage3_stage3_4_34NumDims = max(x_stage3_stage3_4_AdNumDims, this.NumDims.x_stage3_stage3_4_11);

            % Mul:
            x_stage3_stage3_4_46 = x_stage3_stage3_4_34 .* this.Vars.x_stage3_stage3_4_12;
            x_stage3_stage3_4_46NumDims = max(x_stage3_stage3_4_34NumDims, this.NumDims.x_stage3_stage3_4_12);

            % Slice:
            [Indices, x_stage3_stage3_4_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_3_Re, this.Vars.x_stage3_stage3_4__9, x_stage3_stage3_4_46, this.Vars.x_stage3_stage3_4_18, '', x_stage3_stage3_3_ReNumDims);
            x_stage3_stage3_4_61 = x_stage3_stage3_3_Re(Indices{:});

            % Mul:
            x_stage3_stage3_4_Mu = x_stage3_stage3_4_34 .* this.Vars.x_stage3_stage3_4_13;
            x_stage3_stage3_4_MuNumDims = max(x_stage3_stage3_4_34NumDims, this.NumDims.x_stage3_stage3_4_13);

            % Slice:
            [Indices, x_stage3_stage3_4_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_3_Re, x_stage3_stage3_4_46, x_stage3_stage3_4_Mu, this.Vars.x_stage3_stage3_4_18, '', x_stage3_stage3_3_ReNumDims);
            x_stage3_stage3_4_Sl = x_stage3_stage3_3_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_4_SlNumDims1029 = x_stage3_stage3_4_SlNumDims;
            x_stage3_stage3_4_61NumDims1030 = x_stage3_stage3_4_61NumDims;

        end

    end

end