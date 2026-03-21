classdef Shape_To_SliceLayer1008 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1008(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1008(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1008(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_5_Sl', 'x_stage3_stage3_5_61'};
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

        function [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61] = predict(this, x_stage3_stage3_4__6__)
            if isdlarray(x_stage3_stage3_4__6__)
                x_stage3_stage3_4__6_ = stripdims(x_stage3_stage3_4__6__);
            else
                x_stage3_stage3_4__6_ = x_stage3_stage3_4__6__;
            end
            x_stage3_stage3_4__6NumDims = 4;
            x_stage3_stage3_4__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_4__6_, [4 3 1 2], 4);

            [x_stage3_stage3_5_Sl__, x_stage3_stage3_5_61__, x_stage3_stage3_5_SlNumDims__, x_stage3_stage3_5_61NumDims__] = Shape_To_SliceGraph1031(this, x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, false);
            x_stage3_stage3_5_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_5_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_5_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_5_61__, [3 4 2 1], 4);

            x_stage3_stage3_5_Sl = dlarray(single(x_stage3_stage3_5_Sl_), 'SSCB');
            x_stage3_stage3_5_61 = dlarray(single(x_stage3_stage3_5_61_), 'SSCB');
        end

        function [x_stage3_stage3_5_Sl, x_stage3_stage3_5_61, x_stage3_stage3_5_SlNumDims1033, x_stage3_stage3_5_61NumDims1034] = Shape_To_SliceGraph1031(this, x_stage3_stage3_4__6, x_stage3_stage3_4__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_4_Sh, x_stage3_stage3_4_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_4__6, coder.const(x_stage3_stage3_4__6NumDims), 0, coder.const(x_stage3_stage3_4__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_4_Ga, x_stage3_stage3_4_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_4_Sh, this.Vars.x_stage3_stage3_4_14, 0, coder.const(x_stage3_stage3_4_ShNumDims), this.NumDims.x_stage3_stage3_4_14);

            % Shape:
            [x_stage3_stage3_4_52, x_stage3_stage3_4_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_4__6, coder.const(x_stage3_stage3_4__6NumDims), 0, coder.const(x_stage3_stage3_4__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_4_37, x_stage3_stage3_4_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_4_52, this.Vars.x_stage3_stage3_4_15, 0, coder.const(x_stage3_stage3_4_52NumDims), this.NumDims.x_stage3_stage3_4_15);

            % Shape:
            [x_stage3_stage3_4_53, x_stage3_stage3_4_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_4__6, coder.const(x_stage3_stage3_4__6NumDims), 0, coder.const(x_stage3_stage3_4__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_4_38, x_stage3_stage3_4_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_4_53, this.Vars.x_stage3_stage3_4_16, 0, coder.const(x_stage3_stage3_4_53NumDims), this.NumDims.x_stage3_stage3_4_16);

            % Shape:
            [x_stage3_stage3_4_54, x_stage3_stage3_4_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_4__6, coder.const(x_stage3_stage3_4__6NumDims), 0, coder.const(x_stage3_stage3_4__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_4_39, x_stage3_stage3_4_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_4_54, this.Vars.x_stage3_stage3_4_17, 0, coder.const(x_stage3_stage3_4_54NumDims), this.NumDims.x_stage3_stage3_4_17);

            % Div:
            x_stage3_stage3_4_Di = fix(x_stage3_stage3_4_37 ./ this.Vars.x_stage3_stage3_4__7);
            x_stage3_stage3_4_DiNumDims = max(coder.const(x_stage3_stage3_4_37NumDims), this.NumDims.x_stage3_stage3_4__7);

            % Cast:
            x_stage3_stage3_4__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_4_Di)), 'like', x_stage3_stage3_4_Di);
            x_stage3_stage3_4__2NumDims = coder.const(x_stage3_stage3_4_DiNumDims);

            % Cast:
            x_stage3_stage3_4_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_4__2)), 'like', x_stage3_stage3_4__2);
            x_stage3_stage3_4_CaNumDims = coder.const(x_stage3_stage3_4__2NumDims);

            % Unsqueeze:
            [shape1102, x_stage3_stage3_4_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ga, this.Vars.onnx__Unsqueeze_861, coder.const(x_stage3_stage3_4_GaNumDims));
            x_stage3_stage3_4_71 = reshape(x_stage3_stage3_4_Ga, shape1102);

            % Unsqueeze:
            [shape1103, x_stage3_stage3_4_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ca, this.Vars.onnx__Unsqueeze_865, coder.const(x_stage3_stage3_4_CaNumDims));
            x_stage3_stage3_4_Un = reshape(x_stage3_stage3_4_Ca, shape1103);

            % Unsqueeze:
            [shape1104, x_stage3_stage3_4_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_38, this.Vars.onnx__Unsqueeze_867, coder.const(x_stage3_stage3_4_38NumDims));
            x_stage3_stage3_4_65 = reshape(x_stage3_stage3_4_38, shape1104);

            % Unsqueeze:
            [shape1105, x_stage3_stage3_4_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_39, this.Vars.onnx__Unsqueeze_869, coder.const(x_stage3_stage3_4_39NumDims));
            x_stage3_stage3_4_66 = reshape(x_stage3_stage3_4_39, shape1105);

            % Concat:
            [x_stage3_stage3_4_Co, x_stage3_stage3_4_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_4_71, this.Vars.x_stage3_stage3_4__8, x_stage3_stage3_4_Un, x_stage3_stage3_4_65, x_stage3_stage3_4_66}, [coder.const(x_stage3_stage3_4_71NumDims), this.NumDims.x_stage3_stage3_4__8, coder.const(x_stage3_stage3_4_UnNumDims), coder.const(x_stage3_stage3_4_65NumDims), coder.const(x_stage3_stage3_4_66NumDims)]);

            % Reshape:
            [shape1106, x_stage3_stage3_4_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_4__6, x_stage3_stage3_4_Co, coder.const(x_stage3_stage3_4__6NumDims), 0);
            x_stage3_stage3_4_49 = reshape(x_stage3_stage3_4__6, shape1106{:});

            % Transpose:
            [perm1107, x_stage3_stage3_4_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1032, coder.const(x_stage3_stage3_4_49NumDims));
            if isempty(perm1107)
                x_stage3_stage3_4_Tr = x_stage3_stage3_4_49;
            else
                x_stage3_stage3_4_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_4_49), perm1107);
            end

            % Unsqueeze:
            [shape1108, x_stage3_stage3_4_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_Ga, this.Vars.onnx__Unsqueeze_874, coder.const(x_stage3_stage3_4_GaNumDims));
            x_stage3_stage3_4_67 = reshape(x_stage3_stage3_4_Ga, shape1108);

            % Unsqueeze:
            [shape1109, x_stage3_stage3_4_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_37, this.Vars.onnx__Unsqueeze_876, coder.const(x_stage3_stage3_4_37NumDims));
            x_stage3_stage3_4_68 = reshape(x_stage3_stage3_4_37, shape1109);

            % Unsqueeze:
            [shape1110, x_stage3_stage3_4_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_38, this.Vars.onnx__Unsqueeze_878, coder.const(x_stage3_stage3_4_38NumDims));
            x_stage3_stage3_4_69 = reshape(x_stage3_stage3_4_38, shape1110);

            % Unsqueeze:
            [shape1111, x_stage3_stage3_4_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_4_39, this.Vars.onnx__Unsqueeze_880, coder.const(x_stage3_stage3_4_39NumDims));
            x_stage3_stage3_4_70 = reshape(x_stage3_stage3_4_39, shape1111);

            % Concat:
            [x_stage3_stage3_4__5, x_stage3_stage3_4__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_4_67, x_stage3_stage3_4_68, x_stage3_stage3_4_69, x_stage3_stage3_4_70}, [coder.const(x_stage3_stage3_4_67NumDims), coder.const(x_stage3_stage3_4_68NumDims), coder.const(x_stage3_stage3_4_69NumDims), coder.const(x_stage3_stage3_4_70NumDims)]);

            % Reshape:
            [shape1112, x_stage3_stage3_4_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_4_Tr, x_stage3_stage3_4__5, coder.const(x_stage3_stage3_4_TrNumDims), 0);
            x_stage3_stage3_4_Re = reshape(x_stage3_stage3_4_Tr, shape1112{:});

            % Shape:
            [x_stage3_stage3_5_55, x_stage3_stage3_5_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_4_Re, coder.const(x_stage3_stage3_4_ReNumDims), 0, coder.const(x_stage3_stage3_4_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_5_40, x_stage3_stage3_5_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_5_55, this.Vars.x_stage3_stage3_5_18, 0, coder.const(x_stage3_stage3_5_55NumDims), this.NumDims.x_stage3_stage3_5_18);

            % Add:
            x_stage3_stage3_5_Ad = x_stage3_stage3_5_40 + this.Vars.x_stage3_stage3_5_10;
            x_stage3_stage3_5_AdNumDims = max(coder.const(x_stage3_stage3_5_40NumDims), this.NumDims.x_stage3_stage3_5_10);

            % Div:
            x_stage3_stage3_5_34 = fix(x_stage3_stage3_5_Ad ./ this.Vars.x_stage3_stage3_5_11);
            x_stage3_stage3_5_34NumDims = max(coder.const(x_stage3_stage3_5_AdNumDims), this.NumDims.x_stage3_stage3_5_11);

            % Mul:
            x_stage3_stage3_5_46 = x_stage3_stage3_5_34 .* this.Vars.x_stage3_stage3_5_12;
            x_stage3_stage3_5_46NumDims = max(coder.const(x_stage3_stage3_5_34NumDims), this.NumDims.x_stage3_stage3_5_12);

            % Slice:
            [indices1113, x_stage3_stage3_5_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_4_Re, this.Vars.x_stage3_stage3_5__9, x_stage3_stage3_5_46, this.Vars.x_stage3_stage3_5_18, '', coder.const(x_stage3_stage3_4_ReNumDims));
            x_stage3_stage3_5_61 = x_stage3_stage3_4_Re(indices1113{:});

            % Mul:
            x_stage3_stage3_5_Mu = x_stage3_stage3_5_34 .* this.Vars.x_stage3_stage3_5_13;
            x_stage3_stage3_5_MuNumDims = max(coder.const(x_stage3_stage3_5_34NumDims), this.NumDims.x_stage3_stage3_5_13);

            % Slice:
            [indices1114, x_stage3_stage3_5_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_4_Re, x_stage3_stage3_5_46, x_stage3_stage3_5_Mu, this.Vars.x_stage3_stage3_5_18, '', coder.const(x_stage3_stage3_4_ReNumDims));
            x_stage3_stage3_5_Sl = x_stage3_stage3_4_Re(indices1114{:});

            % Set graph output arguments
            x_stage3_stage3_5_SlNumDims1033 = coder.const(x_stage3_stage3_5_SlNumDims);
            x_stage3_stage3_5_61NumDims1034 = coder.const(x_stage3_stage3_5_61NumDims);

        end

    end

end