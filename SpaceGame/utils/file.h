#pragma once

#include <format>
#include <fstream>
#include <sstream>

inline std::string load_text(const char* path) {
	std::string text;
	std::ifstream file;
	file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		text = stream.str();
	}
	catch(std::ifstream::failure e)
	{
		fprintf(stderr, "Could not read file: %s\n", path);
	}
	return text;
}
