#include "NeuronNetwork.h"
#include <cmath>

NeuronNetwork::NeuronNetwork(std::vector<std::vector<std::vector<std::string>>> values)
{
	int hiddenLayerSize = values.size() - 2;

	//loads the input
	for (int i = 0; i < values.at(0).size(); i++)
	{
		_inputLayer->at(i)->setValues(values.at(0).at(i));
	}

	//loads hidden
	for (int i = 1; i < hiddenLayerSize + 1; i++)
	{
		for (int j = 0; j < values.at(0).size(); j++)
		{
			_hiddenLayers.at(i)->at(j)->setValues(values.at(values.size() - 1).at(i));
		}
	}

	//loads output
	for (int i = 0; i < values.at(values.size() - 1).size(); i++)
	{
		_outputLayer->at(i)->setValues(values.at(values.size() - 1).at(i));
	}
}

NeuronNetwork::NeuronNetwork(int numOfLayers, int layerSizes[])
{
	this->_inputLayer = new Layer(layerSizes[0]);
	this->_outputLayer = new Layer(layerSizes[numOfLayers - 1]);

	this->_hiddenLayers = std::vector<Layer*>(numOfLayers - 2);

	for (int i = 1; i < numOfLayers - 1; i++)
	{
		this->_hiddenLayers[i] = new Layer(layerSizes[i]);
	}
}

void NeuronNetwork::setInputLayer(std::vector<float> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		this->_inputLayer->operator[](i)->setOutput(input[i]);
	}
}

void NeuronNetwork::calcHiddenLayer()
{
	for (unsigned int i = 0; i < _hiddenLayers.size(); i++)
	{
		if (0 == i)
		{
			this->_hiddenLayers[i]->calculateLayer(_inputLayer);
		}
		else
		{
			this->_hiddenLayers[i]->calculateLayer(_hiddenLayers[i-1]);
		}
	}
}

void NeuronNetwork::calcLoss(MathVector expectedResult)
{
	_outputLayer->calculateLayer(_hiddenLayers[_hiddenLayers.size() - 1]);

	for (int i = 0; i < expectedResult.size(); i++)
	{
		Neuron* n = _outputLayer->at(i);
		_loss[i] = (n->getOutput() - expectedResult[i]) * (n->getOutput() - expectedResult[i]);
	}
}

void NeuronNetwork::randomize()
{
	for (unsigned int i = 0; i < this->_hiddenLayers.size(); i++)
	{
		_outputLayer[i].randomizeLayer();
	}
}

Layer* NeuronNetwork::getInputLayer()
{
	return _inputLayer;
}

std::vector<Layer*> NeuronNetwork::getHiddeLayer()
{
	return _hiddenLayers;
}

Layer* NeuronNetwork::getOutputLayer()
{
	return _outputLayer;
}

void NeuronNetwork::debugLoss()
{
	//std::cout << "" << std::endl;
}

void NeuronNetwork::backProp(std::vector<float> adjustments)
{
	//the adjustment vector to the results should have the same length as the output, to tell which value each neuron should have had
	if (adjustments.size() != this->_outputLayer->getLength())
	{
		return;
	}

	//making the vector the size of the second to last layer initializing all values to 0
	std::vector<float> fixVector = std::vector<float>(this->_outputLayer->getLength());
	std::fill(fixVector.begin(), fixVector.end(), 0);

	//making a vector of all layers reversed, so it would be easier to tweak each layer's neurons
	std::vector<Layer*> allLayers = std::vector<Layer*>(this->_hiddenLayers.size() + 2);
	allLayers[0] = this->_outputLayer;
	allLayers[allLayers.size() - 1] = _inputLayer;
	for (int i = 1; i < allLayers.size() - 2; i++)
	{
		allLayers[i] = this->_hiddenLayers[this->_hiddenLayers.size() - 1 - i];
	}

	//now, the actual backpropagation
	//going over every layer but the input layer, since there's nothing to be changed there
	for (int i = 0; i < allLayers.size() - 1; i++)
	{
		//current layer and previous layer
		Layer* currL = allLayers.at(i);
		Layer* prevL = allLayers.at(i + 1);
		//P.S. the "previous" layer is actually the next in allLayers, but the point is it works

		//the vector for the next adjustments has the same length as the previous layer to match every "fix" for a neuron
		std::vector<float> nextAdjustments = std::vector<float>(prevL->getLength());

		for (int i = 0; i < currL->getLength(); i++)
		{
			//getting the current neuron and its weights to more easily tweak them
			Neuron* currN = currL->operator[](i);
			MathVector* currNWeights = currN->getWeights();
			currN->setBias(currN->getBias() + adjustments[i]);

			for (int u = 0; u < currNWeights->size(); u++)
			{
				//adjusting the current neuron's weights proportionally to the activations of its previous neurons
				currNWeights->setValueAt(adjustments[u] * prevL->at(u)->getOutput(), u);

				//saving the fix to the adjustment vector so it can pass it on to the next layer
				nextAdjustments[u] += adjustments[i] * prevL->at(u)->getOutput();
			}
		}
		//passing the new adjustment information to the next layer
		adjustments = nextAdjustments;
	}
}