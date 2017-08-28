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
#define USE_OPJ_DEPRECATED
/* set this macro to enable profiling for the given test */
/* warning : in order to be effective, openjpeg must have been built with profiling enabled !! */
/*#define _PROFILE*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include "opj_config.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
#include <strings.h>
#endif /* _WIN32 */

#include "openjpeg.h"
#include "format_defs.h"


/* -------------------------------------------------------------------------- */
/* Declarations                                                               */ 
int get_file_format(const char *filename);
static int infile_format(const char *fname);

/* -------------------------------------------------------------------------- */
int get_file_format(const char *filename) {
        unsigned int i;
        static const char *extension[] = {"pgx", "pnm", "pgm", "ppm", "bmp","tif", "raw", "rawl", "tga", "png", "j2k", "jp2", "jpt", "j2c", "jpc" };
        static const int format[] = { PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT, TIF_DFMT, RAW_DFMT, RAWL_DFMT, TGA_DFMT, PNG_DFMT, J2K_CFMT, JP2_CFMT, JPT_CFMT, J2K_CFMT, J2K_CFMT };
        char * ext = strrchr(filename, '.');
        if (ext == NULL)
                return -1;
        ext++;
        if(ext) {
                for(i = 0; i < sizeof(format)/sizeof(*format); i++) {
                        if(strcasecmp(ext, extension[i]) == 0) {
                                return format[i];
                        }
                }
        }

        return -1;
}

/* -------------------------------------------------------------------------- */
#define JP2_RFC3745_MAGIC "\x00\x00\x00\x0c\x6a\x50\x20\x20\x0d\x0a\x87\x0a"
#define JP2_MAGIC "\x0d\x0a\x87\x0a"
/* position 45: "\xff\x52" */
#define J2K_CODESTREAM_MAGIC "\xff\x4f\xff\x51"

static int infile_format(const char *fname)
{
        FILE *reader;
        const char *s, *magic_s;
        int ext_format, magic_format;
        unsigned char buf[12];
        unsigned int l_nb_read;

        reader = fopen(fname, "rb");

        if (reader == NULL)
                return -1;

        memset(buf, 0, 12);
        l_nb_read = (unsigned int)fread(buf, 1, 12, reader);
        fclose(reader);
        if (l_nb_read != 12)
                return -1;

        ext_format = get_file_format(fname);

        if (ext_format == JPT_CFMT)
                return JPT_CFMT;

        if (memcmp(buf, JP2_RFC3745_MAGIC, 12) == 0 || memcmp(buf, JP2_MAGIC, 4) == 0) {
                magic_format = JP2_CFMT;
                magic_s = ".jp2";
        }
        else if (memcmp(buf, J2K_CODESTREAM_MAGIC, 4) == 0) {
                magic_format = J2K_CFMT;
                magic_s = ".j2k or .jpc or .j2c";
        }
        else
                return -1;

        if (magic_format == ext_format)
                return ext_format;

        s = fname + strlen(fname) - 4;

        fputs("\n===========================================\n", stderr);
        fprintf(stderr, "The extension of this file is incorrect.\n"
                        "FOUND %s. SHOULD BE %s\n", s, magic_s);
        fputs("===========================================\n", stderr);

        return magic_format;
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

int height, width;
/* -------------------------------------------------------------------------- */
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
void Wr_p_matrix(RGB** Matrix,char *r,char *g,char *b) {
	int i,j;
	RGB tmp;
	for (i=height-1; i>-1; i--){
		for (j=0; j<width; j++){
			
			//printf("%d %d 0x%x 0x%x 0x%x \n ",i,j,tmp.RGB[1],tmp.RGB[0],tmp.RGB[2]);
			tmp.RGB[1] = g[0];
			g++;
			tmp.RGB[0] = r[0];
			r++;			
			tmp.RGB[2] = b[0];
			b++;
			//printf("0x%x 0x%x 0x%x \n",tmp.RGB[0],tmp.RGB[1],tmp.RGB[2]);	
			Matrix[i][j] = tmp;		
		}
	}
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

    fseek(arq,26,0);
    fread(&info.planes,1,2,arq); 
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
    
    fseek(arq,38,0);
    fread(&info.xresolution,1,4,arq); 
    fseek(arq,42,0);
    fread(&info.yresolution,1,4,arq);    
    // Number of color used (NCL)
    // vccalue = 0 for full color set
    fseek(arq,46,0);
    fread(&info.colours,1,4,arq);
 
    // Number of important color (NIC)
    // value = 0 means all collors important
    fseek(arq,54,0);
    fread(&info.impcolours,1,4,arq);
 
    return(info);
}
void writeImage(FILE *arqw, RGB** Matrix){
    int i,j;
    RGB tmp;
    //long pos = 119;
    long pos = 122;
	//printf("height %d width %d \n", height,width);
	//tmp = Matrix[0][0];
	//printf("0x%x 0x%x 0x%x \n",tmp.RGB[0],tmp.RGB[1],tmp.RGB[2]);
    //fseek(arqw,0,0);
    char *wrbuf;
    wrbuf = (char *)malloc(height*width*3);
    printf("0x%x \n",wrbuf);
    for (i=0; i<height; i++){
        for (j=0; j<width; j++){
            //pos+= 3;
            //fseek(arqw,pos,0);
            //printf("%ld ",pos);
            //printf("%d %d \n",i,j);
            tmp = Matrix[i][j];
            //printf("0x%x 0x%x 0x%x \n",tmp.RGB[0],tmp.RGB[1],tmp.RGB[2]);
            //fwrite(&tmp,(sizeof(RGB)),1,arqw);
            //Matrix[i][j] = tmp;
            wrbuf[0] = (char)tmp.RGB[2];
            wrbuf++;
            wrbuf[0] = (char)tmp.RGB[1];
            wrbuf++;
            wrbuf[0] = (char)tmp.RGB[0];
            wrbuf++;
            
        }
    }
    fseek(arqw,pos,0);
    //printf("0x%x \n",wrbuf);
    wrbuf= wrbuf - height*width*3;
    //printf("0x%x \n",wrbuf);
    fwrite(wrbuf,(height*width*3),1,arqw);
    free(wrbuf);
    //return(Matrix);
    fclose(arqw);
}
// ********** Write BMP info from file **********
void writeInfo(FILE *arqw,INFOHEADER infowrite){
    //INFOHEADER info;
    char type[3];
    int hdr;
    char offset=122,unknow=108;
    
    hdr = infowrite.height*infowrite.width*3+offset;
    type[0] = 0x42;
    type[1] = 0x4D;

    
    fseek(arqw,2,0);
    fwrite(&hdr,1,4,arqw);

    fseek(arqw,10,0);
    fwrite(&offset,1,1,arqw);

    fseek(arqw,14,0);
    fwrite(&unknow,1,1,arqw);
    	
	fseek(arqw,0,0);
    fwrite(type,1,2,arqw);
    
    // Image Width in pixels
    fseek(arqw,18,0);
    fwrite(&infowrite.width,1,4,arqw);
 
    // Image Height in pixels
    fseek(arqw,22,0);
    fwrite(&infowrite.height,1,4,arqw);
    
    fseek(arqw,26,0);
    fwrite(&infowrite.planes,1,2,arqw); 
    
    // Color depth, BPP (bits per pixel)
    fseek(arqw,28,0);
    fwrite(&infowrite.bpp,1,2,arqw);
 
    // Compression type
    // 0 = Normmally
    // 1 = 8 bits per pixel
    // 2 = 4 bits per pixel
    fseek(arqw,30,0);
    fwrite(&infowrite.compression,1,4,arqw);
 
    // Image size in bytes
    fseek(arqw,34,0);
    fwrite(&infowrite.imagesize,1,4,arqw);

    fseek(arqw,38,0);
    fwrite(&infowrite.xresolution,1,4,arqw); 
    fseek(arqw,42,0);
    fwrite(&infowrite.yresolution,1,4,arqw);
 
    // Number of color used (NCL)
    // vccalue = 0 for full color set
    fseek(arqw,46,0);
    fwrite(&infowrite.colours,1,4,arqw);
 
    // Number of important color (NIC)
    // value = 0 means all collors important
    fseek(arqw,54,0);
    fwrite(&infowrite.impcolours,1,4,arqw);
 
    //return(info);
    //fclose(arqw);
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

int main (int argc, char *argv[])
{
		char *r_decompress,*g_decompress,*b_decompress;
		const char *r_decompress_fn="red";
		const char *g_decompress_fn="green";
		const char *b_decompress_fn="blue";
		//unsigned int *rgb;
		//const char *rgb_decompress_fn="rgb";
		
		int loop;
        opj_dparameters_t l_param;
        opj_codec_t * l_codec;
        opj_image_t * l_image;
        opj_stream_t * l_stream;
        OPJ_UINT32 l_data_size;
        OPJ_UINT32 l_max_data_size = 1000;
        OPJ_UINT32 l_tile_index;
        OPJ_BYTE * l_data = (OPJ_BYTE *) malloc(1000);
        OPJ_BOOL l_go_on = OPJ_TRUE;
        OPJ_UINT32 l_nb_comps=0 ;
        OPJ_INT32 l_current_tile_x0,l_current_tile_y0,l_current_tile_x1,l_current_tile_y1;

        int da_x0=0;
        int da_y0=0;
        int da_x1=1000;
        int da_y1=1000;
        const char *input_file;
		
        /* should be test_tile_decoder 0 0 1000 1000 tte1.j2k */
        if( argc == 6 )
        {
                da_x0=atoi(argv[1]);
                da_y0=atoi(argv[2]);
                da_x1=atoi(argv[3]);
                da_y1=atoi(argv[4]);
                input_file = argv[5];

        }
        else
        {
                da_x0=0;
                da_y0=0;
                da_x1=1000;
                da_y1=1000;
                input_file = "test.j2k";
        }
		//rgb = (int)malloc(da_x1*da_y1*sizeof(int));
        if (! l_data) {
                return EXIT_FAILURE;
        }

        l_stream = opj_stream_create_default_file_stream(input_file,OPJ_TRUE);
        if (!l_stream){
                free(l_data);
                fprintf(stderr, "ERROR -> failed to create the stream from the file\n");
                return EXIT_FAILURE;
        }

        /* Set the default decoding parameters */
        opj_set_default_decoder_parameters(&l_param);

        /* */
        l_param.decod_format = infile_format(input_file);

        /** you may here add custom decoding parameters */
        /* do not use layer decoding limitations */
        l_param.cp_layer = 0;

        /* do not use resolutions reductions */
        l_param.cp_reduce = 0;

        /* to decode only a part of the image data */
        /*opj_restrict_decoding(&l_param,0,0,1000,1000);*/


        switch(l_param.decod_format) {
                case J2K_CFMT:	/* JPEG-2000 codestream */
                        {
                                /* Get a decoder handle */
                                l_codec = opj_create_decompress(OPJ_CODEC_J2K);
                                break;
                        }
                case JP2_CFMT:	/* JPEG 2000 compressed image data */
                        {
                                /* Get a decoder handle */
                                l_codec = opj_create_decompress(OPJ_CODEC_JP2);
                                break;
                        }
                default:
                        {    
                                fprintf(stderr, "ERROR -> Not a valid JPEG2000 file!\n");
                                free(l_data);
                                opj_stream_destroy(l_stream);
                                return EXIT_FAILURE;
                        }
        }

        /* catch events using our callbacks and give a local context */		
        opj_set_info_handler(l_codec, info_callback,00);
        opj_set_warning_handler(l_codec, warning_callback,00);
        opj_set_error_handler(l_codec, error_callback,00);

        /* Setup the decoder decoding parameters using user parameters */
        if (! opj_setup_decoder(l_codec, &l_param))
        {
                fprintf(stderr, "ERROR -> j2k_dump: failed to setup the decoder\n");
                free(l_data);
                opj_stream_destroy(l_stream);
                opj_destroy_codec(l_codec);
                return EXIT_FAILURE;
        }

        /* Read the main header of the codestream and if necessary the JP2 boxes*/
        if (! opj_read_header(l_stream, l_codec, &l_image))
        {
                fprintf(stderr, "ERROR -> j2k_to_image: failed to read the header\n");
                free(l_data);
                opj_stream_destroy(l_stream);
                opj_destroy_codec(l_codec);
                return EXIT_FAILURE;
        }

        if (!opj_set_decode_area(l_codec, l_image, da_x0, da_y0,da_x1, da_y1)){
                fprintf(stderr,	"ERROR -> j2k_to_image: failed to set the decoded area\n");
                free(l_data);
                opj_stream_destroy(l_stream);
                opj_destroy_codec(l_codec);
                opj_image_destroy(l_image);
                return EXIT_FAILURE;
        }


        while (l_go_on)
        {
                if (! opj_read_tile_header( l_codec,
                                        l_stream,
                                        &l_tile_index,
                                        &l_data_size,
                                        &l_current_tile_x0,
                                        &l_current_tile_y0,
                                        &l_current_tile_x1,
                                        &l_current_tile_y1,
                                        &l_nb_comps,
                                        &l_go_on))
                {						
                        free(l_data);
                        opj_stream_destroy(l_stream);
                        opj_destroy_codec(l_codec);
                        opj_image_destroy(l_image);
                        return EXIT_FAILURE;
                }

                if (l_go_on)
                {
                        if (l_data_size > l_max_data_size)
                        {
                                OPJ_BYTE *l_new_data = (OPJ_BYTE *) realloc(l_data, l_data_size);
                                if (! l_new_data)
                                {
                                        free(l_new_data);
                                        opj_stream_destroy(l_stream);
                                        opj_destroy_codec(l_codec);
                                        opj_image_destroy(l_image);
                                        return EXIT_FAILURE;
                                }
                                l_data = l_new_data;
                                l_max_data_size = l_data_size;
                        }

                        if (! opj_decode_tile_data(l_codec,l_tile_index,l_data,l_data_size,l_stream))
                        {
                                free(l_data);
                                opj_stream_destroy(l_stream);
                                opj_destroy_codec(l_codec);
                                opj_image_destroy(l_image);
                                return EXIT_FAILURE;
                        }
                        /** now should inspect image to know the reduction factor and then how to behave with data */
                }
        }
		b_decompress = 	l_data;
		octave_write_byte(b_decompress_fn,b_decompress,da_x1*da_y1);
		g_decompress = 	l_data+da_x1*da_y1;
		octave_write_byte(g_decompress_fn,g_decompress,da_x1*da_y1);
		r_decompress = 	l_data+da_x1*da_y1+da_x1*da_y1;
		octave_write_byte(r_decompress_fn,r_decompress,da_x1*da_y1);
		//for(loop=0;loop<da_x1*da_y1;loop++) {
			//rgb[loop] = b_decompress[loop]*65536+r_decompress[loop]*256+g_decompress[loop];
			//printf("%d 0x%x 0x%x 0x%x 0x%x\n",loop,rgb[loop],r_decompress[loop],g_decompress[loop],b_decompress[loop]);
		//}
		//octave_write(rgb_decompress_fn,rgb,da_x1*da_y1);
	RGB** Matrix_aux_wr;
	

	//Matrix_aux_wr = Matrix;
	int bpp;
	FILE *oo;
	height = da_y1;
	width = da_x1;
	Matrix_aux_wr = createMatrix();
 
	
	Wr_p_matrix(Matrix_aux_wr,b_decompress, g_decompress, r_decompress ); 
	oo = fopen("test_wr.bmp","wb");
	if (!oo) {
			printf("Unable to open file for writing!");
			return 1;
	}
	INFOHEADER infowr;	
	infowr.height = height;
	infowr.width = width;
	
	infowr.imagesize = height*width*3;
	bpp = 24;
	infowr.bpp = bpp;
	infowr.planes = 1;
	infowr.compression = 0;
	infowr.impcolours = 0x73524742;
	
	printf("WR imagesc = 0x%x \n",infowr.imagesize);
	printf("Wr bpp = %d \n",infowr.bpp);
	printf("Wr xresolution = %d yresolution %d \n",infowr.xresolution,infowr.yresolution);
	printf("bpp = %d \n",infowr.bpp);
	printf("xresolution = %d yresolution %d \n",infowr.xresolution,infowr.yresolution);
	writeInfo(oo,infowr);
	writeImage(oo,Matrix_aux_wr);
	free(Matrix_aux_wr);	
		//free(rgb);
        if (! opj_end_decompress(l_codec,l_stream))
        {
                free(l_data);
                opj_stream_destroy(l_stream);
                opj_destroy_codec(l_codec);
                opj_image_destroy(l_image);
                return EXIT_FAILURE;
        }
		printf("at end of loop\n");
        /* Free memory */
        free(l_data);
        opj_stream_destroy(l_stream);
        opj_destroy_codec(l_codec);
        opj_image_destroy(l_image);

        /* Print profiling*/
        /*PROFPRINT();*/

        return EXIT_SUCCESS;
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

//pass ip to a routine 
//which malloc 3 area
//read 65536  values of red 262144 32 bit int  0xc0000424 to 0xc0040423
//read 65536  values of green 262144 32 bit int 0xc0040424 to 0xc00c0423
//read 65536  values of blue 262144 32 bit int
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
