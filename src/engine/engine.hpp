#pragma once

#include "glwindow.hpp"
#include "scene.hpp"

class Engine {
public:
	Engine();
	~Engine();

	void exec();

private:
	GLWindow m_window;
	Scene m_scene;
};
