#pragma once

#include <format>
#include <fstream>
#include <sstream>

inline std::string load_text(std::string path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + path);
	}
    
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}