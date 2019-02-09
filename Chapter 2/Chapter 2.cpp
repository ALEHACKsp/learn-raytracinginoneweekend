
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"

int main()
{
	int nx = 300;
	int ny = 200;

	Image im(nx, ny);
	int x, y;
	float r, g, b;
	//im.resize(nx, ny);


	for (y = 0; y < im.height; y++)
	{
		for (x = 0; x < im.width; x++)
		{
			r = 1.f - float(y) / float(im.height);
			g = float(x) / float(im.width);
			b = 0.2f;

			vec3& color = im.pixel(x, y);
			color.x = r;
			color.y = g;
			color.z = b;
		}
	}

	FILE *fp = NULL;
	fp = fopen("02.bmp", "wb+");
	WriteBMP(fp, im);
}
