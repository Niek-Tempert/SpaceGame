#pragma once

#include "renderable.h"

class MLineRenderable : public MRenderable {
protected:
	void _render() const override;
};