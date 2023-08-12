/*
Простейшие логические
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);

Сравнение
EXPECT_EQ(expected, actual); — =
EXPECT_NE(val1, val2); — !=
EXPECT_LT(val1, val2); — <
EXPECT_LE(val1, val2); — <=
EXPECT_GT(val1, val2); — >
EXPECT_GE(val1, val2); — >=

Сравнение строк
EXPECT_STREQ(expected_str, actual_str);
EXPECT_STRNE(str1, str2);
EXPECT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
EXPECT_STRCASENE(str1, str2); — регистронезависимо

Проверка на исключения
EXPECT_THROW(statement, exception_type);
EXPECT_ANY_THROW(statement);
EXPECT_NO_THROW(statement);

Сравнение чисел с плавающей точкой
EXPECT_FLOAT_EQ(expected, actual); — неточное сравнение float
EXPECT_DOUBLE_EQ(expected, actual); — неточное сравнение double
EXPECT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает
погрешность abs_error Вызов отказа или успеха SUCCEED(); FAIL(); ADD_FAILURE();
ADD_FAILURE_AT(«file_path», line_number);
*/

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <set>

#include "s21_containers.h"

using std::cout;
using std::endl;
using std::string;

TEST(RBTree, basic) {
  s21::RBTree<string> beta;
  beta.insert("one");
  beta.insert("two");
  beta.insert("three");
  beta.insert("four");
  EXPECT_EQ(beta.GetValue("one"), "one");
  EXPECT_EQ(beta.GetValue("two"), "two");
  EXPECT_EQ(beta.GetValue("three"), "three");
  EXPECT_EQ(beta.GetValue("four"), "four");
}

TEST(RBTree, max_min) {
  s21::RBTree<int> one;
  for (int i = -20; i <= 20; ++i) one.insert(i * 2);
  EXPECT_EQ(one.MaxKey(), 40);
  EXPECT_EQ(one.MinKey(), -40);
  one.insert(-100);
  one.insert(100);
  EXPECT_EQ(one.MaxKey(), 100);
  EXPECT_EQ(one.MinKey(), -100);

  s21::RBTree<string> two;
  two.insert("apple");
  two.insert("bee");
  two.insert("cat");
  two.insert("dog");
  two.insert("egg");
  two.insert("fish");
  two.insert("grapes");
  two.insert("hat");
  two.insert("igloo");
  two.insert("jug");
  two.insert("kite");
  two.insert("lemon");
  EXPECT_EQ(two.MinKey(), "apple");
  EXPECT_EQ(two.MaxKey(), "lemon");
  two.Delete("apple");
  EXPECT_EQ(two.MinKey(), "bee");
  EXPECT_EQ(two.MaxKey(), "lemon");
  two.Delete("lemon");
  EXPECT_EQ(two.MinKey(), "bee");
  EXPECT_EQ(two.MaxKey(), "kite");
  two.Delete("bee");
  two.Delete("egg");
  two.Delete("fish");
  two.Delete("grapes");
  two.Delete("hat");
  two.Delete("igloo");
  two.Delete("jug");
  two.Delete("kite");
  EXPECT_EQ(two.MinKey(), "cat");
  EXPECT_EQ(two.MaxKey(), "dog");
  two.Delete("dog");
  EXPECT_EQ(two.MinKey(), "cat");
  EXPECT_EQ(two.MaxKey(), "cat");
}

TEST(RBTree, print) {
  s21::RBTree<int> one;
  for (int i = 0; i < 10; ++i) one.insert(i);
  testing::internal::CaptureStdout();
  one.Print();
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_string(R"([ 3 ](-)
   └————— [ 5 ](-)
   │         └————— [ 7 ](+)
   │         │         └————— [ 8 ](-)
   │         │         │         └————— [ 9 ](+)
   │         │         └————— [ 6 ](-)
   │         └————— [ 4 ](-)
   └————— [ 1 ](-)
             └————— [ 2 ](-)
             └————— [ 0 ](-)
)");
  EXPECT_EQ(expected_string, output);
}

TEST(RBTree, iterator) {
  s21::RBTree<int> one;
  int count = 0;
  for (; count < 20; ++count) one.insert(count);
  count = 0;
  for (auto iter = one.begin(); iter != one.end(); ++iter) {
    EXPECT_EQ(count, *iter);
    ++count;
  }
  count = 19;
  for (auto iter = --(one.end()); iter != one.end(); --iter) {
    EXPECT_EQ(count, *iter);
    --count;
  }
}

TEST(RBTree, const_iterator) {
  s21::RBTree<int> const one{1, 2, 3, 4, 5, 6, 7, 8, 9};
  int count = 1;
  for (auto iter = one.begin(); iter != one.end(); ++iter) {
    EXPECT_EQ(count, *iter);
    ++count;
  }
  count = 9;
  for (auto iter = --(one.end()); iter != one.end(); --iter) {
    EXPECT_EQ(count, *iter);
    --count;
  }
}

TEST(RBTree, delete_node) {
  s21::RBTree<string> one;
  one.insert("apple");
  one.Delete("apple");
  one.insert("apple");
  one.insert("bee");
  one.insert("cat");
  one.insert("dog");
  one.insert("egg");
  one.insert("fish");
  one.insert("grapes");
  one.insert("hat");
  one.insert("igloo");
  one.insert("jug");
  one.insert("kite");
  one.insert("lemon");
  auto iter = one.begin();
  EXPECT_EQ("apple", *iter++);
  EXPECT_EQ("bee", *iter++);
  EXPECT_EQ("cat", *iter++);
  one.Delete("bee");
  EXPECT_EQ("dog", *iter--);
  EXPECT_EQ("cat", *iter--);
  EXPECT_EQ("apple", *iter--);
  iter--;
  EXPECT_EQ("lemon", *iter);
}

TEST(RBTree, big_tree) {
  s21::RBTree<int> one;
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 60000; ++i) one.Delete(rand() % 20000);
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 20000; ++i) one.Delete(rand() % 20000);
}

TEST(RBTree, copy_constructor) {
  s21::RBTree<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::RBTree<int> two(one);
  auto iter_one = one.begin();
  auto iter_two = two.begin();
  for (; iter_one != one.end(); ++iter_one, ++iter_two) {
    EXPECT_EQ(*iter_one, *iter_two);
    EXPECT_NE(iter_one, iter_two);
  }
}

TEST(RBTree, copy_operator) {
  s21::RBTree<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::RBTree<int> two{5, 2, 3, 5, 6};
  two = one;
  auto iter_one = one.begin();
  auto iter_two = two.begin();
  for (; iter_one != one.end(); ++iter_one, ++iter_two) {
    EXPECT_EQ(*iter_one, *iter_two);
    EXPECT_NE(iter_one, iter_two);
  }
}

TEST(RBTree, size_empty) {
  s21::RBTree<int> one;
  EXPECT_EQ(true, one.empty());
  EXPECT_EQ(0, one.size());
  for (int i = 0; i < 8; ++i) one.insert(i);
  EXPECT_EQ(false, one.empty());
  EXPECT_EQ(8, one.size());
  one.clear();
  EXPECT_EQ(true, one.empty());
}

TEST(RBTree, swap) {
  s21::RBTree<int> one;
  s21::RBTree<int> two;
  for (int i = 0; i < 8; ++i) one.insert(i);
  EXPECT_EQ(false, one.empty());
  EXPECT_EQ(8, one.size());
  EXPECT_EQ(true, two.empty());
  EXPECT_EQ(0, two.size());
  one.swap(two);
  EXPECT_EQ(false, two.empty());
  EXPECT_EQ(8, two.size());
  EXPECT_EQ(true, one.empty());
  EXPECT_EQ(0, one.size());
}

TEST(RBTree, copy_and_move_constructors) {
  s21::RBTree<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::RBTree<int> two(one);
  auto iter = two.begin();
  for (auto const &elem : one) {
    EXPECT_EQ(elem, *iter);
    iter++;
  }
  EXPECT_EQ(two.size(), one.size());
  iter = two.begin();
  s21::RBTree<int> three(std::move(one));
  for (auto const &elem : three) {
    EXPECT_EQ(elem, *iter);
    iter++;
  }
  EXPECT_EQ(two.size(), three.size());
  EXPECT_EQ(0, one.size());
}

TEST(RBTree, max_size) {
  s21::RBTree<int> one;
  std::set<int> two;
  EXPECT_EQ(one.max_size(), two.max_size());


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
