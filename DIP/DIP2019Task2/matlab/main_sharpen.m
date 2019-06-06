%% 请大家完成图像锐化函数 mySharpen.m，然后将本主程序中的变量
%% filename设置‘moon’，运行main_sharpen.m，即可得到图像锐化后的结果
%%
clc; 
clear;
close all;

%% 读取图片
filename = 'moon'; %测试图像1
im = imread([filename, '.jpg']);

%% 将图像进行锐化
im_s = mySharpen(im);

%% 将结果保存到当前目录下的result文件夹下
imwrite(im_s, sprintf('result/_%s_s.jpg', filename));

%% 显示结果
figure(1); 
subplot(121); imshow(im); title('原图'); axis on
subplot(122); imshow(im_s); title('图像锐化'); axis on

