#pragma once

class Voxel;
class Player;

struct Program {
	GLFWwindow *window;
	Player *player;
	Input *input;

	bool fullscreen;
	bool focussed;

	double time;
	double delta_time;

	Voxel *moon;
	std::vector<Voxel *> voxels;

	BlockCursor *block_cursor;
	std::vector<IRenderable *> render_queue;
};
