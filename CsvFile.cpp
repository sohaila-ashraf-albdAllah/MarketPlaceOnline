#include "CsvFile.h"

#include <sstream>
#include <fstream>
#include <cassert>
#include <iostream>

std::vector<std::vector<std::string>> CsvFile::readData(const std::string& fileName) {
	std::vector<std::vector<std::string>> data;
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cerr << "File `" << fileName << "` cannot be opened.\n";
		assert(false);
	}
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::vector<std::string> entry;
		std::string cell;
		while (std::getline(ss, cell, ',')) {
			entry.emplace_back(cell);
		}
		data.emplace_back(std::move(entry));
	}
	file.close();
	return data;
}

void CsvFile::writeData(const std::string& fileName, const std::vector<std::vector<std::string>>& data)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cerr << "File `" << fileName << "` cannot be opened.\n";
		assert(false);
	}
	
	for(const auto& entry:data){
		for (int i = 0; i < entry.size(); ++i) {
			file << entry[i];
			if (i < entry.size() - 1) {
				file << ",";
			}
			
		}
		file << "\n";
	
	}
	file.close();
}
