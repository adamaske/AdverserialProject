#pragma once
#include <vector>
#include "Layer.h"
class Network
{
private:
	std::vector<Layer*> mLayers;
	std::vector<float> mCosts;
public:
	Network(std::vector<Layer*> layers) {
		mLayers = layers;
	};

	std::vector<float> Output(std::vector<float> input);
	std::vector<float> Output(std::vector<float> input, std::vector<float> correctOutput);
	void Backpropagate();
	void WriteToFile(const char* fileName);
	void UpdateAllGradients();
};

