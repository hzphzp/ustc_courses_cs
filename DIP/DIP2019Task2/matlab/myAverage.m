function [img_2] = myAverage(img_1)
img_1 = im2double(img_1);
%% 调用均值滤波4次
for i = 1: 4
    img_1 = getOnce(img_1);
end
img_2 = img_1;
img_2 = im2uint8(img_2);
end

%% 这个函数实现一次的滤波
function img_2 = getOnce(img_1)
size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = zeros(h, w);
weight = ones(3, 3);
data = zeros(3, 3);
% 请在下面继续完成均值滤波功能代码
for i = 1: h
    for j = 1: w
        %% 这里获得周围的9个像素点的位置， 这里使用min，max来防止边缘处的越界错误， 相当于是近邻值得padding
        for a = 1: 3
            for b = 1: 3
                data(a, b) = img_1(min(max(i - 2 + a, 1), h), min(max(j - 2 + b, 1), w));
            end
        end
        %% 这里系数和9个周围像素点取加权平均
        img_2(i, j) = sum(sum(weight.* data)) / 9; 
    end
end
end


