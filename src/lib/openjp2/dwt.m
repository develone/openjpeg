 

fid = fopen('dwt-out.32t','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure; imagesc(im1); colorbar; colormap 'gray'
title 'test tile encoder 3 lvls dwt'
 
