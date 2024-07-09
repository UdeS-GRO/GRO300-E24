#ifndef ROBOT_FIELD_HPP
#define ROBOT_FIELD_HPP

#include "robot.hpp"
#include "span.hpp" // span-lite pour compilateurs pré C++20 complet.

class RobotField
{
private:
    nonstd::span<RobotState> robots_; // Vue sur les robots dans la mémoire partagée

public:
    /// @brief Constructeur
    ///
    /// Récupère l'ensemble de robots donné en paramètre.
    ///
    /// @param robots_ptr Pointeur vers un premier élément RobotState dans la mémoire partagée
    /// @param robot_count Nombre de robots
    RobotField(RobotState* robots_ptr, size_t robot_count);

    /// @brief Initialise les robots à des états aléatoires
    /// 
    /// Positions (X,Y) entre 0 et 1, theta entre -pi et pi, vitesses et contrôles à zéro.
    void initRandom();

    /// @brief Exécute un cycle de simulation.
    void runCycle();
};

#endif