function new_img = dicom2jpg(file_name)

info = dicominfo(file_name);
img = dicomread(info);

min_value = min(img(:));
max_value = max(img(:));

ww = max_value - min_value + 1;
wc = (max_value + min_value + 1)/2.0;

[row col] = size(img);
new_img = zeros(row, col);

for i = 1:row
    for j = 1:col
        tmp = img(i, j);
        
        if tmp > (wc + ww/2)
            new_img(i, j) = uint8(255);
        end
        
        if (tmp >= (wc - ww/2)) & (tmp <= (wc + ww/2))
            new_img(i, j) = uint8(255.0/double(ww)*(tmp + ww/2 - wc));
        end
    end
end

new_img = uint8(new_img);
%imshow(new_img, [])
  