function im_wiener = my_wiener(img, H, K)
im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double)); 
H_square = H .* H;
im_F_wiener = im_F .* (H_square ./ (H_square + K)) ./ H;
im_wiener_double = real(ifft2(ifftshift(im_F_wiener)));    % ÆµÓò > ¿ÕÓò
im_wiener = im2uint8(mat2gray(im_wiener_double));
