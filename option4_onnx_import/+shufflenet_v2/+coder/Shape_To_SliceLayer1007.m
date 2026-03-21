classdef Shape_To_SliceLayer1007 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1007(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1007(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1007(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_4_Sl', 'x_stage3_stage3_4_61'};
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

        function [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61] = predict(this, x_stage3_stage3_3__6__)
            if isdlarray(x_stage3_stage3_3__6__)
                x_stage3_stage3_3__6_ = stripdims(x_stage3_stage3_3__6__);
            else
                x_stage3_stage3_3__6_ = x_stage3_stage3_3__6__;
            end
            x_stage3_stage3_3__6NumDims = 4;
            x_stage3_stage3_3__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_3__6_, [4 3 1 2], 4);

            [x_stage3_stage3_4_Sl__, x_stage3_stage3_4_61__, x_stage3_stage3_4_SlNumDims__, x_stage3_stage3_4_61NumDims__] = Shape_To_SliceGraph1027(this, x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, false);
            x_stage3_stage3_4_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_4_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_4_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_4_61__, [3 4 2 1], 4);

            x_stage3_stage3_4_Sl = dlarray(single(x_stage3_stage3_4_Sl_), 'SSCB');
            x_stage3_stage3_4_61 = dlarray(single(x_stage3_stage3_4_61_), 'SSCB');
        end

        function [x_stage3_stage3_4_Sl, x_stage3_stage3_4_61, x_stage3_stage3_4_SlNumDims1029, x_stage3_stage3_4_61NumDims1030] = Shape_To_SliceGraph1027(this, x_stage3_stage3_3__6, x_stage3_stage3_3__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_3_Sh, x_stage3_stage3_3_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_3__6, coder.const(x_stage3_stage3_3__6NumDims), 0, coder.const(x_stage3_stage3_3__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_3_Ga, x_stage3_stage3_3_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_3_Sh, this.Vars.x_stage3_stage3_3_14, 0, coder.const(x_stage3_stage3_3_ShNumDims), this.NumDims.x_stage3_stage3_3_14);

            % Shape:
            [x_stage3_stage3_3_52, x_stage3_stage3_3_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_3__6, coder.const(x_stage3_stage3_3__6NumDims), 0, coder.const(x_stage3_stage3_3__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_3_37, x_stage3_stage3_3_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_3_52, this.Vars.x_stage3_stage3_3_15, 0, coder.const(x_stage3_stage3_3_52NumDims), this.NumDims.x_stage3_stage3_3_15);

            % Shape:
            [x_stage3_stage3_3_53, x_stage3_stage3_3_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_3__6, coder.const(x_stage3_stage3_3__6NumDims), 0, coder.const(x_stage3_stage3_3__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_3_38, x_stage3_stage3_3_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_3_53, this.Vars.x_stage3_stage3_3_16, 0, coder.const(x_stage3_stage3_3_53NumDims), this.NumDims.x_stage3_stage3_3_16);

            % Shape:
            [x_stage3_stage3_3_54, x_stage3_stage3_3_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_3__6, coder.const(x_stage3_stage3_3__6NumDims), 0, coder.const(x_stage3_stage3_3__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_3_39, x_stage3_stage3_3_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_3_54, this.Vars.x_stage3_stage3_3_17, 0, coder.const(x_stage3_stage3_3_54NumDims), this.NumDims.x_stage3_stage3_3_17);

            % Div:
            x_stage3_stage3_3_Di = fix(x_stage3_stage3_3_37 ./ this.Vars.x_stage3_stage3_3__7);
            x_stage3_stage3_3_DiNumDims = max(coder.const(x_stage3_stage3_3_37NumDims), this.NumDims.x_stage3_stage3_3__7);

            % Cast:
            x_stage3_stage3_3__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_3_Di)), 'like', x_stage3_stage3_3_Di);
            x_stage3_stage3_3__2NumDims = coder.const(x_stage3_stage3_3_DiNumDims);

            % Cast:
            x_stage3_stage3_3_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_3__2)), 'like', x_stage3_stage3_3__2);
            x_stage3_stage3_3_CaNumDims = coder.const(x_stage3_stage3_3__2NumDims);

            % Unsqueeze:
            [shape1089, x_stage3_stage3_3_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ga, this.Vars.onnx__Unsqueeze_799, coder.const(x_stage3_stage3_3_GaNumDims));
            x_stage3_stage3_3_71 = reshape(x_stage3_stage3_3_Ga, shape1089);

            % Unsqueeze:
            [shape1090, x_stage3_stage3_3_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ca, this.Vars.onnx__Unsqueeze_803, coder.const(x_stage3_stage3_3_CaNumDims));
            x_stage3_stage3_3_Un = reshape(x_stage3_stage3_3_Ca, shape1090);

            % Unsqueeze:
            [shape1091, x_stage3_stage3_3_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_38, this.Vars.onnx__Unsqueeze_805, coder.const(x_stage3_stage3_3_38NumDims));
            x_stage3_stage3_3_65 = reshape(x_stage3_stage3_3_38, shape1091);

            % Unsqueeze:
            [shape1092, x_stage3_stage3_3_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_39, this.Vars.onnx__Unsqueeze_807, coder.const(x_stage3_stage3_3_39NumDims));
            x_stage3_stage3_3_66 = reshape(x_stage3_stage3_3_39, shape1092);

            % Concat:
            [x_stage3_stage3_3_Co, x_stage3_stage3_3_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_3_71, this.Vars.x_stage3_stage3_3__8, x_stage3_stage3_3_Un, x_stage3_stage3_3_65, x_stage3_stage3_3_66}, [coder.const(x_stage3_stage3_3_71NumDims), this.NumDims.x_stage3_stage3_3__8, coder.const(x_stage3_stage3_3_UnNumDims), coder.const(x_stage3_stage3_3_65NumDims), coder.const(x_stage3_stage3_3_66NumDims)]);

            % Reshape:
            [shape1093, x_stage3_stage3_3_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_3__6, x_stage3_stage3_3_Co, coder.const(x_stage3_stage3_3__6NumDims), 0);
            x_stage3_stage3_3_49 = reshape(x_stage3_stage3_3__6, shape1093{:});

            % Transpose:
            [perm1094, x_stage3_stage3_3_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1028, coder.const(x_stage3_stage3_3_49NumDims));
            if isempty(perm1094)
                x_stage3_stage3_3_Tr = x_stage3_stage3_3_49;
            else
                x_stage3_stage3_3_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_3_49), perm1094);
            end

            % Unsqueeze:
            [shape1095, x_stage3_stage3_3_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_Ga, this.Vars.onnx__Unsqueeze_812, coder.const(x_stage3_stage3_3_GaNumDims));
            x_stage3_stage3_3_67 = reshape(x_stage3_stage3_3_Ga, shape1095);

            % Unsqueeze:
            [shape1096, x_stage3_stage3_3_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_37, this.Vars.onnx__Unsqueeze_814, coder.const(x_stage3_stage3_3_37NumDims));
            x_stage3_stage3_3_68 = reshape(x_stage3_stage3_3_37, shape1096);

            % Unsqueeze:
            [shape1097, x_stage3_stage3_3_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_38, this.Vars.onnx__Unsqueeze_816, coder.const(x_stage3_stage3_3_38NumDims));
            x_stage3_stage3_3_69 = reshape(x_stage3_stage3_3_38, shape1097);

            % Unsqueeze:
            [shape1098, x_stage3_stage3_3_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_3_39, this.Vars.onnx__Unsqueeze_818, coder.const(x_stage3_stage3_3_39NumDims));
            x_stage3_stage3_3_70 = reshape(x_stage3_stage3_3_39, shape1098);

            % Concat:
            [x_stage3_stage3_3__5, x_stage3_stage3_3__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_3_67, x_stage3_stage3_3_68, x_stage3_stage3_3_69, x_stage3_stage3_3_70}, [coder.const(x_stage3_stage3_3_67NumDims), coder.const(x_stage3_stage3_3_68NumDims), coder.const(x_stage3_stage3_3_69NumDims), coder.const(x_stage3_stage3_3_70NumDims)]);

            % Reshape:
            [shape1099, x_stage3_stage3_3_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_3_Tr, x_stage3_stage3_3__5, coder.const(x_stage3_stage3_3_TrNumDims), 0);
            x_stage3_stage3_3_Re = reshape(x_stage3_stage3_3_Tr, shape1099{:});

            % Shape:
            [x_stage3_stage3_4_55, x_stage3_stage3_4_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_3_Re, coder.const(x_stage3_stage3_3_ReNumDims), 0, coder.const(x_stage3_stage3_3_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_4_40, x_stage3_stage3_4_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_4_55, this.Vars.x_stage3_stage3_4_18, 0, coder.const(x_stage3_stage3_4_55NumDims), this.NumDims.x_stage3_stage3_4_18);

            % Add:
            x_stage3_stage3_4_Ad = x_stage3_stage3_4_40 + this.Vars.x_stage3_stage3_4_10;
            x_stage3_stage3_4_AdNumDims = max(coder.const(x_stage3_stage3_4_40NumDims), this.NumDims.x_stage3_stage3_4_10);

            % Div:
            x_stage3_stage3_4_34 = fix(x_stage3_stage3_4_Ad ./ this.Vars.x_stage3_stage3_4_11);
            x_stage3_stage3_4_34NumDims = max(coder.const(x_stage3_stage3_4_AdNumDims), this.NumDims.x_stage3_stage3_4_11);

            % Mul:
            x_stage3_stage3_4_46 = x_stage3_stage3_4_34 .* this.Vars.x_stage3_stage3_4_12;
            x_stage3_stage3_4_46NumDims = max(coder.const(x_stage3_stage3_4_34NumDims), this.NumDims.x_stage3_stage3_4_12);

            % Slice:
            [indices1100, x_stage3_stage3_4_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_3_Re, this.Vars.x_stage3_stage3_4__9, x_stage3_stage3_4_46, this.Vars.x_stage3_stage3_4_18, '', coder.const(x_stage3_stage3_3_ReNumDims));
            x_stage3_stage3_4_61 = x_stage3_stage3_3_Re(indices1100{:});

            % Mul:
            x_stage3_stage3_4_Mu = x_stage3_stage3_4_34 .* this.Vars.x_stage3_stage3_4_13;
            x_stage3_stage3_4_MuNumDims = max(coder.const(x_stage3_stage3_4_34NumDims), this.NumDims.x_stage3_stage3_4_13);

            % Slice:
            [indices1101, x_stage3_stage3_4_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_3_Re, x_stage3_stage3_4_46, x_stage3_stage3_4_Mu, this.Vars.x_stage3_stage3_4_18, '', coder.const(x_stage3_stage3_3_ReNumDims));
            x_stage3_stage3_4_Sl = x_stage3_stage3_3_Re(indices1101{:});

            % Set graph output arguments
            x_stage3_stage3_4_SlNumDims1029 = coder.const(x_stage3_stage3_4_SlNumDims);
            x_stage3_stage3_4_61NumDims1030 = coder.const(x_stage3_stage3_4_61NumDims);

        end

    end

end