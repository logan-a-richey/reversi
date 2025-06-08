// AgentFactory.h

#pragma once

#include <memory>

#include "agents/IAgent.h"

std::unique_ptr<IAgent> create_agent(int type);
