#include "project_version.h"
#include <gtest/gtest.h>

TEST(version, check_version){
    ASSERT_TRUE(version() > 0);
}
