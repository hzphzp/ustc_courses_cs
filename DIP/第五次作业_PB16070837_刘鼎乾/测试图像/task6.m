f=imread('4.tif');
se =strel('disk',30);
fo =myclose(f,se);
figure(1);
imshow(fo);

se =strel('disk',60);

foo=myopen(fo,se);

figure(2);
imshow(foo);

f_temp=foo-imerode(foo,ones(3,3));
figure(3);
imshow(f_temp);

f_1=f+f_temp;
figure(4);
imshow(f_1);
