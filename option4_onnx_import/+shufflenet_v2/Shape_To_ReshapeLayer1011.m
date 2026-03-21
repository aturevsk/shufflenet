classdef Shape_To_ReshapeLayer1011 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.Shape_To_ReshapeLayer1011';
        end
    end


    methods
        function this = Shape_To_ReshapeLayer1011(name)
            this.Name = name;
            this.OutputNames = {'x_stage3_stage3_7_Re'};
        end

        function [x_stage3_stage3_7_Re] = predict(this, x_stage3_stage3_7__6)
            if isdlarray(x_stage3_stage3_7__6)
                x_stage3_stage3_7__6 = stripdims(x_stage3_stage3_7__6);
            end
            x_stage3_stage3_7__6NumDims = 4;
            x_stage3_stage3_7__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_7__6, [4 3 1 2], 4);

            [x_stage3_stage3_7_Re, x_stage3_stage3_7_ReNumDims] = Shape_To_ReshapeGraph1043(this, x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, false);
            x_stage3_stage3_7_Re = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_Re, [3 4 2 1], 4);

            x_stage3_stage3_7_Re = dlarray(single(x_stage3_stage3_7_Re), 'SSCB');
        end

        function [x_stage3_stage3_7_Re] = forward(this, x_stage3_stage3_7__6)
            if isdlarray(x_stage3_stage3_7__6)
                x_stage3_stage3_7__6 = stripdims(x_stage3_stage3_7__6);
            end
            x_stage3_stage3_7__6NumDims = 4;
            x_stage3_stage3_7__6 = shufflenet_v2.ops.permuteInputVar(x_stage3_stage3_7__6, [4 3 1 2], 4);

            [x_stage3_stage3_7_Re, x_stage3_stage3_7_ReNumDims] = Shape_To_ReshapeGraph1043(this, x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, true);
            x_stage3_stage3_7_Re = shufflenet_v2.ops.permuteOutputVar(x_stage3_stage3_7_Re, [3 4 2 1], 4);

            x_stage3_stage3_7_Re = dlarray(single(x_stage3_stage3_7_Re), 'SSCB');
        end

        function [x_stage3_stage3_7_Re, x_stage3_stage3_7_ReNumDims1045] = Shape_To_ReshapeGraph1043(this, x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_7_Sh, x_stage3_stage3_7_ShNumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, 0, x_stage3_stage3_7__6NumDims+1);

            % Gather:
            [x_stage3_stage3_7_Ga, x_stage3_stage3_7_GaNumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_7_Sh, this.Vars.x_stage3_stage3_7_14, 0, x_stage3_stage3_7_ShNumDims, this.NumDims.x_stage3_stage3_7_14);

            % Shape:
            [x_stage3_stage3_7_52, x_stage3_stage3_7_52NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, 0, x_stage3_stage3_7__6NumDims+1);

            % Gather:
            [x_stage3_stage3_7_37, x_stage3_stage3_7_37NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_7_52, this.Vars.x_stage3_stage3_7_15, 0, x_stage3_stage3_7_52NumDims, this.NumDims.x_stage3_stage3_7_15);

            % Shape:
            [x_stage3_stage3_7_53, x_stage3_stage3_7_53NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, 0, x_stage3_stage3_7__6NumDims+1);

            % Gather:
            [x_stage3_stage3_7_38, x_stage3_stage3_7_38NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_7_53, this.Vars.x_stage3_stage3_7_16, 0, x_stage3_stage3_7_53NumDims, this.NumDims.x_stage3_stage3_7_16);

            % Shape:
            [x_stage3_stage3_7_54, x_stage3_stage3_7_54NumDims] = shufflenet_v2.ops.onnxShape(x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, 0, x_stage3_stage3_7__6NumDims+1);

            % Gather:
            [x_stage3_stage3_7_39, x_stage3_stage3_7_39NumDims] = shufflenet_v2.ops.onnxGather(x_stage3_stage3_7_54, this.Vars.x_stage3_stage3_7_17, 0, x_stage3_stage3_7_54NumDims, this.NumDims.x_stage3_stage3_7_17);

            % Div:
            x_stage3_stage3_7_Di = fix(x_stage3_stage3_7_37 ./ this.Vars.x_stage3_stage3_7__7);
            x_stage3_stage3_7_DiNumDims = max(x_stage3_stage3_7_37NumDims, this.NumDims.x_stage3_stage3_7__7);

            % Cast:
            x_stage3_stage3_7__2 = cast(int64(extractdata(x_stage3_stage3_7_Di)), 'like', x_stage3_stage3_7_Di);
            x_stage3_stage3_7__2NumDims = x_stage3_stage3_7_DiNumDims;

            % Cast:
            x_stage3_stage3_7_Ca = cast(int64(extractdata(x_stage3_stage3_7__2)), 'like', x_stage3_stage3_7__2);
            x_stage3_stage3_7_CaNumDims = x_stage3_stage3_7__2NumDims;

            % Unsqueeze:
            [shape, x_stage3_stage3_7_71NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ga, this.Vars.onnx__Unsqueeze_1047, x_stage3_stage3_7_GaNumDims);
            x_stage3_stage3_7_71 = reshape(x_stage3_stage3_7_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_UnNumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ca, this.Vars.onnx__Unsqueeze_1051, x_stage3_stage3_7_CaNumDims);
            x_stage3_stage3_7_Un = reshape(x_stage3_stage3_7_Ca, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_65NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_38, this.Vars.onnx__Unsqueeze_1053, x_stage3_stage3_7_38NumDims);
            x_stage3_stage3_7_65 = reshape(x_stage3_stage3_7_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_66NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_39, this.Vars.onnx__Unsqueeze_1055, x_stage3_stage3_7_39NumDims);
            x_stage3_stage3_7_66 = reshape(x_stage3_stage3_7_39, shape);

            % Concat:
            [x_stage3_stage3_7_Co, x_stage3_stage3_7_CoNumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_7_71, this.Vars.x_stage3_stage3_7__8, x_stage3_stage3_7_Un, x_stage3_stage3_7_65, x_stage3_stage3_7_66}, [x_stage3_stage3_7_71NumDims, this.NumDims.x_stage3_stage3_7__8, x_stage3_stage3_7_UnNumDims, x_stage3_stage3_7_65NumDims, x_stage3_stage3_7_66NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_7_49NumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_7__6, x_stage3_stage3_7_Co, x_stage3_stage3_7__6NumDims, 0);
            x_stage3_stage3_7_49 = reshape(x_stage3_stage3_7__6, shape{:});

            % Transpose:
            [perm, x_stage3_stage3_7_TrNumDims] = shufflenet_v2.ops.prepareTransposeArgs(this.Vars.TransposePerm1044, x_stage3_stage3_7_49NumDims);
            if isempty(perm)
                x_stage3_stage3_7_Tr = x_stage3_stage3_7_49;
            else
                x_stage3_stage3_7_Tr = permute(x_stage3_stage3_7_49, perm);
            end

            % Unsqueeze:
            [shape, x_stage3_stage3_7_67NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ga, this.Vars.onnx__Unsqueeze_1060, x_stage3_stage3_7_GaNumDims);
            x_stage3_stage3_7_67 = reshape(x_stage3_stage3_7_Ga, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_68NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_37, this.Vars.onnx__Unsqueeze_1062, x_stage3_stage3_7_37NumDims);
            x_stage3_stage3_7_68 = reshape(x_stage3_stage3_7_37, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_69NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_38, this.Vars.onnx__Unsqueeze_1064, x_stage3_stage3_7_38NumDims);
            x_stage3_stage3_7_69 = reshape(x_stage3_stage3_7_38, shape);

            % Unsqueeze:
            [shape, x_stage3_stage3_7_70NumDims] = shufflenet_v2.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_39, this.Vars.onnx__Unsqueeze_1066, x_stage3_stage3_7_39NumDims);
            x_stage3_stage3_7_70 = reshape(x_stage3_stage3_7_39, shape);

            % Concat:
            [x_stage3_stage3_7__5, x_stage3_stage3_7__5NumDims] = shufflenet_v2.ops.onnxConcat(0, {x_stage3_stage3_7_67, x_stage3_stage3_7_68, x_stage3_stage3_7_69, x_stage3_stage3_7_70}, [x_stage3_stage3_7_67NumDims, x_stage3_stage3_7_68NumDims, x_stage3_stage3_7_69NumDims, x_stage3_stage3_7_70NumDims]);

            % Reshape:
            [shape, x_stage3_stage3_7_ReNumDims] = shufflenet_v2.ops.prepareReshapeArgs(x_stage3_stage3_7_Tr, x_stage3_stage3_7__5, x_stage3_stage3_7_TrNumDims, 0);
            x_stage3_stage3_7_Re = reshape(x_stage3_stage3_7_Tr, shape{:});

            % Set graph output arguments
            x_stage3_stage3_7_ReNumDims1045 = x_stage3_stage3_7_ReNumDims;

        end

    end

end