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
