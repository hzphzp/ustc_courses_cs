
im_0=imread('2.tif');
im_0=im2double(im_0);
im_1=im2bw(im_0);

se = strel('disk',40);
im_2= myopen(im_0,se);

im_3=imsubtract(im_0,im_2);
im_3=mapminmax(im_3, 0, 1);
im_4=im2bw(im_3);


figure(1);
imshow(im_0);
figure(2);  
imshow(im_1);
figure(3);
imshow(im_2);
figure(4);
imshow(im_3);
figure(5);
imshow(im_4);


