classdef ReduceMeanLayer1016 < nnet.layer.Layer & nnet.layer.Formattable
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
            this_cg = shufflenet_v2.coder.ReduceMeanLayer1016(mlInstance);
        end
        function this_ml = matlabCodegenFromRedirected(cgInstance)
            this_ml = shufflenet_v2.ReduceMeanLayer1016(cgInstance.Name);
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
        function this = ReduceMeanLayer1016(mlInstance)
            this.Name = mlInstance.Name;
            this.OutputNames = {'x_ReduceMean_output_'};
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

        function [x_ReduceMean_output_] = predict(this, x_conv5_conv5_2_Relu__)
            if isdlarray(x_conv5_conv5_2_Relu__)
                x_conv5_conv5_2_Relu_ = stripdims(x_conv5_conv5_2_Relu__);
            else
                x_conv5_conv5_2_Relu_ = x_conv5_conv5_2_Relu__;
            end
            x_conv5_conv5_2_ReluNumDims = 4;
            x_conv5_conv5_2_Relu = shufflenet_v2.coder.ops.permuteInputVar(x_conv5_conv5_2_Relu_, [4 3 1 2], 4);

            [x_ReduceMean_output___, x_ReduceMean_output_NumDims__] = ReduceMeanGraph1061(this, x_conv5_conv5_2_Relu, x_conv5_conv5_2_ReluNumDims, false);
            x_ReduceMean_output__ = shufflenet_v2.coder.ops.permuteOutputVar(x_ReduceMean_output___, [2 1], 2);

            x_ReduceMean_output_ = dlarray(single(x_ReduceMean_output__), 'CB');
        end

        function [x_ReduceMean_output_, x_ReduceMean_output_NumDims1063] = ReduceMeanGraph1061(this, x_conv5_conv5_2_Relu, x_conv5_conv5_2_ReluNumDims, Training)

            % Execute the operators:
            % ReduceMean:
            dims1202 = shufflenet_v2.coder.ops.prepareReduceArgs(this.Vars.ReduceMeanAxes1062, coder.const(x_conv5_conv5_2_ReluNumDims));
            xReduced1203 = mean(x_conv5_conv5_2_Relu, dims1202);
            [x_ReduceMean_output_, x_ReduceMean_output_NumDims] = shufflenet_v2.coder.ops.onnxSqueeze(xReduced1203, this.Vars.ReduceMeanAxes1062, coder.const(x_conv5_conv5_2_ReluNumDims));

            % Set graph output arguments
            x_ReduceMean_output_NumDims1063 = coder.const(x_ReduceMean_output_NumDims);

        end

    end

end