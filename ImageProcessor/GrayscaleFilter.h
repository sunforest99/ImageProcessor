#pragma once
#include "FilterBase.h"

class GrayscaleFilter : public FilterBase
{
public:
	std::string name() const override
	{
		return "grayscale";
	}

	void apply(ip::ImageBuffer& image) const override;
};

