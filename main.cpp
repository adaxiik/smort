#include "NetworkManager.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
struct Input
{
    float expected;
    float input;
};

// std::vector<Input> LoadInputFromFile(const std::string filename)
// {
//     std::vector<Input> inputs;
//     std::ifstream file(filename);
//     while (!file.eof())
//     {
//         Input i;
//         file >> i.input >> i.expected;
//         inputs.push_back(i);
//     }

//     return inputs;
// }

float CalculateError(float expected, float actual)
{
    return (fabs(expected - actual) / fabs(expected))* 100;
}
float fn(float x)
{
    //return (x) / (sqrt(1 + pow(x, 2)));
    return sinf(x);
}
Input GetInput(){
    Input i;
    //generate float input [-3,3]
    i.input = (float)((float)rand()/(float)RAND_MAX)*6 - 3;
    i.expected = fn(i.input);
    return i;
}

Network *train(NetworkManager* manager, size_t iterations,size_t inputs)
{
    
    for (size_t i = 0; i < iterations; i++)
    {
        for (size_t j = 0; j < manager->GetPopulationSize(); j++)
        {
            Network *net = manager->GetNetwork(j);
            float averageError = 0;
            for (size_t k = 0; k < inputs; k++)
            {

                Input input = GetInput();
                net->FeedForward({input.input});
                float output = net->GetOutputs()[0];
                float err = CalculateError(input.expected, output);   
                averageError += err;
                float fitness =  100 - err;         
                //net->AddFitness(fitness>0?fitness:0);
                net->AddFitness(fitness);
            }
            if(j==0)
                std::cout << "Average error: " << averageError / inputs << std::endl;
            
        }


        //std::cout << manager->GetBestNetwork()->GetFitness() << std::endl;
        manager->NextGeneration();
    }
    // std::cout << manager->GetBestNetwork()->GetFitness() << std::endl;
    return manager->GetBestNetwork();
}

// void SampleNetwork(Network* net, float start, float end, float step)
// {
//     std::ofstream file("output.txt");
//     for (float i = start; i < end; i += step)
//     {
//         net->FeedForward({i});
//         float output = net->GetOutputs()[0];
//         if(output<0)
//             std::cout<<"<"<<i<<" "<<output<<std::endl;
//         file << i << " " << output << std::endl;
//     }
// }
void SampleNetwork(Network* net, size_t samples){

    std::ofstream file("output.txt");
    for (size_t i = 0; i < samples; i++)
    {
        Input input = GetInput();
        net->FeedForward({input.input});
        float output = net->GetOutputs()[0];
        file << input.input << " " << output << std::endl;
    }
    file.close();

}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    //std::vector<Input> inputs = LoadInputFromFile("testdata.txt");
    NetworkManager *manager = new NetworkManager(50, {1, 5,5,5, 1});
    Network *net = train(manager, 1000,1000);
    std::cout << "Sampling" << std::endl;
    //SampleNetwork(net, -3, 3, 0.01);
    SampleNetwork(net, 1000);
    // while (true)
    // {
    //     std::cout << "> ";
    //     float input;
    //     std::cin >> input;
    //     if(input == -69)
    //         break;

    //     net->FeedForward({input});
    //     std::cout << "< " << net->GetOutputs()[0] << std::endl;
    // }
    delete manager;

    return 0;
}

