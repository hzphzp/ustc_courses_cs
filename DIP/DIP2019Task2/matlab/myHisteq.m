function [img_2] = myHisteq(img_1, n)
%% 这个函数里面使用的都是 uint8型的数据
size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = zeros(h, w, 'uint8');

% 请在下面继续完成直方图均衡化功能代码
%% 统计图像的直方图
stat = zeros(256, 1);
for i = 1: h
    for j = 1: w
        value = img_1(i, j);
        stat(value + 1, 1) = stat(value + 1, 1) + 1;
    end
end
assert(sum(stat(:)) == h * w);
%% 使用统计得来的直方图， 产生统计直方图均衡图像
for i = 1: h
    for j = 1: w
        % 调用的函数在下面有定义
        img_2(i, j) = myDecimalIntegral(stat, img_1(i, j), h * w, n);
    end
end
%% img_2 = im2uint8(img_2); 问题就出现在这里， double 转 int 会自动调用 im2uint8
end


function result = myDecimalIntegral(stat, lastValue, sumOfNumber, n)
%% 计算lastValue 之前累积的灰度点个数
sum = 0;
for x = 1: lastValue + 1
    sum = sum + stat(x, 1);
end
%% 利用之前积分的灰度点个数 来计算新的灰度值
if n == 2
    % 这里单独写, 是为了是2级灰度图像 的分辨更加明显, 0 和255 而不是0 和127
    result = round(sum / sumOfNumber) * 255;
else
    result = floor(sum / sumOfNumber * n) * (256 / n);
end
result = max(0, min(255, result));
end
