#pragma once

#include "glwindow.hpp"
#include "scene.hpp"
#include <providers/canvas_provider.hpp>

class Engine 
	: public InputProvider
	, public CanvasProvider
	, public TimeProvider {
public:
	Engine();

	void exec();

private:
	GLWindow m_window;
	Scene m_scene;
	f32 m_time, m_deltaTime;
};
