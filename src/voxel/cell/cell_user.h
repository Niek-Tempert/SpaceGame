#pragma once

class ICell;

struct CellUser {
	ICell *type;
	void *data;
};
