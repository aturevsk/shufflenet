classdef Shape_To_SliceLayer1013 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1013';
        end
    end


    methods
        function this = Shape_To_SliceLayer1013(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage4_stage4_2_Sl', 'x_stage4_stage4_2_61'};
        end

        function [x_stage4_stage4_2_Sl, x_stage4_stage4_2_61] = predict(this, x_stage4_stage4_1__6)
            if isdlarray(x_stage4_stage4_1__6)
                x_stage4_stage4_1__6 = stripdims(x_stage4_stage4_1__6);
            end
            x_stage4_stage4_1__6NumDims = 4;
            x_stage4_stage4_1__6 = shufflenet_v2.ops.permuteInputVar(x_stage4_stage4_1__6, [4 3 1 2], 4);

            [x_stage4_stage4_2_Sl, x_stage4_stage4_2_61, x_stage4_stage4_2_SlNumDims, x_stage4_stage4_2_61NumDims] = Shape_To_SliceGraph1050(this, x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, false);
            x_stage4_stage4_2_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage4_stage4_2_Sl, [3 4 2 1], 4);
            x_stage4_stage4_2_61 = shufflenet_v2.ops.permuteOutputVar(x_stage4_stage4_2_61, [3 4 2 1], 4);

            x_stage4_stage4_2_Sl = dlarray(single(x_stage4_stage4_2_Sl), 'SSCB');
            x_stage4_stage4_2_61 = dlarray(single(x_stage4_stage4_2_61), 'SSCB');
        end

        function [x_stage4_stage4_2_Sl, x_stage4_stage4_2_61] = forward(this, x_stage4_stage4_1__6)
            if isdlarray(x_stage4_stage4_1__6)
                x_stage4_stage4_1__6 = stripdims(x_stage4_stage4_1__6);
            end
            x_stage4_stage4_1__6NumDims = 4;
            x_stage4_stage4_1__6 = shufflenet_v2.ops.permuteInputVar(x_stage4_stage4_1__6, [4 3 1 2], 4);

            [x_stage4_stage4_2_Sl, x_stage4_stage4_2_61, x_stage4_stage4_2_SlNumDims, x_stage4_stage4_2_61NumDims] = Shape_To_SliceGraph1050(this, x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, true);
            x_stage4_stage4_2_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage4_stage4_2_Sl, [3 4 2 1], 4);
            x_stage4_stage4_2_61 = shufflenet_v2.ops.permuteOutputVar(x_stage4_stage4_2_61, [3 4 2 1], 4);

            x_stage4_stage4_2_Sl = dlarray(single(x_stage4_stage4_2_Sl), 'SSCB');
            x_stage4_stage4_2_61 = dlarray(single(x_stage4_stage4_2_61), 'SSCB');
        end

        function [x_stage4_stage4_2_Sl, x_stage4_stage4_2_61, x_stage4_stage4_2_SlNumDims1052, x_stage4_stage4_2_61NumDims1053] = Shape_To_SliceGraph1050(this, x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage4_stage4_1_Sh, x_stage4_stage4_1_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, 0, x_stage4_stage4_1__6NumDims+1);

            % Gather:
            [x_stage4_stage4_1_Ga, x_stage4_stage4_1_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage4_stage4_1_Sh, this.Vars.x_stage4_stage4_1_14, 0, x_stage4_stage4_1_ShNumDims, this.NumDims.x_stage4_stage4_1_14);

            % Shape:
            [x_stage4_stage4_1_52, x_stage4_stage4_1_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, 0, x_stage4_stage4_1__6NumDims+1);

            % Gather:
            [x_stage4_stage4_1_37, x_stage4_stage4_1_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage4_stage4_1_52, this.Vars.x_stage4_stage4_1_15, 0, x_stage4_stage4_1_52NumDims, this.NumDims.x_stage4_stage4_1_15);

            % Shape:
            [x_stage4_stage4_1_53, x_stage4_stage4_1_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, 0, x_stage4_stage4_1__6NumDims+1);

            % Gather:
            [x_stage4_stage4_1_38, x_stage4_stage4_1_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage4_stage4_1_53, this.Vars.x_stage4_stage4_1_16, 0, x_stage4_stage4_1_53NumDims, this.NumDims.x_stage4_stage4_1_16);

            % Shape:
            [x_stage4_stage4_1_54, x_stage4_stage4_1_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage4_stage4_1__6, x_stage4_stage4_1__6NumDims, 0, x_stage4_stage4_1__6NumDims+1);

            % Gather:
            [x_stage4_stage4_1_39, x_stage4_stage4_1_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage4_stage4_1_54, this.Vars.x_stage4_stage4_1_17, 0, x_stage4_stage4_1_54NumDims, this.NumDims.x_stage4_stage4_1_17);

            % Div:
            x_stage4_stage4_1_Di = fix(x_stage4_stage4_1_37 ./ this.Vars.x_stage4_stage4_1__7);
            x_stage4_stage4_1_DiNumDims = max(x_stage4_stage4_1_37NumDims, this.NumDims.x_stage4_stage4_1__7);

            % Cast:
            x_stage4_stage4_1__2 = cast(int64(extractdata(x_stage4_stage4_1_Di)), 'like', x_stage4_stage4_1_Di);
            x_stage4_stage4_1__2NumDims = x_stage4_stage4_1_DiNumDims;

            % Cast:
            x_stage4_stage4_1_Ca = cast(int64(extractdata(x_stage4_stage4_1__2)), 'like', x_stage4_stage4_1__2);
            x_stage4_stage4_1_CaNumDims = x_stage4_stage4_1__2NumDims;

            % Unsqueeze:
            [shape, x_stage4_stage4_1_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_Ga, this.Vars.onnx__Unsqueeze_1162, x_stage4_stage4_1_GaNumDims);
            x_stage4_stage4_1_71 = reshape(x_stage4_stage4_1_Ga, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_Ca, this.Vars.onnx__Unsqueeze_1166, x_stage4_stage4_1_CaNumDims);
            x_stage4_stage4_1_Un = reshape(x_stage4_stage4_1_Ca, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_38, this.Vars.onnx__Unsqueeze_1168, x_stage4_stage4_1_38NumDims);
            x_stage4_stage4_1_65 = reshape(x_stage4_stage4_1_38, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_39, this.Vars.onnx__Unsqueeze_1170, x_stage4_stage4_1_39NumDims);
            x_stage4_stage4_1_66 = reshape(x_stage4_stage4_1_39, shape);

            % Concat:
            [x_stage4_stage4_1_Co, x_stage4_stage4_1_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage4_stage4_1_71, this.Vars.x_stage4_stage4_1__8, x_stage4_stage4_1_Un, x_stage4_stage4_1_65, x_stage4_stage4_1_66}, [x_stage4_stage4_1_71NumDims, this.NumDims.x_stage4_stage4_1__8, x_stage4_stage4_1_UnNumDims, x_stage4_stage4_1_65NumDims, x_stage4_stage4_1_66NumDims]);

            % Reshape:
            [shape, x_stage4_stage4_1_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage4_stage4_1__6, x_stage4_stage4_1_Co, x_stage4_stage4_1__6NumDims, 0);
            x_stage4_stage4_1_49 = reshape(x_stage4_stage4_1__6, shape{:});

            % Transpose:
            [perm, x_stage4_stage4_1_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1051, x_stage4_stage4_1_49NumDims);
            if isempty(perm)
                x_stage4_stage4_1_Tr = x_stage4_stage4_1_49;
            else
                x_stage4_stage4_1_Tr = permute(x_stage4_stage4_1_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage4_stage4_1_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_Ga, this.Vars.onnx__Unsqueeze_1175, x_stage4_stage4_1_GaNumDims);
            x_stage4_stage4_1_67 = reshape(x_stage4_stage4_1_Ga, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_37, this.Vars.onnx__Unsqueeze_1177, x_stage4_stage4_1_37NumDims);
            x_stage4_stage4_1_68 = reshape(x_stage4_stage4_1_37, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_38, this.Vars.onnx__Unsqueeze_1179, x_stage4_stage4_1_38NumDims);
            x_stage4_stage4_1_69 = reshape(x_stage4_stage4_1_38, shape);

            % Unsqueeze:
            [shape, x_stage4_stage4_1_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage4_stage4_1_39, this.Vars.onnx__Unsqueeze_1181, x_stage4_stage4_1_39NumDims);
            x_stage4_stage4_1_70 = reshape(x_stage4_stage4_1_39, shape);

            % Concat:
            [x_stage4_stage4_1__5, x_stage4_stage4_1__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage4_stage4_1_67, x_stage4_stage4_1_68, x_stage4_stage4_1_69, x_stage4_stage4_1_70}, [x_stage4_stage4_1_67NumDims, x_stage4_stage4_1_68NumDims, x_stage4_stage4_1_69NumDims, x_stage4_stage4_1_70NumDims]);

            % Reshape:
            [shape, x_stage4_stage4_1_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage4_stage4_1_Tr, x_stage4_stage4_1__5, x_stage4_stage4_1_TrNumDims, 0);
            x_stage4_stage4_1_Re = reshape(x_stage4_stage4_1_Tr, shape{:});

            % Shape:
            [x_stage4_stage4_2_55, x_stage4_stage4_2_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage4_stage4_1_Re, x_stage4_stage4_1_ReNumDims, 0, x_stage4_stage4_1_ReNumDims+1);

            % Gather:
            [x_stage4_stage4_2_40, x_stage4_stage4_2_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage4_stage4_2_55, this.Vars.x_stage4_stage4_2_18, 0, x_stage4_stage4_2_55NumDims, this.NumDims.x_stage4_stage4_2_18);

            % Add:
            x_stage4_stage4_2_Ad = x_stage4_stage4_2_40 + this.Vars.x_stage4_stage4_2_10;
            x_stage4_stage4_2_AdNumDims = max(x_stage4_stage4_2_40NumDims, this.NumDims.x_stage4_stage4_2_10);

            % Div:
            x_stage4_stage4_2_34 = fix(x_stage4_stage4_2_Ad ./ this.Vars.x_stage4_stage4_2_11);
            x_stage4_stage4_2_34NumDims = max(x_stage4_stage4_2_AdNumDims, this.NumDims.x_stage4_stage4_2_11);

            % Mul:
            x_stage4_stage4_2_46 = x_stage4_stage4_2_34 .* this.Vars.x_stage4_stage4_2_12;
            x_stage4_stage4_2_46NumDims = max(x_stage4_stage4_2_34NumDims, this.NumDims.x_stage4_stage4_2_12);

            % Slice:
            [Indices, x_stage4_stage4_2_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage4_stage4_1_Re, this.Vars.x_stage4_stage4_2__9, x_stage4_stage4_2_46, this.Vars.x_stage4_stage4_2_18, '', x_stage4_stage4_1_ReNumDims);
            x_stage4_stage4_2_61 = x_stage4_stage4_1_Re(Indices{:});

            % Mul:
            x_stage4_stage4_2_Mu = x_stage4_stage4_2_34 .* this.Vars.x_stage4_stage4_2_13;
            x_stage4_stage4_2_MuNumDims = max(x_stage4_stage4_2_34NumDims, this.NumDims.x_stage4_stage4_2_13);

            % Slice:
            [Indices, x_stage4_stage4_2_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage4_stage4_1_Re, x_stage4_stage4_2_46, x_stage4_stage4_2_Mu, this.Vars.x_stage4_stage4_2_18, '', x_stage4_stage4_1_ReNumDims);
            x_stage4_stage4_2_Sl = x_stage4_stage4_1_Re(Indices{:});

            % Set graph output arguments
            x_stage4_stage4_2_SlNumDims1052 = x_stage4_stage4_2_SlNumDims;
            x_stage4_stage4_2_61NumDims1053 = x_stage4_stage4_2_61NumDims;

        end

    end

end