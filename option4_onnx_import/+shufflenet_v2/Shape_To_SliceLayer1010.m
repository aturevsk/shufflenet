classdef Shape_To_SliceLayer1010 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1010';
        end
    end


    methods
        function this = Shape_To_SliceLayer1010(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_7_Sl', 'x_stage3_stage3_7_61'};
        end

        function [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61] = predict(this, x_stage3_stage3_6__6)
            if isdlarray(x_stage3_stage3_6__6)
                x_stage3_stage3_6__6 = stripdims(x_stage3_stage3_6__6);
            end
            x_stage3_stage3_6__6NumDims = 4;
            x_stage3_stage3_6__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_6__6, [4 3 1 2], 4);

            [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61, x_stage3_stage3_7_SlNumDims, x_stage3_stage3_7_61NumDims] = Shape_To_SliceGraph1039(this, x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, false);
            x_stage3_stage3_7_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_Sl, [3 4 2 1], 4);
            x_stage3_stage3_7_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_61, [3 4 2 1], 4);

            x_stage3_stage3_7_Sl = dlarray(single(x_stage3_stage3_7_Sl), 'SSCB');
            x_stage3_stage3_7_61 = dlarray(single(x_stage3_stage3_7_61), 'SSCB');
        end

        function [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61] = forward(this, x_stage3_stage3_6__6)
            if isdlarray(x_stage3_stage3_6__6)
                x_stage3_stage3_6__6 = stripdims(x_stage3_stage3_6__6);
            end
            x_stage3_stage3_6__6NumDims = 4;
            x_stage3_stage3_6__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_6__6, [4 3 1 2], 4);

            [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61, x_stage3_stage3_7_SlNumDims, x_stage3_stage3_7_61NumDims] = Shape_To_SliceGraph1039(this, x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, true);
            x_stage3_stage3_7_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_Sl, [3 4 2 1], 4);
            x_stage3_stage3_7_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_61, [3 4 2 1], 4);

            x_stage3_stage3_7_Sl = dlarray(single(x_stage3_stage3_7_Sl), 'SSCB');
            x_stage3_stage3_7_61 = dlarray(single(x_stage3_stage3_7_61), 'SSCB');
        end

        function [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61, x_stage3_stage3_7_SlNumDims1041, x_stage3_stage3_7_61NumDims1042] = Shape_To_SliceGraph1039(this, x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_6_Sh, x_stage3_stage3_6_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, 0, x_stage3_stage3_6__6NumDims+1);

            % Gather:
            [x_stage3_stage3_6_Ga, x_stage3_stage3_6_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_6_Sh, this.Vars.x_stage3_stage3_6_14, 0, x_stage3_stage3_6_ShNumDims, this.NumDims.x_stage3_stage3_6_14);

            % Shape:
            [x_stage3_stage3_6_52, x_stage3_stage3_6_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, 0, x_stage3_stage3_6__6NumDims+1);

            % Gather:
            [x_stage3_stage3_6_37, x_stage3_stage3_6_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_6_52, this.Vars.x_stage3_stage3_6_15, 0, x_stage3_stage3_6_52NumDims, this.NumDims.x_stage3_stage3_6_15);

            % Shape:
            [x_stage3_stage3_6_53, x_stage3_stage3_6_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, 0, x_stage3_stage3_6__6NumDims+1);

            % Gather:
            [x_stage3_stage3_6_38, x_stage3_stage3_6_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_6_53, this.Vars.x_stage3_stage3_6_16, 0, x_stage3_stage3_6_53NumDims, this.NumDims.x_stage3_stage3_6_16);

            % Shape:
            [x_stage3_stage3_6_54, x_stage3_stage3_6_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, 0, x_stage3_stage3_6__6NumDims+1);

            % Gather:
            [x_stage3_stage3_6_39, x_stage3_stage3_6_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_6_54, this.Vars.x_stage3_stage3_6_17, 0, x_stage3_stage3_6_54NumDims, this.NumDims.x_stage3_stage3_6_17);

            % Div:
            x_stage3_stage3_6_Di = fix(x_stage3_stage3_6_37 ./ this.Vars.x_stage3_stage3_6__7);
            x_stage3_stage3_6_DiNumDims = max(x_stage3_stage3_6_37NumDims, this.NumDims.x_stage3_stage3_6__7);

            % Cast:
            x_stage3_stage3_6__2 = cast(int64(extractdata(x_stage3_stage3_6_Di)), 'like', x_stage3_stage3_6_Di);
            x_stage3_stage3_6__2NumDims = x_stage3_stage3_6_DiNumDims;

            % Cast:
            x_stage3_stage3_6_Ca = cast(int64(extractdata(x_stage3_stage3_6__2)), 'like', x_stage3_stage3_6__2);
            x_stage3_stage3_6_CaNumDims = x_stage3_stage3_6__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_6_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ga, this.Vars.onnx__Unsqueeze_985, x_stage3_stage3_6_GaNumDims);
            x_stage3_stage3_6_71 = reshape(x_stage3_stage3_6_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ca, this.Vars.onnx__Unsqueeze_989, x_stage3_stage3_6_CaNumDims);
            x_stage3_stage3_6_Un = reshape(x_stage3_stage3_6_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_38, this.Vars.onnx__Unsqueeze_991, x_stage3_stage3_6_38NumDims);
            x_stage3_stage3_6_65 = reshape(x_stage3_stage3_6_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_39, this.Vars.onnx__Unsqueeze_993, x_stage3_stage3_6_39NumDims);
            x_stage3_stage3_6_66 = reshape(x_stage3_stage3_6_39, shape);

            % Concat:
            [x_stage3_stage3_6_Co, x_stage3_stage3_6_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_6_71, this.Vars.x_stage3_stage3_6__8, x_stage3_stage3_6_Un, x_stage3_stage3_6_65, x_stage3_stage3_6_66}, [x_stage3_stage3_6_71NumDims, this.NumDims.x_stage3_stage3_6__8, x_stage3_stage3_6_UnNumDims, x_stage3_stage3_6_65NumDims, x_stage3_stage3_6_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_6_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_6__6, x_stage3_stage3_6_Co, x_stage3_stage3_6__6NumDims, 0);
            x_stage3_stage3_6_49 = reshape(x_stage3_stage3_6__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_6_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1040, x_stage3_stage3_6_49NumDims);
            if isempty(perm)
                x_stage3_stage3_6_Tr = x_stage3_stage3_6_49;
            else
                x_stage3_stage3_6_Tr = permute(x_stage3_stage3_6_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_6_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ga, this.Vars.onnx__Unsqueeze_998, x_stage3_stage3_6_GaNumDims);
            x_stage3_stage3_6_67 = reshape(x_stage3_stage3_6_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_37, this.Vars.onnx__Unsqueeze_1000, x_stage3_stage3_6_37NumDims);
            x_stage3_stage3_6_68 = reshape(x_stage3_stage3_6_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_38, this.Vars.onnx__Unsqueeze_1002, x_stage3_stage3_6_38NumDims);
            x_stage3_stage3_6_69 = reshape(x_stage3_stage3_6_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_6_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_39, this.Vars.onnx__Unsqueeze_1004, x_stage3_stage3_6_39NumDims);
            x_stage3_stage3_6_70 = reshape(x_stage3_stage3_6_39, shape);

            % Concat:
            [x_stage3_stage3_6__5, x_stage3_stage3_6__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_6_67, x_stage3_stage3_6_68, x_stage3_stage3_6_69, x_stage3_stage3_6_70}, [x_stage3_stage3_6_67NumDims, x_stage3_stage3_6_68NumDims, x_stage3_stage3_6_69NumDims, x_stage3_stage3_6_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_6_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_6_Tr, x_stage3_stage3_6__5, x_stage3_stage3_6_TrNumDims, 0);
            x_stage3_stage3_6_Re = reshape(x_stage3_stage3_6_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_7_55, x_stage3_stage3_7_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_6_Re, x_stage3_stage3_6_ReNumDims, 0, x_stage3_stage3_6_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_7_40, x_stage3_stage3_7_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_7_55, this.Vars.x_stage3_stage3_7_18, 0, x_stage3_stage3_7_55NumDims, this.NumDims.x_stage3_stage3_7_18);

            % Add:
            x_stage3_stage3_7_Ad = x_stage3_stage3_7_40 + this.Vars.x_stage3_stage3_7_10;
            x_stage3_stage3_7_AdNumDims = max(x_stage3_stage3_7_40NumDims, this.NumDims.x_stage3_stage3_7_10);

            % Div:
            x_stage3_stage3_7_34 = fix(x_stage3_stage3_7_Ad ./ this.Vars.x_stage3_stage3_7_11);
            x_stage3_stage3_7_34NumDims = max(x_stage3_stage3_7_AdNumDims, this.NumDims.x_stage3_stage3_7_11);

            % Mul:
            x_stage3_stage3_7_46 = x_stage3_stage3_7_34 .* this.Vars.x_stage3_stage3_7_12;
            x_stage3_stage3_7_46NumDims = max(x_stage3_stage3_7_34NumDims, this.NumDims.x_stage3_stage3_7_12);

            % Slice:
            [Indices, x_stage3_stage3_7_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_6_Re, this.Vars.x_stage3_stage3_7__9, x_stage3_stage3_7_46, this.Vars.x_stage3_stage3_7_18, '', x_stage3_stage3_6_ReNumDims);
            x_stage3_stage3_7_61 = x_stage3_stage3_6_Re(Indices{:});

            % Mul:
            x_stage3_stage3_7_Mu = x_stage3_stage3_7_34 .* this.Vars.x_stage3_stage3_7_13;
            x_stage3_stage3_7_MuNumDims = max(x_stage3_stage3_7_34NumDims, this.NumDims.x_stage3_stage3_7_13);

            % Slice:
            [Indices, x_stage3_stage3_7_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_6_Re, x_stage3_stage3_7_46, x_stage3_stage3_7_Mu, this.Vars.x_stage3_stage3_7_18, '', x_stage3_stage3_6_ReNumDims);
            x_stage3_stage3_7_Sl = x_stage3_stage3_6_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_7_SlNumDims1041 = x_stage3_stage3_7_SlNumDims;
            x_stage3_stage3_7_61NumDims1042 = x_stage3_stage3_7_61NumDims;

        end

    end

end