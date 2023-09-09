// /*
// Простейшие логические
// EXPECT_TRUE(condition);
// EXPECT_FALSE(condition);

// Сравнение
// EXPECT_EQ(expected, actual); — =
// EXPECT_NE(val1, val2); — !=
// EXPECT_LT(val1, val2); — <
// EXPECT_LE(val1, val2); — <=
// EXPECT_GT(val1, val2); — >
// EXPECT_GE(val1, val2); — >=

// Сравнение строк
// EXPECT_STREQ(expected_str, actual_str);
// EXPECT_STRNE(str1, str2);
// EXPECT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
// EXPECT_STRCASENE(str1, str2); — регистронезависимо

// Проверка на исключения
// EXPECT_THROW(statement, exception_type);
// EXPECT_ANY_THROW(statement);
// EXPECT_NO_THROW(statement);

// Сравнение чисел с плавающей точкой
// EXPECT_FLOAT_EQ(expected, actual); — неточное сравнение float
// EXPECT_DOUBLE_EQ(expected, actual); — неточное сравнение double
// EXPECT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает
// погрешность abs_error Вызов отказа или успеха SUCCEED(); FAIL();
// ADD_FAILURE(); ADD_FAILURE_AT(«file_path», line_number);
// */

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <list>
// #include <set>
#include <string>

#include "s21_containers.h"

using std::cout;
using std::endl;
using std::string;

TEST(map, brakets) {
  s21::map<int, std::string> one{
      {1, "one"}, {3, "three"}, {5, "five"}, {1, "one-one"}};
  EXPECT_EQ(one[1], "one");
  EXPECT_EQ(one[4], "");
  one[55] = "fifty five";
  EXPECT_EQ(one[55], "fifty five");
}

TEST(map, insert) {
  s21::map<int, std::string> one{
      {1, "one"}, {3, "three"}, {5, "five"}, {1, "one-one"}};
  EXPECT_EQ(one.size(), 3);
  one.insert(4, "four");
  one.insert(4, "four-no.2");
  EXPECT_EQ(one.size(), 4);
  EXPECT_EQ(one[1], "one");
  EXPECT_EQ(one[4], "four");
  one[55] = "fifty five";
  EXPECT_EQ(one[55], "fifty five");
}

TEST(map, pair) {
  std::pair<int, int> a{1, 2};
  s21::pair<int, int> b(a);
  std::pair<int, int> a_2(b);
  EXPECT_EQ(b.first, 1);
  EXPECT_EQ(b.second, 2);
  EXPECT_EQ(a_2.first, 1);
  EXPECT_EQ(a_2.second, 2);
  s21::pair<int, int> b_2 = a;
  EXPECT_EQ(b_2.first, 1);
  EXPECT_EQ(b_2.second, 2);
  b_2 = std::make_pair(55, 66);
  a = b_2;
  EXPECT_EQ(a.first, 55);
  EXPECT_EQ(a.second, 66);
}

TEST(map, merge) {
  s21::map<int, int> one{{1,2}, {3,4}, {5,6}};
  s21::map<int, int> two{{1,5}, {4,4}, {5,8}};
  one.merge(two);
  EXPECT_EQ(one.size(), 4);
  EXPECT_EQ(two.size(), 2);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 4);
  EXPECT_EQ(one[5], 6);
  EXPECT_EQ(two[1], 5);
  EXPECT_EQ(two[5], 8);
}
