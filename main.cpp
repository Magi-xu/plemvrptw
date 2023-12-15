#include "src/plemvrptw.h"

using namespace vrptw;

int main() {
    /******************************************************************************************************************/
    /*  参数  */
    constexpr auto data_name = "c101";                  //  测例名
    constexpr double vehicle_speed = 1;                 //  车辆速度
    constexpr double delay_time_allow = 0;              //  最大允许迟到时间
    constexpr size_t population_size = 200;             //  种群大小
    constexpr int iterations = 400;                     //  迭代次数
    const double k = sqrt(3 * population_size);     //  拥挤适应度k值
    /*  参数  */
    /******************************************************************************************************************/
    /*  算法  */
    const auto problem = initProblem(
        data_name,
        vehicle_speed,
        delay_time_allow
        );                          //  初始化问题模型

    problem->calDistanceMatrix();   //  计算距离矩阵
    problem->calTimeMatrix();       //  计算时间矩阵

    const auto ea = initModel(
        problem,
        population_size,
        iterations
        );                          //  初始化算法模型

    ea->populationInitialize();     //  种群初始化
    ea->calStrength();              //  计算强度值
    ea->calR_fitness();             //  计算原始适应度值
    ea->calCrowdingDistance();      //  计算拥挤度距离
    ea->calF_fitness(k);            //  计算拥挤适应度值
    ea->sortPopulation();           //  种群排序
    ea->cullPopulation();           //  淘汰多余个体

    ea->encode();

    ea->printBest();
    printSolution(ea->decode(ea->getCodes()[0]));




    /*  算法  */
    /******************************************************************************************************************/



    // for (const auto& solution : ea->getPopulation())
    //     cout << solution->getFitness()[0] << "   " << solution->getFitness()[1] <<endl;
    //
    // cout << ea->getPopulation().size() << endl;
    // cout << ea->getPopulation()[0]->getVehicleNumber() << "  " << ea->getPopulation()[0]->getTotalDistance() << endl;
    // for (const auto& route : ea->getPopulation()[0]->getRoutes()) {
    //     const auto& customers = route->getCustomers();
    //     for (auto it = customers.begin(); it != customers.end(); ++it) {
    //         cout << (*it)->getId();
    //         if (it + 1 != customers.end()) cout << "-->";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << ea->getPopulation()[100]->getVehicleNumber() << "  " << ea->getPopulation()[100]->getTotalDistance() << endl;
    // for (const auto& route : ea->getPopulation()[100]->getRoutes()) {
    //     const auto& customers = route->getCustomers();
    //     for (auto it = customers.begin(); it != customers.end(); ++it) {
    //         cout << (*it)->getId();
    //         if (it + 1 != customers.end()) cout << "-->";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << ea->getPopulation()[150]->getVehicleNumber() << "  " << ea->getPopulation()[150]->getTotalDistance() << endl;
    // for (const auto& route : ea->getPopulation()[150]->getRoutes()) {
    //     const auto& customers = route->getCustomers();
    //     for (auto it = customers.begin(); it != customers.end(); ++it) {
    //         cout << (*it)->getId();
    //         if (it + 1 != customers.end()) cout << "-->";
    //     }
    //     cout << endl;
    // }

    // int64_t input_size = problem->getCustomerNumber();
    // int64_t hidden_size = 128;
    // int64_t output_size = 2;
    // double learning_rate = 0.001;
    // MLP model(input_size, hidden_size, output_size);
    // torch::nn::MSELoss criterion;
    // torch::optim::Adam optimizer(model.parameters(), torch::optim::AdamOptions(learning_rate));



    return 0;
}
