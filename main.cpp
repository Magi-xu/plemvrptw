#include "src/plemvrptw.h"

using namespace vrptw;

/**********************************************************************************************************************/
/*  参数  */
constexpr auto data_name = "c101";                  //  测例名
constexpr double vehicle_speed = 1;                 //  车辆速度
constexpr double delay_time_allow = 0;              //  最大允许迟到时间
constexpr size_t population_size = 200;             //  种群大小
constexpr int iterations = 400;                     //  迭代次数
const double k = sqrt(3 * population_size);	    //  拥挤适应度k值

extern int64_t input_size;                          //  输入维度
constexpr int64_t hidden_size = 128;                //  隐藏层维度
constexpr int64_t output_size = 2;                  //  输出维度
constexpr double learning_rate = 0.001;             //  学习率
constexpr int epochs = 100;                         //  epochs
constexpr double p = 0.7;                           //  p
/*  参数  */
/**********************************************************************************************************************/
/*  算法  */
void run() {
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

    const auto input_size = static_cast<int64_t>(problem->getCustomerNumber());
    const auto mlp = initMLP(
        input_size,
        hidden_size,
        output_size
        );                          //  初始化MLP模型，重定义输入维度

    mlp->defOptimizer(learning_rate);       //  优化器
    mlp->defCriterion();                    //  损失函数

    ea->populationInitialize();     //  种群初始化

    for (int i = 0; i < iterations; ++i) {
        ea->calStrength();                          //  计算强度值
        ea->calR_fitness();                         //  计算原始适应度值
        ea->calCrowdingDistance();                  //  计算拥挤度距离
        ea->calF_fitness(k);                        //  计算拥挤适应度值
        ea->sortPopulation();                       //  种群排序
        // ea->printBest(false);           	        //  打印最优解
        // writeToFile(ea->getPopulation()[0], data_name);
        ea->cullPopulation();                       //  淘汰多余个体
        ea->encode();                               //  编码
        ea->calFeature();                           //  计算特征

        auto [ts_population_codes, ts_population_features] = mlp->toTensor(ea->getCodes(), ea->getFeatures());      //  预处理
        auto loss = mlp->trainModel(ts_population_codes, ts_population_features, epochs);                           //  训练
        auto ts_predicted_outputs = mlp->predict(ts_population_codes);                                              //  预测
        auto [select_index1, select_index2] = mlp->toVector(ts_population_codes, p);                                //  选择
        
        auto [r1, r2] = ea->generate(select_index1, select_index2);

        std::ostringstream output;
        std::ostringstream select_info;
        std::ostringstream generate_info;
        select_info << "{pick: (" << select_index1.size() << "," << select_index2.size() << ")";
        generate_info << "generate: (" << r1 << "," << r2 << ")} \t" ;
        output << "[" << i+1 << "] \t"
               << std::setw(16) << std::left << select_info.str()
               << "|" 
               << std::setw(22) << std::right << generate_info.str();
        std::cout << output.str();
        ea->printBest(false);
    }
}
/**********************************************************************************************************************/

int main() {

    run();

    return 0;
}
