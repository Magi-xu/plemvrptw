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
                 const int& readyTime,
                 const int& dueTime,
                 const int& serviceTime);

        const int& getId() const { return id;}
        const int& getX() const { return x;}
        const int& getY() const { return y;}
        const int& getDemand() const { return demand;}
        const int& getReadyTime() const { return readyTime;}
        const int& getDueTime() const { return dueTime;}
        const int& getServiceTime() const { return serviceTime;}
    private:
        int id;
        int x;
        int y;
        int demand;
        int readyTime;
        int dueTime;
        int serviceTime;
    };
} // vrptw



#endif //PLEMVRPTW_CUSTOMER_H
