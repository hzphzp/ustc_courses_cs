# 第五次编程作业：

#### 黄志鹏 PB16150288

## 实验目的

1. 通过二值形态学处理对文本图像进行长字符提取。
2. 通过二值形态学处理对文本图像进行空洞提取。
3. 通过二值形态学处理对文本图像进行边界清除。
4. 通过灰度形态学中的顶帽变换纠正阴影，并进行图像分割
5. 通过灰度形态学进行粒度测定：自动检测图像中规则圆形颗粒尺寸 
6. 利用灰度形态学做纹理分割

## 实验原理

### 1. 二值形态学

在二值形态学中，一个图案被看做是 ![n](https://wikimedia.org/api/rest_v1/media/math/render/svg/a601995d55609f2d9f5e233e36fbe9ea26011b3b) 维[欧几里得空间 ![{\displaystyle \mathbb {R} ^{n}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/c510b63578322050121fe966f2e5770bea43308d) 或网格 ![{\displaystyle \mathbb {Z} ^{n}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/a9b5de7ced4588982b574fe19894aec6a3ca4c49)的[子集。

#### 1.1 结构元素

在二值结构学中，**结构元素**为一个二值影像，作为分析影像时使用的“探针”，代表当处理影像上的某点时、要取出周围的哪些点进行运算。

以下是几个常用的结构元素(将原图写作A、结构元素写作*B*)：

- 待处理影像为二维类比影像 ![{\displaystyle A\in E=\mathbb {R} ^{2}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/7ccdc8b3a6264f93638c456b22fa9e55bc2bdeea)，使用的结构元素*B*为一以原点为圆心、半径为*r*的圆盘。
- 待处理影像为二维类比影像 ![{\displaystyle A\in E=\mathbb {R} ^{2}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/7ccdc8b3a6264f93638c456b22fa9e55bc2bdeea)，使用的结构元素*B*为一以原点为中心的3x3方形。
- 待处理影像为二维类比影像 ![{\displaystyle A\in E=\mathbb {R} ^{2}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/7ccdc8b3a6264f93638c456b22fa9e55bc2bdeea)，使用的结构元素*B*为一以原点为中心的十字形，或写作![{\displaystyle B=\{(-1,0),(0,-1),(0,0),(0,1),(1,0)\}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/07dddc2cd78bec055c5bb4d9a60a1a4630509581)。

#### 1.2 基础运算子

二值形态学的基础运算子为具对称性的、与闵可夫斯基和直接相关的运算子。基础运算子包含膨胀、腐蚀，以及由前两者组合而成的开运算、闭运算。

##### 1.2.1 膨胀

**膨胀(Dilation)**的定义为“位于某个点的探针(结构元素)是否*有*探测到物件？”一个影像*A*经过结构元素*B*膨胀后的结果可写为：
$$
A \oplus B=\left\{x | B_{x} \cap A \neq \emptyset\right\}
$$
其中![{\displaystyle B_{x}=\{x+b|b\in B\}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/91da9b85d6d3fc5da0a6ebfca668bddcfdb0d43e)，代表结构元素平移x后的点集合，*b*是图像*B*的元素的座标。

另外也可写为：
$$
A \oplus B=\bigcup_{b \in B} A_{-b}
$$
同上，其中![{\displaystyle A_{-b}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/853ae7de21ce8bb45f40b6cfed3a50e4fe6ae86f)是指二值影像*A*经过平移*-b*后新的点集合。

##### 1.2.2 腐蚀

**腐蚀(Erosion)**的定义为“位于某个点的探针(结构元素)是否*全都有*探测到物件？”一个影像*A*经过结构元素*B*腐蚀后的结果可写为：
$$
A \ominus B=\left\{x | B_{x} \subseteq A\right\}=\bigcap_{b \in B} A_{-b}
$$

##### 1.2.3 开运算、闭运算

**开运算(Opening)**与**闭运算(Closing)**是使用相同结构函数的腐蚀与膨胀的组合：

开运算为先腐蚀再膨胀，
$$
A \circ B=(A \ominus B) \oplus B
$$
闭运算为先膨胀再腐蚀
$$
A \bullet B=(A \oplus B) \ominus B
$$


### 2. 灰度形态学图像分析

#### 2.1 腐蚀

为寻求b对 的腐蚀，我们把结构元的原点放在图像的每个像素的位置。在任何位置的腐蚀由从包含在与b重合区域中的 的所有值中选取的最小值决定：
$$
[f \ominus \mathrm{b}](\mathrm{x}, \mathrm{y})=\min _{(s, t) \in b}\{f(x+s, y+t)\}
$$

#### 2.2 膨胀

类似地，当b的原点位于位置$$(x, y)$$处时，平坦结构元b在任何位置$$(x, y)$$处对图像$$f$$的膨胀定义为图像$$f$$中$$b$$ 重合区域的最大值即 :
$$
[f \oplus \mathrm{b}](\mathrm{x}, \mathrm{y})=\max _{(s, t) \in b}\{f(x-s, y-t)\}
$$

#### 2.3 开操作和闭操作

开操作是先对图像进行腐蚀操作再进行膨胀操作：
$$
f \circ b=(f \ominus b) \oplus b
$$
闭操作是先对图像进行膨胀操作再进行腐蚀操作：
$$
f \cdot \mathrm{b}=(f \oplus \mathrm{b}) \ominus b
$$
开操作用于去除较小的明亮细节，而保持整体灰度级和较大的明亮 特征相对不变 

### 3. 自己实验的形态学基本函数：

#### 3.1 腐蚀函数：

```matlab
function f = myErode(A,varargin)
    if length(varargin)==2
        s=varargin{1};
        b=varargin{2};
    else
        s=varargin{1};
        b=[];
    end
    [M,N]=size(A);
    [m,n]=size(s);
    
    if isempty(b)
        b=zeros(m,n);
    end
    % Processing of binary image
    g=zeros(M+m-1,N+n-1);
    f=A;
    for i=1:M
        for j=1:N
            g(i+(m-1)/2,j+(n-1)/2)=A(i,j);        
        end
    end
    h=zeros(m,n);
    % Processing of Gray-scale image
    for i=1:M
        for j=1:N
            for p=1:m
                for q=1:n
                   h(p,q)=g(p+i-1,q+j-1);
                end
            end
            r=h.*s-b+(1-s)*255;
            f(i,j)=min(r(:));
        end 
    end                               
end
```

#### 3.2 膨胀操作：

```matlab
function f = myDilate(A,s)
    [M,N] = size(A);
    [m,n] = size(s);
    g = zeros(M+m-1,N+n-1);
    f = A;
    for i=1:M
        for j=1:N
            g(i+(m-1)/2,j+(n-1)/2)=A(i,j);       
        end
    end
    h=zeros(m,n);
    % gray-scale image 
    for i=1:M
        for j=1:N
            for p=1:m
                for q=1:n
                    h(p,q)=g(p+i-1,q+j-1);
                end
            end
            r=h.*s;
            f(i,j)=max(r(:));
         end 
    end
end
```

#### 3.3 膨胀重建

```matlab
function [ h ] = myReconstruction( f, g, B )
% Implementation of morphlogical operation called reconstruction
    narginchk(1,3);
    nargoutchk(1,1);
    if ~islogical(f) || ~islogical(g)
        error('f, g must be logical matrix');
    end
    if nargin == 2
        B = logical([0, 1, 0; 1, 1, 1; 0, 1, 0]);
    end
    h = f;
    htmp = f;
    flag = false;
    while (~flag)
        h = logical(myDilate(htmp, B) .* g);
        flag = 1-any(any(h - htmp));
        htmp = h;
    end
end
```

## 实验过程

### 1. 二值字符图片的长字符提取

![image](/Users/huangzp/code/DIP/DIP2019Task5/data/提取长字符.png)

### 2. 二值字符图片的空洞填充

![image](/Users/huangzp/code/DIP/DIP2019Task5/data/空洞填充.png)

### 3. 二值字符图片的边界清除

![image](/Users/huangzp/code/DIP/DIP2019Task5/data/界面清除.png)

### 4. 顶帽变换

用一个半径为40pix 的圆形结构元对原图进行开操作，然后用原图减去所得的图像，就完成了顶帽变换。

- 顶帽变换用于暗背景上的亮物体 

- 顶帽变换的一个重要用途是校正不均匀光照的影响。合适(均匀)的光照在从 背景中提取目标的处理中扮演核心的角色。 

  ![image](/Users/huangzp/code/DIP/DIP2019Task5/data/顶帽变换.png)

### 5. 粒度测定

用不同半径的圆形结构元对原图进行开操作，计算像素之和，得到不同半径下的像素和数组，做出这个数组的差分图像。在半径-差分像素图像中的每个峰值对应了原图中的圆形结构的半径大小。

![image](/Users/huangzp/code/DIP/DIP2019Task5/data/粒度测定.png)

### 6. 纹理分割

先对原图做半径为30的结构元进行闭操作，消去左边斑点，再用半径为60的结构元做开操作，弥补右边缝隙，做一个形态学差分得到边界，再加回原图。

![image](/Users/huangzp/code/DIP/DIP2019Task5/data/纹理分割.png)

## 实验结果

### 1. 二值字符图片的长字符提取

原图：![image-20190609213024158](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213024158.png)

长字符提取：![image-20190609213203711](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213203711.png)



### 2. 二值字符图片的空洞填充

![image-20190609213147725](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213147725.png)

### 3. 二值字符图片的边界清除

![image-20190609213227213](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213227213.png)

### 4. 顶帽变换

原图：![image-20190609213442520](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213442520.png)

没有顶帽的阈值分割：![image-20190609213723406](/Users/huangzp/Library/Application Support/typora-user-images/image-20190609213723406.png)

开操作后的图像：![image-20190609213911503](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609213911503.png)

顶帽变换后的图像：![image-20190609213939635](/Users/huangzp/Library/Application Support/typora-user-images/image-20190609213939635.png)

顶帽变换后的阈值分割：![image-20190609214008437](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214008437.png)

### 5. 粒度测定

原图：![image-20190609214028756](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214028756.png)

滤波后的图像：![image-20190609214055144](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214055144.png)

k = 10: ![image-20190609214117600](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214117600.png)

k = 20 : ![image-20190609214344654](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214344654.png)

k = 25 : ![image-20190609214355515](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214355515.png)

k = 30 : ![image-20190609214406399](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214406399.png)

k - 像素差图像：![image-20190609214416065](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214416065.png)

### 6. 纹理分割

原图：![image-20190609214428951](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214428951.png)

删除了小斑点：![image-20190609214437063](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214437063.png)

删除了缝隙：![image-20190609214447110](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214447110.png)

纹理分割结果：![image-20190609214454903](/Users/huangzp/code/DIP/DIP2019Task5/data/image-20190609214454903.png)



## 结果分析

**4.1** **二值形态学**

由实验结果可知，经过二值形态学处理后，图像确实能够分别做到提取出长字符，填充孔洞，以及把边界清除，说明实验结果良好。

**4.2** **顶帽变换**

  由两次图像分割的对比可知，由于原图上面亮，下面暗。分割之后右下角有一些信息丢失了：细菌不完整。而右上角则因为过亮，分割后引入了一些噪声。顶帽变换消除了这种不均匀性，看起来比原图亮度更均匀。而得到的分割图像也克服了原分割图像的问题。这是符合直观预测的。然而，若我们直接按照书上的步骤来，则会因为原图减去开操作的图像，若没有经过归一化处理，事实上会太暗。因此根本无法得到想要的阈值分割，反而比原来效果更差，因此正确的做法是对顶帽变换后的图像做一次归一化，再进行图像分割。

**4.3** **粒度测定**

由实验结果可知见，随着结构元半径的增大，被腐蚀掉的粒子越多，剩余的粒子越少，这和我们的直观是相符的。同时，k越大，图像越模糊，看起来越不逼真。

另外，如果没有经过滤波，我们将得到：

得到的图像得到了不应该有的在低k值的峰值。

因为没有经过滤波，图像上将会有很多很小的小颗粒，结构元在处理并作出曲线时，就把这些噪声等效为实际的球体了。

**4.4** **纹理分割**

由实验结果可知，每一步都很好地复现了教材上的结果，实验结果良好。

## 实验所得

这段时间各种比赛（信安国赛ctf赛/作品赛），实验有一些延后，在考试期间做了认真的复习，实验也认真的完成了， 希望助教不要扣太多分。

