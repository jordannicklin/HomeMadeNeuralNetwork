#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "NeuronNetwork.h"

class FileManager
{
private:
	std::string _filePath;

public:

	FileManager();
	FileManager(std::string filePath);

	void setFilePath(std::string filePath);

	void loadValuesIntoNn(NeuronNetwork* nn);
	NeuronNetwork loadNn();
	void saveNnValues(NeuronNetwork* nn);
};


/*
file layout:

*/