// AgentFactory.h

#pragma once
#include "IAgent.h"
#include <memory>

std::unique_ptr<IAgent> create_agent(int type);
