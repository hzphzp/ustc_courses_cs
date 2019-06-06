function [im_inverse, im_inverse_b] = my_inverse(img, H, D0)

[M,N] = size(img);
%% ÏÂÃæÊµÏÖÈ«ÄæÂË²¨
im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double)); 
im_F_inverse = im_F ./ H;
im_inverse_double = real(ifft2(ifftshift(im_F_inverse)));    % ÆµÓò > ¿ÕÓò
im_inverse = im2uint8(mat2gray(im_inverse_double));

%% ÏÂÃæÊµÏÖ°ë¾¶Ê×ÏÈÄæÂË²¨
H_b = max(D0 / 255 * ones(M, N), H);
im_F_inverse_b = im_F./H_b;
im_inverse_b_double = real(ifft2(ifftshift(im_F_inverse_b)));    % ÆµÓò > ¿ÕÓò
im_inverse_b = im2uint8(mat2gray(im_inverse_b_double));
