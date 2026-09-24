#pragma once
#include "FilterBase.h"

class ThresholdFilter : public FilterBase
{
private:
	int threshold = 0.0f;

public:
	ThresholdFilter(int threshold)
	{
		this->threshold = threshold;
	}

	std::string name() const override
	{
		return "Thresholding";
	}

	void apply(ip::ImageBuffer& image) const override;
};

