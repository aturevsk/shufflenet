classdef Shape_To_SliceLayer1009 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1009';
        end
    end


    methods
        function this = Shape_To_SliceLayer1009(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_6_Sl', 'x_stage3_stage3_6_61'};
        end

        function [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61] = predict(this, x_stage3_stage3_5__6)
            if isdlarray(x_stage3_stage3_5__6)
                x_stage3_stage3_5__6 = stripdims(x_stage3_stage3_5__6);
            end
            x_stage3_stage3_5__6NumDims = 4;
            x_stage3_stage3_5__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_5__6, [4 3 1 2], 4);

            [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61, x_stage3_stage3_6_SlNumDims, x_stage3_stage3_6_61NumDims] = Shape_To_SliceGraph1035(this, x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, false);
            x_stage3_stage3_6_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_6_Sl, [3 4 2 1], 4);
            x_stage3_stage3_6_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_6_61, [3 4 2 1], 4);

            x_stage3_stage3_6_Sl = dlarray(single(x_stage3_stage3_6_Sl), 'SSCB');
            x_stage3_stage3_6_61 = dlarray(single(x_stage3_stage3_6_61), 'SSCB');
        end

        function [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61] = forward(this, x_stage3_stage3_5__6)
            if isdlarray(x_stage3_stage3_5__6)
                x_stage3_stage3_5__6 = stripdims(x_stage3_stage3_5__6);
            end
            x_stage3_stage3_5__6NumDims = 4;
            x_stage3_stage3_5__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_5__6, [4 3 1 2], 4);

            [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61, x_stage3_stage3_6_SlNumDims, x_stage3_stage3_6_61NumDims] = Shape_To_SliceGraph1035(this, x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, true);
            x_stage3_stage3_6_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_6_Sl, [3 4 2 1], 4);
            x_stage3_stage3_6_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_6_61, [3 4 2 1], 4);

            x_stage3_stage3_6_Sl = dlarray(single(x_stage3_stage3_6_Sl), 'SSCB');
            x_stage3_stage3_6_61 = dlarray(single(x_stage3_stage3_6_61), 'SSCB');
        end

        function [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61, x_stage3_stage3_6_SlNumDims1037, x_stage3_stage3_6_61NumDims1038] = Shape_To_SliceGraph1035(this, x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_5_Sh, x_stage3_stage3_5_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, 0, x_stage3_stage3_5__6NumDims+1);

            % Gather:
            [x_stage3_stage3_5_Ga, x_stage3_stage3_5_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_5_Sh, this.Vars.x_stage3_stage3_5_14, 0, x_stage3_stage3_5_ShNumDims, this.NumDims.x_stage3_stage3_5_14);

            % Shape:
            [x_stage3_stage3_5_52, x_stage3_stage3_5_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, 0, x_stage3_stage3_5__6NumDims+1);

            % Gather:
            [x_stage3_stage3_5_37, x_stage3_stage3_5_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_5_52, this.Vars.x_stage3_stage3_5_15, 0, x_stage3_stage3_5_52NumDims, this.NumDims.x_stage3_stage3_5_15);

            % Shape:
            [x_stage3_stage3_5_53, x_stage3_stage3_5_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, 0, x_stage3_stage3_5__6NumDims+1);

            % Gather:
            [x_stage3_stage3_5_38, x_stage3_stage3_5_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_5_53, this.Vars.x_stage3_stage3_5_16, 0, x_stage3_stage3_5_53NumDims, this.NumDims.x_stage3_stage3_5_16);

            % Shape:
            [x_stage3_stage3_5_54, x_stage3_stage3_5_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, 0, x_stage3_stage3_5__6NumDims+1);

            % Gather:
            [x_stage3_stage3_5_39, x_stage3_stage3_5_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_5_54, this.Vars.x_stage3_stage3_5_17, 0, x_stage3_stage3_5_54NumDims, this.NumDims.x_stage3_stage3_5_17);

            % Div:
            x_stage3_stage3_5_Di = fix(x_stage3_stage3_5_37 ./ this.Vars.x_stage3_stage3_5__7);
            x_stage3_stage3_5_DiNumDims = max(x_stage3_stage3_5_37NumDims, this.NumDims.x_stage3_stage3_5__7);

            % Cast:
            x_stage3_stage3_5__2 = cast(int64(extractdata(x_stage3_stage3_5_Di)), 'like', x_stage3_stage3_5_Di);
            x_stage3_stage3_5__2NumDims = x_stage3_stage3_5_DiNumDims;

            % Cast:
            x_stage3_stage3_5_Ca = cast(int64(extractdata(x_stage3_stage3_5__2)), 'like', x_stage3_stage3_5__2);
            x_stage3_stage3_5_CaNumDims = x_stage3_stage3_5__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_5_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ga, this.Vars.onnx__Unsqueeze_923, x_stage3_stage3_5_GaNumDims);
            x_stage3_stage3_5_71 = reshape(x_stage3_stage3_5_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ca, this.Vars.onnx__Unsqueeze_927, x_stage3_stage3_5_CaNumDims);
            x_stage3_stage3_5_Un = reshape(x_stage3_stage3_5_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_38, this.Vars.onnx__Unsqueeze_929, x_stage3_stage3_5_38NumDims);
            x_stage3_stage3_5_65 = reshape(x_stage3_stage3_5_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_39, this.Vars.onnx__Unsqueeze_931, x_stage3_stage3_5_39NumDims);
            x_stage3_stage3_5_66 = reshape(x_stage3_stage3_5_39, shape);

            % Concat:
            [x_stage3_stage3_5_Co, x_stage3_stage3_5_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_5_71, this.Vars.x_stage3_stage3_5__8, x_stage3_stage3_5_Un, x_stage3_stage3_5_65, x_stage3_stage3_5_66}, [x_stage3_stage3_5_71NumDims, this.NumDims.x_stage3_stage3_5__8, x_stage3_stage3_5_UnNumDims, x_stage3_stage3_5_65NumDims, x_stage3_stage3_5_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_5_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_5__6, x_stage3_stage3_5_Co, x_stage3_stage3_5__6NumDims, 0);
            x_stage3_stage3_5_49 = reshape(x_stage3_stage3_5__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_5_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1036, x_stage3_stage3_5_49NumDims);
            if isempty(perm)
                x_stage3_stage3_5_Tr = x_stage3_stage3_5_49;
            else
                x_stage3_stage3_5_Tr = permute(x_stage3_stage3_5_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_5_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ga, this.Vars.onnx__Unsqueeze_936, x_stage3_stage3_5_GaNumDims);
            x_stage3_stage3_5_67 = reshape(x_stage3_stage3_5_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_37, this.Vars.onnx__Unsqueeze_938, x_stage3_stage3_5_37NumDims);
            x_stage3_stage3_5_68 = reshape(x_stage3_stage3_5_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_38, this.Vars.onnx__Unsqueeze_940, x_stage3_stage3_5_38NumDims);
            x_stage3_stage3_5_69 = reshape(x_stage3_stage3_5_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_5_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_39, this.Vars.onnx__Unsqueeze_942, x_stage3_stage3_5_39NumDims);
            x_stage3_stage3_5_70 = reshape(x_stage3_stage3_5_39, shape);

            % Concat:
            [x_stage3_stage3_5__5, x_stage3_stage3_5__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_5_67, x_stage3_stage3_5_68, x_stage3_stage3_5_69, x_stage3_stage3_5_70}, [x_stage3_stage3_5_67NumDims, x_stage3_stage3_5_68NumDims, x_stage3_stage3_5_69NumDims, x_stage3_stage3_5_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_5_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_5_Tr, x_stage3_stage3_5__5, x_stage3_stage3_5_TrNumDims, 0);
            x_stage3_stage3_5_Re = reshape(x_stage3_stage3_5_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_6_55, x_stage3_stage3_6_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_5_Re, x_stage3_stage3_5_ReNumDims, 0, x_stage3_stage3_5_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_6_40, x_stage3_stage3_6_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_6_55, this.Vars.x_stage3_stage3_6_18, 0, x_stage3_stage3_6_55NumDims, this.NumDims.x_stage3_stage3_6_18);

            % Add:
            x_stage3_stage3_6_Ad = x_stage3_stage3_6_40 + this.Vars.x_stage3_stage3_6_10;
            x_stage3_stage3_6_AdNumDims = max(x_stage3_stage3_6_40NumDims, this.NumDims.x_stage3_stage3_6_10);

            % Div:
            x_stage3_stage3_6_34 = fix(x_stage3_stage3_6_Ad ./ this.Vars.x_stage3_stage3_6_11);
            x_stage3_stage3_6_34NumDims = max(x_stage3_stage3_6_AdNumDims, this.NumDims.x_stage3_stage3_6_11);

            % Mul:
            x_stage3_stage3_6_46 = x_stage3_stage3_6_34 .* this.Vars.x_stage3_stage3_6_12;
            x_stage3_stage3_6_46NumDims = max(x_stage3_stage3_6_34NumDims, this.NumDims.x_stage3_stage3_6_12);

            % Slice:
            [Indices, x_stage3_stage3_6_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_5_Re, this.Vars.x_stage3_stage3_6__9, x_stage3_stage3_6_46, this.Vars.x_stage3_stage3_6_18, '', x_stage3_stage3_5_ReNumDims);
            x_stage3_stage3_6_61 = x_stage3_stage3_5_Re(Indices{:});

            % Mul:
            x_stage3_stage3_6_Mu = x_stage3_stage3_6_34 .* this.Vars.x_stage3_stage3_6_13;
            x_stage3_stage3_6_MuNumDims = max(x_stage3_stage3_6_34NumDims, this.NumDims.x_stage3_stage3_6_13);

            % Slice:
            [Indices, x_stage3_stage3_6_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_5_Re, x_stage3_stage3_6_46, x_stage3_stage3_6_Mu, this.Vars.x_stage3_stage3_6_18, '', x_stage3_stage3_5_ReNumDims);
            x_stage3_stage3_6_Sl = x_stage3_stage3_5_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_6_SlNumDims1037 = x_stage3_stage3_6_SlNumDims;
            x_stage3_stage3_6_61NumDims1038 = x_stage3_stage3_6_61NumDims;

        end

    end

end