
#include <iostream>
#include <fstream>

int main()
{
	int nx = 200;
	int ny = 100;


	std::ofstream output("01.ppm");

	output << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;

			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			output << ir << " " << ig << " " << ib << "\n";
		}
	}
}
