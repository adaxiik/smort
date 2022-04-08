#include <iostream>
#include <vector>
#pragma once
class Neuron
{
private:
    float bias;
    std::vector<float> weights;
    float output;
    float error;
public:
    Neuron(int numInputs,bool input);
    Neuron(Neuron* neuron);
    Neuron(int numInputs): Neuron(numInputs, false){};
    void CalculateOutput(std::vector<float> inputs);
    ~Neuron();
    float GetOutput();
    float GetOutputFull();
    void Mutate();
    std::vector<float> GetWeights();
};
