//
// Created by Magi Xu on 2023/12/7.
//

#include "Problem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

namespace vrptw {
    Problem::Problem(const std::string& filename) {
        // 读txt文件
        std::ifstream file(filename);
        std::string line;
        int lineNumber = 0;
        if (file.is_open()) {
            while (getline(file, line)) {
                ++lineNumber;
                if (lineNumber == 1) name = line.substr(0, line.length() - 1);
                else if (lineNumber == 5) std::istringstream (line) >> vehicleNumber >> capacity;
                else if (lineNumber > 9) {
                    int id;
                    int x;
                    int y;
                    int demand;
                    int readyTime;
                    int dueTime;
                    int serviceTime;
                    std::istringstream (line) >> id >> x >> y >> demand >> readyTime >> dueTime >> serviceTime;
                    customers.push_back(Customer::ptr(new Customer(id, x, y, demand, readyTime, dueTime, serviceTime)));
                } else continue;
            }
            file.close();
        } else {
            std::cerr << "无法打开文件" << std::endl;
        }
        distanceMatrix = std::vector<std::vector<float>> (customers.size(), std::vector<float> (customers.size()));
        timeMatrix = std::vector<std::vector<float>> (customers.size(), std::vector<float> (customers.size()));
    }

    void Problem::setDistanceMatrix() {
        if (customers.size() == 0) return;
        for (int i = 0; i < customers.size(); ++i) {
            for (int j = 0; j < customers.size(); ++j) {
                distanceMatrix[i][j] = std::sqrt(std::pow(customers[i]->getX() - customers[j]->getX(), 2)
                        + std::pow(customers[i]->getY() - customers[j]->getY(), 2));
            }
        }

    }

    void Problem::setTimeMatrix() {
        if (vehicleSpeed == 0) return;
        for (int i = 0; i < customers.size(); ++i) {
            for (int j = 0; j < customers.size(); ++j) {
                timeMatrix[i][j] = distanceMatrix[i][j] / vehicleSpeed;
            }
        }
    }
} // vrptw