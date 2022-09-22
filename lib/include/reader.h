#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

#include<boost/property_tree/xml_parser.hpp>
#include<boost/foreach.hpp>


class NOPMatrixReader
{
public:

	NOPMatrixReader() = default;

	NOPMatrixReader(std::string filePath);

	const std::vector<std::vector<int>>& getMatrix();

	int getMatrixSize();

	void resizeMatrix(int newSize);

	void clearMatrix();

	void print();

private:
	void read(std::string filePath);

private:
	int m_size = 0;
	std::vector<std::vector<int>>  m_matrix;
};