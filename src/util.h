//
// Created by Magi Xu on 2023/12/8.
//

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace vrptw {

    inline bool constraints(const Route::ptr& route, const Problem::ptr& problem) {
        if (route->getLoad() > problem->getCapacity()) return false;
        if (route->getTravleTime() > problem->getMaxReturnTime()) return false;
        if (!std::ranges::all_of(route->getDelayTimeMatrix(), [&](const auto& x) {
            return x <= problem->getMaxDelayTime();
        })) return false;

        return true;
    }

    inline double euclideanDistance(const std::vector<double>& individual1, const std::vector<double>& individual2) {
        double sum = 0;
        for (size_t i = 0; i < individual1.size(); ++i) {
            sum += std::pow(individual1[i] - individual2[i], 2);
        }
        return std::sqrt(sum);
    }

    inline Problem::ptr initProblem(const std::string& data_name, const double& vehicle_speed, const double& delay_time_allow) {
        const auto problem = std::make_shared<Problem>("../data/solomon_100/" + data_name + ".txt");
        problem->setVehicleSpeed(vehicle_speed);
        problem->setMaxDelayTime(delay_time_allow);
        problem->setMaxReturnTime(problem->getCustomers()[0]->getDueTime());
        return problem;
    }

    inline EA::ptr initModel(const Problem::ptr& problem, const size_t& population_size, const int& iterations) {
        const auto ea = std::make_shared<EA>(problem);
        ea->setPopulation_size(population_size);
        ea->setIterations(iterations);
        return ea;
    }

    // inline MLP::ptr initMLP(const int64_t& input_size, const int64_t& hidden_size, const int64_t& output_size) {
    //     const auto model = std::make_shared<MLP>(input_size, hidden_size, output_size);
    //     return model;
    // }
    //
    // inline std::tuple<torch::Tensor, torch::Tensor> toTensor(const std::vector<std::vector<int>>& population_codes, const std::vector<std::vector<double>>& population_features) {
    //     torch::Tensor ts_population_codes = torch::from_blob(population_codes.data(), {
    //         static_cast<long>(population_codes.size()), static_cast<long>(population_codes[0].size())
    //     }, torch::kInt);
    //     torch::Tensor ts_population_features = torch::from_blob(population_features.data(), {
    //         static_cast<long>(population_features.size()), static_cast<long>(population_features[0].size())
    //     }, torch::kDouble);
    //     return {ts_population_codes, ts_population_features};
    // }
    //
    // using OptimizerPtr = std::shared_ptr<torch::optim::Optimizer>;
    // using CriterionPtr = std::shared_ptr<torch::nn::MSELoss>;
    //
    // inline OptimizerPtr defOptimizer(MLP::ptr& model, const double& learning_rate) {
    //     return std::make_shared<torch::optim::Adam>(model->parameters(), torch::optim::AdamOptions(learning_rate));
    // }
    //
    // inline CriterionPtr defCriterion() {
    //     return std::make_shared<torch::nn::MSELoss>();
    // }
    //
    // inline void trainModel(MLP::ptr& model, torch::Tensor& ts_population_codes, torch::Tensor& ts_population_features, const int& epochs, OptimizerPtr& optimizer, CriterionPtr& criterion) {
    //     for (int epoch = 0; epoch < epochs; ++epoch) {
    //         torch::Tensor outputs = model->forward(ts_population_codes);
    //         torch::Tensor loss = (*criterion)(outputs, ts_population_features);
    //         optimizer->zero_grad();
    //         loss.backward();
    //         optimizer->step();
    //     }
    // }
    //
    // inline torch::Tensor predict(MLP::ptr& model, torch::Tensor& ts_population_codes) {
    //     return model->forward(ts_population_codes);
    // }
    //
    // inline std::tuple<std::vector<int>, std::vector<int>> toVector(torch::Tensor& predicted_outputs, const double& p) {
    //     auto size = predicted_outputs.sizes();
    //     auto data_accessor = predicted_outputs.accessor<double, 2>();
    //     std::vector<size_t>p1, p2;
    //     for (int i = 0; i < size[0]; ++i) {
    //         for (int j = 0; j < size[1]; ++j) {
    //             if (j == 0) if (data_accessor[i][j] >= p) p1.push_back(i);
    //             if (j == 1) if (data_accessor[i][j] >= p) p2.push_back(i);
    //         }
    //     }
    //     return {p1, p2};
    // }

    inline void printRoute(const Route::ptr& route) {
        std::cout << "Route:\t ";
        const auto& customers = route->getCustomers();
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            std::cout << (*it)->getId();
            if (it + 1 != customers.end()) std::cout << "\t-->\t";
        }
        std::cout << std::endl;
    }

    inline void printRoute(const std::vector<Customer::ptr>& route) {
        std::cout << "Route:\t ";
        const auto& customers = route;
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            std::cout << (*it)->getId();
            if (it + 1 != customers.end()) std::cout << "\t-->\t";
        }
        std::cout << std::endl;
    }

    inline void printSolution(const Solution::ptr& solution, const bool& detal=true) {
        std::cout << "NV: " << solution->getVehicleNumber() << "\t\tTD: " << solution->getTotalDistance() << std::endl;
        if (!detal) return;
        for (const auto& route : solution->getRoutes()) {
            printRoute(route);

        }
    }

    inline void writeToFile(const Solution::ptr& solution, const std::string& data_name) {
        const std::string folder = "../results/solomon_100/" + data_name + "/";
        const std::string filename = folder + data_name + ".txt";
        if (!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);
        const std::ofstream file(filename, std::ios::app);  // 使用 append 模式打开文件
        std::streambuf* original_cout = std::cout.rdbuf();
        std::cout.rdbuf(file.rdbuf());  // 重定向标准输出到文件
        const std::time_t current_time = std::time(nullptr);
        std::cout << data_name << ":\t" << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S") << std::endl;
        printSolution(solution);
        std::cout << std::endl;
        std::cout.rdbuf(original_cout);  // 恢复标准输出
    }

} //vrptw

#endif //UTIL_H
