function [H, im_blured] = atmosph(img)

[M,N] = size(img);

% 大气湍流模型退化函数
k = 0.0025;
[u,v]=meshgrid(1:M,1:N);    % 生成二维坐标系
H=exp(-k* ( (u-M/2).^2+(v-N/2).^2).^(5/6) );

im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double));      % 空域 > 频域 ? 这里是什么意思我不是很明白
im_blured_F = im_F .* H;    % 退化‘’
im_blured_double = real(ifft2(ifftshift(im_blured_F)));    % 频域 > 空域
im_blured = im2uint8(mat2gray(im_blured_double));