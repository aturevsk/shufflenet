classdef Shape_To_ReshapeLayer1003 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_ReshapeLayer1003(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_ReshapeLayer1003(cgInstance.Name);
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
        function this = Shape_To_ReshapeLayer1003(mlInstance)
            this.Name = mlInstance.Name;
            this.OutputNames = {'x_stage2_stage2_3_Re'};
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

        function [x_stage2_stage2_3_Re] = predict(this, x_stage2_stage2_3__6__)
            if isdlarray(x_stage2_stage2_3__6__)
                x_stage2_stage2_3__6_ = stripdims(x_stage2_stage2_3__6__);
            else
                x_stage2_stage2_3__6_ = x_stage2_stage2_3__6__;
            end
            x_stage2_stage2_3__6NumDims = 4;
            x_stage2_stage2_3__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage2_stage2_3__6_, [4 3 1 2], 4);

            [x_stage2_stage2_3_Re__, x_stage2_stage2_3_ReNumDims__] = Shape_To_ReshapeGraph1012(this, x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, false);
            x_stage2_stage2_3_Re_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage2_stage2_3_Re__, [3 4 2 1], 4);

            x_stage2_stage2_3_Re = dlarray(single(x_stage2_stage2_3_Re_), 'SSCB');
        end

        function [x_stage2_stage2_3_Re, x_stage2_stage2_3_ReNumDims1014] = Shape_To_ReshapeGraph1012(this, x_stage2_stage2_3__6, x_stage2_stage2_3__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage2_stage2_3_Sh, x_stage2_stage2_3_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage2_stage2_3__6, coder.const(x_stage2_stage2_3__6NumDims), 0, coder.const(x_stage2_stage2_3__6NumDims)+1);

            % Gather:
            [x_stage2_stage2_3_Ga, x_stage2_stage2_3_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage2_stage2_3_Sh, this.Vars.x_stage2_stage2_3_14, 0, coder.const(x_stage2_stage2_3_ShNumDims), this.NumDims.x_stage2_stage2_3_14);

            % Shape:
            [x_stage2_stage2_3_52, x_stage2_stage2_3_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage2_stage2_3__6, coder.const(x_stage2_stage2_3__6NumDims), 0, coder.const(x_stage2_stage2_3__6NumDims)+1);

            % Gather:
            [x_stage2_stage2_3_37, x_stage2_stage2_3_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage2_stage2_3_52, this.Vars.x_stage2_stage2_3_15, 0, coder.const(x_stage2_stage2_3_52NumDims), this.NumDims.x_stage2_stage2_3_15);

            % Shape:
            [x_stage2_stage2_3_53, x_stage2_stage2_3_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage2_stage2_3__6, coder.const(x_stage2_stage2_3__6NumDims), 0, coder.const(x_stage2_stage2_3__6NumDims)+1);

            % Gather:
            [x_stage2_stage2_3_38, x_stage2_stage2_3_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage2_stage2_3_53, this.Vars.x_stage2_stage2_3_16, 0, coder.const(x_stage2_stage2_3_53NumDims), this.NumDims.x_stage2_stage2_3_16);

            % Shape:
            [x_stage2_stage2_3_54, x_stage2_stage2_3_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage2_stage2_3__6, coder.const(x_stage2_stage2_3__6NumDims), 0, coder.const(x_stage2_stage2_3__6NumDims)+1);

            % Gather:
            [x_stage2_stage2_3_39, x_stage2_stage2_3_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage2_stage2_3_54, this.Vars.x_stage2_stage2_3_17, 0, coder.const(x_stage2_stage2_3_54NumDims), this.NumDims.x_stage2_stage2_3_17);

            % Div:
            x_stage2_stage2_3_Di = fix(x_stage2_stage2_3_37 ./ this.Vars.x_stage2_stage2_3__7);
            x_stage2_stage2_3_DiNumDims = max(coder.const(x_stage2_stage2_3_37NumDims), this.NumDims.x_stage2_stage2_3__7);

            % Cast:
            x_stage2_stage2_3__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage2_stage2_3_Di)), 'like', x_stage2_stage2_3_Di);
            x_stage2_stage2_3__2NumDims = coder.const(x_stage2_stage2_3_DiNumDims);

            % Cast:
            x_stage2_stage2_3_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage2_stage2_3__2)), 'like', x_stage2_stage2_3__2);
            x_stage2_stage2_3_CaNumDims = coder.const(x_stage2_stage2_3__2NumDims);

            % Unsqueeze:
            [shape1039, x_stage2_stage2_3_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ga, this.Vars.onnx__Unsqueeze_560, coder.const(x_stage2_stage2_3_GaNumDims));
            x_stage2_stage2_3_71 = reshape(x_stage2_stage2_3_Ga, shape1039);

            % Unsqueeze:
            [shape1040, x_stage2_stage2_3_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ca, this.Vars.onnx__Unsqueeze_564, coder.const(x_stage2_stage2_3_CaNumDims));
            x_stage2_stage2_3_Un = reshape(x_stage2_stage2_3_Ca, shape1040);

            % Unsqueeze:
            [shape1041, x_stage2_stage2_3_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_38, this.Vars.onnx__Unsqueeze_566, coder.const(x_stage2_stage2_3_38NumDims));
            x_stage2_stage2_3_65 = reshape(x_stage2_stage2_3_38, shape1041);

            % Unsqueeze:
            [shape1042, x_stage2_stage2_3_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_39, this.Vars.onnx__Unsqueeze_568, coder.const(x_stage2_stage2_3_39NumDims));
            x_stage2_stage2_3_66 = reshape(x_stage2_stage2_3_39, shape1042);

            % Concat:
            [x_stage2_stage2_3_Co, x_stage2_stage2_3_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage2_stage2_3_71, this.Vars.x_stage2_stage2_3__8, x_stage2_stage2_3_Un, x_stage2_stage2_3_65, x_stage2_stage2_3_66}, [coder.const(x_stage2_stage2_3_71NumDims), this.NumDims.x_stage2_stage2_3__8, coder.const(x_stage2_stage2_3_UnNumDims), coder.const(x_stage2_stage2_3_65NumDims), coder.const(x_stage2_stage2_3_66NumDims)]);

            % Reshape:
            [shape1043, x_stage2_stage2_3_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage2_stage2_3__6, x_stage2_stage2_3_Co, coder.const(x_stage2_stage2_3__6NumDims), 0);
            x_stage2_stage2_3_49 = reshape(x_stage2_stage2_3__6, shape1043{:});

            % Transpose:
            [perm1044, x_stage2_stage2_3_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1013, coder.const(x_stage2_stage2_3_49NumDims));
            if isempty(perm1044)
                x_stage2_stage2_3_Tr = x_stage2_stage2_3_49;
            else
                x_stage2_stage2_3_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage2_stage2_3_49), perm1044);
            end

            % Unsqueeze:
            [shape1045, x_stage2_stage2_3_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_Ga, this.Vars.onnx__Unsqueeze_573, coder.const(x_stage2_stage2_3_GaNumDims));
            x_stage2_stage2_3_67 = reshape(x_stage2_stage2_3_Ga, shape1045);

            % Unsqueeze:
            [shape1046, x_stage2_stage2_3_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_37, this.Vars.onnx__Unsqueeze_575, coder.const(x_stage2_stage2_3_37NumDims));
            x_stage2_stage2_3_68 = reshape(x_stage2_stage2_3_37, shape1046);

            % Unsqueeze:
            [shape1047, x_stage2_stage2_3_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_38, this.Vars.onnx__Unsqueeze_577, coder.const(x_stage2_stage2_3_38NumDims));
            x_stage2_stage2_3_69 = reshape(x_stage2_stage2_3_38, shape1047);

            % Unsqueeze:
            [shape1048, x_stage2_stage2_3_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage2_stage2_3_39, this.Vars.onnx__Unsqueeze_579, coder.const(x_stage2_stage2_3_39NumDims));
            x_stage2_stage2_3_70 = reshape(x_stage2_stage2_3_39, shape1048);

            % Concat:
            [x_stage2_stage2_3__5, x_stage2_stage2_3__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage2_stage2_3_67, x_stage2_stage2_3_68, x_stage2_stage2_3_69, x_stage2_stage2_3_70}, [coder.const(x_stage2_stage2_3_67NumDims), coder.const(x_stage2_stage2_3_68NumDims), coder.const(x_stage2_stage2_3_69NumDims), coder.const(x_stage2_stage2_3_70NumDims)]);

            % Reshape:
            [shape1049, x_stage2_stage2_3_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage2_stage2_3_Tr, x_stage2_stage2_3__5, coder.const(x_stage2_stage2_3_TrNumDims), 0);
            x_stage2_stage2_3_Re = reshape(x_stage2_stage2_3_Tr, shape1049{:});

            % Set graph output arguments
            x_stage2_stage2_3_ReNumDims1014 = coder.const(x_stage2_stage2_3_ReNumDims);

        end

    end

end