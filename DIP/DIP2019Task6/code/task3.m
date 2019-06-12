clc;
clear;
close all;
count =0;
f=imread('../data/3.tif');

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
figure,imshow(g) 