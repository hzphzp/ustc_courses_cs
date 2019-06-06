f=imread('3.tif');
%w=fspecial('gaussian',4,4);
%f=imfilter(f,w);
figure(1);
imshow(f);

k=10;
se =strel('disk',k);
fo =myopen(f,se);
figure(2);
imshow(fo);

k=20;
se =strel('disk',k);
fo =myopen(f,se);
figure(3);
imshow(fo);

k=25;
se =strel('disk',k);
fo =myopen(f,se);
figure(4);
imshow(fo);

k=30;
se =strel('disk',k);
fo =myopen(f,se);
figure(5);
imshow(fo);

sumpixels=zeros(1,36);
for k=0:35
    se =strel('disk',k);
    fo =imopen(f,se);
    sumpixels(k+1)=sum(fo(:));
end
figure(6);
plot(-diff(sumpixels));
xlabel('k');
ylabel('Surface area reduction');