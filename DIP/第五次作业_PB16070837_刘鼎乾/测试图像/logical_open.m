function [img_2] = logical_open(A,B)

img_1=~logical(myerode(A,B));

img_2=~logical(mydilate(img_1,B));




end