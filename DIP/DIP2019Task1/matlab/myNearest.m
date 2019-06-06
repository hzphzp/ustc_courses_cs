function [img_2] = nearest(img_1, n)
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
for x = 1: h_2
    for y = 1: w_2
        %% 获取这个像素点在原图的坐标， 以及坐标的整数部分和小数部分
        i = floor(x / n);
        j = floor(y / n);
        u = x / n - i;
        v = y / n - j;
        %% 寻找原图中离这个坐标最近的点 这里使用min，max来防止边缘处的越界错误
        if u < 0.5 && v < 0.5
            img_2(x, y) = img_1(min(max(i, 1), h_1), min(max(j, 1), w_1));
        elseif u >= 0.5 && v < 0.5
            img_2(x, y) = img_1(min(max(i + 1, 1), h_1), min(max(j, 1), w_1));
        elseif u < 0.5 && v >= 0.5
            img_2(x, y) = img_1(min(max(i, 1), h_1), min(max(j + 1, 1), w_1));
        else
            img_2(x, y) = img_1(min(max(i + 1, 1), h_1), min(max(j + 1, 1), w_1));
        end
    end
end
%% 这里将灰度值从0到1的double 变到了0到255 的int型
img_2 = im2uint8(img_2);
end


