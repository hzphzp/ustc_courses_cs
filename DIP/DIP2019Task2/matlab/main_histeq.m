%% 请大家完成直方图均衡化函数 myHisteq.m，然后将本主程序中的变量
%% filename设置‘bridge’，运行main_histeq.m，即可得到直方图均衡化后的结果
%%
clc; 
clear;
close all;

%% 读取图片
filename = 'bridge'; %测试图像1
im = imread([filename, '.jpg']);
n_1 = 2;
n_2 = 64;
n_3 = 256;

%% 将图像进行直方图均衡化
im_histeq_1 = myHisteq(im, n_1);
im_histeq_2 = myHisteq(im, n_2);
im_histeq_3 = myHisteq(im, n_3);

%% 将结果保存到当前目录下的result文件夹下
imwrite(im_histeq_1, sprintf('result/_%s_eq_%.d.jpg', filename, n_1));
imwrite(im_histeq_2, sprintf('result/_%s_eq_%.d.jpg', filename, n_2));
imwrite(im_histeq_3, sprintf('result/_%s_eq_%.d.jpg', filename, n_3));

%% 显示结果
figure(1); 
subplot(221); imshow(im); title('原图'); axis on
subplot(222); imshow(im_histeq_1); title('直方图均衡化, n=2'); axis on
subplot(223); imshow(im_histeq_2); title('直方图均衡化, n=64'); axis on
subplot(224); imshow(im_histeq_3); title('直方图均衡化, n=256'); axis on
