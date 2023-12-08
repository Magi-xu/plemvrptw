//
// Created by Magi Xu on 2023/12/7.
//

#include "Solution.h"

namespace vrptw {

    Solution::Solution(const std::vector<Route::ptr>& routes)
        : routes(routes), vehicleNumber(0), totalDistance(0), totalTime(0), waitTime(0), delayTime(0) {
        vehicleNumber = static_cast<int>(routes.size());
        for (auto& route : routes) {
            totalDistance += route->getTravleDistance();
            totalTime += route->getTravleTime();
            waitTime += route->getWaitTime();
            delayTime += route->getDelayTime();
        }
        fitness = std::vector<double> {static_cast<double>(vehicleNumber), totalDistance};
    }

} // vrptw