#pragma once

class ICell;

struct cell_user {
	ICell *type;
	void *data;
};
