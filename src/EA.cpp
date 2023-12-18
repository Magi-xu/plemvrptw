//
// Created by Magi Xu on 2023/12/7.
//

#include "EA.h"

#include <utility>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <random>

#include "util.h"

namespace vrptw {

    EA::EA(Problem::ptr problem)
        : problem(std::move(problem)){ }

    bool EA::checkUniqueness(const Solution::ptr& s) {
        if (std::ranges::all_of(population, [&](const auto& solution) {
            return (s->getVehicleNumber() != solution->getVehicleNumber() ||
                s->getTotalDistance() != solution->getTotalDistance() ||
                s->getTotalTime() != solution->getTotalTime() ||
                s->getWaitTime() != solution->getWaitTime() ||
                s->getDelayTime() != solution->getDelayTime());
        })) return true;
        return false;
    }

    void EA::populationInitialize() {
        for (int i = 0; i < population_size; ++i) {
            if (i < population_size / 2) normal_random_init();
            else if (i < 3 * population_size / 4) pfih_distance_random_init();
            else pfih_time_random_init();
        }
    }

    void EA::normal_random_init() {
        while (true){
            std::vector<int> customer_id(problem->getCustomerNumber());
            std::iota(customer_id.begin(), customer_id.end(), 1);
            const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::ranges::shuffle(customer_id.begin(), customer_id.end(), std::default_random_engine(seed));
            std::vector<std::vector<Customer::ptr>> routes;
            routes.emplace_back(2, problem->getDepot());
            size_t now_route = 0;
            size_t i = 0;
            while (i < customer_id.size()) {
                routes[now_route].insert(routes[now_route].end() - 1, problem->getCustomerById(customer_id[i]));
                if (Route::ptr temp_route(new Route(routes[now_route], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                    !constraints(temp_route, problem)) {
                    routes[now_route].erase(routes[now_route].end() - 2);
                    bool sf = false;
                    for (int j = 0; j < routes.size(); ++j) {
                        for (int k = 1; k < routes[j].size() - 1; ++k) {
                            routes[j].insert(routes[j].begin() + k, problem->getCustomerById(customer_id[i]));
                            if (Route::ptr new_temp_route(new Route(routes[j], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                                !constraints(new_temp_route, problem)) {
                                routes[j].erase(routes[j].begin() + k);
                            } else {
                                sf = true;
                                now_route = j;
                                break;;
                            }
                        }
                        if (sf) break;
                    }
                    if (!sf) {
                        routes.emplace_back(2, problem->getDepot());
                        routes.back().insert(routes.back().end() - 1, problem->getCustomerById(customer_id[i]));
                        now_route = routes.size() - 1;
                    }
                }
                ++i;
            }
            std::vector<Route::ptr> r;
            r.reserve(routes.size());
            for (auto& route : routes) {
                r.push_back(std::make_shared<Route>(route, problem->getDistanceMatrix(), problem->getTimeMatrix()));
            }
            if(auto s = std::make_shared<Solution>(r); checkUniqueness(s)) {
                population.push_back(s);
                break;
            }
        }
    }

    void EA::pfih_distance_random_init() {
        while (true){
            std::vector<int> customer_id(problem->getCustomerNumber());
            std::iota(customer_id.begin(), customer_id.end(), 1);
            std::ranges::sort(customer_id.begin(), customer_id.end(), [&](const int& a, const int& b) {
                return problem->getDistanceMatrix()[0][a] < problem->getDistanceMatrix()[0][b];
            });
            std::vector<std::vector<Customer::ptr>> routes;
            routes.emplace_back(2, problem->getDepot());
            routes[0].insert(routes[0].end() - 1, problem->getCustomerById(customer_id[0]));
            customer_id.erase(customer_id.begin());
            size_t i = 0;
            const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::ranges::shuffle(customer_id.begin(), customer_id.end(), std::default_random_engine(seed));
            while (i < customer_id.size()) {
                double min_gap_distance = std::numeric_limits<double>::max();
                int min_j = 0, min_k = 0;
                bool sf = false;
                for (int j = 0; j < routes.size(); ++j) {
                    const Route::ptr old_route(new Route(routes[j], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                    const double old_distance = old_route->getTravleDistance();
                    for (int k = 1; k < routes[j].size() - 1; ++k) {
                        routes[j].insert(routes[j].begin() + k, problem->getCustomerById(customer_id[i]));
                        if (const Route::ptr new_temp_route(new Route(routes[j], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                            constraints(new_temp_route, problem)){
                            if (const double gap = new_temp_route->getTravleDistance() - old_distance; gap < min_gap_distance) {
                                min_gap_distance = gap;
                                min_j = j;
                                min_k = k;
                                sf = true;
                            }
                        }
                        routes[j].erase(routes[j].begin() + k);
                    }
                }
                if (sf) routes[min_j].insert(routes[min_j].begin() + min_k, problem->getCustomerById(customer_id[i]));
                else {
                    routes.emplace_back(2, problem->getDepot());
                    routes.back().insert(routes.back().end() - 1, problem->getCustomerById(customer_id[i]));
                }
                ++i;
            }
            std::vector<Route::ptr> r;
            r.reserve(routes.size());
            for (auto& route : routes) {
                r.push_back(std::make_shared<Route>(route, problem->getDistanceMatrix(), problem->getTimeMatrix()));
            }
            if(auto s = std::make_shared<Solution>(r); checkUniqueness(s)) {
                population.push_back(s);
                break;
            }
        }
    }

    void EA::pfih_time_random_init() {
        while (true){
            std::vector<int> customer_id(problem->getCustomerNumber());
            std::iota(customer_id.begin(), customer_id.end(), 1);
            std::ranges::sort(customer_id.begin(), customer_id.end(), [&](const int& a, const int& b) {
                return problem->getCustomerById(a)->getReadyTime() < problem->getCustomerById(b)->getReadyTime();
            });
            std::vector<std::vector<Customer::ptr>> routes;
            routes.emplace_back(2, problem->getDepot());
            routes[0].insert(routes[0].end() - 1, problem->getCustomerById(customer_id[0]));
            customer_id.erase(customer_id.begin());
            size_t i = 0;
            const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::ranges::shuffle(customer_id.begin(), customer_id.end(), std::default_random_engine(seed));
            while (i < customer_id.size()) {
                double min_gap_waitTime = std::numeric_limits<double>::max();
                int min_j = 0, min_k = 0;
                bool sf = false;
                for (int j = 0; j < routes.size(); ++j) {
                    const Route::ptr old_route(new Route(routes[j], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                    const double old_waitTime = old_route->getWaitTime();
                    for (int k = 1; k < routes[j].size() - 1; ++k) {
                        routes[j].insert(routes[j].begin() + k, problem->getCustomerById(customer_id[i]));
                        if (const Route::ptr new_temp_route(new Route(routes[j], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                            constraints(new_temp_route, problem)){
                            if (const double gap = new_temp_route->getTravleDistance() - old_waitTime; gap < min_gap_waitTime) {
                                min_gap_waitTime = gap;
                                min_j = j;
                                min_k = k;
                                sf = true;
                            }
                        }
                        routes[j].erase(routes[j].begin() + k);
                    }
                }
                if (sf) routes[min_j].insert(routes[min_j].begin() + min_k, problem->getCustomerById(customer_id[i]));
                else {
                    routes.emplace_back(2, problem->getDepot());
                    routes.back().insert(routes.back().end() - 1, problem->getCustomerById(customer_id[i]));
                }
                ++i;
            }
            std::vector<Route::ptr> r;
            r.reserve(routes.size());
            for (auto& route : routes) {
                r.push_back(std::make_shared<Route>(route, problem->getDistanceMatrix(), problem->getTimeMatrix()));
            }
            if(auto s = std::make_shared<Solution>(r); checkUniqueness(s)) {
                population.push_back(s);
                break;
            }
        }
    }

    void EA::calStrength() const {
        for (const auto& p : population) {
            for (const auto& s : population) {
                if (p == s) continue;
                const auto& fitnessP = p->getFitness();
                const auto& fitnessS = s->getFitness();
                bool allLess = true;
                for (size_t i = 0; i < fitnessP.size(); ++i) {
                    if (fitnessP[i] >= fitnessS[i]) {
                        allLess = false;
                        break;
                    }
                }
                if (allLess) {
                    p->setStrength(p->getStrength() + 1);
                }
            }
        }
    }

    void EA::calR_fitness() const {
        for (const auto& p : population) {
            for (const auto& s : population) {
                if (p == s) continue;
                const auto& fitnessP = p->getFitness();
                const auto& fitnessS = s->getFitness();
                bool allLess = true;
                for (size_t i = 0; i < fitnessP.size(); ++i) {
                    if (fitnessP[i] <= fitnessS[i]) {
                        allLess = false;
                        break;
                    }
                }
                if (allLess) {
                    p->setR_fitness(p->getR_fitness() + s->getStrength());
                }
            }
        }
    }

    void EA::calCrowdingDistance() {
        const size_t n = population.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    crowdingDistanceMatrix[i][j] = euclideanDistance(population[i]->getFitness(), population[j]->getFitness());
                }
            }
        }
    }

    void EA::calF_fitness(const double& k) const {
        std::vector<double> kthDistances(population.size(), 0.0);
        for (size_t i = 0; i < population.size(); ++i) {
            std::vector<double> sortedDistances = crowdingDistanceMatrix[i];
            std::ranges::sort(sortedDistances.begin(), sortedDistances.end());
            kthDistances[i] = sortedDistances[static_cast<int>(k)];
        }
        for (size_t i = 0; i < population.size(); ++i) {
            population[i]->setF_fitness(population[i]->getR_fitness() + 1.0 / (kthDistances[i] + 2));
        }
    }

    void EA::calFeature() {
        std::vector<Solution::ptr> p1 = population;
        std::vector<Solution::ptr> p2 = population;
        std::ranges::sort(p1.begin(), p1.end(), [&](const Solution::ptr&a, const Solution::ptr& b) {
            return a->getVehicleNumber() < b->getVehicleNumber();
        });
        std::ranges::sort(p2.begin(), p2.end(), [&](const Solution::ptr&a, const Solution::ptr& b) {
            return a->getTotalDistance() < b->getTotalDistance();
        });
        double score1 = 1, score2 = 1;
        for (const auto& s : p1) {
            const auto index = std::ranges::distance(population.begin(), std::ranges::find(population, s));
            population_features[index][0] = score1;
            score1 -= 1 / static_cast<double>(population_size);
        }
        for (const auto& s : p2) {
            const auto index = std::ranges::distance(population.begin(), std::ranges::find(population, s));
            population_features[index][1] = score2;
            score2 -= 1 / static_cast<double>(population_size);
        }
    }

    void EA::sortPopulation() {
        std::ranges::sort(population.begin(), population.end(), [&](const Solution::ptr& a, const Solution::ptr& b) {
            return a->getF_fitness() < b->getF_fitness();
        });
    }

    void EA::cullPopulation() {
        const std::vector<Solution::ptr> new_population(population.begin(), population.begin() + static_cast<std::ptrdiff_t>(population_size));
        population = new_population;
    }

    void EA::encode() {
        for (size_t i = 0; i < population.size(); ++i) {
            std::vector<int> code(problem->getCustomerNumber());
            size_t index = 0;
            for (const auto& route : population[i]->getRoutes()) {
                for (const auto& customer : route->getCustomers()) {
                    if (customer->getId() != 0) code[index++] = customer->getId();
                }
            }
            population_codes[i] = code;
        }
    }

    Solution::ptr EA::decode(const std::vector<int>& code) const {
        std::vector<std::vector<Customer::ptr>> routes;
        routes.emplace_back(2, problem->getDepot());
        size_t i = 0;
        while (i < code.size()) {
            const size_t index = routes.size() - 1;
            routes[index].insert(routes[index].end() - 1, problem->getCustomerById(code[i]));
            if (Route::ptr temp_route(new Route(routes[index], problem->getDistanceMatrix(), problem->getTimeMatrix()));
                !constraints(temp_route, problem)) {
                routes[index].erase(routes[index].end() - 2);
                routes.emplace_back(2, problem->getDepot());
                routes.back().insert(routes.back().end() - 1, problem->getCustomerById(code[i]));
            }
            ++i;
        }
        std::vector<Route::ptr> r;
        r.reserve(routes.size());
        for (auto& route : routes) {
            r.push_back(std::make_shared<Route>(route, problem->getDistanceMatrix(), problem->getTimeMatrix()));
        }
        return std::make_shared<Solution>(r);
    }

    void EA::printBest() const {
        printSolution(population[0]);
    }

} // vrptw