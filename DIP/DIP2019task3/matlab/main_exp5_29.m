%% 请大家完成:
% 由运动模糊和加性噪声污染的退化函数 motionblur.m 
% 全逆滤波/半径受限逆滤波函数 my_inverse.m
% 维纳滤波函数 wiener.m 
%% 运行 main_exp5_29.m 获得滤波后的效果

clc;
clear;
close all;

%% 课本图 5.29
% 读取图片
im = imread('demo-2.jpg');   % 原始图像 688x688 uint8

%% 图像退化（运动模糊+高斯噪声）
sigma = 0.01
[H, im1_f] = motionblur(im, sigma);        % 噪声方差=0.01
[~, im2_f] = motionblur(im, sigma*0.1);        
[~, im3_f] = motionblur(im, sigma*0.00001);        % H：退化模型

%% 全逆滤波，半径受限逆滤波
D0 = 33;    % 半径
[~, im1_inverse] = my_inverse(im1_f, H, D0);
[~, im2_inverse] = my_inverse(im2_f, H, D0);
[~, im3_inverse] = my_inverse(im3_f, H, D0);
% [im1_inverse, ~] = my_inverse(im1_f, H, D0);
% [im2_inverse, ~] = my_inverse(im2_f, H, D0);
% [im3_inverse, ~] = my_inverse(im3_f, H, D0);

%% 维纳滤波
K = 0.0001;
im1_wiener = my_wiener(im1_f, H, K);
im2_wiener = my_wiener(im2_f, H, K);
im3_wiener = my_wiener(im3_f, H, K);

%% 显示结果
figure(1); 
subplot(331); imshow(im1_f); title('运动模糊+加性噪声(sigma)'); axis on
subplot(332); imshow(im1_inverse); title('逆滤波结果'); axis on
subplot(333); imshow(im1_wiener); title('维纳滤波结果'); axis on
subplot(334); imshow(im2_f); title('运动模糊+加性噪声(sigma*0.1)'); axis on
subplot(335); imshow(im2_inverse); title('逆滤波结果'); axis on
subplot(336); imshow(im2_wiener); title('维纳滤波结果'); axis on
subplot(337); imshow(im3_f); title('运动模糊+加性噪声(sigma*0.00001)'); axis on
subplot(338); imshow(im3_inverse); title('逆滤波结果'); axis on
subplot(339); imshow(im3_wiener); title('维纳滤波结果'); axis on
