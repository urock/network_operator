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

	NOPMatrixReader(const std::string& matrixPath, const std::string& paramsPath);

	const std::vector<std::vector<int>>& getMatrix();

	const std::vector<float>& getParams();

	int getMatrixSize();

	void resizeMatrix(int newSize);

	void clearMatrix();

	void print();

	void readMatrix(const std::string& matrixPath);
	
	void readParams(const std::string& paramsPath);


private:
	int m_size = 0;
	std::vector<float> m_params;
	std::vector<std::vector<int>>  m_matrix;
};