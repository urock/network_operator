#include "reader.h"



NOPMatrixReader::NOPMatrixReader(const std::string& matrixPath, const std::string& paramsPath)
{

	readMatrix(matrixPath);
	readParams(paramsPath);
}

void NOPMatrixReader::readMatrix(const std::string& matrixPath)
{

	ptree pt;
	read_xml(matrixPath, pt);

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

void NOPMatrixReader::readParams(const std::string& paramsPath)
{
	ptree pt;
	read_xml(paramsPath, pt);
	
	auto contentData = pt.get_child("CONFIG.grid.content").front();
	int size = std::stoi(contentData.second.get("<xmlattr>.cellcount", "")) / 2;
	m_params.resize(size);


	BOOST_FOREACH(ptree::value_type & child, pt.get_child("CONFIG.grid.content.cells"))
	{
		std::string column = child.second.get("<xmlattr>.column", "");
		std::string row = child.second.get("<xmlattr>.row", "");
		std::string value = child.second.get("<xmlattr>.text", "");
		
		if(column != "0" && column != "" && row != "")
		{
			float val = std::stof(value);
			int n = std::stoi(row);
			m_params[n] = val;
		}
	}

}


void NOPMatrixReader::resizeMatrix(int newSize)
{
	clearMatrix();
	m_size = newSize;

	m_matrix.resize(m_size);
	for(auto& row : m_matrix)
	{
		row.resize(m_size);
	}
}

void NOPMatrixReader::print()
{
	std::cout<<"NOP Matrix: \n";
	for(auto n : m_matrix)
	{
		for(int m : n)
		{
			std::cout<<" "<<m<<" ";
		}
		std::cout<<"\n";
	}

	std::cout<<"NOP params: \n";
	for(float i : m_params)
	{
		std::cout<<i<<" ";
	}
	std::cout<<"\n";
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

const std::vector<float>& NOPMatrixReader::getParams()
{
	return m_params;
}


int NOPMatrixReader::getMatrixSize()
{
	return m_size;
}