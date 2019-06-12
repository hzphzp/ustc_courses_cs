clc;
clear;
close all;
count =0;
%f=imread('../data/4.tif');
f=imread('../data/5.tif');
[m,n]=size(f);

im_1_1=f(1:ceil(m/2),1:ceil(n/3));
im_1_2=f(ceil(m/2)+1:m,1:ceil(n/3));
im_2_1=f(1:ceil(m/2),ceil(n/3)+1:ceil(n/3*2));
im_2_2=f(ceil(m/2)+1:m,ceil(n/3)+1:ceil(n/3*2));
im_3_1=f(1:ceil(m/2),ceil(n/3*2)+1:n);
im_3_2=f(ceil(m/2)+1:m,ceil(n/3*2)+1:n);





T=mean2(f);
done =false;
while ~done
    count =count +1;
    g= f > T;
    Tnext=0.5*(mean(f(g))+mean(f(~g)));
    done =abs(T-Tnext) < 0.5;
    T = Tnext;
end

g= im2bw(f,T/255);
imshow(f)
figure;imhist(f);
figure;imshow(g);

f2=imhist(f);
[T,M]=myotsu(f2);
g=im2bw(f,T);
figure,imshow(g);

f1=im_1_1;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_1_1=im2bw(f1,T);

f1=im_1_2;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_1_2=im2bw(f1,T);

f1=im_2_1;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_2_1=im2bw(f1,T);

f1=im_2_2;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_2_2=im2bw(f1,T);

f1=im_3_1;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_3_1=im2bw(f1,T);

f1=im_3_2;
f2=imhist(f1);
[T,M]=myotsu(f2);
g_3_2=im2bw(f1,T);

g_new=g;
g_new(1:ceil(m/2),1:ceil(n/3))=g_1_1;
g_new(ceil(m/2)+1:m,1:ceil(n/3))=g_1_2;
g_new(1:ceil(m/2),ceil(n/3)+1:ceil(n/3*2))=g_2_1;
g_new(ceil(m/2)+1:m,ceil(n/3)+1:ceil(n/3*2))=g_2_2;
g_new(1:ceil(m/2),ceil(n/3*2)+1:n)=g_3_1;
g_new(ceil(m/2)+1:m,ceil(n/3*2)+1:n)=g_3_2;

figure;
imshow(g_new);





