//
// Created by Magi Xu on 2023/12/7.
//

#include "Solution.h"

namespace vrptw {

    Solution::Solution(const std::vector<Route::ptr> routes)
        : routes(routes) {
        vehicleNumber = routes.size();
        for (auto route : routes) {
            travleDistance += route->getTravleDistance();
            travleTime += route->getTravleTime();
            waitTime += route->getWaitTime();
            delayTime += route->getDelayTime();
        }
        fitness = std::vector<float> {float(vehicleNumber), travleDistance};
    }
} // vrptw