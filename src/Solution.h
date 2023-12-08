//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_SOLUTION_H
#define PLEMVRPTW_SOLUTION_H

#include <vector>
#include <memory>

#include "Route.h"

namespace vrptw {

    class Solution {
    public:
        typedef std::shared_ptr<Solution> ptr;
        Solution(const std::vector<Route::ptr> routes);

        void setStrength(const float& s) { strength = s;}
        void setR_fitness(const float& r) {r_fitness = r;}
        void setF_fitness(const float& f) { f_fitness = f;}
    private:
        std::vector<Route::ptr> routes;
        int vehicleNumber = 0;
        float travleDistance = 0;
        float travleTime = 0;
        float waitTime = 0;
        float delayTime = 0;
        std::vector<float> fitness;
        float strength = 0;
        float r_fitness = 0;
        float f_fitness = 0;
    };

} // vrptw

#endif //PLEMVRPTW_SOLUTION_H
