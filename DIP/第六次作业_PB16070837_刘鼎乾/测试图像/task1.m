clear 
clc 
close all;
f=imread('2.png');
figure;
f=rgb2gray(f);
imshow(f);
[gv,t]=edge(f,'canny');

figure;
imshow(gv);

figure;
[H,theta,rho]=hough(gv,'Theta',-90:0.2:90-0.2);
imshow(H,[],'XData',theta,'YData',rho,'initialMagnification','fit');

axis on, axis normal
xlabel('\theta'),ylabel('\rhp');

[x,y]=lineextraction(f);
% Plot the line in the image
figure; imshow(f, [min(min(f)) max(max(f))]), hold on
plot([x(1) y(1)], [x(2) y(2)],'LineWidth',2,'Color','blue');
plot(x(1),x(2),'x','LineWidth',2,'Color','red');
plot(y(1),y(2),'x','LineWidth',2,'Color','red');
hold off

    

