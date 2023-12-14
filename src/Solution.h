//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_SOLUTION_H
#define PLEMVRPTW_SOLUTION_H

#include <vector>

#include "Route.h"

namespace vrptw {

    class Solution {
    public:
        typedef std::shared_ptr<Solution> ptr;
        explicit Solution(const std::vector<Route::ptr>& routes);

        [[nodiscard]] const std::vector<Route::ptr>& getRoutes() const { return routes;}
        [[nodiscard]] const int& getVehicleNumber() const { return vehicleNumber;}
        [[nodiscard]] const double& getTotalDistance() const { return totalDistance;}
        [[nodiscard]] const double& getTotalTime() const { return totalTime;}
        [[nodiscard]] const double& getWaitTime() const { return waitTime;}
        [[nodiscard]] const double& getDelayTime() const { return delayTime;}
        [[nodiscard]] const std::vector<double>& getFitness() const { return fitness;}
        [[nodiscard]] const double& getStrength() const { return strength;}
        [[nodiscard]] const double& getR_fitness() const { return r_fitness;}
        [[nodiscard]] const double& getF_fitness() const {return f_fitness;}

        void setStrength(const double& s) { strength = s;}
        void setR_fitness(const double& r) {r_fitness = r;}
        void setF_fitness(const double& f) { f_fitness = f;}
    private:
        std::vector<Route::ptr> routes;
        int vehicleNumber;
        double totalDistance;
        double totalTime;
        double waitTime;
        double delayTime;
        std::vector<double> fitness;
        double strength = 0;
        double r_fitness = 0;
        double f_fitness = 0;
    };

} // vrptw

#endif //PLEMVRPTW_SOLUTION_H
