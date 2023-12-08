//
// Created by Magi Xu on 2023/12/7.
//

#include "Route.h"

namespace vrptw {

    Route::Route(const std::vector<Customer::ptr> customers,
                 const std::vector<std::vector<float>>& distanceMatrix,
                 const std::vector<std::vector<float>>& timeMatrix)
        : customers(customers) {
        delayTimeMatrix = std::vector<float> (customers.size());
        for (int i = 1; i < customers.size(); ++i) {
            load += customers[i]->getDemand();
            travleDistance += distanceMatrix[i - 1][i];
            travleTime += timeMatrix[i - 1][i];
            if (travleTime < customers[i]->getReadyTime()) {
                waitTime += customers[i]->getReadyTime() - travleTime;
                travleTime = customers[i]->getReadyTime();
            } else if (travleTime > customers[i]->getDueTime()) {
                delayTimeMatrix[i] = travleTime - customers[i]->getDueTime();
                delayTime += delayTimeMatrix[i];
            }
            travleTime += customers[i]->getServiceTime();
        }
    }

} // vrptw