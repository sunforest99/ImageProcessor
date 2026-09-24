#pragma once
#include "FilterBase.h"
#include <algorithm>

class BrightnessContrastFilter : public FilterBase
{
private:
	int birght = 0;
	double contrast = 1.0f;
	const int MIN = 0;
	const int MAX = 255;

public:
	BrightnessContrastFilter(int birght, double contrast)
	{
		this->birght = birght;
		this->contrast = contrast;
	}

	std::string name() const override
	{
		return "BrightnessContrastFilter";
	}

	void apply(ip::ImageBuffer& image) const override;
};

