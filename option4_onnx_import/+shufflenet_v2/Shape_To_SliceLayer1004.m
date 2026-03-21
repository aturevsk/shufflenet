classdef Shape_To_SliceLayer1004 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_SliceLayer1004';
        end
    end


    methods
        function this = Shape_To_SliceLayer1004(name)
            this.Name = name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_1_Sl', 'x_stage3_stage3_1_61'};
        end

        function [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61] = predict(this, x_stage3_stage3_0__5)
            if isdlarray(x_stage3_stage3_0__5)
                x_stage3_stage3_0__5 = stripdims(x_stage3_stage3_0__5);
            end
            x_stage3_stage3_0__5NumDims = 4;
            x_stage3_stage3_0__5 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_0__5, [4 3 1 2], 4);

            [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61, x_stage3_stage3_1_SlNumDims, x_stage3_stage3_1_61NumDims] = Shape_To_SliceGraph1015(this, x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, false);
            x_stage3_stage3_1_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_1_Sl, [3 4 2 1], 4);
            x_stage3_stage3_1_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_1_61, [3 4 2 1], 4);

            x_stage3_stage3_1_Sl = dlarray(single(x_stage3_stage3_1_Sl), 'SSCB');
            x_stage3_stage3_1_61 = dlarray(single(x_stage3_stage3_1_61), 'SSCB');
        end

        function [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61] = forward(this, x_stage3_stage3_0__5)
            if isdlarray(x_stage3_stage3_0__5)
                x_stage3_stage3_0__5 = stripdims(x_stage3_stage3_0__5);
            end
            x_stage3_stage3_0__5NumDims = 4;
            x_stage3_stage3_0__5 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_0__5, [4 3 1 2], 4);

            [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61, x_stage3_stage3_1_SlNumDims, x_stage3_stage3_1_61NumDims] = Shape_To_SliceGraph1015(this, x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, true);
            x_stage3_stage3_1_Sl = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_1_Sl, [3 4 2 1], 4);
            x_stage3_stage3_1_61 = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_1_61, [3 4 2 1], 4);

            x_stage3_stage3_1_Sl = dlarray(single(x_stage3_stage3_1_Sl), 'SSCB');
            x_stage3_stage3_1_61 = dlarray(single(x_stage3_stage3_1_61), 'SSCB');
        end

        function [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61, x_stage3_stage3_1_SlNumDims1017, x_stage3_stage3_1_61NumDims1018] = Shape_To_SliceGraph1015(this, x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_0_34, x_stage3_stage3_0_34NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, 0, x_stage3_stage3_0__5NumDims+1);

            % Gather:
            [x_stage3_stage3_0_24, x_stage3_stage3_0_24NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_0_34, this.Vars.x_stage3_stage3_0_11, 0, x_stage3_stage3_0_34NumDims, this.NumDims.x_stage3_stage3_0_11);

            % Shape:
            [x_stage3_stage3_0_Sh, x_stage3_stage3_0_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, 0, x_stage3_stage3_0__5NumDims+1);

            % Gather:
            [x_stage3_stage3_0_Ga, x_stage3_stage3_0_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_0_Sh, this.Vars.x_stage3_stage3_0__6, 0, x_stage3_stage3_0_ShNumDims, this.NumDims.x_stage3_stage3_0__6);

            % Shape:
            [x_stage3_stage3_0_32, x_stage3_stage3_0_32NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, 0, x_stage3_stage3_0__5NumDims+1);

            % Gather:
            [x_stage3_stage3_0_22, x_stage3_stage3_0_22NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_0_32, this.Vars.x_stage3_stage3_0__7, 0, x_stage3_stage3_0_32NumDims, this.NumDims.x_stage3_stage3_0__7);

            % Shape:
            [x_stage3_stage3_0_33, x_stage3_stage3_0_33NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, 0, x_stage3_stage3_0__5NumDims+1);

            % Gather:
            [x_stage3_stage3_0_23, x_stage3_stage3_0_23NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_0_33, this.Vars.x_stage3_stage3_0__8, 0, x_stage3_stage3_0_33NumDims, this.NumDims.x_stage3_stage3_0__8);

            % Div:
            x_stage3_stage3_0_Di = fix(x_stage3_stage3_0_Ga ./ this.Vars.x_stage3_stage3_0__9);
            x_stage3_stage3_0_DiNumDims = max(x_stage3_stage3_0_GaNumDims, this.NumDims.x_stage3_stage3_0__9);

            % Cast:
            x_stage3_stage3_0__1 = cast(int64(extractdata(x_stage3_stage3_0_Di)), 'like', x_stage3_stage3_0_Di);
            x_stage3_stage3_0__1NumDims = x_stage3_stage3_0_DiNumDims;

            % Cast:
            x_stage3_stage3_0_Ca = cast(int64(extractdata(x_stage3_stage3_0__1)), 'like', x_stage3_stage3_0__1);
            x_stage3_stage3_0_CaNumDims = x_stage3_stage3_0__1NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_0_46NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_24, this.Vars.onnx__Unsqueeze_613, x_stage3_stage3_0_24NumDims);
            x_stage3_stage3_0_46 = reshape(x_stage3_stage3_0_24, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_Ca, this.Vars.onnx__Unsqueeze_617, x_stage3_stage3_0_CaNumDims);
            x_stage3_stage3_0_Un = reshape(x_stage3_stage3_0_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_40NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_22, this.Vars.onnx__Unsqueeze_619, x_stage3_stage3_0_22NumDims);
            x_stage3_stage3_0_40 = reshape(x_stage3_stage3_0_22, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_41NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_23, this.Vars.onnx__Unsqueeze_621, x_stage3_stage3_0_23NumDims);
            x_stage3_stage3_0_41 = reshape(x_stage3_stage3_0_23, shape);

            % Concat:
            [x_stage3_stage3_0_Co, x_stage3_stage3_0_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_0_46, this.Vars.x_stage3_stage3_0_10, x_stage3_stage3_0_Un, x_stage3_stage3_0_40, x_stage3_stage3_0_41}, [x_stage3_stage3_0_46NumDims, this.NumDims.x_stage3_stage3_0_10, x_stage3_stage3_0_UnNumDims, x_stage3_stage3_0_40NumDims, x_stage3_stage3_0_41NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_0_29NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_0__5, x_stage3_stage3_0_Co, x_stage3_stage3_0__5NumDims, 0);
            x_stage3_stage3_0_29 = reshape(x_stage3_stage3_0__5, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_0_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1016, x_stage3_stage3_0_29NumDims);
            if isempty(perm)
                x_stage3_stage3_0_Tr = x_stage3_stage3_0_29;
            else
                x_stage3_stage3_0_Tr = permute(x_stage3_stage3_0_29, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_0_42NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_24, this.Vars.onnx__Unsqueeze_626, x_stage3_stage3_0_24NumDims);
            x_stage3_stage3_0_42 = reshape(x_stage3_stage3_0_24, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_43NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_Ga, this.Vars.onnx__Unsqueeze_628, x_stage3_stage3_0_GaNumDims);
            x_stage3_stage3_0_43 = reshape(x_stage3_stage3_0_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_44NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_22, this.Vars.onnx__Unsqueeze_630, x_stage3_stage3_0_22NumDims);
            x_stage3_stage3_0_44 = reshape(x_stage3_stage3_0_22, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_0_45NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_23, this.Vars.onnx__Unsqueeze_632, x_stage3_stage3_0_23NumDims);
            x_stage3_stage3_0_45 = reshape(x_stage3_stage3_0_23, shape);

            % Concat:
            [x_stage3_stage3_0__4, x_stage3_stage3_0__4NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_0_42, x_stage3_stage3_0_43, x_stage3_stage3_0_44, x_stage3_stage3_0_45}, [x_stage3_stage3_0_42NumDims, x_stage3_stage3_0_43NumDims, x_stage3_stage3_0_44NumDims, x_stage3_stage3_0_45NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_0_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_0_Tr, x_stage3_stage3_0__4, x_stage3_stage3_0_TrNumDims, 0);
            x_stage3_stage3_0_Re = reshape(x_stage3_stage3_0_Tr, shape{:});

            % Shape:
            [x_stage3_stage3_1_55, x_stage3_stage3_1_55NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_0_Re, x_stage3_stage3_0_ReNumDims, 0, x_stage3_stage3_0_ReNumDims+1);

            % Gather:
            [x_stage3_stage3_1_40, x_stage3_stage3_1_40NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_1_55, this.Vars.x_stage3_stage3_1_18, 0, x_stage3_stage3_1_55NumDims, this.NumDims.x_stage3_stage3_1_18);

            % Add:
            x_stage3_stage3_1_Ad = x_stage3_stage3_1_40 + this.Vars.x_stage3_stage3_1_10;
            x_stage3_stage3_1_AdNumDims = max(x_stage3_stage3_1_40NumDims, this.NumDims.x_stage3_stage3_1_10);

            % Div:
            x_stage3_stage3_1_34 = fix(x_stage3_stage3_1_Ad ./ this.Vars.x_stage3_stage3_1_11);
            x_stage3_stage3_1_34NumDims = max(x_stage3_stage3_1_AdNumDims, this.NumDims.x_stage3_stage3_1_11);

            % Mul:
            x_stage3_stage3_1_46 = x_stage3_stage3_1_34 .* this.Vars.x_stage3_stage3_1_12;
            x_stage3_stage3_1_46NumDims = max(x_stage3_stage3_1_34NumDims, this.NumDims.x_stage3_stage3_1_12);

            % Slice:
            [Indices, x_stage3_stage3_1_61NumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_0_Re, this.Vars.x_stage3_stage3_1__9, x_stage3_stage3_1_46, this.Vars.x_stage3_stage3_1_18, '', x_stage3_stage3_0_ReNumDims);
            x_stage3_stage3_1_61 = x_stage3_stage3_0_Re(Indices{:});

            % Mul:
            x_stage3_stage3_1_Mu = x_stage3_stage3_1_34 .* this.Vars.x_stage3_stage3_1_13;
            x_stage3_stage3_1_MuNumDims = max(x_stage3_stage3_1_34NumDims, this.NumDims.x_stage3_stage3_1_13);

            % Slice:
            [Indices, x_stage3_stage3_1_SlNumDims] = shufflenet_v2.ops.prepareSliceArgs(x_stage3_stage3_0_Re, x_stage3_stage3_1_46, x_stage3_stage3_1_Mu, this.Vars.x_stage3_stage3_1_18, '', x_stage3_stage3_0_ReNumDims);
            x_stage3_stage3_1_Sl = x_stage3_stage3_0_Re(Indices{:});

            % Set graph output arguments
            x_stage3_stage3_1_SlNumDims1017 = x_stage3_stage3_1_SlNumDims;
            x_stage3_stage3_1_61NumDims1018 = x_stage3_stage3_1_61NumDims;

        end

    end

end