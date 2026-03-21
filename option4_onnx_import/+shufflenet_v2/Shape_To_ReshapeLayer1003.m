classdef Shape_To_ReshapeLayer1003 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_ReshapeLayer1003';
        end
    end


    methods
        function this = Shape_To_ReshapeLayer1003(name)
            this.Name = name;
            this.OutputNames = {'x_stage2_stage2_3_Re'};
        end

        function [x_stage2_stage2_3_Re] = predict(this, x_stage2_stage2_3__6)
            if isdlarray(x_stage2_stage2_3__6)
                x_stage2_stage2_3__6 = stripdims(x_stage2_stage2_3__6);
            end
            x_stage2_stage2_3__6NumDims = 4;
            x_stage2_stage2_3__6 = shufflenet_v2.ops.permuteInputVar(x_stage2_stage2_3__6, [4 3 1 2], 4);

            [x_stage2_stage2_3_Re, x_stage2_stage2_3_ReNumDims] = Shape_To_ReshapeGraph1012(this, x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, false);
            x_stage2_stage2_3_Re = shufflenet_v2.ops.permuteOutputVar(x_stage2_stage2_3_Re, [3 4 2 1], 4);

            x_stage2_stage2_3_Re = dlarray(single(x_stage2_stage2_3_Re), 'SSCB');
        end

        function [x_stage2_stage2_3_Re] = forward(this, x_stage2_stage2_3__6)
            if isdlarray(x_stage2_stage2_3__6)
                x_stage2_stage2_3__6 = stripdims(x_stage2_stage2_3__6);
            end
            x_stage2_stage2_3__6NumDims = 4;
            x_stage2_stage2_3__6 = shufflenet_v2.ops.permuteInputVar(x_stage2_stage2_3__6, [4 3 1 2], 4);

            [x_stage2_stage2_3_Re, x_stage2_stage2_3_ReNumDims] = Shape_To_ReshapeGraph1012(this, x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, true);
            x_stage2_stage2_3_Re = shufflenet_v2.ops.permuteOutputVar(x_stage2_stage2_3_Re, [3 4 2 1], 4);

            x_stage2_stage2_3_Re = dlarray(single(x_stage2_stage2_3_Re), 'SSCB');
        end

        function [x_stage2_stage2_3_Re, x_stage2_stage2_3_ReNumDims1014] = Shape_To_ReshapeGraph1012(this, x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage2_stage2_3_Sh, x_stage2_stage2_3_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, 0, x_stage2_stage2_3__6NumDims+1);

            % Gather:
            [x_stage2_stage2_3_Ga, x_stage2_stage2_3_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage2_stage2_3_Sh, this.Vars.x_stage2_stage2_3_14, 0, x_stage2_stage2_3_ShNumDims, this.NumDims.x_stage2_stage2_3_14);

            % Shape:
            [x_stage2_stage2_3_52, x_stage2_stage2_3_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, 0, x_stage2_stage2_3__6NumDims+1);

            % Gather:
            [x_stage2_stage2_3_37, x_stage2_stage2_3_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage2_stage2_3_52, this.Vars.x_stage2_stage2_3_15, 0, x_stage2_stage2_3_52NumDims, this.NumDims.x_stage2_stage2_3_15);

            % Shape:
            [x_stage2_stage2_3_53, x_stage2_stage2_3_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, 0, x_stage2_stage2_3__6NumDims+1);

            % Gather:
            [x_stage2_stage2_3_38, x_stage2_stage2_3_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage2_stage2_3_53, this.Vars.x_stage2_stage2_3_16, 0, x_stage2_stage2_3_53NumDims, this.NumDims.x_stage2_stage2_3_16);

            % Shape:
            [x_stage2_stage2_3_54, x_stage2_stage2_3_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, 0, x_stage2_stage2_3__6NumDims+1);

            % Gather:
            [x_stage2_stage2_3_39, x_stage2_stage2_3_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage2_stage2_3_54, this.Vars.x_stage2_stage2_3_17, 0, x_stage2_stage2_3_54NumDims, this.NumDims.x_stage2_stage2_3_17);

            % Div:
            x_stage2_stage2_3_Di = fix(x_stage2_stage2_3_37 ./ this.Vars.x_stage2_stage2_3__7);
            x_stage2_stage2_3_DiNumDims = max(x_stage2_stage2_3_37NumDims, this.NumDims.x_stage2_stage2_3__7);

            % Cast:
            x_stage2_stage2_3__2 = cast(int64(extractdata(x_stage2_stage2_3_Di)), 'like', x_stage2_stage2_3_Di);
            x_stage2_stage2_3__2NumDims = x_stage2_stage2_3_DiNumDims;

            % Cast:
            x_stage2_stage2_3_Ca = cast(int64(extractdata(x_stage2_stage2_3__2)), 'like', x_stage2_stage2_3__2);
            x_stage2_stage2_3_CaNumDims = x_stage2_stage2_3__2NumDims;

            % Unsqueeze:
            [shape, x_stage2_stage2_3_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ga, this.Vars.onnx__Unsqueeze_560, x_stage2_stage2_3_GaNumDims);
            x_stage2_stage2_3_71 = reshape(x_stage2_stage2_3_Ga, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ca, this.Vars.onnx__Unsqueeze_564, x_stage2_stage2_3_CaNumDims);
            x_stage2_stage2_3_Un = reshape(x_stage2_stage2_3_Ca, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_38, this.Vars.onnx__Unsqueeze_566, x_stage2_stage2_3_38NumDims);
            x_stage2_stage2_3_65 = reshape(x_stage2_stage2_3_38, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_39, this.Vars.onnx__Unsqueeze_568, x_stage2_stage2_3_39NumDims);
            x_stage2_stage2_3_66 = reshape(x_stage2_stage2_3_39, shape);

            % Concat:
            [x_stage2_stage2_3_Co, x_stage2_stage2_3_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage2_stage2_3_71, this.Vars.x_stage2_stage2_3__8, x_stage2_stage2_3_Un, x_stage2_stage2_3_65, x_stage2_stage2_3_66}, [x_stage2_stage2_3_71NumDims, this.NumDims.x_stage2_stage2_3__8, x_stage2_stage2_3_UnNumDims, x_stage2_stage2_3_65NumDims, x_stage2_stage2_3_66NumDims]);

            % Reshape:
            [shape, x_stage2_stage2_3_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage2_stage2_3__6, x_stage2_stage2_3_Co, x_stage2_stage2_3__6NumDims, 0);
            x_stage2_stage2_3_49 = reshape(x_stage2_stage2_3__6, shape{:});

            % Transpose:
            [perm, x_stage2_stage2_3_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1013, x_stage2_stage2_3_49NumDims);
            if isempty(perm)
                x_stage2_stage2_3_Tr = x_stage2_stage2_3_49;
            else
                x_stage2_stage2_3_Tr = permute(x_stage2_stage2_3_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage2_stage2_3_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ga, this.Vars.onnx__Unsqueeze_573, x_stage2_stage2_3_GaNumDims);
            x_stage2_stage2_3_67 = reshape(x_stage2_stage2_3_Ga, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_37, this.Vars.onnx__Unsqueeze_575, x_stage2_stage2_3_37NumDims);
            x_stage2_stage2_3_68 = reshape(x_stage2_stage2_3_37, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_38, this.Vars.onnx__Unsqueeze_577, x_stage2_stage2_3_38NumDims);
            x_stage2_stage2_3_69 = reshape(x_stage2_stage2_3_38, shape);

            % Unsqueeze:
            [shape, x_stage2_stage2_3_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_39, this.Vars.onnx__Unsqueeze_579, x_stage2_stage2_3_39NumDims);
            x_stage2_stage2_3_70 = reshape(x_stage2_stage2_3_39, shape);

            % Concat:
            [x_stage2_stage2_3__5, x_stage2_stage2_3__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage2_stage2_3_67, x_stage2_stage2_3_68, x_stage2_stage2_3_69, x_stage2_stage2_3_70}, [x_stage2_stage2_3_67NumDims, x_stage2_stage2_3_68NumDims, x_stage2_stage2_3_69NumDims, x_stage2_stage2_3_70NumDims]);

            % Reshape:
            [shape, x_stage2_stage2_3_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage2_stage2_3_Tr, x_stage2_stage2_3__5, x_stage2_stage2_3_TrNumDims, 0);
            x_stage2_stage2_3_Re = reshape(x_stage2_stage2_3_Tr, shape{:});

            % Set graph output arguments
            x_stage2_stage2_3_ReNumDims1014 = x_stage2_stage2_3_ReNumDims;

        end

    end

end