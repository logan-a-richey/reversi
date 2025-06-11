// agent_factory.cpp

#include <iostream>
#include <memory>

#include "agent_factory.h"
#include "agent_human_terminal.h"
#include "agent_interface.h"
#include "agent_bot_random.h"
#include "agent_bot_minimax.h"
// #include "agent_human_gui.h"

std::unique_ptr<AgentInterface> create_agent(int agent_type) {
    switch (agent_type) {
        case 0:
            return std::make_unique<AgentHumanTerminal>();
        case 1:
            return std::make_unique<AgentBotRandom>();
        case 2:
            return std::make_unique<AgentBotMinimax>();
        /* TODO
        case 3:
            return std::make_unique<AgentHumanGUI>();
        */
        default:
            std::cerr << "Unknown agent type: " << agent_type << std::endl;
            std::cerr << "Using <AgentHumanTerminal> as default" << std::endl;
            return std::make_unique<AgentHumanTerminal>();
    }
}
