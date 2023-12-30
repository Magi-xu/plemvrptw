//
// Created by Magi Xu on 2023/12/7.
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

    inline bool constraints(const Route::ptr& route, const Problem::ptr& problem);

    inline double euclideanDistance(const std::vector<double>& individual1, const std::vector<double>& individual2);

    inline Problem::ptr initProblem(const std::string& data_name, const double& vehicle_speed, const double& delay_time_allow);

    inline EA::ptr initModel(const Problem::ptr& problem, const size_t& population_size, const int& iterations);

    inline MLP::ptr initMLP(const int64_t& input_size, const int64_t& hidden_size, const int64_t& output_size);
    
    inline void printRoute(const Route::ptr& route);

    inline void printRoute(const std::vector<Customer::ptr>& route);

    inline void printSolution(const Solution::ptr& solution, const bool& detal=true);

    inline void writeToFile(const Solution::ptr& solution, const std::string& data_name);

} //vrptw

#endif //UTIL_H
