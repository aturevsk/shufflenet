classdef Shape_To_SliceLayer1004 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.Shape_To_SliceLayer1004(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.Shape_To_SliceLayer1004(cgInstance.Name);
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
        function this = Shape_To_SliceLayer1004(mlInstance)
            this.Name = mlInstance.Name;
            this.NumOutputs = 2;
            this.OutputNames = {'x_stage3_stage3_1_Sl', 'x_stage3_stage3_1_61'};
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

        function [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61] = predict(this, x_stage3_stage3_0__5__)
            if isdlarray(x_stage3_stage3_0__5__)
                x_stage3_stage3_0__5_ = stripdims(x_stage3_stage3_0__5__);
            else
                x_stage3_stage3_0__5_ = x_stage3_stage3_0__5__;
            end
            x_stage3_stage3_0__5NumDims = 4;
            x_stage3_stage3_0__5 = shufflenet_v2.coder.ops.permuteInputVar(x_stage3_stage3_0__5_, [4 3 1 2], 4);

            [x_stage3_stage3_1_Sl__, x_stage3_stage3_1_61__, x_stage3_stage3_1_SlNumDims__, x_stage3_stage3_1_61NumDims__] = Shape_To_SliceGraph1015(this, x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, false);
            x_stage3_stage3_1_Sl_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_1_Sl__, [3 4 2 1], 4);
            x_stage3_stage3_1_61_ = shufflenet_v2.coder.ops.permuteOutputVar(x_stage3_stage3_1_61__, [3 4 2 1], 4);

            x_stage3_stage3_1_Sl = dlarray(single(x_stage3_stage3_1_Sl_), 'SSCB');
            x_stage3_stage3_1_61 = dlarray(single(x_stage3_stage3_1_61_), 'SSCB');
        end

        function [x_stage3_stage3_1_Sl, x_stage3_stage3_1_61, x_stage3_stage3_1_SlNumDims1017, x_stage3_stage3_1_61NumDims1018] = Shape_To_SliceGraph1015(this, x_stage3_stage3_0__5, x_stage3_stage3_0__5NumDims, Training)

            % Execute the operators:
            % Shape:
            [x_stage3_stage3_0_34, x_stage3_stage3_0_34NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_0__5, coder.const(x_stage3_stage3_0__5NumDims), 0, coder.const(x_stage3_stage3_0__5NumDims)+1);

            % Gather:
            [x_stage3_stage3_0_24, x_stage3_stage3_0_24NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_0_34, this.Vars.x_stage3_stage3_0_11, 0, coder.const(x_stage3_stage3_0_34NumDims), this.NumDims.x_stage3_stage3_0_11);

            % Shape:
            [x_stage3_stage3_0_Sh, x_stage3_stage3_0_ShNumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_0__5, coder.const(x_stage3_stage3_0__5NumDims), 0, coder.const(x_stage3_stage3_0__5NumDims)+1);

            % Gather:
            [x_stage3_stage3_0_Ga, x_stage3_stage3_0_GaNumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_0_Sh, this.Vars.x_stage3_stage3_0__6, 0, coder.const(x_stage3_stage3_0_ShNumDims), this.NumDims.x_stage3_stage3_0__6);

            % Shape:
            [x_stage3_stage3_0_32, x_stage3_stage3_0_32NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_0__5, coder.const(x_stage3_stage3_0__5NumDims), 0, coder.const(x_stage3_stage3_0__5NumDims)+1);

            % Gather:
            [x_stage3_stage3_0_22, x_stage3_stage3_0_22NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_0_32, this.Vars.x_stage3_stage3_0__7, 0, coder.const(x_stage3_stage3_0_32NumDims), this.NumDims.x_stage3_stage3_0__7);

            % Shape:
            [x_stage3_stage3_0_33, x_stage3_stage3_0_33NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_0__5, coder.const(x_stage3_stage3_0__5NumDims), 0, coder.const(x_stage3_stage3_0__5NumDims)+1);

            % Gather:
            [x_stage3_stage3_0_23, x_stage3_stage3_0_23NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_0_33, this.Vars.x_stage3_stage3_0__8, 0, coder.const(x_stage3_stage3_0_33NumDims), this.NumDims.x_stage3_stage3_0__8);

            % Div:
            x_stage3_stage3_0_Di = fix(x_stage3_stage3_0_Ga ./ this.Vars.x_stage3_stage3_0__9);
            x_stage3_stage3_0_DiNumDims = max(coder.const(x_stage3_stage3_0_GaNumDims), this.NumDims.x_stage3_stage3_0__9);

            % Cast:
            x_stage3_stage3_0__1 = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_0_Di)), 'like', x_stage3_stage3_0_Di);
            x_stage3_stage3_0__1NumDims = coder.const(x_stage3_stage3_0_DiNumDims);

            % Cast:
            x_stage3_stage3_0_Ca = cast(int64(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_0__1)), 'like', x_stage3_stage3_0__1);
            x_stage3_stage3_0_CaNumDims = coder.const(x_stage3_stage3_0__1NumDims);

            % Unsqueeze:
            [shape1050, x_stage3_stage3_0_46NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_24, this.Vars.onnx__Unsqueeze_613, coder.const(x_stage3_stage3_0_24NumDims));
            x_stage3_stage3_0_46 = reshape(x_stage3_stage3_0_24, shape1050);

            % Unsqueeze:
            [shape1051, x_stage3_stage3_0_UnNumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_Ca, this.Vars.onnx__Unsqueeze_617, coder.const(x_stage3_stage3_0_CaNumDims));
            x_stage3_stage3_0_Un = reshape(x_stage3_stage3_0_Ca, shape1051);

            % Unsqueeze:
            [shape1052, x_stage3_stage3_0_40NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_22, this.Vars.onnx__Unsqueeze_619, coder.const(x_stage3_stage3_0_22NumDims));
            x_stage3_stage3_0_40 = reshape(x_stage3_stage3_0_22, shape1052);

            % Unsqueeze:
            [shape1053, x_stage3_stage3_0_41NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_23, this.Vars.onnx__Unsqueeze_621, coder.const(x_stage3_stage3_0_23NumDims));
            x_stage3_stage3_0_41 = reshape(x_stage3_stage3_0_23, shape1053);

            % Concat:
            [x_stage3_stage3_0_Co, x_stage3_stage3_0_CoNumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_0_46, this.Vars.x_stage3_stage3_0_10, x_stage3_stage3_0_Un, x_stage3_stage3_0_40, x_stage3_stage3_0_41}, [coder.const(x_stage3_stage3_0_46NumDims), this.NumDims.x_stage3_stage3_0_10, coder.const(x_stage3_stage3_0_UnNumDims), coder.const(x_stage3_stage3_0_40NumDims), coder.const(x_stage3_stage3_0_41NumDims)]);

            % Reshape:
            [shape1054, x_stage3_stage3_0_29NumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_0__5, x_stage3_stage3_0_Co, coder.const(x_stage3_stage3_0__5NumDims), 0);
            x_stage3_stage3_0_29 = reshape(x_stage3_stage3_0__5, shape1054{:});

            % Transpose:
            [perm1055, x_stage3_stage3_0_TrNumDims] = shufflenet_v2.coder.ops.prepareTransposeArgs(this.Vars.TransposePerm1016, coder.const(x_stage3_stage3_0_29NumDims));
            if isempty(perm1055)
                x_stage3_stage3_0_Tr = x_stage3_stage3_0_29;
            else
                x_stage3_stage3_0_Tr = permute(shufflenet_v2.coder.ops.extractIfDlarray(x_stage3_stage3_0_29), perm1055);
            end

            % Unsqueeze:
            [shape1056, x_stage3_stage3_0_42NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_24, this.Vars.onnx__Unsqueeze_626, coder.const(x_stage3_stage3_0_24NumDims));
            x_stage3_stage3_0_42 = reshape(x_stage3_stage3_0_24, shape1056);

            % Unsqueeze:
            [shape1057, x_stage3_stage3_0_43NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_Ga, this.Vars.onnx__Unsqueeze_628, coder.const(x_stage3_stage3_0_GaNumDims));
            x_stage3_stage3_0_43 = reshape(x_stage3_stage3_0_Ga, shape1057);

            % Unsqueeze:
            [shape1058, x_stage3_stage3_0_44NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_22, this.Vars.onnx__Unsqueeze_630, coder.const(x_stage3_stage3_0_22NumDims));
            x_stage3_stage3_0_44 = reshape(x_stage3_stage3_0_22, shape1058);

            % Unsqueeze:
            [shape1059, x_stage3_stage3_0_45NumDims] = shufflenet_v2.coder.ops.prepareUnsqueezeArgs(x_stage3_stage3_0_23, this.Vars.onnx__Unsqueeze_632, coder.const(x_stage3_stage3_0_23NumDims));
            x_stage3_stage3_0_45 = reshape(x_stage3_stage3_0_23, shape1059);

            % Concat:
            [x_stage3_stage3_0__4, x_stage3_stage3_0__4NumDims] = shufflenet_v2.coder.ops.onnxConcat(0, {x_stage3_stage3_0_42, x_stage3_stage3_0_43, x_stage3_stage3_0_44, x_stage3_stage3_0_45}, [coder.const(x_stage3_stage3_0_42NumDims), coder.const(x_stage3_stage3_0_43NumDims), coder.const(x_stage3_stage3_0_44NumDims), coder.const(x_stage3_stage3_0_45NumDims)]);

            % Reshape:
            [shape1060, x_stage3_stage3_0_ReNumDims] = shufflenet_v2.coder.ops.prepareReshapeArgs(x_stage3_stage3_0_Tr, x_stage3_stage3_0__4, coder.const(x_stage3_stage3_0_TrNumDims), 0);
            x_stage3_stage3_0_Re = reshape(x_stage3_stage3_0_Tr, shape1060{:});

            % Shape:
            [x_stage3_stage3_1_55, x_stage3_stage3_1_55NumDims] = shufflenet_v2.coder.ops.onnxShape(x_stage3_stage3_0_Re, coder.const(x_stage3_stage3_0_ReNumDims), 0, coder.const(x_stage3_stage3_0_ReNumDims)+1);

            % Gather:
            [x_stage3_stage3_1_40, x_stage3_stage3_1_40NumDims] = shufflenet_v2.coder.ops.onnxGather(x_stage3_stage3_1_55, this.Vars.x_stage3_stage3_1_18, 0, coder.const(x_stage3_stage3_1_55NumDims), this.NumDims.x_stage3_stage3_1_18);

            % Add:
            x_stage3_stage3_1_Ad = x_stage3_stage3_1_40 + this.Vars.x_stage3_stage3_1_10;
            x_stage3_stage3_1_AdNumDims = max(coder.const(x_stage3_stage3_1_40NumDims), this.NumDims.x_stage3_stage3_1_10);

            % Div:
            x_stage3_stage3_1_34 = fix(x_stage3_stage3_1_Ad ./ this.Vars.x_stage3_stage3_1_11);
            x_stage3_stage3_1_34NumDims = max(coder.const(x_stage3_stage3_1_AdNumDims), this.NumDims.x_stage3_stage3_1_11);

            % Mul:
            x_stage3_stage3_1_46 = x_stage3_stage3_1_34 .* this.Vars.x_stage3_stage3_1_12;
            x_stage3_stage3_1_46NumDims = max(coder.const(x_stage3_stage3_1_34NumDims), this.NumDims.x_stage3_stage3_1_12);

            % Slice:
            [indices1061, x_stage3_stage3_1_61NumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_0_Re, this.Vars.x_stage3_stage3_1__9, x_stage3_stage3_1_46, this.Vars.x_stage3_stage3_1_18, '', coder.const(x_stage3_stage3_0_ReNumDims));
            x_stage3_stage3_1_61 = x_stage3_stage3_0_Re(indices1061{:});

            % Mul:
            x_stage3_stage3_1_Mu = x_stage3_stage3_1_34 .* this.Vars.x_stage3_stage3_1_13;
            x_stage3_stage3_1_MuNumDims = max(coder.const(x_stage3_stage3_1_34NumDims), this.NumDims.x_stage3_stage3_1_13);

            % Slice:
            [indices1062, x_stage3_stage3_1_SlNumDims] = shufflenet_v2.coder.ops.prepareSliceArgs(x_stage3_stage3_0_Re, x_stage3_stage3_1_46, x_stage3_stage3_1_Mu, this.Vars.x_stage3_stage3_1_18, '', coder.const(x_stage3_stage3_0_ReNumDims));
            x_stage3_stage3_1_Sl = x_stage3_stage3_0_Re(indices1062{:});

            % Set graph output arguments
            x_stage3_stage3_1_SlNumDims1017 = coder.const(x_stage3_stage3_1_SlNumDims);
            x_stage3_stage3_1_61NumDims1018 = coder.const(x_stage3_stage3_1_61NumDims);

        end

    end

end