//
// Created by Magi Xu on 2023/12/7.
//

#ifndef PLEMVRPTW_EA_H
#define PLEMVRPTW_EA_H

#include <vector>
#include <memory>

#include "Problem.h"
#include "Solution.h"

namespace vrptw {

    class EA {
    public:
        typedef std::shared_ptr<EA> ptr;
        explicit EA(Problem::ptr problem);

        void setPopulation_size(const size_t& size) {
            population_size = size;
            population_features = std::vector<std::vector<double>> (size, std::vector<double> (2));
        }
        void setIterations(const int& iters) { iterations = iters;}

        [[nodiscard]] const std::vector<Solution::ptr>& getPopulation() const { return population;}
        [[nodiscard]] const std::vector<std::vector<int>>& getCodes() const { return population_codes;}
        [[nodiscard]] const std::vector<std::vector<double>>& getFeatures() const { return population_features;}

        [[nodiscard]] bool checkUniqueness(const Solution::ptr& s) ;

        void populationInitialize();

        void calStrength() const;
        void calR_fitness() const;
        void calCrowdingDistance();
        void calF_fitness(const double& k) const;
        void calFeature();

        void sortPopulation();
        void cullPopulation();

        void encode();
        [[nodiscard]] Solution::ptr decode(const std::vector<int>& code) const;

        void generate(const std::vector<size_t>& i1, const std::vector<size_t>& i2);

        void printBest(const int& i, const bool& detal) const;
    private:
        Problem::ptr problem{};
        std::vector<Solution::ptr> population{};
        size_t population_size = 0;
        int iterations = 0;

        std::vector<std::vector<double>> crowdingDistanceMatrix;
        std::vector<std::vector<int>> population_codes;
        std::vector<std::vector<double>> population_features;

        void normal_random_init();
        void pfih_distance_random_init();
        void pfih_time_random_init();
        void cross1(const std::vector<std::vector<std::vector<Customer::ptr>>>& solutions);
        void cross2(const std::vector<std::vector<std::vector<Customer::ptr>>>& solutions);
        void mutation1(const std::vector<std::vector<std::vector<Customer::ptr>>>& solutions);
        void mutation2(const std::vector<std::vector<std::vector<Customer::ptr>>>& solutions);
        void getNewPopulation(const std::vector<Solution::ptr>& selected_population, const int8_t& type = 0);
    };

} // vrptw

#endif //PLEMVRPTW_EA_H
