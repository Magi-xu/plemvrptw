//
// Created by Magi Xu on 2023/12/7.
//

#include "Customer.h"

namespace vrptw {
    Customer::Customer(const int& id,
                       const int& x,
                       const int& y,
                       const int& demand,
                       const int& readyTime,
                       const int& dueTime,
                       const int& serviceTime)
        : id(id),
          x(x),
          y(y),
          demand(demand),
          readyTime(readyTime),
          dueTime(dueTime),
          serviceTime(serviceTime) { }
}