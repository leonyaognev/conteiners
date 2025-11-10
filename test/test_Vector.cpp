#include <gtest/gtest.h>

#include "array/Vector.h"

TEST(VectorCreate, Noargs) {
  Vector<int> a;
  EXPECT_EQ(a.data(), nullptr);
  EXPECT_EQ(a.capacity(), 0);
  EXPECT_EQ(a.size(), 0);
}

TEST(VectorCreate, Arg) {
  Vector<double> b(5);
  EXPECT_NE(b.data(), nullptr);
  EXPECT_EQ(b.capacity(), 40);
  EXPECT_EQ(b.size(), 5);
}

TEST(VectorCreate, Args) {
  Vector<std::string> c(4, "hello");
  EXPECT_NE(c.data(), nullptr);
  // local buffer on 15 elements
  EXPECT_EQ(c.capacity(), 128);
  EXPECT_EQ(c.size(), 4);
  //c.Print();
}

TEST(VectorCopy, Args) {
  Vector<int> a(5);
  Vector<int> b(a);
  EXPECT_NE(b.data(), a.data());
  EXPECT_EQ(b.capacity(), 20);
  EXPECT_EQ(b.size(), 5);
  //a.Print();
  //b.Print();
}

TEST(VectorIter, BeginEnd) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, postfixPlus) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); i++) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, prefixPlus) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, postfixMinus) {
  Vector<int> a(5);
  for (auto i = a.end(); i != a.begin(); i--) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, prefixMinus) {
  Vector<int> a(5);
  for (auto i = a.end(); i != a.begin(); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, EqualOperator) {
  Vector<int> a(5);
  for (auto i = a.end(); !(i == a.begin()); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, MemberAccessOperator) {
  struct Item {
    int value;
  };

  Vector<Item> a(3, Item{21});
  auto i = a.begin();
  EXPECT_EQ(i->value, 21);
  EXPECT_EQ((*i).value, i->value);
}

TEST(VectorIter, IncreaseIter){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  //a.Print();
  auto b = a.begin();
  EXPECT_EQ(*b, 0);
  //b = b + 3;
  EXPECT_EQ(*b, 3);
}

TEST(VectorIter, DecreaseIter){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  //a.Print();
  auto b = a.end() - 2;
  EXPECT_EQ(*b, 7);
}

TEST(VectorEdit, EraseOneArg){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  //a.Print();
  a.erase(a.begin() + 5);
  //a.Print();
}

TEST(VectorEdit, EraseTwoArgs){
  Vector<int> a(4);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 2;
  }
  //a.Print();
  a.erase((a.begin() + 1), (a.begin() + 3));
  //a.Print();
}

TEST(VectorEdit, ExtendNoArgs){
	Vector<int> a(4);
	for (size_t i = 0; i < a.size(); i++){
		a[i] = i;
	}
	//a.Print();
	a.extend();
	//a.Print();
	EXPECT_EQ(a.capacity(), 8);
}

TEST(VectorEdit, PushBackNoExtend){
	Vector<int> a(5);
	for (size_t i = 0; i < a.size(); i++){
		a[i] = i;
	}
	a.extend();
	EXPECT_EQ(a.capacity(), 10);
	EXPECT_EQ(a.size(), 5);
	//a.Print();
	a.push_back(10);
	EXPECT_EQ(a.capacity(), 10);
	EXPECT_EQ(a.size(), 6);
	//a.Print();
}

TEST(VectorEdit, PushBackWithExtend){
	Vector<int> a(5);
	for (size_t i = 0; i < a.size(); i++){
		a[i] = i + 5;
	}
	EXPECT_EQ(a.capacity(), 5);
	EXPECT_EQ(a.size(), 5);
	//a.Print();
	a.push_back(10);
	EXPECT_EQ(a.capacity(), 10);
	EXPECT_EQ(a.size(), 6);
	//a.Print();
}

TEST(VectorEdit, ShrinkToFit){
	Vector<int> a(5);
	EXPECT_EQ(a.capacity(), 5);
	a.extend(20);
	EXPECT_EQ(a.capacity(), 20);
	a.push_back(1);
	a.push_back(10);
	a.shrink_to_fit();
	EXPECT_EQ(a.capacity(), 7);
}

TEST(VectorEdit, ResizeTwoArgs){
	Vector<int> a(6);
	for (size_t i = 0; i < a.size(); i++){
		a[i] = i;
	}
//	a.Print();
	a.resize(9);
//	a.Print();
	EXPECT_EQ(a.capacity(), 9);
}

TEST(VectorEdit, ResizeNULL){
  Vector<double> a(5,1.23);
  //a.Print();
  a.resize(9);
  //a.Print();
}

TEST(VectorCopy, SwapOne){
  Vector<int> a(5,1);
  Vector<int> b(10);
  for(std::size_t i = 0; i < b.size(); i++){
    b[i] = i;
  }
  a.swap(b);
  //a.Print();
  //b.Print();
}

TEST(VectorEdit, InsertOne){
  Vector<int> a(3);
  for(std::size_t i = 0; i < a.size(); i++){
    a[i] = i;
  }
 // a.Print();
  a.insert(a.begin()+1, 5);
 // a.Print();
}

TEST(VectorEdit, InsertMany){
  Vector<double> a(4);
  for(std::size_t i = 0; i < a.size(); i++){
    a[i] = i + 1;
  }
  //a.Print();
  a.insert(a.begin()+2, 3, 5.5);
  //a.Print();
}

TEST(VectorEdit, ClearInt){
  Vector<int> a(5);
 // a.Print();
  a.clear();
 // a.Print();
}

TEST(VectorEdit, EmplaceBackString){
  Vector<std::string> a(5, "hello");
  a.Print();
  a.emplace_back("hi!", "hi:(");
  a.Print();
}

TEST(VectorEdit, EmplaceString){
  Vector<std::string> a(3, "cool!");
  a.Print();
  a.emplace(a.begin() + 1, "privet");
  a.Print();
}

TEST(VectorCopy, AssignValue){
  Vector<int> a(5);
  for (std::size_t i = 0; i < a.size(); i++){
    a[i] = 1 + i;
  }
  a.Print();
  a.assign(7,5);
  a.Print();
}

TEST(VectorEdit, AssignIter){
  Vector<double> a(3);
  Vector<double> b(7);
  for (std::size_t i = 0; i < b.size(); i++){
    b[i] = 1.5 + i;
  }
  a.assign(b.begin(), b.end());
  a.Print();
}

TEST(VectorEdit, InsertOnIterators){
	Vector<double> a(4);
  	int b[5];
	for (int i = 0; i < 5; i++){
		b[i] = i + 1;
	}
	for(std::size_t i = 0; i < a.size(); i++){
    	a[i] = i + 1.5;
  	}
	a.Print();
	a.insert((a.begin() + 2), b + 1, b + 3);
	a.Print();
}

TEST(VectorEdit, InsertManyBackStrings){
	Vector<std::string> a(5, "hi!");
	a.Print();
	a.insert_many_back("hello", "zdarov", "priv");
	a.Print();
}

TEST(VectorEdit, InsertManyStringsIterati){
	Vector<std::string> a(5, "hi!");
	a.Print();
	a.insert_many(a.end() - 3, "hello", "zdarov", "priv");
	a.Print();
}