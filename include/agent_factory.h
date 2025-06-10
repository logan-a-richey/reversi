// agent_factory.h

#pragma once
#include <memory>
#include "agent_interface.h"

std::unique_ptr<AgentInterface> create_agent(int agent_type);


