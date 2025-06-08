// AgentFactory.cpp

#include <iostream>
#include <memory>

#include "agents/AgentFactory.h"
#include "agents/AgentHumanTerminal.h"
#include "agents/AgentMinimax.h"
#include "agents/AgentRandomBot.h"
#include "agents/IAgent.h"

std::unique_ptr<IAgent> create_agent(int type)
{
    switch (type)
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
