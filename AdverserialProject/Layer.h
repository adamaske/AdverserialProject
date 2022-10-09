#pragma once
#include <vector>
#include <iostream>
class Layer
{
private:
	int mInNodes = 0;
	int mOutNodes = 0;
	//Each of my in nodes has a weight associted with each out node
	//Therefore in x out amount of weights
	std::vector<float> mWeights = { };
	//On bias per in or out node
	std::vector<float> mBiases;
	//For backpropagation
	std::vector<float> mBiasGradients;
	std::vector<float> mWeightGradients;
	std::vector<float> mLastWeightedInputs;
	std::vector<float> mLastInputs;
	std::vector<float> mLastActivation;
	std::vector<float> mLastCorrect;
	std::vector<float> mCosts;

	float mLearningRate = 0.1f;
	float mTotalCost = 0;
public:
	Layer(int connections, int nodes) {
		mInNodes = connections;
		mOutNodes = nodes;
		//Each in node has an outNodes amount of connections
		//So for each inNode, we need an array of OutNodes size
		//Init with zero values
		for (int i = 0; i < mInNodes * mOutNodes; i++) {
			mWeights.push_back(0);
			mWeightGradients.push_back(0);
		}

		for (int i = 0; i < mOutNodes; i++) {
			mBiases.push_back(0);
			mBiasGradients.push_back(0);
		}
	}

	void PopulateWithRandomness() {
		//std::cout << "Started randomness function!" << std::endl;
		for (int i = 0; i < mOutNodes; i++) {
			mBiases[i] = rand() % 10;
			//std::cout << "Set bias in outNodes : " + static_cast<int16_t>(i) << std::endl;
			for (int j = 0; j < mInNodes; j++) {
				mWeights[WeightIndex(j, i)] = ((-5 + (rand() % 10)) / 10.f);
			}

		}
	}

	std::vector<float> Output(std::vector<float> input) {
		mLastInputs = input;
		//Outputs = c1*w1.. +cN*wN +bN
		std::vector<float> outputs;
		//These are the inputs * weights + biases
		for (int i = 0; i < mOutNodes; i++) {
			outputs.push_back(0);
		}
		//For each of my nodes that gives an output, the outnodes
		for (int i = 0; i < mOutNodes; i++) {
			//Each node = c1*w1+cN*wN+biasN, init with the bias for this outnode
			float weighted = mBiases[i];
			//For each connections to this node
			for (int j = 0; j < mInNodes; j++){
				//Get the weight of this connection j to the current node i
				//Times the input input from this connection
				weighted  += input[j] * mWeights[WeightIndex(j, i)];
			}
			//This node has completed the cN*wN+bN
			mLastWeightedInputs.push_back(weighted);
			outputs[i] = CalculateActivation(weighted);
		}
		//Set last activation
		mLastActivation = outputs;
		//Return all the outputs
		return outputs;
	}

	float CalculateActivation(float value) {
		return tanh(value);
	}
	float CalculateActivationDerivative(float value) {
		return 1 - pow(tanh(value),2);
	}

	void CalculateCosts(std::vector<float> correctOutput) {
		mLastCorrect = correctOutput;
		for (int i = 0; i < mLastActivation.size(); i++) {
			mCosts.push_back(pow(mLastActivation[i] - correctOutput[i], 2));
		}
		float cost = 0;
		for (int i = 0; i < mCosts.size(); i++) {
			cost += mCosts[i];
		}
		mTotalCost = cost;
	}

	float CostDerivative(float activation, float correct) {
		return 2 * (activation - correct);
	}

	float WeightIndex(int in, int out) {
		return (in * out) + in;
	}
	
	void Backpropagate(float learnRate) {
		//We want to change every variable as to reduce the cost function
		//We can find what way we should move the variable by getting the cost function
		//Derived on the variable, here for weights, the new weight the equals itself minus the gradient/slope/value
		for (int i = 0; i < mInNodes; i++) {
			for (int j = 0; j < mOutNodes; j++) {
				//Find the partial derivatives, find totalCost/mWeigts[i] from it
				mWeightGradients[WeightIndex(i, j)] = mLastInputs[i] * CalculateActivationDerivative(mLastActivation[i]) * 2 * (mLastInputs[i] - mLastCorrect[i]);
				mWeights[WeightIndex(i, j)] = mWeights[WeightIndex(i, j)] - (mWeightGradients[WeightIndex(i, j)] * learnRate);

				//The same for bias
				//mTotalCost / mBiases[i] = 

				mBiasGradients[WeightIndex(i, j)] = 0;
				mBiases[WeightIndex(i, j)] = mBiases[WeightIndex(i, j)] -	(mBiasGradients[WeightIndex(i, j)] * learnRate);
			}
		}
		
	}
	void Backpropagate(float a, float b) {

	}

};

