function [x, y] = lineextraction(f)
[gv,t]=edge(f,'sobel','vertical');
[x, y] = mylineextraction(gv);
end  