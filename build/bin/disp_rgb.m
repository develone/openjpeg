fid = fopen('red-out.32t','r'); im1 = fread(fid, [256,inf], 'char'); fclose(fid);
figure; imagesc(im1); colorbar; colormap 'gray';
title"red sub band 256 x 256 RPi Raspbian"

fid = fopen('grn-out.32t','r'); im2 = fread(fid, [256,inf], 'char'); fclose(fid);
figure; imagesc(im2); colorbar; colormap 'gray';
title"green sub band 256 x 256 RPi Raspbian"

fid = fopen('blu-out.32t','r'); im3 = fread(fid, [256,inf], 'char'); fclose(fid);
figure; imagesc(im3); colorbar; colormap 'gray';
title"blue sub band 256 x 256 RPi Raspbian"

%fid = fopen('dwt-out.32t','r'); im4 = fread(fid, [256,inf], 'int32'); fclose(fid);
%figure; imagesc(im4); colorbar; colormap 'gray';title" 256 x 256 n = 5 lvls numresolution 4 RPi Raspbian"
