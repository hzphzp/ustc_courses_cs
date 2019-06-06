function [img_2] = myopen(A,B)

img_1=imerode(A,B);

img_2=imdilate(img_1,B);




end