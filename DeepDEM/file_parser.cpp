#include "stdafx.h"
#include <fstream>
#include <algorithm>

#include "file_parser.h"

// Return the complete path to a specified file as a string.
std::string ParseFile::filePath(const std::string &file_name, const std::string &file_directory) const {
	if (file_directory.empty()) {
		return file_name;
	}
	else {
		return file_directory + "\\" + file_name;
	}
}


// Function for determining whether a CSV line is a comment line or not.
bool ParseCSV::isComment(const std::string line) {
	// Empty line.
	if (line.length() <= 0) {
		return false;
	}
	// First character is 'comment character'.
	if (line[0] == '#') {
		return true;
	} else {
		return false;
	}
}


ParseFile::ParseFile(const std::string &file_name, const std::string &file_directory) : m_file_name(file_name), m_file_directory(file_directory) {

	// Open file.
	std::ifstream file = openFile(file_name, file_directory);
	
	// Read file into vector array and record row count.
	std::string line;
	while (std::getline(file, line)) {
		m_text.push_back(line);
	}
	std::cout << "Read " << m_text.size() << " rows of text" << std::endl;


};





void ParseFile::printFile() const {

	for (std::vector<std::string>::const_iterator it = m_text.begin(); it != m_text.end(); ++it) {
		std::cout << *it << std::endl;
	}

}


int ParseFile::getRowCount() const {
	return m_text.size();
}


std::string ParseFile::getFileName() const {
	return m_file_name;
}


std::string ParseFile::getFileDirectory() const {
	return m_file_directory;
}


std::ifstream ParseFile::openFile(const std::string &file_name, const std::string &file_directory) {

	std::string file_path = filePath(m_file_name, m_file_directory);
	std::cout << "Opening file : '" << file_path << "'" << std::endl;
	std::ifstream file(file_path);
	// Request a new file path if the file could not be opened.
	if (!file) {
		std::cerr << "  Error : Could not read file!" << std::endl;
		bool read_file = false;
		while (!read_file) {
			std::string new_file_path;
			std::cout << "  Enter valid file path : ";
			std::cin >> new_file_path;
			file.open(new_file_path);
			if (file) {
				read_file = true;
			}
		}
	}

	return file;

}


// Overload the [] operator to return the text line indicated by 'row'.
std::string& ParseFile::operator[](const int row) {
	// Ensure given row is valid.
	if (row >= 0 && row < getRowCount()) {
		return m_text[row];
	}
	else {
		std::string empty_string("");
		return empty_string;
	}
}

ParseCSV::ParseCSV(const std::string &file_name, const std::string &file_path) : ParseFile(file_name, file_path) {

	// Parse number of CSV columns.
	for (std::vector<std::string>::const_iterator it = m_text.begin(); it != m_text.end(); ++it) {
		// Skip comment lines.
		if (isComment(*it)) {
			continue;
		}
		int cols = std::count((*it).begin(), (*it).end(), ',') + 1;
		std::cout << cols << std::endl;
		m_cols = cols;
		break;
	}

	// Parse the stored text as CSV entries line-by-line.
	for (std::vector<std::string>::const_iterator it = m_text.begin(); it != m_text.end(); ++it) {
		// Skip comment lines.
		if (isComment(*it)) {
			continue;
		}
		// Read text line as a string stream.
		std::stringstream ss(*it);
		std::string entry;
		// New string vector corresponsing to a CSV row.
		std::vector<std::string> csv_row;
		while (std::getline(ss, entry, ',')) {
			csv_row.push_back(entry);
		}
		// Add parsed CSV row to array.
		m_array.push_back(csv_row);
	}

}


void ParseCSV::printFile() {

	for (int row = 0; row < getRowCount(); ++row) {
		for (int col = 0; col < getColumnCount(); ++col) {
			std::cout << m_array[row][col] << " ";
		}
		std::cout << std::endl;
	}

}


// Return the CSV row count (excluding comments).
int ParseCSV::getRowCount() const {
	return m_array.size();
}


// Return the CSV column count.
int ParseCSV::getColumnCount() const {
	return m_cols;
}

// Return a CSV element as a double type.
double ParseCSV::elemToDouble(const int row, const int col) const {
	return std::stod(m_array[row][col]);
}

// Return a CSV element as a float type.
float ParseCSV::elemToFloat(const int row, const int col) const {
	return std::stof(m_array[row][col]);
}

// Return a CSV element as an int type.
int ParseCSV::elemToInt(const int row, const int col) const {
	return std::stoi(m_array[row][col]);
}