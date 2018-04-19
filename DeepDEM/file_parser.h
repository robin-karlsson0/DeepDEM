#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Class for parsing an storing a text file's content as 'text lines'.
//
// Read a file specified by a 'file name' and 'directory path', and store its
// contents in a string vector 'm_text', where each element correspond to a text line.
//
// Data members:
//   (private)   m_file_name      : Name of the file.
//   (private)   m_file_directory : Directory path of the file.
//   (protected) m_text           : Vector of text rows.
// Member functions:
//   void printFile()               : Print the stored content.
//   std::string getFileName()      : Returns the file name.
//   std::string getFileDirectory() : Return the directory path of the file.
//   int getRowCount()              : Return the number of rows.  
class ParseFile
{
private:
	std::string m_file_name;
	std::string m_file_directory;
	// Open a file and return it as an 'ifstream' object.
	// If the file cannot be opened, a new manually inputted file path is required.
	std::ifstream openFile(const std::string &file_name, const std::string &file_directory);
	// Return the full file path as a 'string' object.
	std::string filePath(const std::string &file_name, const std::string &file_directory) const;
public:
	// CONSTRUCTOR : Read the file and parse it as lines of text.
	ParseFile(const std::string &file_name, const std::string &file_directory = std::string(""));
	// Print the contents of the file.
	virtual void printFile() const;
	// Return the 'file name' of the file.
	std::string getFileName() const;
	// Return the 'directory path' of the file.
	std::string getFileDirectory() const;
	// Return the number of rows in the file.
	virtual int getRowCount() const;

	virtual std::string& operator[](const int row);

protected:
	std::vector<std::string> m_text;
};

// Class for parsing an storing a CSV file as a 2D data array.
//
// A file is first read as a text file, which then is parsed as a CSV file. All
// CSV elements are stored as string objects in a 2D string vector. The first
// vector contains data row, where each row contains the column elements.
//
// Member data:
//   (private) m_cols  : Number of columns of the CSV file.
//   (private) m_array : Vector of 'string vectors', each representing one
//                       CSV row.
// Member functions:
//   void printFile()     :
//   int getRowCount()    :
//   int getColumnCount() :
//
//   double elemToDouble() :
//   float elemToFloat()   :
//   float elemToInt()     :
class ParseCSV : public ParseFile
{
private:
	// Number of columns in the CSV file.
	int m_cols;
	// 2D row-column string vector array containing all elements as a string object.
	std::vector<std::vector<std::string>> m_array;
	// Return true if a string line is a comment.
	static bool isComment(const std::string line);
public:
	// CONSTRUCTOR : First read the file as a text file, and then parse it as a CSV file.
	ParseCSV(const std::string &file_name, const std::string &file_path);
	// Print the contents of the CSV file.
	virtual void printFile();
	// Return the CSV row count.
	virtual int getRowCount() const;
	// Return the number of CSV data columns.
	int getColumnCount() const;
	// Functions for returning a CSV data element as different data types.
	double elemToDouble(const int row, const int col) const;
	float elemToFloat(const int row, const int col) const;
	int elemToInt(const int row, const int col) const;
};

#endif