fid = fopen('c0.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im1); colorbar; colormap 'gray'

fid = fopen('c1.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im2); colorbar; colormap 'gray'

fid = fopen('c2.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im3); colorbar; colormap 'gray'
