//
//  Utility.h
//  GameInfrastructure
//
//  Created by Navid Milani on 3/16/14.
//  Copyright (c) 2014 ConcreteInteractive. All rights reserved.
//
#ifndef GameInfrastructure_Utility_h
#define GameInfrastructure_Utility_h

#include "Texture.h"

png_uint_32 powerOfTwo( png_uint_32 num )
{
    if( num != 0 )
    {
        num--;
        num |= (num >> 1); //Or first 2 bits
        num |= (num >> 2); //Or next 2 bits
        num |= (num >> 4); //Or next 4 bits
        num |= (num >> 8); //Or next 8 bits
        num |= (num >> 16); //Or next 16 bits
        num++;
    }
    
    return num;
}

Texture* loadPngImage(char* name) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
    
    if ((fp = fopen(name, "rb")) == NULL)
        return NULL;
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
    
    if (png_ptr == NULL) {
        fclose(fp);
        return NULL;
    }
    
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return NULL;
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return NULL;
    }
    
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
    
    png_set_sig_bytes(png_ptr, sig_read);
    
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
    
    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    
    unsigned long row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    
    Texture* texture = (Texture*)malloc(sizeof(Texture));
    texture->id = -1;
    texture->width = width;
    texture->height = height;
    texture->data = (unsigned char*) malloc(row_bytes * height);
    
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    
    for (int i = 0; i < texture->height; i++) {
        //opengl holds texture supside down by default... expects it that way...
        //our cordinate system is upside down so im ommiting this fact...
        //uncomment the below code and remove i to have it do so...
        memcpy(texture->data+(row_bytes * i/*(texture->height-1-i)*/), row_pointers[i], row_bytes);
    }
    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    /* Close the file */
    fclose(fp);
    
    return texture;
}

#endif
