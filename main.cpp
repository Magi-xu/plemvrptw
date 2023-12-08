#include <iostream>
#include "src/plemvrptw.h"

using namespace std;
using namespace vrptw;

Problem::ptr initProblem(const string& dataname) {
    Problem::ptr problem = Problem::ptr(new Problem("../data/solomon_100/" + dataname + ".txt"));
    problem->setVehicleSpeed(1);
    problem->setMaxDelayTime(0);
    problem->setMaxReturnTime(problem->getCustomers()[0]->getDueTime());
    problem->setDistanceMatrix();
    problem->setTimeMatrix();
    return problem;
}

int main() {
    Problem::ptr problem = initProblem("c101");
    cout << problem->getName() << problem->getVehicleNumber() << problem->getCapacity() << endl;
    vector<Customer::ptr> customers = problem->getCustomers();
    cout << customers[1]->getServiceTime() << endl;
    int64_t input_size = problem->getCustomerNumber();

//    int64_t hidden_size = 128;
//    int64_t output_size = 2;
//    double learning_rate = 0.001;
//    MLP model(input_size, hidden_size, output_size);
//    torch::nn::MSELoss criterion;
//    torch::optim::Adam optimizer(model.parameters(), torch::optim::AdamOptions(learning_rate));



    return 0;
}
