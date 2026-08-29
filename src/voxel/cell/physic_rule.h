#pragma once

#include "cell_user.h"

class IPhysicRule {
public:
	virtual ~IPhysicRule() = default;

	virtual void update(CellUser &user) = 0;
};
