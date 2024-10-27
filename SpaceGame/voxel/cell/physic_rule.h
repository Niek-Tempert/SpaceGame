#pragma once

struct user;

class IPhysicRule {
public:
	virtual ~IPhysicRule() = default;

	virtual void update(user &user) = 0;
};
