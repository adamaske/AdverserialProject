#include "Network.h"

std::vector<float> Network::Output(std::vector<float> input)
{
    for (int i = 0; i < mLayers.size(); i++) {
        input = mLayers[i]->Output(input);
    }
    return input;
}

std::vector<float> Network::Output(std::vector<float> input, std::vector<float> correctOutput)
{
    for (int i = 0; i < mLayers.size(); i++) {
        input = mLayers[i]->Output(input);
    }
    //Get squares of costs
    float cost = 0;
    //Cost equals the sum of input - correctanswer, squared for positive number
    for (int i = 0; i < correctOutput.size(); i++) {
        cost += pow(input[i] - correctOutput[i], 2);
    }
    mCosts.push_back(cost);
    Backpropagate();
    return input;
   
}

void Network::Backpropagate()
{
    //Use mCost and affect the layer
}

void Network::WriteToFile(const char* fileName)
{
    //Create file 
    //Go through every layer, start from the last one
    for(int i = mLayers.size() - 1; i > 0; i--) {

    }
}
