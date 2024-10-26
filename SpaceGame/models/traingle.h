#pragma once

#include "vertex.h"

#define VERT_COUNT 3

static constexpr vertex vertices[VERT_COUNT] = {
	{ { -0.6f, -0.4f, -1.f }, { 1.f, 0.f, 0.f } },
	{ { 0.6f, -0.4f, -1.f }, { 0.f, 1.f, 0.f } },
	{ { 0.f, 0.6f, -1.f }, { 0.f, 0.f, 1.f } }
};
