#pragma once
#include "ImageBuffer.h"
#include <iostream>

class Histogram
{
private:
	int histogram[256] = {};

public:
	void calculateHistogram(ip::ImageBuffer& image);
	void printHistogram() const;
};

