%% 请大家完成两个空域滤波算法函数 myAverage.m、myMedian.m，然后将本主程序中的变量
%% filename设置为'circuit'，运行main_filter.m，即可得到滤波后结果
%%
clc; 
clear;
close all;

%% 读取图像
filename = 'circuit'; % 受到椒盐噪声污染的电路板X射线图像
im = imread([filename, '.jpg']);

%% 将图像进行均值滤波
im_a = myAverage(im);

%% 将图像进行中值滤波
im_m = myMedian(im);

%% 将结果保存到当前目录下的result文件夹下
imwrite(im_a, sprintf('result/_%s_a.jpg', filename));
imwrite(im_m, sprintf('result/_%s_m.jpg', filename));

%% 显示结果
figure(1); 
subplot(131); imshow(im); title('原图'); axis on
subplot(132); imshow(im_a); title('均值滤波'); axis on
subplot(133); imshow(im_m); title('中值滤波'); axis on
