#include "reader.h"



NOPMatrixReader::NOPMatrixReader(std::string filePath)
{

	read(filePath);

}

void NOPMatrixReader::read(std::string filePath)
{

	ptree pt;
	read_xml(filePath, pt);

	auto contentData = pt.get_child("CONFIG.grid.content").front();
	int sizeSquared = std::stoi(contentData.second.get("<xmlattr>.cellcount", ""));
	int size = sqrt(sizeSquared);
	
	resizeMatrix(size);	

	BOOST_FOREACH(ptree::value_type & child, pt.get_child("CONFIG.grid.content.cells"))
	{
		std::string column = child.second.get("<xmlattr>.column", "");
		std::string row = child.second.get("<xmlattr>.row", "");
		std::string value = child.second.get("<xmlattr>.text", "");
		
		// skip first column 
		if(column != "0" && row != "0" && column != "" && row != "")
		{
			int val = std::stoi(value);
			int m = std::stoi(column) - 1;
			int n = std::stoi(row) - 1;
			m_matrix[n][m] = val;
		}
	}
}

void NOPMatrixReader::resizeMatrix(int newSize)
{
	m_size = newSize;

	m_matrix.resize(m_size);
	for(auto& row : m_matrix)
	{
		row.resize(m_size);
	}
}

void NOPMatrixReader::print()
{
	for(auto n : m_matrix)
	{
		for(auto m : n)
		{
			std::cout<<" "<<m<<" ";
		}
		std::cout<<std::endl;
	}
}

void NOPMatrixReader::clearMatrix()
{
	for(auto& row : m_matrix)
	{
		row.clear();
	}
}

const std::vector<std::vector<int>>& NOPMatrixReader::getMatrix()
{
	return m_matrix;
}

int NOPMatrixReader::getMatrixSize()
{
	return m_size;
}