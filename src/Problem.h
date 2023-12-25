//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_PROBLEM_H
#define PLEMVRPTW_PROBLEM_H

#include <string>
#include <vector>
#include <memory>

#include "Customer.h"

namespace vrptw {

    class Problem {
    public:
        typedef std::shared_ptr<Problem> ptr;
        explicit Problem(const std::string& filename);

        [[nodiscard]] const std::string& getName() const { return name;}
        [[nodiscard]] const int& getVehicleNumber() const { return vehicleNumber;}
        [[nodiscard]] const int& getCapacity() const { return capacity;}
        [[nodiscard]] std::vector<Customer::ptr> getCustomers() const { return customers;}
        [[nodiscard]] int getCustomerNumber() const { return static_cast<int>(customers.size() - 1);}
        [[nodiscard]] Customer::ptr getCustomerById(const int& id) const { return customers[id];}
        [[nodiscard]] Customer::ptr getDepot() const { return customers[0];}

        void setVehicleSpeed(const double& speed) { vehicleSpeed = speed;}
        void setMaxDelayTime(const double& time) { maxDelayTime = time;}
        [[nodiscard]] const double& getMaxDelayTime() const { return maxDelayTime;}
        void setMaxReturnTime(const double& time) { maxReturnTime = time;}
        [[nodiscard]] const double& getMaxReturnTime() const { return maxReturnTime;}

        void calDistanceMatrix();
        [[nodiscard]] const std::vector<std::vector<double>>& getDistanceMatrix() const { return distanceMatrix;}
        void calTimeMatrix();
        [[nodiscard]] const std::vector<std::vector<double>>& getTimeMatrix() const { return timeMatrix;}
    private:
        std::string name;
        int vehicleNumber;
        int capacity;
        std::vector<Customer::ptr> customers;

        double vehicleSpeed = 1;
        double maxDelayTime = 0;
        double maxReturnTime = 0;

        std::vector<std::vector<double>> distanceMatrix;
        std::vector<std::vector<double>> timeMatrix;
    };

} // vrptw

#endif //PLEMVRPTW_PROBLEM_H
