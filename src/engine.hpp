#pragma once

#include "utils/input.hpp"
#include "scene.hpp"

class Engine {
public:
	Engine();
	~Engine();

	void exec();

private:
	GLFWwindow* m_window{};
	bool m_fullscreen{};
	bool m_focussed{};
	Input m_input{};

	Scene m_scene{};
};
