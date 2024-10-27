#pragma once

#include "shape.h"

class IPhysicRule;
class ICellMesher;

class ICell {
public:
	virtual ~ICell() = default;
	
	virtual IPhysicRule *get_physic_rule() = 0;
	virtual ICellMesher *get_mesher() = 0;
	virtual cell_shape get_shape() = 0; 
};
