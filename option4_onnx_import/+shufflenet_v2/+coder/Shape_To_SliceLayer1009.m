classdef Shape_To_SliceLayer1009 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1009(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1009(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1009(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_6_Sl', 'x_stage3_stage3_6_61'};
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

        function [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61] = predict(this, x_stage3_stage3_5__6__)
            if isdlarray(x_stage3_stage3_5__6__)
                x_stage3_stage3_5__6_ = stripdims(x_stage3_stage3_5__6__);
            else
                x_stage3_stage3_5__6_ = x_stage3_stage3_5__6__;
            end
            x_stage3_stage3_5__6NumDims = 4;
            x_stage3_stage3_5__6 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_5__6_, [4 3 1 2], 4);

            [x_stage3_stage3_6_Sl__, x_stage3_stage3_6_61__, x_stage3_stage3_6_SlNumDims__, x_stage3_stage3_6_61NumDims__] = Shape_To_SliceGraph1035(this, x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, false);
            x_stage3_stage3_6_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_6_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_6_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_6_61__, [3 4 2 1], 4);

            x_stage3_stage3_6_Sl = dlarray(single(x_stage3_stage3_6_Sl_), 'SSCB');
            x_stage3_stage3_6_61 = dlarray(single(x_stage3_stage3_6_61_), 'SSCB');
        end

        function [x_stage3_stage3_6_Sl, x_stage3_stage3_6_61, x_stage3_stage3_6_SlNumDims1037, x_stage3_stage3_6_61NumDims1038] = Shape_To_SliceGraph1035(this, x_stage3_stage3_5__6, x_stage3_stage3_5__6NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_5_Sh, x_stage3_stage3_5_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_5__6, coder.const(x_stage3_stage3_5__6NumDims), 0, coder.const(x_stage3_stage3_5__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_5_Ga, x_stage3_stage3_5_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_5_Sh, this.Vars.x_stage3_stage3_5_14, 0, coder.const(x_stage3_stage3_5_ShNumDims), this.NumDims.x_stage3_stage3_5_14);

            % Shape:
            [x_stage3_stage3_5_52, x_stage3_stage3_5_52NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_5__6, coder.const(x_stage3_stage3_5__6NumDims), 0, coder.const(x_stage3_stage3_5__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_5_37, x_stage3_stage3_5_37NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_5_52, this.Vars.x_stage3_stage3_5_15, 0, coder.const(x_stage3_stage3_5_52NumDims), this.NumDims.x_stage3_stage3_5_15);

            % Shape:
            [x_stage3_stage3_5_53, x_stage3_stage3_5_53NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_5__6, coder.const(x_stage3_stage3_5__6NumDims), 0, coder.const(x_stage3_stage3_5__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_5_38, x_stage3_stage3_5_38NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_5_53, this.Vars.x_stage3_stage3_5_16, 0, coder.const(x_stage3_stage3_5_53NumDims), this.NumDims.x_stage3_stage3_5_16);

            % Shape:
            [x_stage3_stage3_5_54, x_stage3_stage3_5_54NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_5__6, coder.const(x_stage3_stage3_5__6NumDims), 0, coder.const(x_stage3_stage3_5__6NumDims)+1);

            % Gather:
            [x_stage3_stage3_5_39, x_stage3_stage3_5_39NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_5_54, this.Vars.x_stage3_stage3_5_17, 0, coder.const(x_stage3_stage3_5_54NumDims), this.NumDims.x_stage3_stage3_5_17);

            % Div:
            x_stage3_stage3_5_Di = fix(x_stage3_stage3_5_37 ./ this.Vars.x_stage3_stage3_5__7);
            x_stage3_stage3_5_DiNumDims = max(coder.const(x_stage3_stage3_5_37NumDims), this.NumDims.x_stage3_stage3_5__7);

            % Cast:
            x_stage3_stage3_5__2 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_5_Di)), 'like', x_stage3_stage3_5_Di);
            x_stage3_stage3_5__2NumDims = coder.const(x_stage3_stage3_5_DiNumDims);

            % Cast:
            x_stage3_stage3_5_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_5__2)), 'like', x_stage3_stage3_5__2);
            x_stage3_stage3_5_CaNumDims = coder.const(x_stage3_stage3_5__2NumDims);

            % Unsqueeze:
            [shape1115, x_stage3_stage3_5_71NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ga, this.Vars.onnx__Unsqueeze_923, coder.const(x_stage3_stage3_5_GaNumDims));
            x_stage3_stage3_5_71 = reshape(x_stage3_stage3_5_Ga, shape1115);

            % Unsqueeze:
            [shape1116, x_stage3_stage3_5_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ca, this.Vars.onnx__Unsqueeze_927, coder.const(x_stage3_stage3_5_CaNumDims));
            x_stage3_stage3_5_Un = reshape(x_stage3_stage3_5_Ca, shape1116);

            % Unsqueeze:
            [shape1117, x_stage3_stage3_5_65NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_38, this.Vars.onnx__Unsqueeze_929, coder.const(x_stage3_stage3_5_38NumDims));
            x_stage3_stage3_5_65 = reshape(x_stage3_stage3_5_38, shape1117);

            % Unsqueeze:
            [shape1118, x_stage3_stage3_5_66NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_39, this.Vars.onnx__Unsqueeze_931, coder.const(x_stage3_stage3_5_39NumDims));
            x_stage3_stage3_5_66 = reshape(x_stage3_stage3_5_39, shape1118);

            % Concat:
            [x_stage3_stage3_5_Co, x_stage3_stage3_5_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_5_71, this.Vars.x_stage3_stage3_5__8, x_stage3_stage3_5_Un, x_stage3_stage3_5_65, x_stage3_stage3_5_66}, [coder.const(x_stage3_stage3_5_71NumDims), this.NumDims.x_stage3_stage3_5__8, coder.const(x_stage3_stage3_5_UnNumDims), coder.const(x_stage3_stage3_5_65NumDims), coder.const(x_stage3_stage3_5_66NumDims)]);

            % Reshape:
            [shape1119, x_stage3_stage3_5_49NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_5__6, x_stage3_stage3_5_Co, coder.const(x_stage3_stage3_5__6NumDims), 0);
            x_stage3_stage3_5_49 = reshape(x_stage3_stage3_5__6, shape1119{:});

            % Transpose:
            [perm1120, x_stage3_stage3_5_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1036, coder.const(x_stage3_stage3_5_49NumDims));
            if isempty(perm1120)
                x_stage3_stage3_5_Tr = x_stage3_stage3_5_49;
            else
                x_stage3_stage3_5_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_5_49), perm1120);
            end

            % Unsqueeze:
            [shape1121, x_stage3_stage3_5_67NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_Ga, this.Vars.onnx__Unsqueeze_936, coder.const(x_stage3_stage3_5_GaNumDims));
            x_stage3_stage3_5_67 = reshape(x_stage3_stage3_5_Ga, shape1121);

            % Unsqueeze:
            [shape1122, x_stage3_stage3_5_68NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_37, this.Vars.onnx__Unsqueeze_938, coder.const(x_stage3_stage3_5_37NumDims));
            x_stage3_stage3_5_68 = reshape(x_stage3_stage3_5_37, shape1122);

            % Unsqueeze:
            [shape1123, x_stage3_stage3_5_69NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_38, this.Vars.onnx__Unsqueeze_940, coder.const(x_stage3_stage3_5_38NumDims));
            x_stage3_stage3_5_69 = reshape(x_stage3_stage3_5_38, shape1123);

            % Unsqueeze:
            [shape1124, x_stage3_stage3_5_70NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_5_39, this.Vars.onnx__Unsqueeze_942, coder.const(x_stage3_stage3_5_39NumDims));
            x_stage3_stage3_5_70 = reshape(x_stage3_stage3_5_39, shape1124);

            % Concat:
            [x_stage3_stage3_5__5, x_stage3_stage3_5__5NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_5_67, x_stage3_stage3_5_68, x_stage3_stage3_5_69, x_stage3_stage3_5_70}, [coder.const(x_stage3_stage3_5_67NumDims), coder.const(x_stage3_stage3_5_68NumDims), coder.const(x_stage3_stage3_5_69NumDims), coder.const(x_stage3_stage3_5_70NumDims)]);

            % Reshape:
            [shape1125, x_stage3_stage3_5_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_5_Tr, x_stage3_stage3_5__5, coder.const(x_stage3_stage3_5_TrNumDims), 0);
            x_stage3_stage3_5_Re = reshape(x_stage3_stage3_5_Tr, shape1125{:});

            % Shape:
            [x_stage3_stage3_6_55, x_stage3_stage3_6_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_5_Re, coder.const(x_stage3_stage3_5_ReNumDims), 0, coder.const(x_stage3_stage3_5_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_6_40, x_stage3_stage3_6_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_6_55, this.Vars.x_stage3_stage3_6_18, 0, coder.const(x_stage3_stage3_6_55NumDims), this.NumDims.x_stage3_stage3_6_18);

            % Add:
            x_stage3_stage3_6_Ad = x_stage3_stage3_6_40 + this.Vars.x_stage3_stage3_6_10;
            x_stage3_stage3_6_AdNumDims = max(coder.const(x_stage3_stage3_6_40NumDims), this.NumDims.x_stage3_stage3_6_10);

            % Div:
            x_stage3_stage3_6_34 = fix(x_stage3_stage3_6_Ad ./ this.Vars.x_stage3_stage3_6_11);
            x_stage3_stage3_6_34NumDims = max(coder.const(x_stage3_stage3_6_AdNumDims), this.NumDims.x_stage3_stage3_6_11);

            % Mul:
            x_stage3_stage3_6_46 = x_stage3_stage3_6_34 .* this.Vars.x_stage3_stage3_6_12;
            x_stage3_stage3_6_46NumDims = max(coder.const(x_stage3_stage3_6_34NumDims), this.NumDims.x_stage3_stage3_6_12);

            % Slice:
            [indices1126, x_stage3_stage3_6_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_5_Re, this.Vars.x_stage3_stage3_6__9, x_stage3_stage3_6_46, this.Vars.x_stage3_stage3_6_18, '', coder.const(x_stage3_stage3_5_ReNumDims));
            x_stage3_stage3_6_61 = x_stage3_stage3_5_Re(indices1126{:});

            % Mul:
            x_stage3_stage3_6_Mu = x_stage3_stage3_6_34 .* this.Vars.x_stage3_stage3_6_13;
            x_stage3_stage3_6_MuNumDims = max(coder.const(x_stage3_stage3_6_34NumDims), this.NumDims.x_stage3_stage3_6_13);

            % Slice:
            [indices1127, x_stage3_stage3_6_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_5_Re, x_stage3_stage3_6_46, x_stage3_stage3_6_Mu, this.Vars.x_stage3_stage3_6_18, '', coder.const(x_stage3_stage3_5_ReNumDims));
            x_stage3_stage3_6_Sl = x_stage3_stage3_5_Re(indices1127{:});

            % Set graph output arguments
            x_stage3_stage3_6_SlNumDims1037 = coder.const(x_stage3_stage3_6_SlNumDims);
            x_stage3_stage3_6_61NumDims1038 = coder.const(x_stage3_stage3_6_61NumDims);

        end

    end

end