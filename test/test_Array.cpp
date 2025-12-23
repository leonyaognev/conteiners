#include <gtest/gtest.h>
#include "array/Array.h"
#include <array>

// -------------------------------------------------------------
// 1. Constructors
// -------------------------------------------------------------

TEST(ArrayTest, DefaultConstructor) {
    Array<int, 5> a{};
    std::array<int, 5> b{};

    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(ArrayTest, InitListConstructor) {
    Array<int, 3> a = {1, 2, 3};
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int, 3> a = {1, 2, 3};
    Array<int, 3> b(a);

    for (int i = 0; i < 3; i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(ArrayTest, CopyAssignment) {
    Array<int, 3> a = {1, 2, 3};
    Array<int, 3> b;

    b = a;

    for (int i = 0; i < 3; i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int, 3> a = {1, 2, 3};
    Array<int, 3> b(std::move(a));

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(ArrayTest, MoveAssignment) {
    Array<int, 3> a = {1, 2, 3};
    Array<int, 3> b;

    b = std::move(a);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

// -------------------------------------------------------------
// 2. Element access
// -------------------------------------------------------------

TEST(ArrayTest, OperatorBrackets) {
    Array<int, 3> a = {10, 20, 30};

    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

TEST(ArrayTest, AtThrowsOutOfRange) {
    Array<int, 3> a = {1, 2, 3};
    EXPECT_NO_THROW(a.at(2));
    EXPECT_THROW(a.at(3), std::out_of_range);
}

TEST(ArrayTest, FrontBack) {
    Array<int, 4> a = {10, 20, 30, 40};

    EXPECT_EQ(a.front(), 10);
    EXPECT_EQ(a.back(), 40);
}

TEST(ArrayTest, DataAccess) {
    Array<int, 3> a = {1, 2, 3};
    auto b = a.data();
	int* ptr = b.current;
    EXPECT_EQ(ptr[0], 1);
    EXPECT_EQ(ptr[1], 2);
    EXPECT_EQ(ptr[2], 3);
}

// -------------------------------------------------------------
// 3. Iterators
// -------------------------------------------------------------

TEST(ArrayTest, IterationRangeFor) {
    Array<int, 3> a = {1, 2, 3};

    int sum = 0;
    for (auto v : a) sum += v;

    EXPECT_EQ(sum, 6);
}

TEST(ArrayTest, BeginEnd) {
    Array<int, 3> a = {1, 2, 3};

    auto it = a.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;

    EXPECT_EQ(it, a.end());
}

TEST(ArrayTest, ConstBeginEnd) {
    const Array<int, 3> a = {1, 2, 3};

    auto it = a.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;

    EXPECT_EQ(it, a.end());
}

// -------------------------------------------------------------
// 4. Capacity
// -------------------------------------------------------------

TEST(ArrayTest, SizeEmptyMaxSize) {
    Array<int, 5> a;
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a.max_size(), 5);
    EXPECT_FALSE(a.empty());

    Array<int, 0> b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.max_size(), 0);
    EXPECT_TRUE(b.empty());
}

// -------------------------------------------------------------
// 5. Modifiers
// -------------------------------------------------------------

TEST(ArrayTest, Fill) {
    Array<int, 5> a;
    a.fill(42);

    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(a[i], 42);
}

TEST(ArrayTest, Swap) {
    Array<int, 3> a = {1, 2, 3};
    Array<int, 3> b = {4, 5, 6};

    a.swap(b);

    EXPECT_EQ(a[0], 4);
    EXPECT_EQ(a[1], 5);
    EXPECT_EQ(a[2], 6);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

// -------------------------------------------------------------
// 6. Comparison with std::array (reference behavior)
// -------------------------------------------------------------

TEST(ArrayTest, CompareWithStdArray) {
    Array<int, 4> my = {10, 20, 30, 40};
    std::array<int, 4> st = {10, 20, 30, 40};

    for (int i = 0; i < 4; i++)
        EXPECT_EQ(my[i], st[i]);

    EXPECT_EQ(my.size(), st.size());
    EXPECT_EQ(my.empty(), st.empty());
    EXPECT_EQ(my.max_size(), st.max_size());
}

