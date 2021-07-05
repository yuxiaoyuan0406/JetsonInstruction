#include <torch/torch.h>
#include <iostream>
#include "network.h"

using namespace torch;

int main()
{
    Net network(50, 10);
    auto x = torch::randn({2, 50});
    
    // torch::Device device(torch::kCPU);
    // if (torch::cuda::is_available())
    // {
    //     std::cout << "CUDA is available" << std::endl;
    //     device = torch::kCUDA;
    // }
    
    // x.to(device);
    // network->to(device);
    // network->out->to(device);

    std::cout << network << std::endl;
    std::cout << x << std::endl;

    auto output = network->forward(x);
    std::cout << output << std::endl;

    return 0;
}
