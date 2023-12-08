//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_ROUTE_H
#define PLEMVRPTW_ROUTE_H

#include <vector>
#include <memory>

#include "Problem.h"
#include "Customer.h"

namespace vrptw {

    class Route {
    public:
        typedef std::shared_ptr<Route> ptr;
        Route(const std::vector<Customer::ptr> customers,
              const std::vector<std::vector<float>>& distanceMatrix,
              const std::vector<std::vector<float>>& timeMatrix);

        const std::vector<Customer::ptr> getCustomers() const { return customers;}
        const int& getLoad() const { return load;}
        const float& getTravleDistance() const { return travleDistance;}
        const float& getTravleTime() const { return travleTime;}
        const float& getWaitTime() const { return waitTime;}
        const float& getDelayTime() const { return delayTime;}
    private:
        std::vector<Customer::ptr> customers;
        int load = 0;
        float travleDistance = 0;
        float travleTime = 0;
        float waitTime = 0;
        float delayTime = 0;
        std::vector<float> delayTimeMatrix;
    };

} // vrptw

#endif //PLEMVRPTW_ROUTE_H
