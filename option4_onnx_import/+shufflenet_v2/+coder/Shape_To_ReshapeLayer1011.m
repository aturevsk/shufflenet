classdef Shape_To_ReshapeLayer1011 < nnet.layer.Layer & nnet.layer.Formattable
    % A custom layer auto-generated while importing an ONNX network.
    %#codegen

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
        % Specify the properties of the class that will not be modified
        % after the first assignment.
        function p = matlabCodegenNontunableProperties(~)
            p = {
                % Constants, i.e., Vars, NumDims and all learnables and states
                'Vars'
                'NumDims'
                };
        end
    end


    methods(Static, Hidden)
        % Instantiate a codegenable layer instance from a MATLAB layer instance
        function this_cg = matlabCodegenToRedirected(mlInstance)
            this_cg = shufflenet_v2.coder.Shape_To_ReshapeLayer1011(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_ReshapeLayer1011(cgInstance.Name);
            if isstruct(cgInstance.Vars)
                names = fieldnames(cgInstance.Vars);
                for i=1:numel(names)
                    fieldname = names{i};
                    this_ml.Vars.(fieldname) = dlarray(cgInstance.Vars.(fieldname));
                end
            else
                this_ml.Vars = [];
            end
            this_ml.NumDims = cgInstance.NumDims;
        end
    end

    methods
        function this = Shape_To_ReshapeLayer1011(mlInstance)
            this.Name = mlInstance.Name;
            this.OutputNames = {'x_stage3_stage3_7_Re'};
            if isstruct(mlInstance.Vars)
                names = fieldnames(mlInstance.Vars);
                for i=1:numel(names)
                    fieldname = names{i};
                    this.Vars.(fieldname) = shufflenet_v2.coder.ops.extractIfDlarray(mlInstance.Vars.(fieldname));
                end
            else
                this.Vars = [];
            end

            this.NumDims = mlInstance.NumDims;
        end

        function [x_stage3_stage3_7_Re] = predict(this, x_stage3_stage3_7__6__)
            if isdlarray(x_stage3_stage3_7__6__)
                x_stage3_stage3_7__6_ = stripdims(x_stage3_stage3_7__6__);
            else
                x_stage3_stage3_7__6_ = x_stage3_stage3_7__6__;
            end
            x_stage3_stage3_7__6NumDims = 4;
            x_stage3_stage3_7__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_7__6_, [4 3 1 2], 4);

            [x_stage3_stage3_7_Re__, x_stage3_stage3_7_ReNumDims__] = Shape_To_ReshapeGraph1043(this, x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, false);
            x_stage3_stage3_7_Re_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_7_Re__, [3 4 2 1], 4);

            x_stage3_stage3_7_Re = dlarray(single(x_stage3_stage3_7_Re_), 'SSCB');
        end

        function [x_stage3_stage3_7_Re, x_stage3_stage3_7_ReNumDims1045] = Shape_To_ReshapeGraph1043(this, x_stage3_stage3_7__6, x_stage3_stage3_7__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_7_Sh, x_stage3_stage3_7_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_7__6, coder.const(x_stage3_stage3_7__6NumDims), 0, coder.const(x_stage3_stage3_7__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_7_Ga, x_stage3_stage3_7_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_7_Sh, this.Vars.x_stage3_stage3_7_14, 0, coder.const(x_stage3_stage3_7_ShNumDims), this.NumDims.x_stage3_stage3_7_14);

            % Shape:
            [x_stage3_stage3_7_52, x_stage3_stage3_7_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_7__6, coder.const(x_stage3_stage3_7__6NumDims), 0, coder.const(x_stage3_stage3_7__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_7_37, x_stage3_stage3_7_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_7_52, this.Vars.x_stage3_stage3_7_15, 0, coder.const(x_stage3_stage3_7_52NumDims), this.NumDims.x_stage3_stage3_7_15);

            % Shape:
            [x_stage3_stage3_7_53, x_stage3_stage3_7_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_7__6, coder.const(x_stage3_stage3_7__6NumDims), 0, coder.const(x_stage3_stage3_7__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_7_38, x_stage3_stage3_7_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_7_53, this.Vars.x_stage3_stage3_7_16, 0, coder.const(x_stage3_stage3_7_53NumDims), this.NumDims.x_stage3_stage3_7_16);

            % Shape:
            [x_stage3_stage3_7_54, x_stage3_stage3_7_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_7__6, coder.const(x_stage3_stage3_7__6NumDims), 0, coder.const(x_stage3_stage3_7__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_7_39, x_stage3_stage3_7_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_7_54, this.Vars.x_stage3_stage3_7_17, 0, coder.const(x_stage3_stage3_7_54NumDims), this.NumDims.x_stage3_stage3_7_17);

            % Div:
            x_stage3_stage3_7_Di = fix(x_stage3_stage3_7_37 ./ this.Vars.x_stage3_stage3_7__7);
            x_stage3_stage3_7_DiNumDims = max(coder.const(x_stage3_stage3_7_37NumDims), this.NumDims.x_stage3_stage3_7__7);

            % Cast:
            x_stage3_stage3_7__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_7_Di)), 'like', x_stage3_stage3_7_Di);
            x_stage3_stage3_7__2NumDims = coder.const(x_stage3_stage3_7_DiNumDims);

            % Cast:
            x_stage3_stage3_7_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_7__2)), 'like', x_stage3_stage3_7__2);
            x_stage3_stage3_7_CaNumDims = coder.const(x_stage3_stage3_7__2NumDims);

            % Unsqueeze:
            [shape1141, x_stage3_stage3_7_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ga, this.Vars.onnx__Unsqueeze_1047, coder.const(x_stage3_stage3_7_GaNumDims));
            x_stage3_stage3_7_71 = reshape(x_stage3_stage3_7_Ga, shape1141);

            % Unsqueeze:
            [shape1142, x_stage3_stage3_7_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ca, this.Vars.onnx__Unsqueeze_1051, coder.const(x_stage3_stage3_7_CaNumDims));
            x_stage3_stage3_7_Un = reshape(x_stage3_stage3_7_Ca, shape1142);

            % Unsqueeze:
            [shape1143, x_stage3_stage3_7_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_38, this.Vars.onnx__Unsqueeze_1053, coder.const(x_stage3_stage3_7_38NumDims));
            x_stage3_stage3_7_65 = reshape(x_stage3_stage3_7_38, shape1143);

            % Unsqueeze:
            [shape1144, x_stage3_stage3_7_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_39, this.Vars.onnx__Unsqueeze_1055, coder.const(x_stage3_stage3_7_39NumDims));
            x_stage3_stage3_7_66 = reshape(x_stage3_stage3_7_39, shape1144);

            % Concat:
            [x_stage3_stage3_7_Co, x_stage3_stage3_7_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_7_71, this.Vars.x_stage3_stage3_7__8, x_stage3_stage3_7_Un, x_stage3_stage3_7_65, x_stage3_stage3_7_66}, [coder.const(x_stage3_stage3_7_71NumDims), this.NumDims.x_stage3_stage3_7__8, coder.const(x_stage3_stage3_7_UnNumDims), coder.const(x_stage3_stage3_7_65NumDims), coder.const(x_stage3_stage3_7_66NumDims)]);

            % Reshape:
            [shape1145, x_stage3_stage3_7_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_7__6, x_stage3_stage3_7_Co, coder.const(x_stage3_stage3_7__6NumDims), 0);
            x_stage3_stage3_7_49 = reshape(x_stage3_stage3_7__6, shape1145{:});

            % Transpose:
            [perm1146, x_stage3_stage3_7_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1044, coder.const(x_stage3_stage3_7_49NumDims));
            if isempty(perm1146)
                x_stage3_stage3_7_Tr = x_stage3_stage3_7_49;
            else
                x_stage3_stage3_7_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_7_49), perm1146);
            end

            % Unsqueeze:
            [shape1147, x_stage3_stage3_7_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_Ga, this.Vars.onnx__Unsqueeze_1060, coder.const(x_stage3_stage3_7_GaNumDims));
            x_stage3_stage3_7_67 = reshape(x_stage3_stage3_7_Ga, shape1147);

            % Unsqueeze:
            [shape1148, x_stage3_stage3_7_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_37, this.Vars.onnx__Unsqueeze_1062, coder.const(x_stage3_stage3_7_37NumDims));
            x_stage3_stage3_7_68 = reshape(x_stage3_stage3_7_37, shape1148);

            % Unsqueeze:
            [shape1149, x_stage3_stage3_7_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_38, this.Vars.onnx__Unsqueeze_1064, coder.const(x_stage3_stage3_7_38NumDims));
            x_stage3_stage3_7_69 = reshape(x_stage3_stage3_7_38, shape1149);

            % Unsqueeze:
            [shape1150, x_stage3_stage3_7_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_7_39, this.Vars.onnx__Unsqueeze_1066, coder.const(x_stage3_stage3_7_39NumDims));
            x_stage3_stage3_7_70 = reshape(x_stage3_stage3_7_39, shape1150);

            % Concat:
            [x_stage3_stage3_7__5, x_stage3_stage3_7__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_7_67, x_stage3_stage3_7_68, x_stage3_stage3_7_69, x_stage3_stage3_7_70}, [coder.const(x_stage3_stage3_7_67NumDims), coder.const(x_stage3_stage3_7_68NumDims), coder.const(x_stage3_stage3_7_69NumDims), coder.const(x_stage3_stage3_7_70NumDims)]);

            % Reshape:
            [shape1151, x_stage3_stage3_7_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_7_Tr, x_stage3_stage3_7__5, coder.const(x_stage3_stage3_7_TrNumDims), 0);
            x_stage3_stage3_7_Re = reshape(x_stage3_stage3_7_Tr, shape1151{:});

            % Set graph output arguments
            x_stage3_stage3_7_ReNumDims1045 = coder.const(x_stage3_stage3_7_ReNumDims);

        end

    end

end