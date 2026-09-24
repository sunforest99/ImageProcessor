#include "FilterDispatcher.h"

void FilterDispatcher::checkOption(const ip::ProgramOptions& options, ip::ImageBuffer& image) const
{
	if (!options.pipeline.empty())
	{
		pipelineFilter(options.pipeline, image);
		return;
	}
	else if (options.filterName == "threshold")
	{
		if (options.threshold < 0)
		{
			throw ip::FilterError("--threshold is required");
		}

		ThresholdFilter filter(options.threshold);
		filter.apply(image);
		return;
	}
	
	applyOne(options.filterName, image);
	
	// --filter threshold --threshold 128
	// 이런 명령어 사용하기 위한 처리
	if (options.threshold >= 0) 
	{
		ThresholdFilter filter(options.threshold);
		filter.apply(image);
	}
}

void FilterDispatcher::pipelineFilter(const std::string& pipeline, ip::ImageBuffer& image) const
{
	const std::vector<std::string> filters = split(pipeline, ',');

	for (const std::string& filterText : filters) 
	{
		if (filterText.empty()) 
		{
			throw ip::FilterError("Pipeline contains an empty filter");
		}

		applyOne(filterText, image);
	}
}

void FilterDispatcher::applyOne(const std::string& filterText, ip::ImageBuffer& image) const
{
	if (filterText == "grayscale") 
	{
		GrayscaleFilter filter;
		filter.apply(image);
	}
	else if (filterText == "brightness")
	{
		BrightnessContrastFilter filter(30, 1.2);
		filter.apply(image);
	}
	else if (filterText == "blur")
	{
		ConvolutionFilter filter(ConvolutionType::Blur);
		filter.apply(image);
	}
	else if (filterText == "sharpen")
	{
		ConvolutionFilter filter(ConvolutionType::Sharpen);
		filter.apply(image);
	}
	else if (filterText.rfind("threshold:", 0) == 0)
	{
		const std::string valueText = filterText.substr(10);

		if (valueText.empty()) 
		{
			throw ip::FilterError("Threshold is empty");
		}

		int value = 0;

		try 
		{
			value = std::stoi(valueText);
		}
		catch (const std::exception&) 
		{
			throw ip::FilterError("threshold exception: " + valueText);
		}

		if (value < 0 || value > 255) 
		{
			throw ip::FilterError("Threshold 0-255");
		}

		ThresholdFilter filter(value);
		filter.apply(image);
	}
	else if (filterText == "crop") 
	{
		ImageTransformFilter filter(
			0,
			0,
			image.width() / 2,
			image.height() / 2
		);
		filter.apply(image);
	}
	else if (filterText == "resize")
	{
		ImageTransformFilter filter(image.width() / 2, image.height() / 2);
		filter.apply(image);
	}
	else if (filterText == "flip-horizontal")
	{
		FlipFilter filter(FlipType::Horizontal);
		filter.apply(image);
	}
	else if (filterText == "flip-vertical")
	{
		FlipFilter filter(FlipType::Vertical);
		filter.apply(image);
	}
	else if (filterText == "flip-both")
	{
		FlipFilter filter(FlipType::Both);
		filter.apply(image);
	}
	else if (filterText == "histogram")
	{
		Histogram histogram;
		histogram.calculateHistogram(image);
	}
	else
	{
		throw ip::FilterError("Unknown filter: " + filterText);
	}
}

std::vector<std::string> FilterDispatcher::split(const std::string& options, char delimiter) const
{
	std::vector<std::string> result;
	std::stringstream stream(options);
	std::string item;

	while (std::getline(stream, item, delimiter))
	{
		result.push_back(item);
	}

	return result;
}
