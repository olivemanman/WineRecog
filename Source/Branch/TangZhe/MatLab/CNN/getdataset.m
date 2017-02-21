function [names labels] = getdataset(path)

folder_list = dir(path);
[folder_num, tmp] = size(folder_list);
count = 1;

for i = 3:folder_num
    file_filter = [path, '\', folder_list(i).name, '\', '*.jpg'];
    file_list = dir(file_filter);
    [file_num, tmp] = size(file_list);
    
    % get the label of current folder
    label_file_name = [path, '\', folder_list(i).name, '\label.txt'];
    current_label = load(label_file_name);
    
    % get the file names
    for j = 1:file_num
        names{1,count} = [path, '\', folder_list(i).name, '\', file_list(j).name];
        labels(:, count) = current_label;
        
        count = count + 1;
    end
end
