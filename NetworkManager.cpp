#include "NetworkManager.hpp"
#include <algorithm>

NetworkManager::NetworkManager(size_t numNetworks, std::vector<size_t> layers)
{
    numNetworks += numNetworks % 2;
    for (size_t i = 0; i < numNetworks; i++)
    {
        Network *net = new Network(0.1);
        for (size_t j = 0; j < layers.size(); j++)
            net->AddLayer(layers[j]);
        this->networks.push_back(net);
    }
    this->generation = 0;

    this->networkSizes = layers;
}

NetworkManager::~NetworkManager()
{
    for (auto net : this->networks)
    {
        delete net;
    }
}

Network *NetworkManager::GetNetwork(size_t index)
{
    return this->networks[index];
}

void NetworkManager::NextGeneration()
{
    this->generation++;
    //sort by fitness
    std::sort(this->networks.begin(), this->networks.end(), [](Network *a, Network *b)
              { return a->GetFitness() > b->GetFitness(); });

    size_t toKeep = this->networks.size()/2;

    for (size_t i = toKeep; i < this->networks.size(); i++)
    {
        delete this->networks[i];
    }
    this->networks.resize(toKeep);
    // for (size_t i = 0; i < this->networks.size(); i++)
    // {
    //     this->networks[i]->SetFitness(0);
    //     this->networks[i]->Mutate();
    // }

    for (size_t i = 0; i < toKeep; i++)
    {
        Network *net = new Network(this->networks[i]);
        net->Mutate();
        this->networks.push_back(net);
    }

    for (size_t i = 0; i < this->networks.size(); i++)
        this->networks[i]->SetFitness(0);

}

size_t NetworkManager::GetPopulationSize()
{
    return this->networks.size();
}

size_t NetworkManager::GetGeneration()
{
    return this->generation;
}

Network* NetworkManager::GetBestNetwork()
{
    return this->networks[0];
}