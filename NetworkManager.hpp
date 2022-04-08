#pragma once
#include <iostream>
#include <vector>
#include "Network.hpp"
class NetworkManager
{
private:    
    std::vector<Network*> networks;
    std::vector<size_t> networkSizes;
    size_t generation;
public:
    NetworkManager(size_t numNetworks, std::vector<size_t> layers);
    ~NetworkManager();

    Network* GetNetwork(size_t index);
    Network* GetBestNetwork();
    void NextGeneration();
    size_t GetPopulationSize();
    size_t GetGeneration();
};
