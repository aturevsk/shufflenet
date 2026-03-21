%% Add %#codegen pragma to all auto-generated custom layers
% This enables code generation for custom layers created by
% importNetworkFromPyTorch. Without the pragma, MATLAB Coder
% refuses to generate code for these layers.

fprintf('Adding %%#codegen pragmas to custom layers...\n');

customLayerDir = fullfile(pwd, '+shufflenet_exported');
if ~isfolder(customLayerDir)
    error('Custom layer directory not found: %s', customLayerDir);
end

% Process custom layer class files
files = dir(fullfile(customLayerDir, '*.m'));
modified = 0;
for i = 1:numel(files)
    fpath = fullfile(files(i).folder, files(i).name);
    content = fileread(fpath);
    if ~contains(content, '%#codegen')
        % Find the end of the classdef line (including multi-line classdefs)
        % and add %#codegen right after
        lines = strsplit(content, newline);
        newLines = {};
        inClassdef = false;
        pragmaAdded = false;
        for j = 1:numel(lines)
            newLines{end+1} = lines{j}; %#ok<AGROW>
            if ~pragmaAdded
                if contains(lines{j}, 'classdef')
                    inClassdef = true;
                end
                if inClassdef && ~contains(lines{j}, '...')
                    % End of classdef line, add pragma
                    newLines{end+1} = '    %#codegen'; %#ok<AGROW>
                    pragmaAdded = true;
                    inClassdef = false;
                end
            end
        end
        newContent = strjoin(newLines, newline);
        fid = fopen(fpath, 'w');
        fwrite(fid, newContent);
        fclose(fid);
        modified = modified + 1;
        fprintf('  Added to: %s\n', files(i).name);
    end
end

% Process ops files
opsDir = fullfile(customLayerDir, '+ops');
if isfolder(opsDir)
    opsFiles = dir(fullfile(opsDir, '*.m'));
    for i = 1:numel(opsFiles)
        fpath = fullfile(opsFiles(i).folder, opsFiles(i).name);
        content = fileread(fpath);
        if ~contains(content, '%#codegen')
            % Add %#codegen after first function line
            lines = strsplit(content, newline);
            newLines = {};
            pragmaAdded = false;
            for j = 1:numel(lines)
                newLines{end+1} = lines{j}; %#ok<AGROW>
                if ~pragmaAdded && startsWith(strtrim(lines{j}), 'function')
                    newLines{end+1} = '%#codegen'; %#ok<AGROW>
                    pragmaAdded = true;
                end
            end
            newContent = strjoin(newLines, newline);
            fid = fopen(fpath, 'w');
            fwrite(fid, newContent);
            fclose(fid);
            modified = modified + 1;
            fprintf('  Added to ops: %s\n', opsFiles(i).name);
        end
    end
end

fprintf('Done. Modified %d files.\n', modified);
