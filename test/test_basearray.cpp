#include <gtest/gtest.h>
#include "../src/include/array/BaseArray.h"

TEST(BaseArrayCreate, Noargs){
	BaseArray<int> a;
	EXPECT_EQ(a.data(), nullptr);
	EXPECT_EQ(a.capacity(), 0);
	EXPECT_EQ(a.size(), 0);
}

TEST(BaseArrayCreate, Arg){
	BaseArray<double> b(5);
	EXPECT_NOT_NE(b.data(), nullptr);
	EXPECT_EQ(b.capacity(), 40);
	EXPECT_EQ(b.size(), 5);
}

TEST(BaseArrayCreate, Args){
	BaseArray<std::string> c(4, "hello");
	EXPECT_NOT_NE(c.data(), nullptr);
	EXPECT_EQ(c.capacity(), 40);
	EXPECT_EQ(c.size(), 5);
}