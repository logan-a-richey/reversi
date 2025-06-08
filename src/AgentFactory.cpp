// AgentFactory.cpp

#include <iostream>
#include <memory>

#include "AgentFactory.h"
#include "IAgent.h"
#include "AgentHumanTerminal.h"
#include "AgentRandomBot.h"
#include "AgentMinimax.h"

std::unique_ptr<IAgent> create_agent(int type)
{
    switch(type)
    {
        case 0: 
            return std::make_unique<AgentHumanTerminal>();
        case 1: 
            return std::make_unique<AgentRandomBot>();
        case 2:
            return std::make_unique<AgentMinimax>();
        default:
            std::cerr << "[E] Unknown agent type " << type << std::endl;
            exit(1);
    }
}

