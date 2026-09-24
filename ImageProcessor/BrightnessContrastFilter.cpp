#include "BrightnessContrastFilter.h"

void BrightnessContrastFilter::apply(ip::ImageBuffer& image) const
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

			pixel[0] = std::clamp(b + birght, MIN, MAX);
			pixel[1] = std::clamp(g + birght, MIN, MAX);
			pixel[2] = std::clamp(r + birght, MIN, MAX);

			pixel[0] = std::clamp(
				static_cast<int>((b - 128) * contrast + 128 + birght),
				MIN,
				MAX
			);

			pixel[1] = std::clamp(
				static_cast<int>((g - 128) * contrast + 128 + birght),
				MIN,
				MAX
			);

			pixel[2] = std::clamp(
				static_cast<int>((r - 128) * contrast + 128 + birght),
				MIN,
				MAX
			);
		}
	}
}
