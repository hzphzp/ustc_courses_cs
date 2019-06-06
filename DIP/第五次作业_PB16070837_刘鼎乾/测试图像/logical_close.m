function [img_2] = logical_close(A,B)

img_1=~logical(mydilate(A,B));

img_2=~logical(myopen(img_1,B));




end