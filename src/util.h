//
// Created by Magi Xu on 2023/12/8.
//

#ifndef UTIL_H
#define UTIL_H

namespace vrptw {

    inline bool constraints(const Route::ptr& route, const Problem::ptr& problem) {
        if (route->getLoad() > problem->getCapacity()) return false;
        if (route->getTravleTime() > problem->getMaxReturnTime()) return false;
        if (!std::ranges::all_of(route->getDelayTimeMatrix(), [&](const auto& x) {
            return x <= problem->getMaxDelayTime();
        })) return false;

        return true;
    }

    inline double euclideanDistance(const std::vector<double>& individual1, const std::vector<double>& individual2) {
        double sum = 0;
        for (size_t i = 0; i < individual1.size(); ++i) {
            sum += std::pow(individual1[i] - individual2[i], 2);
        }
        return std::sqrt(sum);
    }

} //vertp

#endif //UTIL_H
