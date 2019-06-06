function [img_2] = bicubic(img_1, n)
%% 这里将图像的灰度值大小从255 的int 变成了0到1 的double
img_1 = im2double(img_1);
%% 获取新的图像的尺寸
size_1 = size(img_1);
h_1 = size_1(1);
w_1 = size_1(2);
h_2 = floor(h_1 * n);
w_2 = floor(w_1 * n);
img_2 = zeros(h_2, w_2);
D = zeros(4, 4);
%% 对新的图像的每个像素点的灰度值进行赋值
for x = 1: w_2
    for y = 1: h_2
        %% 获取这个像素点在原图的坐标， 以及坐标的整数部分和小数部分
        i = floor(x / n);
        j = floor(y / n);
        u = x / n - i;
        v = y / n - j;
        %% 这里获得16个相邻像素点的系数，采用bicubic函数， getWeight函数的实现在下面
        W = getWeight(u, v);
        %% 这里获得周围的16个像素点的位置， 这里使用min，max来防止边缘处的越界错误
        for a = 1:4
            for b = 1:4
                D(a, b) = img_1(min(max(i - 2 + a, 1), h_1), min(max(j - 2 + b, 1), w_1));
            end
        end
        %% 这里系数和16个周围像素点依次相乘 然后相加
        img_2(x, y) = sum(sum(W.* D)); %% 注意这里使用的是点乘
    end
end
%% 这里将灰度值从0到1的double 变到了0到255 的int型
img_2 = im2uint8(img_2);
end

function weight = getWeight(u, v)
weight = zeros(4, 4);
x_weight = zeros(4, 1);
y_weight = zeros(1, 4);
%% 对x， 和y 方向分别计算系数， 最后相乘在一起， 调用的Bic函数在下面有定义
for i = 1: 4
    d = abs(u + 2 - i);
    x_weight(i, 1) = Bic(d);
end
for j = 1: 4
    d = abs(v + 2 - j);
    y_weight(1, j) = Bic(d);
end
weight = x_weight* y_weight;
end

function w = Bic(d)
%% bicubic函数的数学定义， 这里参数a 采用 -1
a = - 1;
if d <= 1
    w = 1 - (a + 3) * d ^ 2 + (a + 2) * d ^ 3;
elseif d > 1 && d < 2
    w = -4 * a + 8 * a * d - 5 * a * d ^ 2 + a * d ^ 3; 
else
    w = 0;
end
end
