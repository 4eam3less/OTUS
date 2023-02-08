#include "../project-version.hpp"
#include <gtest/gtest.h>

TEST(version, check_version){
    ASSERT_TRUE(version() > 0);
}
