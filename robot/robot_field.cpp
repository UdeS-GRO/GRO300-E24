#include "robot_field.hpp"
#include <cmath>
#include <random>
#include <algorithm>

#include <iostream>

RobotField::RobotField(RobotState* robots_ptr, size_t robot_count):
    robots_(robots_ptr, robot_count)
{
}

void RobotField::initRandom()
{
    int c = 0;
    for (auto& robot: robots_)
    {
        robot.x = 0.01+static_cast<double>(rand()) / RAND_MAX;
        robot.y = 0.01+static_cast<double>(rand()) / RAND_MAX;
        robot.t = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI - M_PI;
        
        robot.dx = 0;
        robot.dt = 0;
        robot.ux = 0;
        robot.ut = 0;

        c++;
        
        // Pour déboguage:
        // std::cerr << "RS: Robot " << c << " initialisé à ("
        //           << robot.x << ", " << robot.y << ", " << robot.t << ")" << std::endl;
    }
}

void RobotField::runCycle()
{
    constexpr double time_step = 0.01; // 10 ms

    for (auto& robot: robots_)
    {
        // Appliquer le contrôle et mettre à jour l'état
        robot.applyControl(time_step);

        // S'assurer que le robot reste dans le champ (supposé 1x1)
        robot.x = std::clamp(robot.x, 0.0, 1.0);
        robot.y = std::clamp(robot.y, 0.0, 1.0);

        // Limiter l'angle à [-π, π]
        robot.t = std::atan2(std::sin(robot.t), std::cos(robot.t));

        // Commandes initiales aléatoires.
        robot.ux += static_cast<double>(rand()) / RAND_MAX * 0.01; // Valeur aléatoire entre 0 et 0.01
        robot.ut += static_cast<double>(rand()) / RAND_MAX * 1.00 - 0.50; // Valeur aléatoire entre -0.5 et 0.5

    }
}