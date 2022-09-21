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

std::cout<<"OPEN FILE"<<std::endl;

// std::string text = pt.get<std::string>("CONFIG.grid.content.cells.cell1.text");

// std::cout<<text<<std::endl;

BOOST_FOREACH(ptree::value_type & child, pt.get_child("CONFIG.grid.content.cells"))
{
	// std::cout<<"NODE NAME: "<<child.first << std::endl;
	//if (child.first == "cell126")
	//{
		auto column = child.second.get("<xmlattr>.column", "test");
		auto row = child.second.get("<xmlattr>.row", "test");
		auto value = child.second.get("<xmlattr>.row", "test");
		std::cout<< "column " << column << " row " << row << " value " << value <<std::endl;
	//}  
	// std::cout<<"test: "<<child.second.data() << std::endl;
	// std::cout<<"TEST: "<<child.second.get<int>("<xmlattr>.column") << std::endl;
}

}