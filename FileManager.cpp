#include "FileManager.h"

//t
FileManager::FileManager()
{
	_filePath = "network.db";
}

FileManager::FileManager(std::string filePath)
{
	_filePath = filePath;
}

void FileManager::setFilePath(std::string filePath)
{
	_filePath = filePath;
}

void FileManager::loadValuesIntoNn(NeuronNetwork* nn)
{
	std::ifstream _fileStream;
	std::string line;

	_fileStream.open(_filePath, 'r');

	while (getline(_fileStream, line))
	{
		std::cout << line << '\n';
	}

	_fileStream.close();
}

NeuronNetwork FileManager::loadNn()
{
	std::string line;
	std::ifstream myfile("example.txt");

	std::string numberOfLayers;
	std::string numberOfNeuronsInInput;

	int neuronIndex = 0;
	int layerIndex = 0;

	// layer neuron value
	std::vector<std::vector<std::vector<std::string>>> values;

	getline(myfile, numberOfLayers);

	while (getline(myfile, line) && line != "end")
	{
		if (line == "h")
		{
			layerIndex++;
		}
		if (line == "n")
		{
			neuronIndex++;
		}
		else
		{
			values.at(layerIndex).at(neuronIndex).push_back(line);
		}
	}
	
	myfile.close();

	NeuronNetwork nn = NeuronNetwork(values);

	return nn;
}

void FileManager::saveNnValues(NeuronNetwork* nn)
{
	std::ofstream _fileStream;

	_fileStream.open(_filePath, 'w');

	//saves input layer
	for (int j = 0; j < nn->getInputLayer()->getLength(); j++)
	{
		//sets a new neuron
		_fileStream << 'n';
		_fileStream << '\n';

		//saves the neuron details
		_fileStream << nn->getInputLayer()->at(j)->getWeights();
		_fileStream << '\n';
		_fileStream << nn->getInputLayer()->at(j)->getBias();
		_fileStream << '\n';
	}

	//saves the hidden layer
	for (int i = 0; i < nn->getHiddeLayer().size(); i++)
	{
		//sets a new layer
		_fileStream << 'l';
		_fileStream << '\n';

		for (int j = 0; j < nn->getHiddeLayer().at(i)->getLength(); j++)
		{
			//sets a new neuron
			_fileStream << 'n';
			_fileStream << '\n';

			//saves the neuron details
			_fileStream << nn->getHiddeLayer().at(i)->at(j)->getWeights();
			_fileStream << '\n';
			_fileStream << nn->getHiddeLayer().at(i)->at(j)->getBias();
			_fileStream << '\n';
		}
	}
	
	//sets a new layer
	_fileStream << 'l';
	_fileStream << '\n';

	//saves output layer
	for (int j = 0; j < nn->getOutputLayer()->getLength(); j++)
	{
		//sets a new neuron
		_fileStream << 'n';
		_fileStream << '\n';

		//saves the neuron details
		_fileStream << nn->getOutputLayer()->at(j)->getWeights();
		_fileStream << '\n';
		_fileStream << nn->getOutputLayer()->at(j)->getBias();
		_fileStream << '\n';
	}

	//saves the number of neurons in the output layer
	_fileStream << "end";
	_fileStream << '\n';

	_fileStream.close();
}