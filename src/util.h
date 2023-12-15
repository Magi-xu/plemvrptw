//
// Created by Magi Xu on 2023/12/8.
//

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>

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

    inline void printSolution(const Solution::ptr& solution) {
        std::cout << "vehicle_number:" << solution->getVehicleNumber() << " total_distance:" << solution->getTotalDistance() << std::endl;
        for (const auto& route : solution->getRoutes()) {
            const auto& customers = route->getCustomers();
            for (auto it = customers.begin(); it != customers.end(); ++it) {
                std::cout << (*it)->getId();
                if (it + 1 != customers.end()) std::cout << "-->";
            }
            std::cout << std::endl;
        }
    }

} //vrptw

#endif //UTIL_H
