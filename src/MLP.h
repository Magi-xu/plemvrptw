//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_MLP_H
#define PLEMVRPTW_MLP_H

#include <torch/torch.h>


namespace vrptw{

    struct MLP : torch::nn::Module {
        MLP(int64_t input_size, int64_t hidden_size, int64_t output_size) {
            fc1 = register_module("fc1", torch::nn::Linear(input_size, hidden_size));
            fc2 = register_module("fc2", torch::nn::Linear(hidden_size, hidden_size));
            fc3 = register_module("fc3", torch::nn::Linear(hidden_size, output_size));
            relu = register_module("relu", torch::nn::ReLU());
            sigmoid = register_module("sigmoid", torch::nn::Sigmoid());
        }

        torch::Tensor forward(torch::Tensor x) {
            x = relu->forward(fc1->forward(x));
            x = relu->forward(fc2->forward(x));
            x = sigmoid->forward(fc3->forward(x));
            return x;
        }

        torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
        torch::nn::ReLU relu;
        torch::nn::Sigmoid sigmoid;
    };

} //vrptw


#endif //PLEMVRPTW_MLP_H
