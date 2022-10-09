#pragma once
#include <vector>
#include "Layer.h"
class Network
{
private:
	std::vector<Layer*> mLayers;
public:
	Network(std::vector<Layer*> layers) {
		mLayers = layers;
	};

	std::vector<float> Output();
};

