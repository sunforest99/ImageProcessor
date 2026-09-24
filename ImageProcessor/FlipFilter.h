#pragma once
#include "FilterBase.h"

enum class FlipType
{
	Horizontal,
	Vertical,
	Both
};

class FlipFilter : public FilterBase
{
private:
	FlipType type;

public:
	FlipFilter(FlipType type)
	{
		this->type = type;
	}

	std::string name() const override
	{
		return "FlipFilter";
	}

	void apply(ip::ImageBuffer& image) const override;

	void applyHorizontal(ip::ImageBuffer& image) const;
	void applyVertical(ip::ImageBuffer& image) const;
};

