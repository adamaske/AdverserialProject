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
    
    //Update cost on last layer/create cost array
    Layer* mOutputLayer = mLayers[mLayers.size() - 1];
    mOutputLayer->Backpropagate(0.5);

    for(int i = mLayers.size()-2; i >= 0; i--) {
        Layer* hiddenLayer = mLayers[i];
        hiddenLayer->Backpropagate(0.5);
    }

    return input;
}

void Network::Backpropagate()
{
    //Use mCost and affect the layer
    //the last layer
    Layer* outputLayer = mLayers[mLayers.size() - 1];
    
   //for (int i = mLayers.size() - 2; i >= 0; i--) {
   //    Layer* hiddenLayer = mLayers[i];
   //    hiddenLayer.
   //}
}

void Network::WriteToFile(const char* fileName)
{
    //Create file 
    //Go through every layer, start from the last one
    for(int i = mLayers.size() - 1; i > 0; i--) {

    }
}
