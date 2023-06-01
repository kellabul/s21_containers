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

#include "s21_containers.h"

using std::cout;
using std::endl;
using std::string;

TEST(RBTree, basic) {
  s21::RBTree<string> beta;
  beta.Insert("one");
  beta.Insert("two");
  beta.Insert("three");
  beta.Insert("four");
  EXPECT_EQ(beta.GetValue("one"), "one");
  EXPECT_EQ(beta.GetValue("two"), "two");
  EXPECT_EQ(beta.GetValue("three"), "three");
  EXPECT_EQ(beta.GetValue("four"), "four");
}

TEST(RBTree, max_min) {
  s21::RBTree<int> one;
  for (int i = -20; i <= 20; ++i) one.Insert(i * 2);
  EXPECT_EQ(one.MaxKey(), 40);
  EXPECT_EQ(one.MinKey(), -40);
  one.Insert(-100);
  one.Insert(100);
  EXPECT_EQ(one.MaxKey(), 100);
  EXPECT_EQ(one.MinKey(), -100);

  s21::RBTree<string> two;
  two.Insert("apple");
  two.Insert("bee");
  two.Insert("cat");
  two.Insert("dog");
  two.Insert("egg");
  two.Insert("fish");
  two.Insert("grapes");
  two.Insert("hat");
  two.Insert("igloo");
  two.Insert("jug");
  two.Insert("kite");
  two.Insert("lemon");
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
  for (int i = 0; i < 10; ++i) one.Insert(i);
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
  for (; count < 20; ++count) one.Insert(count);
  count = 0;
  for (auto iter = one.Begin(); iter != one.End(); ++iter) {
    EXPECT_EQ(count, *iter);
    ++count;
  }
}

TEST(RBTree, delete_node) {
  s21::RBTree<string> beta;
  beta.Insert("apple");
  beta.Insert("bee");
  beta.Insert("cat");
  beta.Insert("dog");
  beta.Insert("egg");
  beta.Insert("fish");
  beta.Insert("grapes");
  beta.Insert("hat");
  beta.Insert("igloo");
  beta.Insert("jug");
  beta.Insert("kite");
  beta.Insert("lemon");
  auto iter = beta.Begin();
  EXPECT_EQ("apple", *iter++);
  EXPECT_EQ("bee", *iter++);
  EXPECT_EQ("cat", *iter++);
  beta.Delete("bee");
  EXPECT_EQ("dog", *iter--);
  EXPECT_EQ("cat", *iter--);
  EXPECT_EQ("apple", *iter);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
