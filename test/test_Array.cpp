#include <gtest/gtest.h>
#include "array/Array.h"

// ----------------------------------------------------------
// Size / Capacity
// ----------------------------------------------------------

TEST(ArrayTest, SizeAndEmpty) {
    Array<int, 5> arr;
    EXPECT_EQ(arr.size(), std::size_t(5));
    EXPECT_FALSE(arr.empty());

    Array<int, 0> arr0;
    EXPECT_EQ(arr0.size(), 0);
    EXPECT_TRUE(arr0.empty());
}

// ----------------------------------------------------------
// Element Access
// ----------------------------------------------------------

TEST(ArrayTest, OperatorIndex) {
    Array<int, 3> arr;
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, AtFunctionWorks) {
    Array<int, 3> arr;
    arr[0] = 7;
    arr[1] = 8;
    arr[2] = 9;

    EXPECT_EQ(arr.at(0), 7);
    EXPECT_EQ(arr.at(1), 8);
    EXPECT_EQ(arr.at(2), 9);
}

TEST(ArrayTest, AtThrowsOutOfRange) {
    Array<int, 3> arr;
    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(99), std::out_of_range);
}

TEST(ArrayTest, FrontBack) {
    Array<int, 3> arr;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    EXPECT_EQ(arr.front(), 1);
    EXPECT_EQ(arr.back(),  3);
}

TEST(ArrayTest, DataPointer) {
    Array<int, 3> arr;
    arr[0] = 4;
    arr[1] = 5;
    arr[2] = 6;

    auto ptr = arr.data();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*(ptr.current), 4);
    EXPECT_EQ(*(ptr.current + 1), 5);
    EXPECT_EQ(*(ptr.current + 2), 6);
}

// ----------------------------------------------------------
// Iterators
// ----------------------------------------------------------

TEST(ArrayTest, BeginEndIteration) {
    Array<int, 4> arr;
    arr[0] = 11;
    arr[1] = 22;
    arr[2] = 33;
    arr[3] = 44;

    int sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 11 + 22 + 33 + 44);
}

TEST(ArrayTest, ConstBeginEndIteration) {
    Array<int, 3> arr;
    arr[0] = 3;
    arr[1] = 6;
    arr[2] = 9;

    const Array<int, 3>& c = arr;

    int sum = 0;
    for (auto it = c.begin(); it != c.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 18);
}

TEST(ArrayTest, IteratorIncrementDecrement) {
    Array<int, 3> arr;
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    auto it = arr.begin();
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);

    it++;
    EXPECT_EQ(*it, 30);

    --it;
    EXPECT_EQ(*it, 20);

    it--;
    EXPECT_EQ(*it, 10);
}

TEST(ArrayTest, IteratorComparison) {
    Array<int, 2> arr;
    arr[0] = 1;
    arr[1] = 2;

    auto it1 = arr.begin();
    auto it2 = arr.begin();
    auto itEnd = arr.end();

    EXPECT_TRUE(it1 == it2);
    EXPECT_TRUE(it1 != itEnd);
}

// ----------------------------------------------------------
// Modifiers
// ----------------------------------------------------------

TEST(ArrayTest, FillWorks) {
    Array<int, 4> arr;
    arr.fill(99);

    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 99);
    EXPECT_EQ(arr[3], 99);
}

TEST(ArrayTest, SwapWorks) {
    Array<int, 3> a;
    Array<int, 3> b;

    a[0] = 1;  a[1] = 2;  a[2] = 3;
    b[0] = 4;  b[1] = 5;  b[2] = 6;

    a.swap(b);

    EXPECT_EQ(a[0], 4);
    EXPECT_EQ(a[1], 5);
    EXPECT_EQ(a[2], 6);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

// ----------------------------------------------------------
// Assignment
// ----------------------------------------------------------

TEST(ArrayTest, AssignmentOperator) {
    Array<int, 3> a;
    Array<int, 3> b;

    a[0] = 100;
    a[1] = 200;
    a[2] = 300;

    b = a;

    EXPECT_EQ(b[0], 100);
    EXPECT_EQ(b[1], 200);
    EXPECT_EQ(b[2], 300);
}

