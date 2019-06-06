function [H, im_blured] = motionblur(img, sigma)
[M,N] = size(img);
% 运动模糊退化函数

%% 参数设置
H_moved = zeros(M, N);
H_gaussian = zeros(M, N);
H = zeros(M, N);
a = 0.1;
b = 0.1;
T = 1;
K = 0.01 * sigma;
alpha = 0.0001;
%% 产生退化函数
for u = 1: M
    for v = 1: N
        tmp = pi .* ((u  - M ./ 2) .* a + (v - N ./ 2) .* b);
        % 这里防止零频分量在之后的H（退化函数）中产生无穷大的量
        if abs(tmp) < 0.1
            tmp = 0.1;
        end
        tmp2 = (u - M ./ 2).^2 + (v - N ./ 2).^2;
        % 这里防止零频分量在之后的H（退化函数）中产生无穷大的量
        if abs(tmp2) < 0.1
            tmp2 = 0.1;
        end
        H_moved(u, v) = (T ./ tmp) .* sin(tmp) .* exp(-i .* tmp);
        H_gaussian(u, v) = K .* exp(-alpha .* tmp2);
    end
end

%% 使用退化函数对图像进行模糊化处理 
im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double));      % 空域 > 频域 
im_blured_F = im_F .* H_moved .* H_gaussian;    % 退化
im_blured_double = real(ifft2(ifftshift(im_blured_F)));    % 频域 > 空域
im_blured = im2uint8(mat2gray(im_blured_double));
H = H_moved .* H_gaussian;


