#include "../../inc/bsb_engine/bsb_texture.h"
#include <GL/gl.h>
Bsb_Texture::Bsb_Texture(const char* filename){
	unsigned int tex_num;

	std::vector< unsigned char > rawImage;
	LodePNG::loadFile( rawImage, filename );

	LodePNG::Decoder decoder;
	std::vector< unsigned char > image;
	decoder.decode( image, rawImage.empty() ? 0 : &rawImage[0],
		            (unsigned)rawImage.size() );

	//
	// Flip and invert the PNG image since OpenGL likes to load everything
	// backwards from what is considered normal!
	//
/*
	unsigned char *imagePtr = &image[0];
	int halfTheHeightInPixels = decoder.getHeight() / 2;
	int heightInPixels = decoder.getHeight();

	// Assuming RGBA for 4 components per pixel.
	int numColorComponents = 4;

	// Assuming each color component is an unsigned char.
	int widthInChars = decoder.getWidth() * numColorComponents;

	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;

	for( int h = 0; h < halfTheHeightInPixels; ++h )
	{
		top = imagePtr + h * widthInChars;
		bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;

		for( int w = 0; w < widthInChars; ++w )
		{
		    // Swap the chars around.
		    temp = *top;
		    *top = *bottom;
		    *bottom = temp;

		    ++top;
		    ++bottom;
		}
	}*/


	//
	// Create the OpenGL texture and fill it with our PNG image.
	//

	// Allocates one texture handle
	glGenTextures( 1, &tex_num);

	// Binds this texture handle so we can load the data into it
	glBindTexture( GL_TEXTURE_2D, tex_num );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, decoder.getWidth(),
		          decoder.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		          &image[0] );
	id=tex_num;
}
Bsb_Texture::Bsb_Texture(const char* filename,bool inverted){
	unsigned int tex_num;

	std::vector< unsigned char > rawImage;
	LodePNG::loadFile( rawImage, filename );

	LodePNG::Decoder decoder;
	std::vector< unsigned char > image;
	decoder.decode( image, rawImage.empty() ? 0 : &rawImage[0],
		            (unsigned)rawImage.size() );

	//
	// Flip and invert the PNG image since OpenGL likes to load everything
	// backwards from what is considered normal!
	//

	unsigned char *imagePtr = &image[0];
	int halfTheHeightInPixels = decoder.getHeight() / 2;
	int heightInPixels = decoder.getHeight();

	// Assuming RGBA for 4 components per pixel.
	int numColorComponents = 4;

	// Assuming each color component is an unsigned char.
	int widthInChars = decoder.getWidth() * numColorComponents;

	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;

	for( int h = 0; h < halfTheHeightInPixels; ++h )
	{
		top = imagePtr + h * widthInChars;
		bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;

		for( int w = 0; w < widthInChars; ++w )
		{
		    // Swap the chars around.
		    temp = *top;
		    *top = *bottom;
		    *bottom = temp;

		    ++top;
		    ++bottom;
		}
	}


	//
	// Create the OpenGL texture and fill it with our PNG image.
	//

	// Allocates one texture handle
	glGenTextures( 1, &tex_num);

	// Binds this texture handle so we can load the data into it
	glBindTexture( GL_TEXTURE_2D, tex_num );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, decoder.getWidth(),
		          decoder.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		          &image[0] );
	id=tex_num;
}
void Bsb_Texture::bind(){
	glBindTexture(GL_TEXTURE_2D,id);
}
void Bsb_Texture::unload(){
	glDeleteTextures(1,(GLuint*)&id);
}
