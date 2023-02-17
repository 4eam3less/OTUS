#include "../ip-convert.hpp"
#include <gtest/gtest.h>

TEST(ip, literal_ip){

    EXPECT_ANY_THROW(convert_ip_to_vector("i.am.not.ip"));
    EXPECT_ANY_THROW(convert_ip_to_vector("19b.3qw.d.33"));
}

TEST(ip, incorrect_range){

    EXPECT_ANY_THROW(convert_ip_to_vector("555.23.15.3"));
    EXPECT_ANY_THROW(convert_ip_to_vector("8888.888.8888.88"));
}

TEST(ip, incorrect_structure){

    EXPECT_ANY_THROW(convert_ip_to_vector("1.1.1.1.1.1"));
    EXPECT_ANY_THROW(convert_ip_to_vector("123.123.1"));
}

TEST(ip, correct_ip){

   std::vector<std::string> ip_pool = {"1.1.1.1", "192.168.1.1", "178.239.223.132"};
   std::vector<std::vector<uint8_t>> sample = {{1,1,1,1}, {192,168,1,1}, {178,239,223,132}};

   auto it_sample = sample.cbegin();
   for(const auto& it: ip_pool){
       ASSERT_TRUE(convert_ip_to_vector(it) == *it_sample);
       ++it_sample;
   }
}

