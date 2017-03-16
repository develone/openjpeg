 

fid = fopen('red-out.32t','r'); im4 = fread(fid, [256,inf], 'char'); fclose(fid);
fid = fopen('grn-out.32t','r'); im5 = fread(fid, [256,inf], 'char'); fclose(fid);
fid = fopen('blu-out.32t','r'); im6 = fread(fid, [256,inf], 'char'); fclose(fid);

figure
imagesc(im4)
colorbar
colormap 'gray'
title 'red sub band lena rgb 256.bmp'
figure
imagesc(im5)
colorbar
colormap 'gray'
title 'green sub band lena rgb 256.bmp'
figure
imagesc(im6)
colorbar
colormap 'gray' 
title 'blue sub band lena_rgb rgb 256.bmp'
