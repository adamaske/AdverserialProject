#include "Network.h"
#include <iostream>
#include <fstream>
#include <string>
Network::Network(const char* name, std::vector<Layer*> layers)
{
    mName = name;
    mLayers = layers;
}

Network::Network(const char* fileName)
{
    //Load network from file
    LoadFromFile(fileName);
}

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

    ////We want to change every variable as to reduce the cost function
    //    //We can find what way we should move the variable by getting the cost function
    //    //Derived on the variable, here for weights, the new weight the equals itself minus the gradient/slope/value
    //for (int i = 0; i < mInNodes; i++) {
    //    for (int j = 0; j < mOutNodes; j++) {
    //        //Find the partial derivatives, find totalCost/mWeigts[i] from it
    //        mWeightGradients[WeightIndex(i, j)] = mLastInputs[i] * CalculateActivationDerivative(mLastActivation[i]) * 2 * (mLastInputs[i] - mLastCorrect[i]);
    //        mWeights[WeightIndex(i, j)] = mWeights[WeightIndex(i, j)] - (mWeightGradients[WeightIndex(i, j)] * learnRate);
    //
    //        //The same for bias
    //        //mTotalCost / mBiases[i] = 
    //
    //        mBiasGradients[WeightIndex(i, j)] = 0;
    //        mBiases[WeightIndex(i, j)] = mBiases[WeightIndex(i, j)] - (mBiasGradients[WeightIndex(i, j)] * learnRate);
    //    }
    //}
    //The cost is a function of SUm(a-y^2), which is a function of w which is a function b
    // 
    //Update cost on last layer/create cost array
    Layer* mOutputLayer = mLayers[mLayers.size() - 1];
    mOutputLayer->CalculateCosts(correctOutput);
    //Sum of the costs for each output
    float cost = mOutputLayer->mTotalCost;


    //mOutputLayer->Backpropagate(0.5);
    for(int i = mLayers.size()-2; i >= 0; i--) {
        Layer* hiddenLayer = mLayers[i];
       
        //hiddenLayer->Backpropagate(0.5);
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
    std::ofstream file;
    file.open(mName);
    //Opens file
    if (file.is_open()) {
        //Start with the network name
        file << mName << std::endl;
        //Go through every layer
        for (int i = 0; i < mLayers.size(); i++) {
            //Start by name
            file << "Start Layer" << std::endl;
            //Print the layer here
            file << "Layer" << i << std::endl;
            //For each output node
            for (int node = 0; node < mLayers[i]->mOutNodes; node++) {
                //Every output node has inNodes amount weights connected to it
                for (int j = 0; j < mLayers[i]->mInNodes; j++) {
                    std::cout << "N" << node << ": ";
                    std::cout << "w" << mLayers[i]->mWeights[j + (mLayers[i]->mInNodes*node)] << ", ";
                }
                //Every out node has a bias
                std::cout << "B" << node << mLayers[i]->mBiases[node] << std::endl;
            }
            file << "End Layer" << std::endl;
        }
    }

    
}

void Network::LoadFromFile(const char* fileName)
{
    bool doLayer = false;
    std::vector<Layer*> layers;

    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        std::string line;
        int count = 0;
        while (std::getline(file, line)) {
            //The first line is always the name
            if (count == 0) {
               mName = line.c_str();
               break;
            }
            //A layer definition starts here
            if (line == "Start Layer") {
                Layer* layer;
                doLayer = true;
                //Go from here in layer mode
                while (std::getline(file, line) && doLayer) {
                    //End of the layer
                    if (line == "End Layer") {
                        
                        doLayer = false;
                        break;
                    }
                    //Layer info
                    if (line[0] == 'L') {

                    }
                    if(line[0] == 'N'){
                        //Go through the node for weights and bias
                    }
                }

                break;
            }

            
        }
    }
    else {
        //Cant open file
    }
   
}
