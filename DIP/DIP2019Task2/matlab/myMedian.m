function [img_2] = myMedian(img_1)
img_1 = im2double(img_1);
%% 调用中值滤波4次
for i = 1: 4
    img_1 = getOnce(img_1);
end
img_2 = img_1;
img_2 = im2uint8(img_2);        
end

%% 下面的函数是一次的均值滤波
function img_2 = getOnce(img_1)
size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = zeros(h, w);
data = zeros(3, 3);
for i = 1: h
    for j = 1: w
        %% 这里获得周围的9个像素点的位置， 这里使用min，max来防止边缘处的越界错误，相当于是近邻值的padding
        for a = 1:3
            for b = 1:3
                data(a, b) = img_1(min(max(i - 2 + a, 1), h), min(max(j - 2 + b, 1), w));
            end
        end
        %% 取9 个像素点的中值
        img_2(i, j) = median(data(:));
    end
end
end


