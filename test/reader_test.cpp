#include "reader.h"

#include <gtest/gtest.h>



TEST(Reader, ConstructorTests)
{
    NOPMatrixReader reader = NOPMatrixReader("test_data/24_NOP_461");
    reader.print();
}

