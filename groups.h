#ifndef GROUPS_H
#define GROUPS_H

#include <iostream>
#include <string>

#include "G0_G1_database.h"
#include "G1_G2_database.h"
#include "G2_G3_database.h"
#include "G3_G4_database.h"

#include "G0_G1_goal.h"
#include "G1_G2_goal.h"
#include "G2_G3_goal.h"
#include "G3_G4_goal.h"

#include "databasegenerator.h"

// base class for the 4 groups in Thistlethwaite's algorithm
struct Group
{
    // loads the database or generates it if a file is not provided
    void loadDatabase()
    {
        std::cout << "Loading database for " << name << "..." << std::endl;
        if (database->load())
        {
            std::cout << "Loaded database for " << name << " successfully." << std::endl;
        }
        else
        {
            std::cout << "Failed to load database for " << name << ". generating:" << std::endl;
            databaseGen.generate(*goal, *database);
        }
    }

    bool        useDatabase = false;
    Database*   database    = nullptr;
    Goal*       goal        = nullptr;
    std::string name;

protected:
    DatabaseGenerator databaseGen;
};

template<typename DatabaseType, typename GoalType>
struct TypedGroup : public Group
{
    TypedGroup()
    {
        database = &m_database;
        goal	 = &m_goal;
    }

private:
    DatabaseType m_database;
    GoalType m_goal;
};

#endif // GROUPS_H
