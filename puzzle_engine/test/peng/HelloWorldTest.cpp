#include "peng/HelloWorld.h"
#include "gtest/gtest.h"

// simplemath.h

#include <cmath>

double cubic(double d)
{
    return pow(d, 3);
}

TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, cubic(10));
}
