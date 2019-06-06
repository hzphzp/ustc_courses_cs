f=imread('2.png');
f=rgb2gray(f);
% Find the longest line segment based on Hough transform.
[x, y] = mylineextraction(f);
% Plot the line in the image
figure; imshow(f, [min(min(f)) max(max(f))]), hold on
plot([x(1) y(1)], [x(2) y(2)],'LineWidth',2,'Color','blue');
plot(x(1),x(2),'x','LineWidth',2,'Color','red');
plot(y(1),y(2),'x','LineWidth',2,'Color','red');
hold off
