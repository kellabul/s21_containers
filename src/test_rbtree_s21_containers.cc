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
}

TEST(RBTree, delete_node) {
  s21::RBTree<int> one;
  one.Insert(11);
  one.Insert(2);
  one.Insert(14);
  one.Insert(1);
  one.Insert(7);
  one.Insert(15);
  one.Insert(5);
  one.Insert(8);
  one.Insert(4);
  // one.Insert(0, 1111);
  // one.Delete(10);
  // one.Print();
}

TEST(RBTree, print) {
  s21::RBTree<int> one;
  for (int i = 0; i <= 10; ++i) one.Insert(i);
  testing::internal::CaptureStdout();
  one.Print();
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_string(R"([3](-)
 L_____ [1](-)
         L_____ [0](-)
         L_____ [2](-)
 L_____ [5](-)
         L_____ [4](-)
         L_____ [7](+)
                 L_____ [6](-)
                 L_____ [9](-)
                         L_____ [8](+)
                         L_____ [10](+)
)");
  EXPECT_EQ(expected_string, output);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
