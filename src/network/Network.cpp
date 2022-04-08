#include "Network.hpp"
#include "Neuron.hpp"

Network::Network(float learningRate)
{
    this->learningRate = learningRate;
    this->fitness = 0;
}

Network::Network(Network *net)
{
    this->learningRate = net->GetLearningRate();
    this->fitness = 0;
    for (size_t i = 0; i < net->GetLayers().size(); i++)
    {
        this->layers.push_back(std::vector<Neuron *>());
        for (size_t j = 0; j < net->GetLayers()[i].size(); j++)
        {
            this->layers[i].push_back(new Neuron(net->GetLayers()[i][j]));
        }
    }
}

Network::~Network()
{
    for (auto layer : this->layers)
    {
        for (auto neuron : layer)
        {
            delete neuron;
        }
    }
}
std::vector<std::vector<Neuron *>> Network::GetLayers()
{
    return this->layers;
}

void Network::AddLayer(int numNeurons)
{
    std::vector<Neuron *> layer;
    for (int i = 0; i < numNeurons; i++)
    {
        //layer.push_back(Neuron(layers[layers.size() - 1].size()));
        if (layers.size() == 0)
        {
            layer.push_back(new Neuron(1, true));
        }
        else
        {
            layer.push_back(new Neuron(layers[layers.size() - 1].size()));
        }
    }
    this->layers.push_back(layer);
}

void Network::FeedForward(std::vector<float> inputs)
{
    //std::vector<float> outputs;
    for (size_t i = 0; i < this->layers[0].size(); i++)
    {
        this->layers[0][i]->CalculateOutput(std::vector<float>{inputs[i]});
        //outputs.push_back(this->layers[0][i].GetOutput());
    }

    for (size_t i = 1; i < this->layers.size(); i++)
    {
        for (size_t j = 0; j < this->layers[i].size(); j++)
        {
            this->layers[i][j]->CalculateOutput(GetLayerOutputs(i - 1));
        }
    }
}

std::vector<float> Network::GetOutputs()
{
    std::vector<float> outputs;
    size_t last = this->layers.size() - 1;
    for (size_t i = 0; i < this->layers[last].size(); i++)
        outputs.push_back(this->layers[last][i]->GetOutputFull());
    
    return outputs;
}

std::vector<float> Network::GetLayerOutputs(size_t index)
{
    std::vector<float> outputs;
    if(!index)
        for (size_t i = 0; i < this->layers[0].size(); i++)
            outputs.push_back(this->layers[0][i]->GetOutputFull());
    else
        for (size_t i = 0; i < this->layers[index].size(); i++)
            outputs.push_back(this->layers[index][i]->GetOutput());

    return outputs;
}

void Network::Mutate()
{

    // ?

    for (size_t i = 1; i < this->layers.size(); i++)
    {
        for (size_t j = 0; j < this->layers[i].size(); j++)
        {
            if (((float)(rand() % 1000) / 1000) < this->learningRate){
                this->layers[i][j]->Mutate();
            }
        }
    }
}

float Network::GetFitness()
{
    return this->fitness;
}

void Network::SetFitness(float fitness)
{
    this->fitness = fitness;
}
void Network::AddFitness(float fitness)
{
    this->fitness += fitness;
}

float Network::GetLearningRate()
{
    return this->learningRate;
}