#pragma once
#include "FilterBase.h"
#include "Exceptions.h"

class ImageTransformFilter : public FilterBase
{
private:
	int x = 0;
	int y = 0;

	int width = 0;
	int height = 0;

	bool isCrop = false;

public:
	ImageTransformFilter(int x, int y, int width, int height)
	{
		isCrop = true;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	ImageTransformFilter(int width, int height)
	{
		isCrop = false;
		this->width = width;
		this->height = height;
	}


	std::string name() const override
	{
		return "ImageTransformFilter";
	}

	void apply(ip::ImageBuffer& image) const override;

	void applyCrop(ip::ImageBuffer& image) const;
	void applyResize(ip::ImageBuffer& image) const;
};

