
im_0=imread('1.tif');
im_erode=imerode(im_0,ones(51,1));
im_open=imopen(im_0,ones(51,1));
im_dest=imreconstruct(im_erode,im_0);

im_erode=imresize(im_erode,0.5);
im_open=imresize(im_open,0.5);
im_dest=imresize(im_dest,0.5);

figure(1);
imshow(im_erode);

figure(2);
imshow(im_open);

figure(3);
imshow(im_dest);
