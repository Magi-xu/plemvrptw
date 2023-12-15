//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_CUSTOMER_H
#define PLEMVRPTW_CUSTOMER_H

#include <memory>


namespace vrptw {

    class Customer {
    public:
        typedef std::shared_ptr<Customer> ptr;
        Customer(const int& id,
                 const int& x,
                 const int& y,
                 const int& demand,
                 const double& readyTime,
                 const double& dueTime,
                 const double& serviceTime);

        [[nodiscard]] const int& getId() const { return id;}
        [[nodiscard]] const int& getX() const { return x;}
        [[nodiscard]] const int& getY() const { return y;}
        [[nodiscard]] const int& getDemand() const { return demand;}
        [[nodiscard]] const double& getReadyTime() const { return readyTime;}
        [[nodiscard]] const double& getDueTime() const { return dueTime;}
        [[nodiscard]] const double& getServiceTime() const { return serviceTime;}
    private:
        int id;
        int x;
        int y;
        int demand;
        double readyTime;
        double dueTime;
        double serviceTime;
    };

} // vrptw

#endif //PLEMVRPTW_CUSTOMER_H
