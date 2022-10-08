#pragma once
#include <vector>
class Layer
{
	int mInNodes = 0;
	int mOutNodes = 0;
	//Each of my in nodes has a weight associted with each out node
	//Therefore in x out amount of weights
	std::vector<std::vector<float>> mWeights = { {} };
	//On bias per in or out node
	std::vector<float> mBiases = { {} };
public:
	Layer(int connections, int nodes) {
		mInNodes = connections;
		mOutNodes = nodes;
		//Each in node has an outNodes amount of connections
		//So for each inNode, we need an array of OutNodes size
		mWeights.reserve(mInNodes);
		for (int i = 0; i < mWeights.size(); i++) {
			mWeights[i].reserve(mOutNodes);
		}
		mBiases.reserve(mOutNodes);
	}

	std::vector<float> Output(std::vector<float> input) {
		//Outputs = c1*w1.. +cN*wN +bN
		std::vector<float> outputs;
		//These are the inputs * weights + biases
		outputs.reserve(mOutNodes);
		//For each of my nodes that gives an output, the outnodes
		for (int i = 0; i < mOutNodes; i++) {
			//Each node = c1*w1+cN*wN+biasN, init with the bias for this outnode
			float weighted = mBiases[i];
			//For each connections to this node
			for (int j = 0; j < mInNodes; j++){
				//Get the weight of this connection j to the current node i
				//Times the input input from this connection
				weighted  += input[j] * mWeights[j][i];
			}
			//This node has completed the cN*wN+bN
			outputs[i] = weighted;
		}
		//Return all the outputs
		return outputs;
	}

	void PopulateWithRandomness() {
		for (int i = 0; i < mOutNodes; i++) {
			mBiases[i] = (rand() % 10);
			for (int j = 0; j < mInNodes; j++) {
				mWeights[i][j] = (rand() % 10) / 10;
			}
			
		}
	}
};

