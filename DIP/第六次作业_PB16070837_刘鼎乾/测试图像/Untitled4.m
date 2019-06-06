clear 
clc 
close all; 
%RGB = imread('circuit.tif'); 
%RGB = imread('gantrycrane.png'); 
RGB = imread('2.png'); 
%RGB = imread('wanqu.png'); 
I = rgb2gray(RGB); 
BW = edge(I,'canny');% Canny边缘检测 转换二值图像 
figure 
imshow(BW) 
[H,theta,rho] = hough(BW,'RhoResolution',0.5,'ThetaResolution',0.5); 
subplot(2,1,1); 
imshow(RGB); 
title('gantrycrane.png'); 
subplot(2,1,2); 
imshow(imadjust(mat2gray(H)),'XData',theta,'YData',rho,'InitialMagnification','fit'); 
title('Hough transform of gantrycrane.png'); 
xlabel('\theta'), ylabel('\rho'); 
axis on, axis normal, hold on; 
colormap(hot); 
P = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:)))); 
lines = houghlines(BW,theta,rho,P,'FillGap',5,'MinLength',7); 
%% 画出图像中的直线 
figure, 
subplot(2,1,1); 
imshow(BW), hold on 
subplot(2,1,2) 
imshow(BW) 
hold on 
max_len = 0; 
for k = 1:length(lines) 
xy = [lines(k).point1; lines(k).point2]; 
plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green'); 
% Plot beginnings and ends of lines 
plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow'); 
plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red'); 
% Determine the endpoints of the longest line segment 
len = norm(lines(k).point1 - lines(k).point2); 
if ( len > max_len) 
max_len = len; 
xy_long = xy; 
end 
end

% highlight the longest line segment 
plot(xy_long(:,1),xy_long(:,2),'LineWidth',2, 'Color','red');
