//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_EA_H
#define PLEMVRPTW_EA_H

#include "Problem.h"
#include "Solution.h"

namespace vrptw {

    class EA {
    public:
        typedef std::shared_ptr<EA> ptr;
        explicit EA(Problem::ptr problem);

        void setPopulation_size(const size_t& size) { population_size = size;}
        void setIterations(const int& iters) { iterations = iters;}

        [[nodiscard]] const std::vector<Solution::ptr>& getPopulation() const { return population;}

        [[nodiscard]] bool checkUniqueness(const Solution::ptr& s) ;

        void populationInitialize();

        void calStrength() const;
        void calR_fitness() const;
        void calCrowdingDistance();
        void calF_fitness(const double& k) const;

        void sortPopulation();
        void cullPopulation();
    private:
        Problem::ptr problem{};
        std::vector<Solution::ptr> population{};
        size_t population_size = 0;
        int iterations = 0;

        std::vector<std::vector<double>> crowdingDistanceMatrix;

        void normal_random_init();
        void pfih_distance_random_init();
        void pfih_time_random_init();
    };

} // vrptw

#endif //PLEMVRPTW_EA_H
