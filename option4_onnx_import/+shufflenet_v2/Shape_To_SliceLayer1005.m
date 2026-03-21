classdef Shape_To_SliceLayer1005 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1005';
        end
    end


    methods
        function this = Shape_To_SliceLayer1005(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_2_Sl', 'x_stage3_stage3_2_61'};
        end

        function [x_stage3_stage3_2_Sl, x_stage3_stage3_2_61] = predict(this, x_stage3_stage3_1__6)
            if isdlarray(x_stage3_stage3_1__6)
                x_stage3_stage3_1__6 = stripdims(x_stage3_stage3_1__6);
            end
            x_stage3_stage3_1__6NumDims = 4;
            x_stage3_stage3_1__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_1__6, [4 3 1 2], 4);

            [x_stage3_stage3_2_Sl, x_stage3_stage3_2_61, x_stage3_stage3_2_SlNumDims, x_stage3_stage3_2_61NumDims] = Shape_To_SliceGraph1019(this, x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, false);
            x_stage3_stage3_2_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_2_Sl, [3 4 2 1], 4);
            x_stage3_stage3_2_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_2_61, [3 4 2 1], 4);

            x_stage3_stage3_2_Sl = dlarray(single(x_stage3_stage3_2_Sl), 'SSCB');
            x_stage3_stage3_2_61 = dlarray(single(x_stage3_stage3_2_61), 'SSCB');
        end

        function [x_stage3_stage3_2_Sl, x_stage3_stage3_2_61] = forward(this, x_stage3_stage3_1__6)
            if isdlarray(x_stage3_stage3_1__6)
                x_stage3_stage3_1__6 = stripdims(x_stage3_stage3_1__6);
            end
            x_stage3_stage3_1__6NumDims = 4;
            x_stage3_stage3_1__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_1__6, [4 3 1 2], 4);

            [x_stage3_stage3_2_Sl, x_stage3_stage3_2_61, x_stage3_stage3_2_SlNumDims, x_stage3_stage3_2_61NumDims] = Shape_To_SliceGraph1019(this, x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, true);
            x_stage3_stage3_2_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_2_Sl, [3 4 2 1], 4);
            x_stage3_stage3_2_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_2_61, [3 4 2 1], 4);

            x_stage3_stage3_2_Sl = dlarray(single(x_stage3_stage3_2_Sl), 'SSCB');
            x_stage3_stage3_2_61 = dlarray(single(x_stage3_stage3_2_61), 'SSCB');
        end

        function [x_stage3_stage3_2_Sl, x_stage3_stage3_2_61, x_stage3_stage3_2_SlNumDims1021, x_stage3_stage3_2_61NumDims1022] = Shape_To_SliceGraph1019(this, x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_1_Sh, x_stage3_stage3_1_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, 0, x_stage3_stage3_1__6NumDims+1);

            % Gather:
            [x_stage3_stage3_1_Ga, x_stage3_stage3_1_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_1_Sh, this.Vars.x_stage3_stage3_1_14, 0, x_stage3_stage3_1_ShNumDims, this.NumDims.x_stage3_stage3_1_14);

            % Shape:
            [x_stage3_stage3_1_52, x_stage3_stage3_1_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, 0, x_stage3_stage3_1__6NumDims+1);

            % Gather:
            [x_stage3_stage3_1_37, x_stage3_stage3_1_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_1_52, this.Vars.x_stage3_stage3_1_15, 0, x_stage3_stage3_1_52NumDims, this.NumDims.x_stage3_stage3_1_15);

            % Shape:
            [x_stage3_stage3_1_53, x_stage3_stage3_1_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, 0, x_stage3_stage3_1__6NumDims+1);

            % Gather:
            [x_stage3_stage3_1_38, x_stage3_stage3_1_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_1_53, this.Vars.x_stage3_stage3_1_16, 0, x_stage3_stage3_1_53NumDims, this.NumDims.x_stage3_stage3_1_16);

            % Shape:
            [x_stage3_stage3_1_54, x_stage3_stage3_1_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_1__6, x_stage3_stage3_1__6NumDims, 0, x_stage3_stage3_1__6NumDims+1);

            % Gather:
            [x_stage3_stage3_1_39, x_stage3_stage3_1_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_1_54, this.Vars.x_stage3_stage3_1_17, 0, x_stage3_stage3_1_54NumDims, this.NumDims.x_stage3_stage3_1_17);

            % Div:
            x_stage3_stage3_1_Di = fix(x_stage3_stage3_1_37 ./ this.Vars.x_stage3_stage3_1__7);
            x_stage3_stage3_1_DiNumDims = max(x_stage3_stage3_1_37NumDims, this.NumDims.x_stage3_stage3_1__7);

            % Cast:
            x_stage3_stage3_1__2 = cast(int64(extractdata(x_stage3_stage3_1_Di)), 'like', x_stage3_stage3_1_Di);
            x_stage3_stage3_1__2NumDims = x_stage3_stage3_1_DiNumDims;

            % Cast:
            x_stage3_stage3_1_Ca = cast(int64(extractdata(x_stage3_stage3_1__2)), 'like', x_stage3_stage3_1__2);
            x_stage3_stage3_1_CaNumDims = x_stage3_stage3_1__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_1_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_Ga, this.Vars.onnx__Unsqueeze_675, x_stage3_stage3_1_GaNumDims);
            x_stage3_stage3_1_71 = reshape(x_stage3_stage3_1_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_Ca, this.Vars.onnx__Unsqueeze_679, x_stage3_stage3_1_CaNumDims);
            x_stage3_stage3_1_Un = reshape(x_stage3_stage3_1_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_38, this.Vars.onnx__Unsqueeze_681, x_stage3_stage3_1_38NumDims);
            x_stage3_stage3_1_65 = reshape(x_stage3_stage3_1_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_39, this.Vars.onnx__Unsqueeze_683, x_stage3_stage3_1_39NumDims);
            x_stage3_stage3_1_66 = reshape(x_stage3_stage3_1_39, shape);

            % Concat:
            [x_stage3_stage3_1_Co, x_stage3_stage3_1_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_1_71, this.Vars.x_stage3_stage3_1__8, x_stage3_stage3_1_Un, x_stage3_stage3_1_65, x_stage3_stage3_1_66}, [x_stage3_stage3_1_71NumDims, this.NumDims.x_stage3_stage3_1__8, x_stage3_stage3_1_UnNumDims, x_stage3_stage3_1_65NumDims, x_stage3_stage3_1_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_1_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_1__6, x_stage3_stage3_1_Co, x_stage3_stage3_1__6NumDims, 0);
            x_stage3_stage3_1_49 = reshape(x_stage3_stage3_1__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_1_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1020, x_stage3_stage3_1_49NumDims);
            if isempty(perm)
                x_stage3_stage3_1_Tr = x_stage3_stage3_1_49;
            else
                x_stage3_stage3_1_Tr = permute(x_stage3_stage3_1_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_1_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_Ga, this.Vars.onnx__Unsqueeze_688, x_stage3_stage3_1_GaNumDims);
            x_stage3_stage3_1_67 = reshape(x_stage3_stage3_1_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_37, this.Vars.onnx__Unsqueeze_690, x_stage3_stage3_1_37NumDims);
            x_stage3_stage3_1_68 = reshape(x_stage3_stage3_1_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_38, this.Vars.onnx__Unsqueeze_692, x_stage3_stage3_1_38NumDims);
            x_stage3_stage3_1_69 = reshape(x_stage3_stage3_1_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_1_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_1_39, this.Vars.onnx__Unsqueeze_694, x_stage3_stage3_1_39NumDims);
            x_stage3_stage3_1_70 = reshape(x_stage3_stage3_1_39, shape);

            % Concat:
            [x_stage3_stage3_1__5, x_stage3_stage3_1__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_1_67, x_stage3_stage3_1_68, x_stage3_stage3_1_69, x_stage3_stage3_1_70}, [x_stage3_stage3_1_67NumDims, x_stage3_stage3_1_68NumDims, x_stage3_stage3_1_69NumDims, x_stage3_stage3_1_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_1_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_1_Tr, x_stage3_stage3_1__5, x_stage3_stage3_1_TrNumDims, 0);
            x_stage3_stage3_1_Re = reshape(x_stage3_stage3_1_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_2_55, x_stage3_stage3_2_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_1_Re, x_stage3_stage3_1_ReNumDims, 0, x_stage3_stage3_1_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_2_40, x_stage3_stage3_2_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_2_55, this.Vars.x_stage3_stage3_2_18, 0, x_stage3_stage3_2_55NumDims, this.NumDims.x_stage3_stage3_2_18);

            % Add:
            x_stage3_stage3_2_Ad = x_stage3_stage3_2_40 + this.Vars.x_stage3_stage3_2_10;
            x_stage3_stage3_2_AdNumDims = max(x_stage3_stage3_2_40NumDims, this.NumDims.x_stage3_stage3_2_10);

            % Div:
            x_stage3_stage3_2_34 = fix(x_stage3_stage3_2_Ad ./ this.Vars.x_stage3_stage3_2_11);
            x_stage3_stage3_2_34NumDims = max(x_stage3_stage3_2_AdNumDims, this.NumDims.x_stage3_stage3_2_11);

            % Mul:
            x_stage3_stage3_2_46 = x_stage3_stage3_2_34 .* this.Vars.x_stage3_stage3_2_12;
            x_stage3_stage3_2_46NumDims = max(x_stage3_stage3_2_34NumDims, this.NumDims.x_stage3_stage3_2_12);

            % Slice:
            [Indices, x_stage3_stage3_2_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_1_Re, this.Vars.x_stage3_stage3_2__9, x_stage3_stage3_2_46, this.Vars.x_stage3_stage3_2_18, '', x_stage3_stage3_1_ReNumDims);
            x_stage3_stage3_2_61 = x_stage3_stage3_1_Re(Indices{:});

            % Mul:
            x_stage3_stage3_2_Mu = x_stage3_stage3_2_34 .* this.Vars.x_stage3_stage3_2_13;
            x_stage3_stage3_2_MuNumDims = max(x_stage3_stage3_2_34NumDims, this.NumDims.x_stage3_stage3_2_13);

            % Slice:
            [Indices, x_stage3_stage3_2_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_1_Re, x_stage3_stage3_2_46, x_stage3_stage3_2_Mu, this.Vars.x_stage3_stage3_2_18, '', x_stage3_stage3_1_ReNumDims);
            x_stage3_stage3_2_Sl = x_stage3_stage3_1_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_2_SlNumDims1021 = x_stage3_stage3_2_SlNumDims;
            x_stage3_stage3_2_61NumDims1022 = x_stage3_stage3_2_61NumDims;

        end

    end

end