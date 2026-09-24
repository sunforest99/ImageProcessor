#include "ImageTransformFilter.h"

void ImageTransformFilter::apply(ip::ImageBuffer& image) const
{
	if (isCrop)
	{
		applyCrop(image);
	}
	else
	{
		applyResize(image);
	}
}

void ImageTransformFilter::applyCrop(ip::ImageBuffer& image) const
{
	if (x < 0 || y < 0 || width <= 0 || height <= 0)
	{
		throw ip::FilterError("width height is zero");
	}

	ip::ImageBuffer result(width, height);

	for (int newY = 0; newY < height; ++newY)
	{
		std::uint8_t* resultRow = result.rowPtr(newY);

		const std::uint8_t* sourceRow = image.rowPtr(y + newY);
		for (int newX = 0; newX < width; ++newX)
		{
			std::uint8_t* resultPixel = resultRow + newX * 3;

			const std::uint8_t* sourcePixel = sourceRow + (x + newX) * 3;

			resultPixel[0] = sourcePixel[0];
			resultPixel[1] = sourcePixel[1];
			resultPixel[2] = sourcePixel[2];
		}
	}

	image = std::move(result);
}

void ImageTransformFilter::applyResize(ip::ImageBuffer& image) const
{
	if (width <= 0 || height <= 0)
	{
		throw ip::FilterError("width height is zero");
	}

	ip::ImageBuffer result(width, height);

	for (int newY = 0; newY < height; ++newY)
	{
		std::uint8_t* resultRow = result.rowPtr(newY);

		int sourceY = newY * image.height() / height;

		const std::uint8_t* sourceRow = image.rowPtr(sourceY);
		for (int newX = 0; newX < width; ++newX)
		{
			int sourceX = newX * image.width() / width;

			std::uint8_t* resultPixel = resultRow + newX * 3;

			const std::uint8_t* sourcePixel = sourceRow + sourceX * 3;

			resultPixel[0] = sourcePixel[0];
			resultPixel[1] = sourcePixel[1];
			resultPixel[2] = sourcePixel[2];
		}
	}

	image = std::move(result);
}
