function [img_2] = mySharpen(img_1)
img_1 = im2double(img_1);
size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = zeros(h, w);
% 这里讲 拉普拉斯和 图像增强相结合
weight = [-1 -1 -1; -1 9 -1; -1 -1 -1]
data = zeros(3, 3);

for i = 1: h
    for j = 1: w
        %% 这里获得周围的9个像素点的位置， 这里使用min，max来防止边缘处的越界错误， 相当于是近邻值得padding
        for a = 1: 3
            for b = 1: 3
                data(a, b) = img_1(min(max(i - 2 + a, 1), h), min(max(j - 2 + b, 1), w));
            end
        end
        %% 这里系数和9个周围像素点依次相乘 然后相加 取绝对值
        img_2(i, j) = abs(sum(sum(weight.* data)));
    end
end
end


