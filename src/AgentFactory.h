// AgentFactory.h

#pragma once
#include <memory>
#include "IAgent.h"

std::unique_ptr<IAgent> create_agent(int type);

