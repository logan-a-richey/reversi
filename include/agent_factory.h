// agent_factory.h

#pragma once
#include "agent_interface.h"
#include <memory>

std::unique_ptr<AgentInterface> create_agent(int agent_type);
