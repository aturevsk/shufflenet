classdef Shape_To_SliceLayer1008 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1008';
        end
    end


    methods
        function this = Shape_To_SliceLayer1008(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_5_Sl', 'x_stage3_stage3_5_61'};
        end

        function [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61] = predict(this, x_stage3_stage3_4__6)
            if isdlarray(x_stage3_stage3_4__6)
                x_stage3_stage3_4__6 = stripdims(x_stage3_stage3_4__6);
            end
            x_stage3_stage3_4__6NumDims = 4;
            x_stage3_stage3_4__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_4__6, [4 3 1 2], 4);

            [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61, x_stage3_stage3_5_SlNumDims, x_stage3_stage3_5_61NumDims] = Shape_To_SliceGraph1031(this, x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, false);
            x_stage3_stage3_5_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_5_Sl, [3 4 2 1], 4);
            x_stage3_stage3_5_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_5_61, [3 4 2 1], 4);

            x_stage3_stage3_5_Sl = dlarray(single(x_stage3_stage3_5_Sl), 'SSCB');
            x_stage3_stage3_5_61 = dlarray(single(x_stage3_stage3_5_61), 'SSCB');
        end

        function [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61] = forward(this, x_stage3_stage3_4__6)
            if isdlarray(x_stage3_stage3_4__6)
                x_stage3_stage3_4__6 = stripdims(x_stage3_stage3_4__6);
            end
            x_stage3_stage3_4__6NumDims = 4;
            x_stage3_stage3_4__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_4__6, [4 3 1 2], 4);

            [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61, x_stage3_stage3_5_SlNumDims, x_stage3_stage3_5_61NumDims] = Shape_To_SliceGraph1031(this, x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, true);
            x_stage3_stage3_5_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_5_Sl, [3 4 2 1], 4);
            x_stage3_stage3_5_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_5_61, [3 4 2 1], 4);

            x_stage3_stage3_5_Sl = dlarray(single(x_stage3_stage3_5_Sl), 'SSCB');
            x_stage3_stage3_5_61 = dlarray(single(x_stage3_stage3_5_61), 'SSCB');
        end

        function [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61, x_stage3_stage3_5_SlNumDims1033, x_stage3_stage3_5_61NumDims1034] = Shape_To_SliceGraph1031(this, x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_4_Sh, x_stage3_stage3_4_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, 0, x_stage3_stage3_4__6NumDims+1);

            % Gather:
            [x_stage3_stage3_4_Ga, x_stage3_stage3_4_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_4_Sh, this.Vars.x_stage3_stage3_4_14, 0, x_stage3_stage3_4_ShNumDims, this.NumDims.x_stage3_stage3_4_14);

            % Shape:
            [x_stage3_stage3_4_52, x_stage3_stage3_4_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, 0, x_stage3_stage3_4__6NumDims+1);

            % Gather:
            [x_stage3_stage3_4_37, x_stage3_stage3_4_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_4_52, this.Vars.x_stage3_stage3_4_15, 0, x_stage3_stage3_4_52NumDims, this.NumDims.x_stage3_stage3_4_15);

            % Shape:
            [x_stage3_stage3_4_53, x_stage3_stage3_4_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, 0, x_stage3_stage3_4__6NumDims+1);

            % Gather:
            [x_stage3_stage3_4_38, x_stage3_stage3_4_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_4_53, this.Vars.x_stage3_stage3_4_16, 0, x_stage3_stage3_4_53NumDims, this.NumDims.x_stage3_stage3_4_16);

            % Shape:
            [x_stage3_stage3_4_54, x_stage3_stage3_4_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, 0, x_stage3_stage3_4__6NumDims+1);

            % Gather:
            [x_stage3_stage3_4_39, x_stage3_stage3_4_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_4_54, this.Vars.x_stage3_stage3_4_17, 0, x_stage3_stage3_4_54NumDims, this.NumDims.x_stage3_stage3_4_17);

            % Div:
            x_stage3_stage3_4_Di = fix(x_stage3_stage3_4_37 ./ this.Vars.x_stage3_stage3_4__7);
            x_stage3_stage3_4_DiNumDims = max(x_stage3_stage3_4_37NumDims, this.NumDims.x_stage3_stage3_4__7);

            % Cast:
            x_stage3_stage3_4__2 = cast(int64(extractdata(x_stage3_stage3_4_Di)), 'like', x_stage3_stage3_4_Di);
            x_stage3_stage3_4__2NumDims = x_stage3_stage3_4_DiNumDims;

            % Cast:
            x_stage3_stage3_4_Ca = cast(int64(extractdata(x_stage3_stage3_4__2)), 'like', x_stage3_stage3_4__2);
            x_stage3_stage3_4_CaNumDims = x_stage3_stage3_4__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_4_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ga, this.Vars.onnx__Unsqueeze_861, x_stage3_stage3_4_GaNumDims);
            x_stage3_stage3_4_71 = reshape(x_stage3_stage3_4_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ca, this.Vars.onnx__Unsqueeze_865, x_stage3_stage3_4_CaNumDims);
            x_stage3_stage3_4_Un = reshape(x_stage3_stage3_4_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_38, this.Vars.onnx__Unsqueeze_867, x_stage3_stage3_4_38NumDims);
            x_stage3_stage3_4_65 = reshape(x_stage3_stage3_4_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_39, this.Vars.onnx__Unsqueeze_869, x_stage3_stage3_4_39NumDims);
            x_stage3_stage3_4_66 = reshape(x_stage3_stage3_4_39, shape);

            % Concat:
            [x_stage3_stage3_4_Co, x_stage3_stage3_4_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_4_71, this.Vars.x_stage3_stage3_4__8, x_stage3_stage3_4_Un, x_stage3_stage3_4_65, x_stage3_stage3_4_66}, [x_stage3_stage3_4_71NumDims, this.NumDims.x_stage3_stage3_4__8, x_stage3_stage3_4_UnNumDims, x_stage3_stage3_4_65NumDims, x_stage3_stage3_4_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_4_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_4__6, x_stage3_stage3_4_Co, x_stage3_stage3_4__6NumDims, 0);
            x_stage3_stage3_4_49 = reshape(x_stage3_stage3_4__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_4_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1032, x_stage3_stage3_4_49NumDims);
            if isempty(perm)
                x_stage3_stage3_4_Tr = x_stage3_stage3_4_49;
            else
                x_stage3_stage3_4_Tr = permute(x_stage3_stage3_4_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_4_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ga, this.Vars.onnx__Unsqueeze_874, x_stage3_stage3_4_GaNumDims);
            x_stage3_stage3_4_67 = reshape(x_stage3_stage3_4_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_37, this.Vars.onnx__Unsqueeze_876, x_stage3_stage3_4_37NumDims);
            x_stage3_stage3_4_68 = reshape(x_stage3_stage3_4_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_38, this.Vars.onnx__Unsqueeze_878, x_stage3_stage3_4_38NumDims);
            x_stage3_stage3_4_69 = reshape(x_stage3_stage3_4_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_4_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_39, this.Vars.onnx__Unsqueeze_880, x_stage3_stage3_4_39NumDims);
            x_stage3_stage3_4_70 = reshape(x_stage3_stage3_4_39, shape);

            % Concat:
            [x_stage3_stage3_4__5, x_stage3_stage3_4__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_4_67, x_stage3_stage3_4_68, x_stage3_stage3_4_69, x_stage3_stage3_4_70}, [x_stage3_stage3_4_67NumDims, x_stage3_stage3_4_68NumDims, x_stage3_stage3_4_69NumDims, x_stage3_stage3_4_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_4_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_4_Tr, x_stage3_stage3_4__5, x_stage3_stage3_4_TrNumDims, 0);
            x_stage3_stage3_4_Re = reshape(x_stage3_stage3_4_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_5_55, x_stage3_stage3_5_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_4_Re, x_stage3_stage3_4_ReNumDims, 0, x_stage3_stage3_4_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_5_40, x_stage3_stage3_5_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_5_55, this.Vars.x_stage3_stage3_5_18, 0, x_stage3_stage3_5_55NumDims, this.NumDims.x_stage3_stage3_5_18);

            % Add:
            x_stage3_stage3_5_Ad = x_stage3_stage3_5_40 + this.Vars.x_stage3_stage3_5_10;
            x_stage3_stage3_5_AdNumDims = max(x_stage3_stage3_5_40NumDims, this.NumDims.x_stage3_stage3_5_10);

            % Div:
            x_stage3_stage3_5_34 = fix(x_stage3_stage3_5_Ad ./ this.Vars.x_stage3_stage3_5_11);
            x_stage3_stage3_5_34NumDims = max(x_stage3_stage3_5_AdNumDims, this.NumDims.x_stage3_stage3_5_11);

            % Mul:
            x_stage3_stage3_5_46 = x_stage3_stage3_5_34 .* this.Vars.x_stage3_stage3_5_12;
            x_stage3_stage3_5_46NumDims = max(x_stage3_stage3_5_34NumDims, this.NumDims.x_stage3_stage3_5_12);

            % Slice:
            [Indices, x_stage3_stage3_5_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_4_Re, this.Vars.x_stage3_stage3_5__9, x_stage3_stage3_5_46, this.Vars.x_stage3_stage3_5_18, '', x_stage3_stage3_4_ReNumDims);
            x_stage3_stage3_5_61 = x_stage3_stage3_4_Re(Indices{:});

            % Mul:
            x_stage3_stage3_5_Mu = x_stage3_stage3_5_34 .* this.Vars.x_stage3_stage3_5_13;
            x_stage3_stage3_5_MuNumDims = max(x_stage3_stage3_5_34NumDims, this.NumDims.x_stage3_stage3_5_13);

            % Slice:
            [Indices, x_stage3_stage3_5_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_4_Re, x_stage3_stage3_5_46, x_stage3_stage3_5_Mu, this.Vars.x_stage3_stage3_5_18, '', x_stage3_stage3_4_ReNumDims);
            x_stage3_stage3_5_Sl = x_stage3_stage3_4_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_5_SlNumDims1033 = x_stage3_stage3_5_SlNumDims;
            x_stage3_stage3_5_61NumDims1034 = x_stage3_stage3_5_61NumDims;

        end

    end

end