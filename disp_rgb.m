fid = fopen('r.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im1); colorbar; colormap 'gray'

fid = fopen('g.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im2); colorbar; colormap 'gray'

fid = fopen('b.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im3); colorbar; colormap 'gray'
