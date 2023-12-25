//
// Created by Magi Xu on 2023/12/7.
//

#include "MLP.h"

namespace vrptw{

    std::tuple<torch::Tensor, torch::Tensor> MLP::toTensor(std::vector<std::vector<double>>& population_codes, std::vector<std::vector<double>>& population_features) {
        torch::Tensor ts_population_codes = torch::from_blob(population_codes.data(), {
            static_cast<long>(population_codes.size()), static_cast<long>(population_codes[0].size())
        }, torch::kFloat);
        torch::Tensor ts_population_features = torch::from_blob(population_features.data(), {
            static_cast<long>(population_features.size()), static_cast<long>(population_features[0].size())
        }, torch::kFloat);
        return {ts_population_codes, ts_population_features};
    }
    
    void MLP::defOptimizer(const double& learning_rate) {
        optimizer = std::make_shared<torch::optim::Adam>(this->parameters(), torch::optim::AdamOptions(learning_rate));
    }
    
    void MLP::defCriterion() {
        criterion = std::make_shared<torch::nn::MSELoss>();
    }
    
    void MLP::trainModel(torch::Tensor& ts_population_codes, torch::Tensor& ts_population_features, const int& epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            torch::Tensor outputs = this->forward(ts_population_codes);
            torch::Tensor loss = (*criterion)(outputs, ts_population_features);
            optimizer->zero_grad();
            loss.backward();
            optimizer->step();
        }
    }
    
    torch::Tensor MLP::predict(torch::Tensor& ts_population_codes) {
        return this->forward(ts_population_codes);
    }
    
    std::tuple<std::vector<size_t>, std::vector<size_t>> MLP::toVector(torch::Tensor& predicted_outputs, const double& p) {
        auto size = predicted_outputs.sizes();
        auto data_accessor = predicted_outputs.accessor<float, 2>();
        std::vector<size_t>p1, p2;
        for (int i = 0; i < size[0]; ++i) {
            for (int j = 0; j < size[1]; ++j) {
                if (j == 0) if (data_accessor[i][j] >= p) p1.push_back(i);
                if (j == 1) if (data_accessor[i][j] >= p) p2.push_back(i);
            }
        }
        return {p1, p2};
    }

} //vrptw