#include <iostream>
#include <memory>
#include "src/plemvrptw.h"

using namespace std;
using namespace vrptw;

Problem::ptr initProblem(const string& data_name, const double& vehicle_speed, const double& delay_time_allow) {
    const auto problem = std::make_shared<Problem>("../data/solomon_100/" + data_name + ".txt");
    problem->setVehicleSpeed(vehicle_speed);
    problem->setMaxDelayTime(delay_time_allow);
    problem->setMaxReturnTime(problem->getCustomers()[0]->getDueTime());
    problem->setDistanceMatrix();
    problem->setTimeMatrix();
    return problem;
}

EA::ptr initModel(const Problem::ptr& problem, const size_t& population_size, const int& iterations) {
    const auto ea = make_shared<EA>(problem);
    ea->setPopulation_size(population_size);
    ea->setIterations(iterations);
    ea->populationInitialize();
    return ea;
}

int main() {
    constexpr  auto data_name = "c101";
    constexpr  double vehicle_speed = 1;
    constexpr  double delay_time_allow = 0;
    constexpr  size_t population_size = 200;
    constexpr  int iterations = 400;
    constexpr double k = sqrt(3 * population_size);

    const auto problem = initProblem(data_name, vehicle_speed, delay_time_allow);
    const auto ea = initModel(problem, population_size, iterations);
    ea->calStrength();
    ea->calR_fitness();
    ea->calCrowdingDistance();
    ea->calF_fitness(k);
    ea->sortPopulation();
    ea->cullPopulation();





    for (const auto& solution : ea->getPopulation())
        cout << solution->getFitness()[0] << "   " << solution->getFitness()[1] <<endl;

    cout << ea->getPopulation().size() << endl;
    cout << ea->getPopulation()[0]->getVehicleNumber() << "  " << ea->getPopulation()[0]->getTotalDistance() << endl;
    for (const auto& route : ea->getPopulation()[0]->getRoutes()) {
        const auto& customers = route->getCustomers();
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            cout << (*it)->getId();
            if (it + 1 != customers.end()) cout << "-->";
        }
        cout << endl;
    }
    cout << endl;
    cout << ea->getPopulation()[100]->getVehicleNumber() << "  " << ea->getPopulation()[100]->getTotalDistance() << endl;
    for (const auto& route : ea->getPopulation()[100]->getRoutes()) {
        const auto& customers = route->getCustomers();
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            cout << (*it)->getId();
            if (it + 1 != customers.end()) cout << "-->";
        }
        cout << endl;
    }
    cout << endl;
    cout << ea->getPopulation()[150]->getVehicleNumber() << "  " << ea->getPopulation()[150]->getTotalDistance() << endl;
    for (const auto& route : ea->getPopulation()[150]->getRoutes()) {
        const auto& customers = route->getCustomers();
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            cout << (*it)->getId();
            if (it + 1 != customers.end()) cout << "-->";
        }
        cout << endl;
    }

    // int64_t input_size = problem->getCustomerNumber();
    // int64_t hidden_size = 128;
    // int64_t output_size = 2;
    // double learning_rate = 0.001;
    // MLP model(input_size, hidden_size, output_size);
    // torch::nn::MSELoss criterion;
    // torch::optim::Adam optimizer(model.parameters(), torch::optim::AdamOptions(learning_rate));



    return 0;
}
