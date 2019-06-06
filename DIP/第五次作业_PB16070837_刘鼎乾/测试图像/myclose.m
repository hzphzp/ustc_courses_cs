function [img_2] = myclose(A,B)

img_1=imdilate(A,B);

img_2=imerode(img_1,B);




end