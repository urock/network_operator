#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

#include<boost/property_tree/xml_parser.hpp>
#include<boost/foreach.hpp>


int main()
{

ptree pt;
read_xml("24_NOP_461", pt);

std::vector<int> Psi_1d;
std::vector<std::vector<int>> Psi_2d(24, std::vector<int> (24, 0)); 

std::string column;
std::string row;

auto test = pt.get_child("CONFIG.grid.content").front();
std::cout<<test.first<<std::endl;
std::cout<<test.second.get("<xmlattr>.cellcount", "")<<std::endl;

BOOST_FOREACH(ptree::value_type & child, pt.get_child("CONFIG.grid.content.cells"))
{
	column = child.second.get("<xmlattr>.column", "");
	row = child.second.get("<xmlattr>.row", "");
	std::string value = child.second.get("<xmlattr>.text", "");
	
	// skip first column 
	if(column != "0" && row != "0" && column != "" && row != "")
	{
		int val = std::stoi(value);
		int m = std::stoi(column) - 1;
		int n = std::stoi(row) - 1;
		// std::cout<<"val "<<val<<" m "<<m<<" n "<<n<<std::endl;
		Psi_2d[n][m] = val;
	}
}

for(auto n : Psi_2d)
{
	for(auto m : n)
	{
		std::cout<<" "<<m<<" ";
	}
	std::cout<<std::endl;
}

}