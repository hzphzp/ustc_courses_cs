f=imread('../data/4.tif');
se =strel('disk',30);
fo =myImClose(f,se);
figure(1);
imshow(fo);

se =strel('disk',60);

foo=myImOpen(fo,se);

figure(2);
imshow(foo);

f_temp=foo-myerode(foo,ones(3,3));
figure(3);
imshow(f_temp);

f_1=f+f_temp;
figure(4);
imshow(f_1);
