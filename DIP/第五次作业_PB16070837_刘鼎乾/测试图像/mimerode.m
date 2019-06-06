function answ =mimerode(A,B)

 

%初始化

[ha,wa] =size(A);

[hb,wb] =size(B);

origin =[0,0];

answ =zeros(ha,wa);

 

for i = 1:hb

    for j = 1:wb

        if (B(i,j)== 1)

            origin = [i,j];

            break;

        end

    end

end

 

%对矩阵A进行边扩张 以0补充

new_A =zeros(ha+hb*2,wa+wb*2);

for i = 1:ha

    for j = 1:wa

        new_A(i+hb,j+wb) = A(i,j);

    end

end

 

%对矩阵A进行遍历

for i = 1:ha

    for j = 1:wa

        if  A(i,j) == 0

            continue;

        end

        %把B的origin点移到当前处理点 

        %寻找B的影响区域块

        begin_i = i + hb - origin(1);

        begin_j = j + wb - origin(2);

            

        %对矩阵new_A中和重合的B中的元素对比

        for i1 =begin_i:begin_i+hb-1

            for j1 =begin_j:begin_j+wb-1

                flag  = true;

                if (B(i1-begin_i+1,j1-begin_j+1)== 1 & new_A(i1,j1) == 0)

                    flag = false;

                    break;

                end

            end

        end

        if flag

        answ(i,j) = 1;

        else

        answ(i,j) = 0;

        end

    end

end