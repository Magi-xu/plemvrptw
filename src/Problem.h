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
        Problem(const std::string& filename);

        const std::string& getName() const { return name;}
        const int& getVehicleNumber() const { return vehicleNumber;}
        const int& getCapacity() const { return capacity;}
        const std::vector<Customer::ptr> getCustomers() const { return customers;}
        const int getCustomerNumber() const { return customers.size();}

        void setVehicleSpeed(const int& speed) { vehicleSpeed = speed;}
        void setMaxDelayTime(const int& time) { maxDelayTime = time;}
        void setMaxReturnTime(const int& time) { maxReturnTime = time;}

        void setDistanceMatrix();
        void setTimeMatrix();
    private:
        std::string name;
        int vehicleNumber;
        int capacity;
        std::vector<Customer::ptr> customers;

        int vehicleSpeed;
        int maxDelayTime;
        int maxReturnTime;

        std::vector<std::vector<float>> distanceMatrix;
        std::vector<std::vector<float>> timeMatrix;
    };

} // vrptw

#endif //PLEMVRPTW_PROBLEM_H
