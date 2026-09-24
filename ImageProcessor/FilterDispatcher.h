#pragma once

#include <vector>
#include <sstream>

#include "Exceptions.h"
#include "ImageBuffer.h"
#include "CommandLineParser.h"

// Ä¿½ºÅÒ Çì´õ
#include "GrayscaleFilter.h"
#include "BrightnessContrastFilter.h"
#include "ThresholdFilter.h"
#include "ConvolutionFilter.h"
#include "Histogram.h"
#include "FlipFilter.h"
#include "ImageTransformFilter.h"

class FilterDispatcher
{
public:
	void checkOption(const ip::ProgramOptions& options, ip::ImageBuffer& image) const;
	
	void applyOne(const std::string& filterText, ip::ImageBuffer& image) const;
	void pipelineFilter(const std::string& pipeline, ip::ImageBuffer& image) const;

	std::vector<std::string> split(const std::string& options, char delimiter) const;
};

