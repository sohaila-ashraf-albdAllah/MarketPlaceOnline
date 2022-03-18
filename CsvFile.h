#pragma once

#include <vector>
#include <string>

namespace CsvFile {
	std::vector<std::vector<std::string>> readData(const std::string& fileName);
	void writeData(const std::string& fileName, const std::vector<std::vector<std::string>> &data);
}
