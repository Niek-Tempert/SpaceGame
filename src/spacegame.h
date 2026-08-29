#pragma once

#include <vector>

class BlockCursor;
class IRenderable;
struct GLFWwindow;
class Input;
class Voxel;
class Player;

struct Engine {
	GLFWwindow *window;
	Player *player;
	Input *input;

	bool fullscreen;
	bool focussed;

	double time;
	double delta_time;
	float time_speed;

	Voxel *moon;
	std::vector<Voxel *> voxels;

	BlockCursor *block_cursor;
	std::vector<IRenderable *> render_queue;
};

void start(Engine* engine);
void update(Engine* engine);
void cleanup(Engine* engine);
