#include "Histogram.h"

void Histogram::calculateHistogram(ip::ImageBuffer& image)
{
	for (int y = 0; y < image.height(); ++y)
	{
		std::uint8_t* row = image.rowPtr(y);

		for (int x = 0; x < image.width(); ++x)
		{
			std::uint8_t* pixel = row + x * 3;

			int b = pixel[0];
			int g = pixel[1];
			int r = pixel[2];

			int gray = (299 * r + 587 * g + 114 * b) / 1000;
			histogram[gray]++;
		}
	}

	printHistogram();
}

void Histogram::printHistogram() const
{
	for (int i = 0; i < 256; ++i)
	{
		std::cout
			<< "brightness " << i
			<< ": " << histogram[i]
			<< '\n';
	}
}
