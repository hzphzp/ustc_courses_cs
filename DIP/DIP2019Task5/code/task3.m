clc;
clear;

im_0=imread('../data/1.tif');
[m,n]=size(im_0);
im_temp=true(m,n);
im_temp(2:m-1,2:n-1)=false(m-2,n-2);

im_label=im_0 & im_temp;
%se=logical(ones(3000,3000));
%im_dilate=imdilate(im_label,se);

%im_next= im_dilate & im_reverse;
im_next=myReconstruction(im_label,im_0);

im_h=im_0 & (~im_next);
im_h=imresize(im_h,0.5);
imshow(im_h);
