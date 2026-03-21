classdef Shape_To_SliceLayer1010 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1010(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1010(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1010(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_7_Sl', 'x_stage3_stage3_7_61'};
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

        function [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61] = predict(this, x_stage3_stage3_6__6__)
            if isdlarray(x_stage3_stage3_6__6__)
                x_stage3_stage3_6__6_ = stripdims(x_stage3_stage3_6__6__);
            else
                x_stage3_stage3_6__6_ = x_stage3_stage3_6__6__;
            end
            x_stage3_stage3_6__6NumDims = 4;
            x_stage3_stage3_6__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_6__6_, [4 3 1 2], 4);

            [x_stage3_stage3_7_Sl__, x_stage3_stage3_7_61__, x_stage3_stage3_7_SlNumDims__, x_stage3_stage3_7_61NumDims__] = Shape_To_SliceGraph1039(this, x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, false);
            x_stage3_stage3_7_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_7_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_7_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_7_61__, [3 4 2 1], 4);

            x_stage3_stage3_7_Sl = dlarray(single(x_stage3_stage3_7_Sl_), 'SSCB');
            x_stage3_stage3_7_61 = dlarray(single(x_stage3_stage3_7_61_), 'SSCB');
        end

        function [x_stage3_stage3_7_Sl, x_stage3_stage3_7_61, x_stage3_stage3_7_SlNumDims1041, x_stage3_stage3_7_61NumDims1042] = Shape_To_SliceGraph1039(this, x_stage3_stage3_6__6, x_stage3_stage3_6__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_6_Sh, x_stage3_stage3_6_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_6__6, coder.const(x_stage3_stage3_6__6NumDims), 0, coder.const(x_stage3_stage3_6__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_6_Ga, x_stage3_stage3_6_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_6_Sh, this.Vars.x_stage3_stage3_6_14, 0, coder.const(x_stage3_stage3_6_ShNumDims), this.NumDims.x_stage3_stage3_6_14);

            % Shape:
            [x_stage3_stage3_6_52, x_stage3_stage3_6_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_6__6, coder.const(x_stage3_stage3_6__6NumDims), 0, coder.const(x_stage3_stage3_6__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_6_37, x_stage3_stage3_6_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_6_52, this.Vars.x_stage3_stage3_6_15, 0, coder.const(x_stage3_stage3_6_52NumDims), this.NumDims.x_stage3_stage3_6_15);

            % Shape:
            [x_stage3_stage3_6_53, x_stage3_stage3_6_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_6__6, coder.const(x_stage3_stage3_6__6NumDims), 0, coder.const(x_stage3_stage3_6__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_6_38, x_stage3_stage3_6_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_6_53, this.Vars.x_stage3_stage3_6_16, 0, coder.const(x_stage3_stage3_6_53NumDims), this.NumDims.x_stage3_stage3_6_16);

            % Shape:
            [x_stage3_stage3_6_54, x_stage3_stage3_6_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_6__6, coder.const(x_stage3_stage3_6__6NumDims), 0, coder.const(x_stage3_stage3_6__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_6_39, x_stage3_stage3_6_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_6_54, this.Vars.x_stage3_stage3_6_17, 0, coder.const(x_stage3_stage3_6_54NumDims), this.NumDims.x_stage3_stage3_6_17);

            % Div:
            x_stage3_stage3_6_Di = fix(x_stage3_stage3_6_37 ./ this.Vars.x_stage3_stage3_6__7);
            x_stage3_stage3_6_DiNumDims = max(coder.const(x_stage3_stage3_6_37NumDims), this.NumDims.x_stage3_stage3_6__7);

            % Cast:
            x_stage3_stage3_6__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_6_Di)), 'like', x_stage3_stage3_6_Di);
            x_stage3_stage3_6__2NumDims = coder.const(x_stage3_stage3_6_DiNumDims);

            % Cast:
            x_stage3_stage3_6_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_6__2)), 'like', x_stage3_stage3_6__2);
            x_stage3_stage3_6_CaNumDims = coder.const(x_stage3_stage3_6__2NumDims);

            % Unsqueeze:
            [shape1128, x_stage3_stage3_6_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ga, this.Vars.onnx__Unsqueeze_985, coder.const(x_stage3_stage3_6_GaNumDims));
            x_stage3_stage3_6_71 = reshape(x_stage3_stage3_6_Ga, shape1128);

            % Unsqueeze:
            [shape1129, x_stage3_stage3_6_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ca, this.Vars.onnx__Unsqueeze_989, coder.const(x_stage3_stage3_6_CaNumDims));
            x_stage3_stage3_6_Un = reshape(x_stage3_stage3_6_Ca, shape1129);

            % Unsqueeze:
            [shape1130, x_stage3_stage3_6_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_38, this.Vars.onnx__Unsqueeze_991, coder.const(x_stage3_stage3_6_38NumDims));
            x_stage3_stage3_6_65 = reshape(x_stage3_stage3_6_38, shape1130);

            % Unsqueeze:
            [shape1131, x_stage3_stage3_6_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_39, this.Vars.onnx__Unsqueeze_993, coder.const(x_stage3_stage3_6_39NumDims));
            x_stage3_stage3_6_66 = reshape(x_stage3_stage3_6_39, shape1131);

            % Concat:
            [x_stage3_stage3_6_Co, x_stage3_stage3_6_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_6_71, this.Vars.x_stage3_stage3_6__8, x_stage3_stage3_6_Un, x_stage3_stage3_6_65, x_stage3_stage3_6_66}, [coder.const(x_stage3_stage3_6_71NumDims), this.NumDims.x_stage3_stage3_6__8, coder.const(x_stage3_stage3_6_UnNumDims), coder.const(x_stage3_stage3_6_65NumDims), coder.const(x_stage3_stage3_6_66NumDims)]);

            % Reshape:
            [shape1132, x_stage3_stage3_6_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_6__6, x_stage3_stage3_6_Co, coder.const(x_stage3_stage3_6__6NumDims), 0);
            x_stage3_stage3_6_49 = reshape(x_stage3_stage3_6__6, shape1132{:});

            % Transpose:
            [perm1133, x_stage3_stage3_6_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1040, coder.const(x_stage3_stage3_6_49NumDims));
            if isempty(perm1133)
                x_stage3_stage3_6_Tr = x_stage3_stage3_6_49;
            else
                x_stage3_stage3_6_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_6_49), perm1133);
            end

            % Unsqueeze:
            [shape1134, x_stage3_stage3_6_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_Ga, this.Vars.onnx__Unsqueeze_998, coder.const(x_stage3_stage3_6_GaNumDims));
            x_stage3_stage3_6_67 = reshape(x_stage3_stage3_6_Ga, shape1134);

            % Unsqueeze:
            [shape1135, x_stage3_stage3_6_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_37, this.Vars.onnx__Unsqueeze_1000, coder.const(x_stage3_stage3_6_37NumDims));
            x_stage3_stage3_6_68 = reshape(x_stage3_stage3_6_37, shape1135);

            % Unsqueeze:
            [shape1136, x_stage3_stage3_6_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_38, this.Vars.onnx__Unsqueeze_1002, coder.const(x_stage3_stage3_6_38NumDims));
            x_stage3_stage3_6_69 = reshape(x_stage3_stage3_6_38, shape1136);

            % Unsqueeze:
            [shape1137, x_stage3_stage3_6_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_6_39, this.Vars.onnx__Unsqueeze_1004, coder.const(x_stage3_stage3_6_39NumDims));
            x_stage3_stage3_6_70 = reshape(x_stage3_stage3_6_39, shape1137);

            % Concat:
            [x_stage3_stage3_6__5, x_stage3_stage3_6__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_6_67, x_stage3_stage3_6_68, x_stage3_stage3_6_69, x_stage3_stage3_6_70}, [coder.const(x_stage3_stage3_6_67NumDims), coder.const(x_stage3_stage3_6_68NumDims), coder.const(x_stage3_stage3_6_69NumDims), coder.const(x_stage3_stage3_6_70NumDims)]);

            % Reshape:
            [shape1138, x_stage3_stage3_6_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_6_Tr, x_stage3_stage3_6__5, coder.const(x_stage3_stage3_6_TrNumDims), 0);
            x_stage3_stage3_6_Re = reshape(x_stage3_stage3_6_Tr, shape1138{:});

            % Shape:
            [x_stage3_stage3_7_55, x_stage3_stage3_7_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_6_Re, coder.const(x_stage3_stage3_6_ReNumDims), 0, coder.const(x_stage3_stage3_6_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_7_40, x_stage3_stage3_7_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_7_55, this.Vars.x_stage3_stage3_7_18, 0, coder.const(x_stage3_stage3_7_55NumDims), this.NumDims.x_stage3_stage3_7_18);

            % Add:
            x_stage3_stage3_7_Ad = x_stage3_stage3_7_40 + this.Vars.x_stage3_stage3_7_10;
            x_stage3_stage3_7_AdNumDims = max(coder.const(x_stage3_stage3_7_40NumDims), this.NumDims.x_stage3_stage3_7_10);

            % Div:
            x_stage3_stage3_7_34 = fix(x_stage3_stage3_7_Ad ./ this.Vars.x_stage3_stage3_7_11);
            x_stage3_stage3_7_34NumDims = max(coder.const(x_stage3_stage3_7_AdNumDims), this.NumDims.x_stage3_stage3_7_11);

            % Mul:
            x_stage3_stage3_7_46 = x_stage3_stage3_7_34 .* this.Vars.x_stage3_stage3_7_12;
            x_stage3_stage3_7_46NumDims = max(coder.const(x_stage3_stage3_7_34NumDims), this.NumDims.x_stage3_stage3_7_12);

            % Slice:
            [indices1139, x_stage3_stage3_7_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_6_Re, this.Vars.x_stage3_stage3_7__9, x_stage3_stage3_7_46, this.Vars.x_stage3_stage3_7_18, '', coder.const(x_stage3_stage3_6_ReNumDims));
            x_stage3_stage3_7_61 = x_stage3_stage3_6_Re(indices1139{:});

            % Mul:
            x_stage3_stage3_7_Mu = x_stage3_stage3_7_34 .* this.Vars.x_stage3_stage3_7_13;
            x_stage3_stage3_7_MuNumDims = max(coder.const(x_stage3_stage3_7_34NumDims), this.NumDims.x_stage3_stage3_7_13);

            % Slice:
            [indices1140, x_stage3_stage3_7_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_6_Re, x_stage3_stage3_7_46, x_stage3_stage3_7_Mu, this.Vars.x_stage3_stage3_7_18, '', coder.const(x_stage3_stage3_6_ReNumDims));
            x_stage3_stage3_7_Sl = x_stage3_stage3_6_Re(indices1140{:});

            % Set graph output arguments
            x_stage3_stage3_7_SlNumDims1041 = coder.const(x_stage3_stage3_7_SlNumDims);
            x_stage3_stage3_7_61NumDims1042 = coder.const(x_stage3_stage3_7_61NumDims);

        end

    end

end