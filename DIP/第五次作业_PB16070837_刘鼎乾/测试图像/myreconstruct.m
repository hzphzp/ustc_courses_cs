function [ im_0 ] = myreconstruct( biaoji,muban,jiegouyuan )
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明

f=biaoji;
b=jiegouyuan;
g=muban;

im_0=f;

for i=1:500
   
    
    im_1=imdilate(im_0,b);
    im_0=min(im_1,g);
    
    
    
    
  
end







end

