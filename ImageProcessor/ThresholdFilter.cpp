#include "ThresholdFilter.h"

void ThresholdFilter::apply(ip::ImageBuffer& image) const
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
			int value = gray >= threshold ? 255 : 0;

			pixel[0] = value;
			pixel[1] = value;
			pixel[2] = value;
		}
	}
}
