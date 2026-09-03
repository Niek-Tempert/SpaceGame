#pragma once

#include <common/types.h>

enum class BlockTypes {
	Air = 0,
	Wool = 1
};

struct Block {
	u32 type;
	void* user;
};
