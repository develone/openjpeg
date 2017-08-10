/*
 * Copyright (c) 2008, Jerome Fimes, Communications & Systemes <jerome.fimes@c-s.fr>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "opj_config.h"
#include "openjpeg.h"
#include "stdlib.h"
#include <sys/time.h>

#include "dwtlift.h"
/* Global */
int height, width;
typedef struct
    {
        unsigned char RGB[3];
    }RGB;
    
    
// ********** Create Matrix **********
RGB** createMatrix(){
    RGB** Matrix;
    int i;
    Matrix = (RGB **) malloc (sizeof (RGB*) * height);
    if (Matrix == NULL){
        perror("***** No memory available *****");
        exit(0);
    }
    for (i=0;i<height;i++){
        Matrix[i] = (RGB *) malloc (sizeof(RGB) * width);
        if (Matrix[i] == NULL){
        perror("***** No memory available *****");
            exit(0);
        }
    }
    return(Matrix);
}

RGB** loadImage(FILE *arq, RGB** Matrix){
    int i,j;
    RGB tmp;
    long pos = 119;
 
    fseek(arq,0,0);
 
    for (i=0; i<height; i++){
        for (j=0; j<width; j++){
            pos+= 3;
            fseek(arq,pos,0);
            fread(&tmp,(sizeof(RGB)),1,arq);
            Matrix[i][j] = tmp;
        }
    }
    return(Matrix);
}
/*upside down data in bitmap*/
void p_matrix(RGB** Matrix,char *r,char *g,char *b) {
	int i,j;
	RGB tmp;
	for (i=height-1; i>-1; i--){
		for (j=0; j<width; j++){
			tmp = Matrix[i][j];
			//printf("%d %d 0x%x 0x%x 0x%x \n ",i,j,tmp.RGB[1],tmp.RGB[0],tmp.RGB[2]);
			r[0] = tmp.RGB[1];
			r++;
			g[0] = tmp.RGB[0];
			g++;			
			b[0] = tmp.RGB[2];
			b++;			
		}
	}
}

/*top down data in bitmap*/
void pp_matrix(RGB** Matrix,char *r,char *g,char *b) {
	int i,j;
	RGB tmp;
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			tmp = Matrix[i][j];
			//printf("%d %d 0x%x 0x%x 0x%x \n ",i,j,tmp.RGB[1],tmp.RGB[0],tmp.RGB[2]);
			r[0] = tmp.RGB[1];
			r++;
			g[0] = tmp.RGB[0];
			g++;			
			b[0] = tmp.RGB[2];
			b++;			
		}
	}
}
 
typedef struct
    {
        unsigned int size;
        int width,height;
        unsigned short int planes;
        unsigned short int bpp;
        unsigned int compression;
        unsigned int imagesize;
        int xresolution,yresolution;
        unsigned int colours;
        unsigned int impcolours;
    }INFOHEADER;
 
// ********** Read BMP info from file **********
INFOHEADER readInfo(FILE *arq){
    INFOHEADER info;
 
    // Image Width in pixels
    fseek(arq,18,0);
    fread(&info.width,1,4,arq);
 
    // Image Height in pixels
    fseek(arq,22,0);
    fread(&info.height,1,4,arq);
 
    // Color depth, BPP (bits per pixel)
    fseek(arq,28,0);
    fread(&info.bpp,1,2,arq);
 
    // Compression type
    // 0 = Normmally
    // 1 = 8 bits per pixel
    // 2 = 4 bits per pixel
    fseek(arq,30,0);
    fread(&info.compression,1,4,arq);
 
    // Image size in bytes
    fseek(arq,34,0);
    fread(&info.imagesize,1,4,arq);
 
    // Number of color used (NCL)
    // vccalue = 0 for full color set
    fseek(arq,46,0);
    fread(&info.colours,1,4,arq);
 
    // Number of important color (NIC)
    // value = 0 means all collors important
    fseek(arq,50,0);
    fread(&info.impcolours,1,4,arq);
 
    return(info);
}
// ********** Verify if the file is BMP *********
void isBMP(FILE* arq, INFOHEADER info){
    char type[3];
    unsigned short int bpp;
    fseek(arq,0,0);
    fread(type,1,2,arq);
    type[2] = '\0';
 
    fseek(arq,28,0);
    fread(&bpp,1,2,arq);
	printf("testing if bitmap %c%c bpp = %d \n",type[0],type[1],bpp);
    if (strcmp(type,"BM") || (bpp != 24)){
        printf("\nThe file is not BMP format or is not 24 bits\n");
            exit(0);
    }
}

int octave_write(const char * fn,int * d_ptr, int sz) {
	 
	FILE *subfileptr;
	subfileptr = fopen(fn,"w");
	printf("file name %s data ptr 0x%x size %d \n",fn, d_ptr,sz);
	if (NULL == subfileptr) {
		/*
		fprintf(stderr, "Could not open red for writing\n");
		perror("RED-WR:");
		exit(EXIT_FAILURE);
		*/
		return(0);
	}
 
	if (sz != (int)fwrite(d_ptr,  sizeof(int), sz, subfileptr)) {
		fprintf(stderr, "Write of red failed\n"); perror("RED:");
		exit(EXIT_FAILURE);
	}
	
 	
	fclose(subfileptr);
	
	return(1);
}
int octave_write_byte(const char * fn,char * d_ptr, int sz) {
	 
	FILE *subfileptr;
	subfileptr = fopen(fn,"w");
	printf("file name %s data ptr 0x%x size %d \n",fn, d_ptr,sz);
	if (NULL == subfileptr) {
		/*
		fprintf(stderr, "Could not open red for writing\n");
		perror("RED-WR:");
		exit(EXIT_FAILURE);
		*/
		return(0);
	}
 
	if (sz != (int)fwrite(d_ptr,  sizeof(char), sz, subfileptr)) {
		fprintf(stderr, "Write of red failed\n"); perror("RED:");
		exit(EXIT_FAILURE);
	}
	
 	
	fclose(subfileptr);
	
	return(1);
}

/* -------------------------------------------------------------------------- */

/**
sample error debug callback expecting no client object
*/
static void error_callback(const char *msg, void *client_data) {
	(void)client_data;
	fprintf(stdout, "[ERROR] %s", msg);
}
/**
sample warning debug callback expecting no client object
*/
static void warning_callback(const char *msg, void *client_data) {
	(void)client_data;
	fprintf(stdout, "[WARNING] %s", msg);
}
/**
sample debug callback expecting no client object
*/
static void info_callback(const char *msg, void *client_data) {
	(void)client_data;
	fprintf(stdout, "[INFO] %s", msg);
}

/* -------------------------------------------------------------------------- */

#define NUM_COMPS_MAX 4
int main (int argc, char *argv[])
{
	int TopDown,TCP_DISTORATIO,FILTER;
	
	/* need wha bit indicate TopDown*/
	TopDown = 0;
 	char *r,*g,*b;
 
	const char *octave_output_file_1;
	const char *octave_output_file_2;
	const char *octave_output_file_3;
	
	 
	FILE *in,*fp;
	char *fn,fnstr[20];
	if(argc == 1) {
		strcpy(fnstr,"../../lena_rgb_2048.bmp");
		in = fopen(fnstr,"rb");
		printf("Using default image %s %d\n",fnstr,argc);
		if (!in) {
			printf("Unle to open file!");
			return 1;
		}
	}
	else
	{ 
		fn = argv[1];
		printf("Passed file %s %d \n",fn,argc);
		in = fopen(fn,"rb");
		if (!in) {
			printf("Unle to open file!");
			return 1;
		}
	}
	
	
	
	//char inchar;
	//int bpp;
	//long int offset;
	int pixels, size, sz;
	
	RGB** Matrix_aux;
	RGB** Matrix;
	INFOHEADER info;
	info = readInfo(in);
	height = info.height;
	width = info.width;
	TCP_DISTORATIO= 44;
	FILTER = 0;
	isBMP(in,info);
	r = malloc(sizeof(char)*height*width);
	g = malloc(sizeof(char)*height*width);
	b = malloc(sizeof(char)*height*width);
	printf("allocating 0x%x 0x%x 0x%x \n",r,g,b);
	Matrix_aux = createMatrix();
	printf("size = %d \n",info.imagesize);
	printf("planes = %d \n",info.planes);
	printf("colours = %d \n",info.colours);

	printf("height = %d width = %d \n",height,width);
	printf("bpp = %d \n",info.bpp);
	printf("xresolution = %d yresolution %d \n",info.xresolution,info.yresolution);
	printf("rgb from Matrix to r g b ptrs\n");
	Matrix = loadImage(in,Matrix_aux);
	printf("splitting data to rgb\n");
	if (TopDown == 0) {
		/*upside down data in bitmap*/	
		p_matrix(Matrix_aux,r,b,g);
		r = &r[0];
		g = &g[0];
		b = &b[0];
		printf("0x%x 0x%x 0x%x \n",r,g,b);
	}
	else 
	{
		/*top down data in bitmap*/
		pp_matrix(Matrix_aux,r,b,g);
	}

	 
	/*
	octave_output_file_1 = "r.bin";
	octave_output_file_2 = "g.bin";
	octave_output_file_3 = "b.bin";
    */
	int plot=0;
	encode = 1;
	decomp = 3;
	
	printf("enc %d decomp %d distor %d filter %d\n",encode,decomp,TCP_DISTORATIO,FILTER);
 	
	/* read header */
	info = readInfo(in);
	
 
 	gettimeofday(&start, NULL);
 

	
 
 
 	
 
 	

	
	opj_cparameters_t l_param;
	opj_codec_t * l_codec;
	opj_image_t * l_image;
	opj_image_cmptparm_t l_params [NUM_COMPS_MAX];
	opj_stream_t * l_stream;
	OPJ_UINT32 l_nb_tiles;
	OPJ_UINT32 l_data_size;
	size_t len;

#ifdef USING_MCT
	const OPJ_FLOAT32 l_mct [] =
	{
		1 , 0 , 0 ,
		0 , 1 , 0 ,
		0 , 0 , 1
	};

	const OPJ_INT32 l_offsets [] =
	{
		128 , 128 , 128
	};
#endif

	opj_image_cmptparm_t * l_current_param_ptr;
	OPJ_UINT32 i;
	OPJ_BYTE *l_data;

  OPJ_UINT32 num_comps;
  int image_width;
  int image_height;
  int tile_width;
  int tile_height;
  int comp_prec;
  int irreversible;
  const char *output_file;

  
 

    num_comps = 3;
    image_width = width;
    image_height = height;
    tile_width = width;
    tile_height = height;
    comp_prec = 8;
    irreversible = FILTER;
    output_file = "test.j2k";
    
  if( num_comps > NUM_COMPS_MAX )
    {
    return 1;
    }
	l_nb_tiles = (OPJ_UINT32)(image_width/tile_width) * (OPJ_UINT32)(image_height/tile_height);
	l_data_size = (OPJ_UINT32)tile_width * (OPJ_UINT32)tile_height * (OPJ_UINT32)num_comps * (OPJ_UINT32)(comp_prec/8);
	printf("l_nb_tiles %d l_data_size %d \n", l_nb_tiles, l_data_size);
	l_data = (OPJ_BYTE*) malloc(l_data_size * sizeof(OPJ_BYTE));
	if(l_data == NULL){
		return 1;
	}
 
 	
		if(plot == 1) {
			
			printf("write the files \n");
			printf("red-out.32t, grn-out.32t, and blu-out.32t\n");
			octave_output_file_1 = "red-out.32t";
			 
			
			i = octave_write_byte(octave_output_file_1,r , width*height);
			if(i == 0) printf("could not write file\n");
	
			octave_output_file_2 = "grn-out.32t";
			//i = octave_write(octave_output_file_2, imgbm->m_green, sz);
			i = octave_write_byte(octave_output_file_2, g, width*height);	
			if(i == 0) printf("could not write file\n");
	
			octave_output_file_3 = "blu-out.32t";
			 
			i = octave_write_byte(octave_output_file_3, b, width*height);
			if(i == 0) printf("could not write file\n");
		}
	
	
 
		printf("loading RGB data \n");
		printf("TRANSFER 0x%x 0x%x 0x%x \n",r,g,b);
 

		for (i=0;i<((info.imagesize)/3);i++)	{	
			l_data[i] = (OPJ_BYTE)g[i];
			
		}
	
		 
 		
		for (i=0;i<((info.imagesize/3));i++)	{	
			l_data[i+(info.imagesize/3)] = (OPJ_BYTE)r[i];
			
		}
	 
		 
		for (i=0;i<((info.imagesize/3));i++)	{	
			l_data[i+(info.imagesize/3)*2] = (OPJ_BYTE)b[i];
			
		}
		 
		printf("before reset 0x%x 0x%x 0x%x \n",r,g,b); 

 

 

	//opj_mct_encode(imgbm->m_red,imgbm->m_green,imgbm->m_blue,size/3);	

	opj_set_default_encoder_parameters(&l_param);
	/** you may here add custom encoding parameters */
	/* rate specifications */
	/** number of quality layers in the stream */
	l_param.tcp_numlayers = 1;
	//l_param.cp_fixed_quality = 1;
	//l_param.tcp_distoratio[0] = TCP_DISTORATIO;
	/* is using others way of calculation */
	/* l_param.cp_disto_alloc = 1 or l_param.cp_fixed_alloc = 1 */
	/* l_param.tcp_rates[0] = ... */
	l_param.cp_disto_alloc = 1; 
	l_param.tcp_rates[0] = 100;
	/* tile definitions parameters */
	/* position of the tile grid aligned with the image */
	l_param.cp_tx0 = 0;
	l_param.cp_ty0 = 0;
	/* tile size, we are using tile based encoding */
	l_param.tile_size_on = OPJ_TRUE;
	l_param.cp_tdx = tile_width;
	l_param.cp_tdy = tile_height;

	/* use irreversible encoding ?*/
	l_param.irreversible = irreversible;

	/* do not bother with mct, the rsiz is set when calling opj_set_MCT*/
	/*l_param.cp_rsiz = OPJ_STD_RSIZ;*/

	/* no cinema */
	/*l_param.cp_cinema = 0;*/

	/* no not bother using SOP or EPH markers, do not use custom size precinct */
	/* number of precincts to specify */
	/* l_param.csty = 0;*/
	/* l_param.res_spec = ... */
	/* l_param.prch_init[i] = .. */
	/* l_param.prcw_init[i] = .. */


	/* do not use progression order changes */
	/*l_param.numpocs = 0;*/
	/* l_param.POC[i].... */

	/* do not restrain the size for a component.*/
	/* l_param.max_comp_size = 0; */

	/** block encoding style for each component, do not use at the moment */
	/** J2K_CCP_CBLKSTY_TERMALL, J2K_CCP_CBLKSTY_LAZY, J2K_CCP_CBLKSTY_VSC, J2K_CCP_CBLKSTY_SEGSYM, J2K_CCP_CBLKSTY_RESET */
	/* l_param.mode = 0;*/

	/** number of resolutions */
	l_param.numresolution = 6;

	/** progression order to use*/
	/** OPJ_LRCP, OPJ_RLCP, OPJ_RPCL, PCRL, CPRL */
	l_param.prog_order = OPJ_LRCP;

	/** no "region" of interest, more precisally component */
	/* l_param.roi_compno = -1; */
	/* l_param.roi_shift = 0; */

	/* we are not using multiple tile parts for a tile. */
	/* l_param.tp_on = 0; */
	/* l_param.tp_flag = 0; */

	/* if we are using mct */
#ifdef USING_MCT
	opj_set_MCT(&l_param,l_mct,l_offsets,NUM_COMPS);
#endif


	/* image definition */
	l_current_param_ptr = l_params;
	for (i=0;i<num_comps;++i) {
		/* do not bother bpp useless */
		/*l_current_param_ptr->bpp = COMP_PREC;*/
		l_current_param_ptr->dx = 1;
		l_current_param_ptr->dy = 1;

		l_current_param_ptr->h = (OPJ_UINT32)image_height;
		l_current_param_ptr->w = (OPJ_UINT32)image_width;

		l_current_param_ptr->sgnd = 0;
		l_current_param_ptr->prec = (OPJ_UINT32)comp_prec;

		l_current_param_ptr->x0 = 0;
		l_current_param_ptr->y0 = 0;

		++l_current_param_ptr;
	}

  /* should we do j2k or jp2 ?*/
  len = strlen( output_file );
  if( strcmp( output_file + len - 4, ".jp2" ) == 0 )
    {
    l_codec = opj_create_compress(OPJ_CODEC_JP2);
    }
  else
    {
		printf("In test_tile_encoder\n");
		printf("creating J2k\n");
    l_codec = opj_create_compress(OPJ_CODEC_J2K);
    }
	if (!l_codec) {
		free(l_data);
		return 1;
	}

	/* catch events using our callbacks and give a local context */
	opj_set_info_handler(l_codec, info_callback,00);
	opj_set_warning_handler(l_codec, warning_callback,00);
	opj_set_error_handler(l_codec, error_callback,00);

	l_image = opj_image_tile_create(num_comps,l_params,OPJ_CLRSPC_SRGB);
	if (! l_image) {
		free(l_data);
		opj_destroy_codec(l_codec);
		return 1;
	}

	l_image->x0 = 0;
	l_image->y0 = 0;
	l_image->x1 = (OPJ_UINT32)image_width;
	l_image->y1 = (OPJ_UINT32)image_height;
	l_image->color_space = OPJ_CLRSPC_SRGB;

	if (! opj_setup_encoder(l_codec,&l_param,l_image)) {
		fprintf(stderr, "ERROR -> test_tile_encoder: failed to setup the codec!\n");
		opj_destroy_codec(l_codec);
		opj_image_destroy(l_image);
		free(l_data);
		return 1;
	}

    l_stream = opj_stream_create_default_file_stream(output_file, OPJ_FALSE);
    if (! l_stream) {
		fprintf(stderr, "ERROR -> test_tile_encoder: failed to create the stream from the output file %s !\n",output_file );
		opj_destroy_codec(l_codec);
		opj_image_destroy(l_image);
		free(l_data);
		return 1;
	}

	if (! opj_start_compress(l_codec,l_image,l_stream)) {
		fprintf(stderr, "ERROR -> test_tile_encoder: failed to start compress!\n");
        opj_stream_destroy(l_stream);
		opj_destroy_codec(l_codec);
		opj_image_destroy(l_image);
		free(l_data);
		return 1;
	}

	for (i=0;i<l_nb_tiles;++i) {
		if (! opj_write_tile(l_codec,i,l_data,l_data_size,l_stream)) {
			fprintf(stderr, "ERROR -> test_tile_encoder: failed to write the tile %d!\n",i);
            opj_stream_destroy(l_stream);
			opj_destroy_codec(l_codec);
			opj_image_destroy(l_image);
			free(l_data);
			return 1;
		}
	}

	if (! opj_end_compress(l_codec,l_stream)) {
		fprintf(stderr, "ERROR -> test_tile_encoder: failed to end compress!\n");
        opj_stream_destroy(l_stream);
		opj_destroy_codec(l_codec);
		opj_image_destroy(l_image);
		free(l_data);
		return 1;
	}

    opj_stream_destroy(l_stream);
	opj_destroy_codec(l_codec);
	opj_image_destroy(l_image);
	//free(dataptr);
	printf("FREE 0x%x 0x%x 0x%x \n",r,g,b);
	free(r);
	free(g);
	free(b);
	free(Matrix);
	 
	free(l_data);

	/* Print profiling*/
	/*PROFPRINT();*/
	
	return 0;
}






