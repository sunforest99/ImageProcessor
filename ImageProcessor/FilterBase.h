#pragma once
#include <string>
#include "ImageBuffer.h"

class FilterBase
{
public:
	virtual std::string name() const = 0;
	virtual void apply(ip::ImageBuffer& image) const = 0;
};

