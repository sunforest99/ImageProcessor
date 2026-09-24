#include "FlipFilter.h"

void FlipFilter::apply(ip::ImageBuffer& image) const
{
    switch (type)
    {
    case FlipType::Horizontal:
        applyHorizontal(image);
        break;
    case FlipType::Vertical:
        applyVertical(image);
        break;
    case FlipType::Both:
        applyHorizontal(image);
        applyVertical(image);
        break;
    }
}

void FlipFilter::applyHorizontal(ip::ImageBuffer& image) const
{
    ip::ImageBuffer tempImg = image;

    for (int y = 0; y < image.height(); ++y) 
    {
        std::uint8_t* destinationRow = image.rowPtr(y);

        const std::uint8_t* sourceRow =tempImg.rowPtr(y);

        for (int x = 0; x < image.width(); ++x) 
        {
            std::uint8_t* destinationPixel = destinationRow + x * 3;

            int sourceX = image.width() - 1 - x;

            const std::uint8_t* sourcePixel = sourceRow + sourceX * 3;

            destinationPixel[0] = sourcePixel[0];
            destinationPixel[1] = sourcePixel[1];
            destinationPixel[2] = sourcePixel[2];
        }
    }
}

void FlipFilter::applyVertical(ip::ImageBuffer& image) const
{
	ip::ImageBuffer tempImg = image;

	for (int y = 0; y < image.height(); ++y) 
    {
		std::uint8_t* row = image.rowPtr(y);

		const std::uint8_t* sourceRow = tempImg.rowPtr(image.height() - 1 - y);

		for (int x = 0; x < image.width(); ++x) 
        {
			std::uint8_t* destinationPixel = row + x * 3;

			const std::uint8_t* sourcePixel = sourceRow + x * 3;

			destinationPixel[0] = sourcePixel[0];
			destinationPixel[1] = sourcePixel[1];
			destinationPixel[2] = sourcePixel[2];
		}
	}
}
