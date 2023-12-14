//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_ROUTE_H
#define PLEMVRPTW_ROUTE_H

#include <vector>

#include "Customer.h"

namespace vrptw {

    class Route {
    public:
        typedef std::shared_ptr<Route> ptr;
        Route(const std::vector<Customer::ptr>& customers,
              const std::vector<std::vector<double>>& distanceMatrix,
              const std::vector<std::vector<double>>& timeMatrix);

        [[nodiscard]] std::vector<Customer::ptr> getCustomers() const { return customers;}
        [[nodiscard]] const int& getLoad() const { return load;}
        [[nodiscard]] const double& getTravleDistance() const { return travleDistance;}
        [[nodiscard]] const double& getTravleTime() const { return travleTime;}
        [[nodiscard]] const double& getWaitTime() const { return waitTime;}
        [[nodiscard]] const double& getDelayTime() const { return delayTime;}
        [[nodiscard]] const std::vector<double>& getDelayTimeMatrix() const { return delayTimeMatrix;}
    private:
        std::vector<Customer::ptr> customers;
        int load;
        double travleDistance;
        double travleTime;
        double waitTime;
        double delayTime;
        std::vector<double> delayTimeMatrix;
    };

} // vrptw

#endif //PLEMVRPTW_ROUTE_H
