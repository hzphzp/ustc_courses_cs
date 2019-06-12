clc;
clear;

im_0=imread('../data/1.tif');
[m,n]=size(im_0);
im_reverse=~im_0;
im_temp=true(m,n);
im_temp(2:m-1,2:n-1)=false(m-2,n-2);

im_label=im_reverse & im_temp;
im_next=myReconstruction(im_label,im_reverse);
im_h=~im_next;
im_h=imresize(im_h,0.5);
imshow(im_h);