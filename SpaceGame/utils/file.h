#pragma once

#include <format>
#include <fstream>
#include <sstream>

inline std::string load_text(std::string path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		fprintf(stderr, "Could not open file: %s\n", path.c_str());
	}
    
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}