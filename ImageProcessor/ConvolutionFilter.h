#pragma once
#include "FilterBase.h"
#include <algorithm>
#include <thread>
#include <vector>

enum class ConvolutionType
{
	Blur,
	Sharpen
};

class ConvolutionFilter : public FilterBase
{
private:
	int blurKernel[3][3] = {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
	};
	int sharpenKernel[3][3] = {
	{ 0, -1,  0},
	{-1,  5, -1},
	{ 0, -1,  0}
	};

	int(*kernel)[3] = nullptr;
	int divisor = 0.0f;

private:
	void processRowRange(
		ip::ImageBuffer& image,
		const ip::ImageBuffer& original,
		int startY,
		int endY
	) const;

public:
	ConvolutionFilter(ConvolutionType filter)
	{
		if (filter == ConvolutionType::Blur)
		{
			kernel = blurKernel;
			divisor = 9;
		}
		else if (filter == ConvolutionType::Sharpen)
		{
			kernel = sharpenKernel;
			divisor = 1;
		}
	}

	std::string name() const override
	{
		return "ConvolutionFilter";
	}
	void apply(ip::ImageBuffer& image) const override;
};

