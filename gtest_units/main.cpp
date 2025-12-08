/**
 * @file main.cpp
 */

#include <gtest/gtest.h>

// include test headers

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    // register testsuit
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    return RUN_ALL_TESTS();
}
