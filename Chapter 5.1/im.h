#include <vector>
#include <stdio.h>
#include "vec3.h"

#ifndef IMH
#define IMH

typedef std::vector< vec3 > Color3Matrix;
typedef unsigned char  BYTE;
/** Data structure for a float image. */
struct Image
{
	/** Dimensions of image */
	int width, height;

	/** 2D array of image pixels */
	mutable Color3Matrix pixels;

	/** Image constructor */
	Image(int _width = 0, int _height = 0)
	{
		resize(_width, _height);
	}

	/** Set the image size and allocate the vector. */
	void resize(int _width, int _height)
	{
		width = _width;
		height = _height;
		// allocate the image
		pixels.resize(width*height);
	}

	vec3& pixel(int x, int y) const
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			return pixels[x + width * y];
		}
	}

	bool pixel(int x, int y, vec3** result) const
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			*result = &pixels[x + width * y];
			return true;
		}
		return false;
	}

};

void WriteBMP(FILE *fp, Image& im)
{
	int x, y;
	int r, g, b;

	BYTE heads[] = { 0x42,0x4D,0x36,0xC2,0x01,00,00,00,00,00,0x36,00,00,00,0x28,00,00,00,0xF0,00,00,00,0xA0,00,00,00,0x01,00,0x18,00,00,00,00,00,00,0xC2,0x01,00,0xE8,03,00,00,0xE8,03,00,00,00,00,00,00,00,00,00,00 };
	int width = im.width;
	int height = im.height;
	short int channel = 24;
	unsigned int size = width * height * 3;

	int bmpHeight = -height;

	memcpy(&heads[18], &width, sizeof(width));
	memcpy(&heads[22], &bmpHeight, sizeof(bmpHeight));
	memcpy(&heads[28], &channel, sizeof(channel));
	memcpy(&heads[2], &size, sizeof(size));
	fwrite(&heads, sizeof(heads), 1, fp);

	vec3 *color = NULL;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (im.pixel(x, y, &color))
			{
				r = (int)(255.0 * color->r);
				g = (int)(255.0 * color->g);
				b = (int)(255.0 * color->b);
				fwrite(&b, sizeof(BYTE), 1, fp);
				fwrite(&g, sizeof(BYTE), 1, fp);
				fwrite(&r, sizeof(BYTE), 1, fp);
			}

		}
	}

}


#endif