classdef Shape_To_SliceLayer1006 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1006(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1006(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1006(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_3_Sl', 'x_stage3_stage3_3_61'};
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

        function [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61] = predict(this, x_stage3_stage3_2__6__)
            if isdlarray(x_stage3_stage3_2__6__)
                x_stage3_stage3_2__6_ = stripdims(x_stage3_stage3_2__6__);
            else
                x_stage3_stage3_2__6_ = x_stage3_stage3_2__6__;
            end
            x_stage3_stage3_2__6NumDims = 4;
            x_stage3_stage3_2__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_2__6_, [4 3 1 2], 4);

            [x_stage3_stage3_3_Sl__, x_stage3_stage3_3_61__, x_stage3_stage3_3_SlNumDims__, x_stage3_stage3_3_61NumDims__] = Shape_To_SliceGraph1023(this, x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, false);
            x_stage3_stage3_3_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_3_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_3_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_3_61__, [3 4 2 1], 4);

            x_stage3_stage3_3_Sl = dlarray(single(x_stage3_stage3_3_Sl_), 'SSCB');
            x_stage3_stage3_3_61 = dlarray(single(x_stage3_stage3_3_61_), 'SSCB');
        end

        function [x_stage3_stage3_3_Sl, x_stage3_stage3_3_61, x_stage3_stage3_3_SlNumDims1025, x_stage3_stage3_3_61NumDims1026] = Shape_To_SliceGraph1023(this, x_stage3_stage3_2__6, x_stage3_stage3_2__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_2_Sh, x_stage3_stage3_2_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_2__6, coder.const(x_stage3_stage3_2__6NumDims), 0, coder.const(x_stage3_stage3_2__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_2_Ga, x_stage3_stage3_2_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_2_Sh, this.Vars.x_stage3_stage3_2_14, 0, coder.const(x_stage3_stage3_2_ShNumDims), this.NumDims.x_stage3_stage3_2_14);

            % Shape:
            [x_stage3_stage3_2_52, x_stage3_stage3_2_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_2__6, coder.const(x_stage3_stage3_2__6NumDims), 0, coder.const(x_stage3_stage3_2__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_2_37, x_stage3_stage3_2_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_2_52, this.Vars.x_stage3_stage3_2_15, 0, coder.const(x_stage3_stage3_2_52NumDims), this.NumDims.x_stage3_stage3_2_15);

            % Shape:
            [x_stage3_stage3_2_53, x_stage3_stage3_2_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_2__6, coder.const(x_stage3_stage3_2__6NumDims), 0, coder.const(x_stage3_stage3_2__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_2_38, x_stage3_stage3_2_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_2_53, this.Vars.x_stage3_stage3_2_16, 0, coder.const(x_stage3_stage3_2_53NumDims), this.NumDims.x_stage3_stage3_2_16);

            % Shape:
            [x_stage3_stage3_2_54, x_stage3_stage3_2_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_2__6, coder.const(x_stage3_stage3_2__6NumDims), 0, coder.const(x_stage3_stage3_2__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_2_39, x_stage3_stage3_2_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_2_54, this.Vars.x_stage3_stage3_2_17, 0, coder.const(x_stage3_stage3_2_54NumDims), this.NumDims.x_stage3_stage3_2_17);

            % Div:
            x_stage3_stage3_2_Di = fix(x_stage3_stage3_2_37 ./ this.Vars.x_stage3_stage3_2__7);
            x_stage3_stage3_2_DiNumDims = max(coder.const(x_stage3_stage3_2_37NumDims), this.NumDims.x_stage3_stage3_2__7);

            % Cast:
            x_stage3_stage3_2__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_2_Di)), 'like', x_stage3_stage3_2_Di);
            x_stage3_stage3_2__2NumDims = coder.const(x_stage3_stage3_2_DiNumDims);

            % Cast:
            x_stage3_stage3_2_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_2__2)), 'like', x_stage3_stage3_2__2);
            x_stage3_stage3_2_CaNumDims = coder.const(x_stage3_stage3_2__2NumDims);

            % Unsqueeze:
            [shape1076, x_stage3_stage3_2_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ga, this.Vars.onnx__Unsqueeze_737, coder.const(x_stage3_stage3_2_GaNumDims));
            x_stage3_stage3_2_71 = reshape(x_stage3_stage3_2_Ga, shape1076);

            % Unsqueeze:
            [shape1077, x_stage3_stage3_2_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ca, this.Vars.onnx__Unsqueeze_741, coder.const(x_stage3_stage3_2_CaNumDims));
            x_stage3_stage3_2_Un = reshape(x_stage3_stage3_2_Ca, shape1077);

            % Unsqueeze:
            [shape1078, x_stage3_stage3_2_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_38, this.Vars.onnx__Unsqueeze_743, coder.const(x_stage3_stage3_2_38NumDims));
            x_stage3_stage3_2_65 = reshape(x_stage3_stage3_2_38, shape1078);

            % Unsqueeze:
            [shape1079, x_stage3_stage3_2_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_39, this.Vars.onnx__Unsqueeze_745, coder.const(x_stage3_stage3_2_39NumDims));
            x_stage3_stage3_2_66 = reshape(x_stage3_stage3_2_39, shape1079);

            % Concat:
            [x_stage3_stage3_2_Co, x_stage3_stage3_2_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_2_71, this.Vars.x_stage3_stage3_2__8, x_stage3_stage3_2_Un, x_stage3_stage3_2_65, x_stage3_stage3_2_66}, [coder.const(x_stage3_stage3_2_71NumDims), this.NumDims.x_stage3_stage3_2__8, coder.const(x_stage3_stage3_2_UnNumDims), coder.const(x_stage3_stage3_2_65NumDims), coder.const(x_stage3_stage3_2_66NumDims)]);

            % Reshape:
            [shape1080, x_stage3_stage3_2_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_2__6, x_stage3_stage3_2_Co, coder.const(x_stage3_stage3_2__6NumDims), 0);
            x_stage3_stage3_2_49 = reshape(x_stage3_stage3_2__6, shape1080{:});

            % Transpose:
            [perm1081, x_stage3_stage3_2_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1024, coder.const(x_stage3_stage3_2_49NumDims));
            if isempty(perm1081)
                x_stage3_stage3_2_Tr = x_stage3_stage3_2_49;
            else
                x_stage3_stage3_2_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_2_49), perm1081);
            end

            % Unsqueeze:
            [shape1082, x_stage3_stage3_2_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_Ga, this.Vars.onnx__Unsqueeze_750, coder.const(x_stage3_stage3_2_GaNumDims));
            x_stage3_stage3_2_67 = reshape(x_stage3_stage3_2_Ga, shape1082);

            % Unsqueeze:
            [shape1083, x_stage3_stage3_2_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_37, this.Vars.onnx__Unsqueeze_752, coder.const(x_stage3_stage3_2_37NumDims));
            x_stage3_stage3_2_68 = reshape(x_stage3_stage3_2_37, shape1083);

            % Unsqueeze:
            [shape1084, x_stage3_stage3_2_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_38, this.Vars.onnx__Unsqueeze_754, coder.const(x_stage3_stage3_2_38NumDims));
            x_stage3_stage3_2_69 = reshape(x_stage3_stage3_2_38, shape1084);

            % Unsqueeze:
            [shape1085, x_stage3_stage3_2_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_2_39, this.Vars.onnx__Unsqueeze_756, coder.const(x_stage3_stage3_2_39NumDims));
            x_stage3_stage3_2_70 = reshape(x_stage3_stage3_2_39, shape1085);

            % Concat:
            [x_stage3_stage3_2__5, x_stage3_stage3_2__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_2_67, x_stage3_stage3_2_68, x_stage3_stage3_2_69, x_stage3_stage3_2_70}, [coder.const(x_stage3_stage3_2_67NumDims), coder.const(x_stage3_stage3_2_68NumDims), coder.const(x_stage3_stage3_2_69NumDims), coder.const(x_stage3_stage3_2_70NumDims)]);

            % Reshape:
            [shape1086, x_stage3_stage3_2_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_2_Tr, x_stage3_stage3_2__5, coder.const(x_stage3_stage3_2_TrNumDims), 0);
            x_stage3_stage3_2_Re = reshape(x_stage3_stage3_2_Tr, shape1086{:});

            % Shape:
            [x_stage3_stage3_3_55, x_stage3_stage3_3_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_2_Re, coder.const(x_stage3_stage3_2_ReNumDims), 0, coder.const(x_stage3_stage3_2_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_3_40, x_stage3_stage3_3_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_3_55, this.Vars.x_stage3_stage3_3_18, 0, coder.const(x_stage3_stage3_3_55NumDims), this.NumDims.x_stage3_stage3_3_18);

            % Add:
            x_stage3_stage3_3_Ad = x_stage3_stage3_3_40 + this.Vars.x_stage3_stage3_3_10;
            x_stage3_stage3_3_AdNumDims = max(coder.const(x_stage3_stage3_3_40NumDims), this.NumDims.x_stage3_stage3_3_10);

            % Div:
            x_stage3_stage3_3_34 = fix(x_stage3_stage3_3_Ad ./ this.Vars.x_stage3_stage3_3_11);
            x_stage3_stage3_3_34NumDims = max(coder.const(x_stage3_stage3_3_AdNumDims), this.NumDims.x_stage3_stage3_3_11);

            % Mul:
            x_stage3_stage3_3_46 = x_stage3_stage3_3_34 .* this.Vars.x_stage3_stage3_3_12;
            x_stage3_stage3_3_46NumDims = max(coder.const(x_stage3_stage3_3_34NumDims), this.NumDims.x_stage3_stage3_3_12);

            % Slice:
            [indices1087, x_stage3_stage3_3_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_2_Re, this.Vars.x_stage3_stage3_3__9, x_stage3_stage3_3_46, this.Vars.x_stage3_stage3_3_18, '', coder.const(x_stage3_stage3_2_ReNumDims));
            x_stage3_stage3_3_61 = x_stage3_stage3_2_Re(indices1087{:});

            % Mul:
            x_stage3_stage3_3_Mu = x_stage3_stage3_3_34 .* this.Vars.x_stage3_stage3_3_13;
            x_stage3_stage3_3_MuNumDims = max(coder.const(x_stage3_stage3_3_34NumDims), this.NumDims.x_stage3_stage3_3_13);

            % Slice:
            [indices1088, x_stage3_stage3_3_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_2_Re, x_stage3_stage3_3_46, x_stage3_stage3_3_Mu, this.Vars.x_stage3_stage3_3_18, '', coder.const(x_stage3_stage3_2_ReNumDims));
            x_stage3_stage3_3_Sl = x_stage3_stage3_2_Re(indices1088{:});

            % Set graph output arguments
            x_stage3_stage3_3_SlNumDims1025 = coder.const(x_stage3_stage3_3_SlNumDims);
            x_stage3_stage3_3_61NumDims1026 = coder.const(x_stage3_stage3_3_61NumDims);

        end

    end

end