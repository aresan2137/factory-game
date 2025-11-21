#pragma once

#include "../../define.h"

namespace BinaryManager {
	void LoadFileAsItemsBin(std::vector<uint>& stacks, std::vector<const char*>& names, std::vector<const char*>& descriptions, const char* name);

	std::vector<byte> LoadFileToVector(const std::string& path);

};

