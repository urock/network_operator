#include "reader.h"
#include <iostream>
#include <string> 
#include <gtest/gtest.h>

#include <limits.h>
#include <unistd.h>

namespace
{

std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

} // namespace

TEST(Reader, ConstructorTests)
{
    std::string cwd = getexepath();
    cwd = std::string(cwd.begin(), cwd.end()-9);
    std::string matrixPath = cwd + "/test_data/24_NOP_461";
    std::string paramsPath = cwd + "/test_data/q_461.txt";
    NOPMatrixReader reader = NOPMatrixReader(matrixPath, paramsPath);
    reader.print();
}

