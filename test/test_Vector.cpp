#include <gtest/gtest.h>
#include "array/Vector.h"
#include <vector>

// --- Constructors ---
TEST(VectorTest, DefaultConstructor) {
    Vector<int> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
    EXPECT_TRUE(a.empty());
}

TEST(VectorTest, ConstructorWithSize) {
    Vector<int> a(5);
    EXPECT_EQ(a.size(), 5);
    EXPECT_GE(a.capacity(), 5);
}

TEST(VectorTest, ConstructorWithSizeAndValue) {
    Vector<int> a(5, 123);
    for (int i = 0; i < 5; i++) EXPECT_EQ(a[i], 123);
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<int> a = {1,2,3,4,5};
    std::vector<int> b = {1,2,3,4,5};
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); i++)
        EXPECT_EQ(a[i], b[i]);
}

// --- Copy / Move ---
TEST(VectorTest, CopyConstructor) {
    Vector<int> a = {1,2,3};
    Vector<int> b = a;
    ASSERT_EQ(a.size(), b.size());
    for (int i = 0; i < 3; i++) EXPECT_EQ(a[i], b[i]);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> a = {1,2,3};
    Vector<int> b = std::move(a);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(VectorTest, CopyAssignment) {
    Vector<int> a = {5,6,7};
    Vector<int> b;
    b = a;
    ASSERT_EQ(a.size(), b.size());
    for (int i = 0; i < 3; i++) EXPECT_EQ(a[i], b[i]);
}

TEST(VectorTest, MoveAssignment) {
    Vector<int> a = {1,2,3};
    Vector<int> b;
    b = std::move(a);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b[2], 3);
}

// --- Element access ---
TEST(VectorTest, AccessOperator) {
    Vector<int> a = {10, 20, 30};
    EXPECT_EQ(a[1], 20);
    a[1] = 25;
    EXPECT_EQ(a[1], 25);
}

// --- Modifiers ---
TEST(VectorTest, PushBackInt) {
    Vector<int> a;
    for (int i = 0; i < 10; i++)
        a.push_back(i);
    EXPECT_EQ(a.size(), 10);
    for (int i = 0; i < 10; i++) EXPECT_EQ(a[i], i);
}

TEST(VectorTest, PopBack) {
    Vector<int> a = {1,2,3};
    a.pop_back();
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[1], 2);
}

TEST(VectorTest, Clear) {
    Vector<int> a(5, 42);
    EXPECT_EQ(a.size(), 5);
    a.clear();
    EXPECT_EQ(a.size(), 0);
    EXPECT_TRUE(a.empty());
}

TEST(VectorTest, EmplaceBackString) {
    Vector<std::string> a;
    a.emplace_back("hello");
    a.emplace_back(5, 'x'); // string(5,'x')
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], "hello");
    EXPECT_EQ(a[1], "xxxxx");
}

struct Obj2Arg {
    std::string a, b;
    Obj2Arg(const std::string& x, const std::string& y) : a(x), b(y) {}
};

TEST(VectorTest, EmplaceBackTwoArgs) {
    Vector<Obj2Arg> v;
    v.emplace_back("one", "two");
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0].a, "one");
    EXPECT_EQ(v[0].b, "two");
}

TEST(VectorTest, InsertSingle) {
    Vector<int> a = {1,2,3};
    a.insert(a.begin() + 1, 99);
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[1], 99);
}

TEST(VectorTest, InsertRange) {
    Vector<int> a = {1, 4};
    Vector<int> b = {12, 13, 14, 15};
    a.insert(a.begin() + 1, b.begin() + 1, b.end() - 2);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[1], 13);
}

TEST(VectorTest, EraseOne) {
    Vector<int> a = {1,2,3};
    a.erase(a.begin() + 1); // remove 2
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[1], 3);
}

TEST(VectorTest, EraseRange) {
    Vector<int> a = {1,2,3,4,5};
    a.erase(a.begin() + 1, a.begin() + 4); // remove [2,3,4]
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 5);
}

TEST(VectorTest, ResizeSmaller) {
    Vector<int> a = {1,2,3,4};
    a.resize(2);
    EXPECT_EQ(a.size(), 2);
}

TEST(VectorTest, ResizeBigger) {
    Vector<int> a = {1,2};
    a.resize(5, 7);
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a[4], 7);
}

TEST(VectorTest, Reserve) {
    Vector<int> a;
    a.reserve(50);
    EXPECT_GE(a.capacity(), 50);
}

TEST(VectorTest, ShrinkToFit) {
    Vector<int> a = {1,2,3,4,5};
    a.reserve(100);
    a.shrink_to_fit();
    EXPECT_EQ(a.capacity(), a.size());
}

TEST(VectorTest, AssignCountValue) {
    Vector<int> a;
    a.assign(4, 7);
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[0], 7);
    EXPECT_EQ(a[1], 7);
}

TEST(VectorTest, AssignIteratorRange) {
    Vector<double> a(3);
    Vector<double> b(7);
    for (std::size_t i = 0; i < b.size(); i++){
        b[i] = 1.5 + i;
    }
    a.assign(b.begin(), b.end());
    EXPECT_EQ(a.size(), 7);
    EXPECT_EQ(a[0], 1.5);
    EXPECT_EQ(a[6], 7.5);
}

TEST(VectorTest, AssignInitializerList) {
    Vector<int> a;
    a.assign({10, 20, 30});
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[1], 20);
}

TEST(VectorTest, Swap) {
    Vector<int> a = {1,2,3};
    Vector<int> b = {9,9};
    a.swap(b);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(a[0], 9);
    EXPECT_EQ(b[2], 3);
}

// --- Iterators ---
TEST(VectorTest, IteratorTraversal) {
    Vector<int> a(5);
    for (auto i = a.begin(); i != a.end(); ++i) {
        *i = 4;
    }
    EXPECT_EQ(a[3], 4);
}

TEST(VectorTest, IteratorArithmetic) {
    Vector<int> a(10);
    for (size_t i = 0; i < a.size(); i++){
        a[i] = static_cast<int>(i);
    }
    auto it = a.begin();
    EXPECT_EQ(*(it + 3), 3);
    EXPECT_EQ(*(a.end() - 2), 8);
}

TEST(VectorTest, IteratorComparison) {
    Vector<int> a = {1,2,3};
    EXPECT_TRUE(a.begin() == a.begin());
    EXPECT_TRUE(a.begin() != a.end());
}

TEST(VectorTest, IteratorMemberAccess) {
    struct Item { int value; };
    Vector<Item> a(3, Item{21});
    auto i = a.begin();
    EXPECT_EQ(i->value, 21);
    EXPECT_EQ((*i).value, i->value);
}

// --- Move-only types ---
struct MoveOnly {
    int x;
    MoveOnly(int v) : x(v) {}
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&& other) { x = other.x; other.x = -1; }
};

TEST(VectorTest, MoveOnlyType) {
    Vector<MoveOnly> v;
    v.emplace_back(10);
    v.emplace_back(20);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0].x, 10);
    EXPECT_EQ(v[1].x, 20);
}

TEST(VectorCustom, InsertManyBack) {
    Vector<std::string> a(5, "hi!");
    a.insert_many_back("hello", "zdarov", "priv");
    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a[5], "hello");
    EXPECT_EQ(a[6], "zdarov");
    EXPECT_EQ(a[7], "priv");
}

TEST(VectorCustom, InsertManyAt) {
    Vector<std::string> a(5, "hi!");
    a.insert_many(a.end() - 3, "hello", "zdarov", "priv");
    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a[2], "hello");
    EXPECT_EQ(a[3], "zdarov");
    EXPECT_EQ(a[4], "priv");
}

TEST(VectorAccess, AtWorks) {
    Vector<int> v{1,2,3,4};
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(3), 4);

    v.at(1) = 10;
    EXPECT_EQ(v.at(1), 10);

    const Vector<int> cv{5,6,7};
    EXPECT_EQ(cv.at(2), 7);
}

TEST(VectorAccess, FrontBack) {
    Vector<int> v{10,20,30};
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);

    v.front() = 100;
    v.back() = 300;

    EXPECT_EQ(v.front(), 100);
    EXPECT_EQ(v.back(), 300);

    const Vector<int> cv{1,2,3};
    EXPECT_EQ(cv.front(), 1);
    EXPECT_EQ(cv.back(), 3);
}

TEST(VectorAccess, DataPointer) {
    Vector<int> v{1,2,3};
    int* ptr = v.data();

    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 1);
    EXPECT_EQ(ptr[1], 2);

    const Vector<int> cv{5,6};
    const int* cptr = cv.data();

    ASSERT_NE(cptr, nullptr);
    EXPECT_EQ(cptr[1], 6);
}

TEST(VectorInsert, InsertSingleMiddle) {
    Vector<int> v{1,2,3,4};
    auto it = v.insert(v.begin() + 2, 99);

    EXPECT_EQ(*it, 99);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 99);
    EXPECT_EQ(v.at(3), 3);
    EXPECT_EQ(v.at(4), 4);
    EXPECT_EQ(v.size(), 5);
}

TEST(VectorInsert, InsertSingleAtBegin) {
    Vector<int> v{2,3};
    auto it = v.insert(v.begin(), 1);

    EXPECT_EQ(*it, 1);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
}

TEST(VectorInsert, InsertSingleAtEnd) {
    Vector<int> v{1,2};
    auto it = v.insert(v.end(), 3);

    EXPECT_EQ(*it, 3);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
}

TEST(VectorInsert, InsertManyMiddle) {
    Vector<double> v{1.2,2.3,7.8,8.9};
    auto it = v.insert(v.begin() + 2, 3, 99.9);

    EXPECT_EQ(*it, 99.9);
    EXPECT_EQ(v.size(), 7);

    EXPECT_EQ(v.at(0), 1.2);
    EXPECT_EQ(v.at(1), 2.3);
    EXPECT_EQ(v.at(2), 99.9);
    EXPECT_EQ(v.at(3), 99.9);
    EXPECT_EQ(v.at(4), 99.9);
    EXPECT_EQ(v.at(5), 7.8);
    EXPECT_EQ(v.at(6), 8.9);
}

TEST(VectorInsert, InsertMiddle) {
    Vector<double> v{1.2,2.3,7.8,8.9};
	const Vector<double> h{1,2,3,4};
    auto it = v.insert(v.begin() + 2, h[2]);

    EXPECT_EQ(*it, 3.0);
    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v.at(0), 1.2);
    EXPECT_EQ(v.at(1), 2.3);
    EXPECT_EQ(v.at(2), 3.0);
    EXPECT_EQ(v.at(3), 7.8);
    EXPECT_EQ(v.at(4), 8.9);
}