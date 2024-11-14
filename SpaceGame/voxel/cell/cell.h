#pragma once

#include "cell_shape.h"

class IPhysicRule;
class ICellMesher;

class ICell {
public:
	virtual ~ICell() = default;
	
	virtual IPhysicRule *get_physic_rule() const = 0;
	virtual ICellMesher *get_mesher() const = 0;
	virtual CellShape get_shape() const = 0; 
};
