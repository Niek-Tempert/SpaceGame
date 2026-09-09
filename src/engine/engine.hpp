#pragma once

#include <providers/input_provider.hpp>
#include <providers/canvas_provider.hpp>
#include <providers/time_provider.hpp>

#include "glwindow.hpp"
#include "scene.hpp"

class Engine 
	: public InputProvider
	, public CanvasProvider
	, public TimeProvider {
public:
	Engine();
	~Engine();

	void exec();

private:
	GLWindow m_window;
	Scene m_scene;
	f32 m_time, m_deltaTime;
};
