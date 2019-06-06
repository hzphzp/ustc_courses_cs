function [img_2] = mydilate(A,B)

A=double(A);
B=double(B);
B_temp=B;
%初始化

[h,w] =size(A);

[hb,wb] =size(B);

for i= 1:hb
    for j=1:wb
        B(i,j)=B_temp(hb+1-i,wb+1-j);
    end
end


 

%对矩阵A进行边扩张 以0补充

new_A =double(zeros(h+hb*2,w+wb*2));

for i = 1:h

    for j = 1:w

        new_A(i+hb,j+wb) = A(i,j);

    end

end


% initializing the desired  image
img_2 = double((zeros(h, w)));


for i =1:h
    for j=1:w
        
        
        tempMatrix=new_A(i:i+hb-1,j:j+wb-1)+B;
        img_2(i,j)=max(tempMatrix(:));
        
        
        
    end
end









end