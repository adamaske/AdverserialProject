#pragma once
#include <vector>
#include "Layer.h"
class Network
{
private:
	std::vector<Layer*> mLayers;
	std::vector<float> mCosts;
	const char* mName = "Network 1";
public:
	Network(const char* name, std::vector<Layer*> layers);
	Network(const char* fileName);
	std::vector<float> Output(std::vector<float> input);
	std::vector<float> Output(std::vector<float> input, std::vector<float> correctOutput);
	void Backpropagate();
	void WriteToFile(const char* fileName);
	void LoadFromFile(const char* fileName);
	void UpdateAllGradients();
};

