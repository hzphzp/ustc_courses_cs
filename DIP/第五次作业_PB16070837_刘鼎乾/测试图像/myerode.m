function [img_2] = myerode(A,B)

A=double(A);
B=double(B);

%初始化

[h,w] =size(A);

[hb,wb] =size(B);



 

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
        
        
        tempMatrix=new_A(i:i+hb-1,j:j+wb-1)-B;
        img_2(i,j)=min(tempMatrix(:));
        
        
        
    end
end








end