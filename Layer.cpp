#include "Layer.h"

Layer::Layer()
{
	neurons = std::vector<Neuron*>(0);
}

Layer::Layer(std::vector<Neuron*> input)
{
	neurons = input;
}

Layer::Layer(int n)
{
	this->neurons = std::vector<Neuron*>(n);
}

Layer::~Layer()
{
	for (unsigned int i = 0; i < this->neurons.size(); i++)
	{
		delete this->neurons[i];
	}
}

void Layer::calculateLayer(Layer* prevLayer)
{
	for (unsigned int c = 0; c < this->neurons.size(); c++) //c is for current layer's index
	{
		MathVector previousNodes(prevLayer->getLength());
		for (unsigned int p = 0; p < prevLayer->getLength(); p++) //p is for previous layer's index
		{
			previousNodes.push_back(prevLayer->operator[](p)->getOutput());
		}
		this->neurons[c]->calcOutput(&previousNodes);
	}
}

void Layer::setNeuron(int index, Neuron* n)
{
	this->neurons[index] = n;
}
Neuron* Layer::operator[](int index)
{
	return this->neurons[index];
}
Neuron* Layer::at(int index)
{
	return this->neurons[index];
}
unsigned int Layer::getLength()
{
	return this->neurons.size();
}

void Layer::randomizeLayer()
{
	for (unsigned int i = 0; i < neurons.size(); i++)
	{
		neurons[i]->randomizeNeuron();
	}
}