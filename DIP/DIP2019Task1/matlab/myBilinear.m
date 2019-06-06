function [img_2] = bilinear(img_1, n)
%% 这里将图像的灰度值大小从255 的int 变成了0到1 的double
img_1 = im2double(img_1);
%% 获取新的图像的尺寸
size_1 = size(img_1);
h_1 = size_1(1);
w_1 = size_1(2);
h_2 = floor(h_1 * n);
w_2 = floor(w_1 * n);
img_2 = zeros(h_2, w_2);
%% 对新的图像的每个像素点的灰度值进行赋值
for x = 1: w_2
    for y = 1: h_2
        %% 获取这个像素点在原图的坐标， 以及坐标的整数部分和小数部分
        i = floor(x / n);
        j = floor(y / n);
        u = x / n - i;
        v = y / n - j;
        i = max(i, 1);
        i = min(i + 1, h_1) - 1;
        j = max(j, 1);
        j = min(j + 1, w_1) - 1;
        %% 使用周围4个整数像素点进行插值 这里使用min，max来防止边缘处的越界错误
        img_2(x, y) = (1-u) * (1-v) * img_1(i, j)...
            + (1-u) * v * img_1(i, j+1)...
            + u * (1-v) * img_1(i+1, j)...
            + u * v * img_1(i+1, j+1);
    end
end
%% 这里将灰度值从0到1的double 变到了0到255 的int型
img_2 = im2uint8(img_2);
end

