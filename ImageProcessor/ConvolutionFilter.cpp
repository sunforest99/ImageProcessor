#include "ConvolutionFilter.h"

void ConvolutionFilter::apply(ip::ImageBuffer& image) const
{
	const ip::ImageBuffer original = image;

	int processRows = image.height() - 2;

	if (processRows <= 0)
	{
		return;
	}

	std::uint32_t threadCount = std::thread::hardware_concurrency();

	if (threadCount == 0)
	{
		threadCount = 1;
	}

	threadCount = std::min(threadCount, static_cast<std::uint32_t>(processRows));

	int rowsPerThread = (processRows + threadCount - 1) / threadCount;

	std::vector<std::thread> threads;

	for (std::uint32_t i = 0; i < threadCount; ++i)
	{
		int startY = 1 + i * rowsPerThread;
		
		int endY = std::min(startY + rowsPerThread, image.height() - 1);

		if (startY >= endY)
		{
			break;
		}

		threads.emplace_back(
			[this, &image, &original, startY, endY]()
			{
				processRowRange(image, original, startY, endY);
			}
		);
	}

	for (std::thread& thread : threads)
	{
		thread.join();
	}
}

void ConvolutionFilter::processRowRange(ip::ImageBuffer& image, const ip::ImageBuffer& original, int startY, int endY) const
{
	for (int y = startY; y < endY; ++y)
	{
		for (int x = 1; x < image.width() - 1; ++x)
		{
			int sumB = 0;
			int sumG = 0;
			int sumR = 0;

			for (int offsetY = -1; offsetY <= 1; ++offsetY)
			{
				const std::uint8_t* sourceRow = original.rowPtr(y + offsetY);

				for (int offsetX = -1; offsetX <= 1; ++offsetX)
				{
					const std::uint8_t* sourcePixel = sourceRow + (x + offsetX) * 3;

					int weight = kernel[offsetY + 1][offsetX + 1];

					sumB += sourcePixel[0] * weight;
					sumG += sourcePixel[1] * weight;
					sumR += sourcePixel[2] * weight;
				}
			}
			std::uint8_t* resultPixel = image.rowPtr(y) + x * 3;

			resultPixel[0] = std::clamp(sumB / divisor, 0, 255);
			resultPixel[1] = std::clamp(sumG / divisor, 0, 255);
			resultPixel[2] = std::clamp(sumR / divisor, 0, 255);
		}
	}
}
