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
    //
    for (int i = 0; i < mLayers.size(); i++) {
        input = mLayers[i]->Output(input);
    }
    //Update cost on last layer/create cost array
    std::cout << "Starting backprop" << std::endl;
    float learnRate = 0.5;
    Layer* mOutputLayer = mLayers[mLayers.size() - 1];
    //Only the output layer can create the cost function
    mOutputLayer->CalculateCosts(correctOutput);
    std::cout << "Started finding OutputLayer gradients" << std::endl;
    //For every weight we want to find a gradient for which it affects the cost function    
    for (int i = 0; i < mOutputLayer->mInNodes; i++) {
        for (int j = 0; j < mOutputLayer->mOutNodes; j++) {
            //outh1 = aL, Etotal = TotalCost, net = z(l) 
            //This should be correct now
            //c0/aL = 2(aL -y) because '(a-y)^2 = 2 al -y, 
            //How the cost function is effected by the activation of this node
            auto c = 2 * mOutputLayer->mLastActivation[j] - correctOutput[j];

            //al/z(l) = 'activationfunction, 
            //How the activation of this node is affected by the weightedInput, derivative of thee activation function
            auto b = mOutputLayer->CalculateActivationDerivative(mOutputLayer->mLastWeightedInputs[j]);

            //zL/wL = al-1, 
            //How the activation of this node is effected by the current weight
            auto a = mLayers[mLayers.size() - 1]->mLastActivation[j];

            //zL/bL = 1
            //TotalCost derived by this weight = gradient
            mOutputLayer->mWeightGradients[j + (j*i)] = a * b * c;
            mOutputLayer->mBiasGradients[j] = 1 * b * c;
        }
    }
    //now we have the gradients for all the weights connected to the outputs
    //Now go backwards in the network
    
    //Sum of the costs for each output SUM(a_j*^2 -y_j)^2
    float c0 = mOutputLayer->mTotalCost;
    //Go through every weight
    std::vector<float> costs = mOutputLayer->mCosts;

    //mOutputLayer->Backpropagate(0.5);
    for (int l = mLayers.size() - 2; l >= 0; l--) {
        for (int i = 0; i < mLayers[l]->mInNodes; i++) {
            for (int j = 0; j < mLayers[l]->mOutNodes; j++) {
                //outh1 = aL, Etotal = TotalCost, net = z(l) 
                //This should be correct now
                //c0/aL = 2(aL -y) because '(a-y)^2 = 2 al -y, 
                // c0 / al = e / al + e1 / al
                //How the cost function is effected by the activation of this node
                //Denne er annerledes
                //Vil ha nodeouts fra layersa over denne
                float test = 1;
                for (int k = l; k < mLayers.size(); k++) {
                    for (int p = 0; p < mLayers[k]->mOutNodes; p++) {
                       
                    }
                    
                }
                auto c = 2 * mLayers[l]->mLastActivation[j] - ;
                //al/z(l) = 'activationfunction, 
                //How the activation of this node is affected by the weightedInput, derivative of thee activation function
                auto b = mLayers[l]->CalculateActivationDerivative(mLayers[l]->mLastWeightedInputs[j]);
                //zL/wL = al-1, AL-1 is the activation of the previous node
                //How the activation of this node is effected by the current weight
                auto a = mLayers[l]->mLastInputs[i];
                //zL/bL = 1
                //TotalCost derived by this weight = gradient
                mLayers[l]->mWeightGradients[i + (j * i)] = a * b * c;
                mLayers[l]->mBiasGradients[j] = 1 * b * c;                
            }
        }
        //hiddenLayer->Backpropagate(0.5);
    }
    //Apply gradients to all the weights
    for (int i = 0; i < mLayers.size(); i++) {
        for (int j = 0; j < mLayers[i]->mInNodes; j++) {
            for (int k = 0; k < mLayers[i]->mOutNodes; k++) {
                mLayers[i]->mWeights[j + (k * j)] = mLayers[i]->mWeights[j + (k * j)] - (mLayers[i]->mWeightGradients[j + (k*j)] * learnRate);
                mLayers[i]->mBiases[k] = mLayers[i]->mBiases[k] - (mLayers[i]->mBiasGradients[k] * learnRate);
            }
        }
    }

    //all the weights = weight - (learnRate * gradientWeights)
    std::cout << "Completed an output of network" << std::endl;
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
