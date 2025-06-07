// AgentFactory.h

#pragma once

#include "IAgent.h"
#include "AgentHumanTerminal.h"
#include "AgentRandomBot.h"

#include <memory>
#include <iostream>

std::unique_ptr<IAgent> create_agent(int type)
{
    switch(type)
    {
        case 0: 
            return std::make_unique<AgentHumanTerminal>();
        case 1: 
            return std::make_unique<AgentRandomBot>();
        default:
            std::cerr << "[E] Unknown agent type " << type << std::endl;
            exit(1);
    }
}

