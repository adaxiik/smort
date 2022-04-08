#include "Neuron.hpp"
#include <random>

Neuron::Neuron(int numInputs, bool input)
{
	this->bias = input?0:1;
	this->output = 0.0;
	
	for (int i = 0; i < numInputs; i++)
		if (input)
			this->weights.push_back(1.0);
		else
			this->weights.push_back((float)(rand()) / ((float)(RAND_MAX / 2)) - 1);
}

Neuron::Neuron(Neuron* neuron)
{
	this->bias = neuron->bias;
	this->output = neuron->output;
	this->weights = neuron->GetWeights();
}

Neuron::~Neuron()
{
}

float Neuron::GetOutput()
{
	return std::max(0.0f, this->output);
	//return this->output;
}

float Neuron::GetOutputFull()
{
	return this->output;
}

void Neuron::CalculateOutput(std::vector<float> inputs)
{
	float sum = 0.0;
	for (size_t i = 0; i < this->weights.size(); i++)
	{
		sum += this->weights[i] * inputs[i];
	}
	sum += this->bias;
	this->output = sum; // ReLU
}
void Neuron::Mutate()
{

	for (size_t i = 0; i < this->weights.size(); i++)
	{
		//Mutate types:
		//0: Flip sign
		//1: Random between -1 and 1
		//2: Random increase
		//3: Random decrease
		int type = rand() % 4;
		switch (type)
		{
		case 0:
			this->weights[i] = -this->weights[i];
			break;
		case 1:
			this->weights[i] = ((float)rand()/(float)RAND_MAX)*2 - 1;
			break;
		case 2:
			this->weights[i] *= ((float)rand()/(float)RAND_MAX) + 1.0f;
			break;
		case 3:
			this->weights[i] *= ((float)rand()/(float)RAND_MAX);
			break;
		default:
			break;
		}
	}
	int type = rand()%100;
	if (type < 10)
		this->bias = ((float)rand()/(float)RAND_MAX)*2 - 1;
	else if(type < 20)
		this->bias *= ((float)rand()/(float)RAND_MAX) + 1.0f;
	else if(type < 30)
		this->bias *= ((float)rand()/(float)RAND_MAX);
	

}

std::vector<float> Neuron::GetWeights()
{
	return this->weights;
}