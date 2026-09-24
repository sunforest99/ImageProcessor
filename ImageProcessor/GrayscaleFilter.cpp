#include "GrayscaleFilter.h"

void GrayscaleFilter::apply(ip::ImageBuffer& image) const
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
			pixel[0] = gray;
			pixel[1] = gray;
			pixel[2] = gray;
		}
	}
}
