classdef ReduceMeanLayer1016 < nnet.layer.Layer & nnet.layer.Formattable
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
            name = 'shufflenet_v2.coder.ReduceMeanLayer1016';
        end
    end


    methods
        function this = ReduceMeanLayer1016(name)
            this.Name = name;
            this.OutputNames = {'x_ReduceMean_output_'};
        end

        function [x_ReduceMean_output_] = predict(this, x_conv5_conv5_2_Relu)
            if isdlarray(x_conv5_conv5_2_Relu)
                x_conv5_conv5_2_Relu = stripdims(x_conv5_conv5_2_Relu);
            end
            x_conv5_conv5_2_ReluNumDims = 4;
            x_conv5_conv5_2_Relu = shufflenet_v2.ops.permuteInputVar(x_conv5_conv5_2_Relu, [4 3 1 2], 4);

            [x_ReduceMean_output_, x_ReduceMean_output_NumDims] = ReduceMeanGraph1061(this, x_conv5_conv5_2_Relu, x_conv5_conv5_2_ReluNumDims, false);
            x_ReduceMean_output_ = shufflenet_v2.ops.permuteOutputVar(x_ReduceMean_output_, [2 1], 2);

            x_ReduceMean_output_ = dlarray(single(x_ReduceMean_output_), 'CB');
        end

        function [x_ReduceMean_output_] = forward(this, x_conv5_conv5_2_Relu)
            if isdlarray(x_conv5_conv5_2_Relu)
                x_conv5_conv5_2_Relu = stripdims(x_conv5_conv5_2_Relu);
            end
            x_conv5_conv5_2_ReluNumDims = 4;
            x_conv5_conv5_2_Relu = shufflenet_v2.ops.permuteInputVar(x_conv5_conv5_2_Relu, [4 3 1 2], 4);

            [x_ReduceMean_output_, x_ReduceMean_output_NumDims] = ReduceMeanGraph1061(this, x_conv5_conv5_2_Relu, x_conv5_conv5_2_ReluNumDims, true);
            x_ReduceMean_output_ = shufflenet_v2.ops.permuteOutputVar(x_ReduceMean_output_, [2 1], 2);

            x_ReduceMean_output_ = dlarray(single(x_ReduceMean_output_), 'CB');
        end

        function [x_ReduceMean_output_, x_ReduceMean_output_NumDims1063] = ReduceMeanGraph1061(this, x_conv5_conv5_2_Relu, x_conv5_conv5_2_ReluNumDims, Training)

            % Execute the operators:
            % ReduceMean:
            dims = shufflenet_v2.ops.prepareReduceArgs(this.Vars.ReduceMeanAxes1062, x_conv5_conv5_2_ReluNumDims);
            xMean = mean(x_conv5_conv5_2_Relu, dims);
            [x_ReduceMean_output_, x_ReduceMean_output_NumDims] = shufflenet_v2.ops.onnxSqueeze(xMean, this.Vars.ReduceMeanAxes1062, x_conv5_conv5_2_ReluNumDims);

            % Set graph output arguments
            x_ReduceMean_output_NumDims1063 = x_ReduceMean_output_NumDims;

        end

    end

end