classdef Shape_To_SliceLayer1006 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1006';
        end
    end


    methods
        function this = Shape_To_SliceLayer1006(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_3_Sl', 'x_stage3_stage3_3_61'};
        end

        function [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61] = predict(this, x_stage3_stage3_2__6)
            if isdlarray(x_stage3_stage3_2__6)
                x_stage3_stage3_2__6 = stripdims(x_stage3_stage3_2__6);
            end
            x_stage3_stage3_2__6NumDims = 4;
            x_stage3_stage3_2__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_2__6, [4 3 1 2], 4);

            [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61, x_stage3_stage3_3_SlNumDims, x_stage3_stage3_3_61NumDims] = Shape_To_SliceGraph1023(this, x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, false);
            x_stage3_stage3_3_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_3_Sl, [3 4 2 1], 4);
            x_stage3_stage3_3_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_3_61, [3 4 2 1], 4);

            x_stage3_stage3_3_Sl = dlarray(single(x_stage3_stage3_3_Sl), 'SSCB');
            x_stage3_stage3_3_61 = dlarray(single(x_stage3_stage3_3_61), 'SSCB');
        end

        function [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61] = forward(this, x_stage3_stage3_2__6)
            if isdlarray(x_stage3_stage3_2__6)
                x_stage3_stage3_2__6 = stripdims(x_stage3_stage3_2__6);
            end
            x_stage3_stage3_2__6NumDims = 4;
            x_stage3_stage3_2__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_2__6, [4 3 1 2], 4);

            [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61, x_stage3_stage3_3_SlNumDims, x_stage3_stage3_3_61NumDims] = Shape_To_SliceGraph1023(this, x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, true);
            x_stage3_stage3_3_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_3_Sl, [3 4 2 1], 4);
            x_stage3_stage3_3_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_3_61, [3 4 2 1], 4);

            x_stage3_stage3_3_Sl = dlarray(single(x_stage3_stage3_3_Sl), 'SSCB');
            x_stage3_stage3_3_61 = dlarray(single(x_stage3_stage3_3_61), 'SSCB');
        end

        function [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61, x_stage3_stage3_3_SlNumDims1025, x_stage3_stage3_3_61NumDims1026] = Shape_To_SliceGraph1023(this, x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_2_Sh, x_stage3_stage3_2_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, 0, x_stage3_stage3_2__6NumDims+1);

            % Gather:
            [x_stage3_stage3_2_Ga, x_stage3_stage3_2_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_2_Sh, this.Vars.x_stage3_stage3_2_14, 0, x_stage3_stage3_2_ShNumDims, this.NumDims.x_stage3_stage3_2_14);

            % Shape:
            [x_stage3_stage3_2_52, x_stage3_stage3_2_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, 0, x_stage3_stage3_2__6NumDims+1);

            % Gather:
            [x_stage3_stage3_2_37, x_stage3_stage3_2_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_2_52, this.Vars.x_stage3_stage3_2_15, 0, x_stage3_stage3_2_52NumDims, this.NumDims.x_stage3_stage3_2_15);

            % Shape:
            [x_stage3_stage3_2_53, x_stage3_stage3_2_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, 0, x_stage3_stage3_2__6NumDims+1);

            % Gather:
            [x_stage3_stage3_2_38, x_stage3_stage3_2_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_2_53, this.Vars.x_stage3_stage3_2_16, 0, x_stage3_stage3_2_53NumDims, this.NumDims.x_stage3_stage3_2_16);

            % Shape:
            [x_stage3_stage3_2_54, x_stage3_stage3_2_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, 0, x_stage3_stage3_2__6NumDims+1);

            % Gather:
            [x_stage3_stage3_2_39, x_stage3_stage3_2_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_2_54, this.Vars.x_stage3_stage3_2_17, 0, x_stage3_stage3_2_54NumDims, this.NumDims.x_stage3_stage3_2_17);

            % Div:
            x_stage3_stage3_2_Di = fix(x_stage3_stage3_2_37 ./ this.Vars.x_stage3_stage3_2__7);
            x_stage3_stage3_2_DiNumDims = max(x_stage3_stage3_2_37NumDims, this.NumDims.x_stage3_stage3_2__7);

            % Cast:
            x_stage3_stage3_2__2 = cast(int64(extractdata(x_stage3_stage3_2_Di)), 'like', x_stage3_stage3_2_Di);
            x_stage3_stage3_2__2NumDims = x_stage3_stage3_2_DiNumDims;

            % Cast:
            x_stage3_stage3_2_Ca = cast(int64(extractdata(x_stage3_stage3_2__2)), 'like', x_stage3_stage3_2__2);
            x_stage3_stage3_2_CaNumDims = x_stage3_stage3_2__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_2_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ga, this.Vars.onnx__Unsqueeze_737, x_stage3_stage3_2_GaNumDims);
            x_stage3_stage3_2_71 = reshape(x_stage3_stage3_2_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ca, this.Vars.onnx__Unsqueeze_741, x_stage3_stage3_2_CaNumDims);
            x_stage3_stage3_2_Un = reshape(x_stage3_stage3_2_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_38, this.Vars.onnx__Unsqueeze_743, x_stage3_stage3_2_38NumDims);
            x_stage3_stage3_2_65 = reshape(x_stage3_stage3_2_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_39, this.Vars.onnx__Unsqueeze_745, x_stage3_stage3_2_39NumDims);
            x_stage3_stage3_2_66 = reshape(x_stage3_stage3_2_39, shape);

            % Concat:
            [x_stage3_stage3_2_Co, x_stage3_stage3_2_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_2_71, this.Vars.x_stage3_stage3_2__8, x_stage3_stage3_2_Un, x_stage3_stage3_2_65, x_stage3_stage3_2_66}, [x_stage3_stage3_2_71NumDims, this.NumDims.x_stage3_stage3_2__8, x_stage3_stage3_2_UnNumDims, x_stage3_stage3_2_65NumDims, x_stage3_stage3_2_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_2_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_2__6, x_stage3_stage3_2_Co, x_stage3_stage3_2__6NumDims, 0);
            x_stage3_stage3_2_49 = reshape(x_stage3_stage3_2__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_2_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1024, x_stage3_stage3_2_49NumDims);
            if isempty(perm)
                x_stage3_stage3_2_Tr = x_stage3_stage3_2_49;
            else
                x_stage3_stage3_2_Tr = permute(x_stage3_stage3_2_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_2_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ga, this.Vars.onnx__Unsqueeze_750, x_stage3_stage3_2_GaNumDims);
            x_stage3_stage3_2_67 = reshape(x_stage3_stage3_2_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_37, this.Vars.onnx__Unsqueeze_752, x_stage3_stage3_2_37NumDims);
            x_stage3_stage3_2_68 = reshape(x_stage3_stage3_2_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_38, this.Vars.onnx__Unsqueeze_754, x_stage3_stage3_2_38NumDims);
            x_stage3_stage3_2_69 = reshape(x_stage3_stage3_2_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_2_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_39, this.Vars.onnx__Unsqueeze_756, x_stage3_stage3_2_39NumDims);
            x_stage3_stage3_2_70 = reshape(x_stage3_stage3_2_39, shape);

            % Concat:
            [x_stage3_stage3_2__5, x_stage3_stage3_2__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_2_67, x_stage3_stage3_2_68, x_stage3_stage3_2_69, x_stage3_stage3_2_70}, [x_stage3_stage3_2_67NumDims, x_stage3_stage3_2_68NumDims, x_stage3_stage3_2_69NumDims, x_stage3_stage3_2_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_2_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_2_Tr, x_stage3_stage3_2__5, x_stage3_stage3_2_TrNumDims, 0);
            x_stage3_stage3_2_Re = reshape(x_stage3_stage3_2_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_3_55, x_stage3_stage3_3_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_2_Re, x_stage3_stage3_2_ReNumDims, 0, x_stage3_stage3_2_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_3_40, x_stage3_stage3_3_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_3_55, this.Vars.x_stage3_stage3_3_18, 0, x_stage3_stage3_3_55NumDims, this.NumDims.x_stage3_stage3_3_18);

            % Add:
            x_stage3_stage3_3_Ad = x_stage3_stage3_3_40 + this.Vars.x_stage3_stage3_3_10;
            x_stage3_stage3_3_AdNumDims = max(x_stage3_stage3_3_40NumDims, this.NumDims.x_stage3_stage3_3_10);

            % Div:
            x_stage3_stage3_3_34 = fix(x_stage3_stage3_3_Ad ./ this.Vars.x_stage3_stage3_3_11);
            x_stage3_stage3_3_34NumDims = max(x_stage3_stage3_3_AdNumDims, this.NumDims.x_stage3_stage3_3_11);

            % Mul:
            x_stage3_stage3_3_46 = x_stage3_stage3_3_34 .* this.Vars.x_stage3_stage3_3_12;
            x_stage3_stage3_3_46NumDims = max(x_stage3_stage3_3_34NumDims, this.NumDims.x_stage3_stage3_3_12);

            % Slice:
            [Indices, x_stage3_stage3_3_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_2_Re, this.Vars.x_stage3_stage3_3__9, x_stage3_stage3_3_46, this.Vars.x_stage3_stage3_3_18, '', x_stage3_stage3_2_ReNumDims);
            x_stage3_stage3_3_61 = x_stage3_stage3_2_Re(Indices{:});

            % Mul:
            x_stage3_stage3_3_Mu = x_stage3_stage3_3_34 .* this.Vars.x_stage3_stage3_3_13;
            x_stage3_stage3_3_MuNumDims = max(x_stage3_stage3_3_34NumDims, this.NumDims.x_stage3_stage3_3_13);

            % Slice:
            [Indices, x_stage3_stage3_3_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_2_Re, x_stage3_stage3_3_46, x_stage3_stage3_3_Mu, this.Vars.x_stage3_stage3_3_18, '', x_stage3_stage3_2_ReNumDims);
            x_stage3_stage3_3_Sl = x_stage3_stage3_2_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_3_SlNumDims1025 = x_stage3_stage3_3_SlNumDims;
            x_stage3_stage3_3_61NumDims1026 = x_stage3_stage3_3_61NumDims;

        end

    end

end