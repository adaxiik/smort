#include <iostream>
#include <vector>
#include "Neuron.hpp"
#pragma once
class Network
{
private:
    std::vector<std::vector<Neuron*>> layers;
    //std::vector<float> outputs;
    //std::vector<float> inputs;
    std::vector<float> GetLayerOutputs(size_t index);
    float learningRate;
    float fitness;


public:
    Network(float learningRate);
    Network(Network* net);
    ~Network();
    void AddLayer(int numNeurons);
    void FeedForward(std::vector<float> inputs);
    std::vector<float> GetOutputs();
    void Mutate();
    float GetFitness();
    void SetFitness(float fitness);
    void AddFitness(float fitness);
    float GetLearningRate();
    std::vector<std::vector<Neuron*>> GetLayers();

};
