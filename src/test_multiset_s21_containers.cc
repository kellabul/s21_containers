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
// #include <set>
#include <string>

#include "s21_containers.h"

using std::cout;
using std::endl;
using std::string;

TEST(multiset, initialization) {
  s21::multiset<int> one{3, 3, 3, 3, 3};
  EXPECT_EQ(one.size(), 5);
  for (auto &i : one) {
    EXPECT_EQ(i, 3);
  }
}

TEST(multiset, lower_bound) {
  s21::multiset<int> one{1, 2, 3, 3, 4, 5};
  auto iter = one.lower_bound(3);
  EXPECT_NE(iter, one.end());
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
}

TEST(multiset, upper_bound) {
  s21::multiset<int> one{1, 2, 3, 3, 4, 5};
  auto iter = one.upper_bound(3);
  EXPECT_NE(iter, one.end());
  EXPECT_EQ(*iter, 4);
  --iter;
  EXPECT_EQ(*iter, 3);
  --iter;
  EXPECT_EQ(*iter, 3);
}

TEST(multiset, equal_range) {
  s21::multiset<int> one{1, 2, 3, 3, 4, 5};
  auto iter = one.equal_range(3);

  EXPECT_EQ(*iter.first, 3);
  ++iter.first;
  EXPECT_EQ(*iter.first, 3);
  ++iter.first;
  EXPECT_EQ(*iter.first, 4);

  EXPECT_EQ(*iter.second, 4);
  --iter.second;
  EXPECT_EQ(*iter.second, 3);
  --iter.second;
  EXPECT_EQ(*iter.second, 3);
}

TEST(multiset, count) {
  s21::multiset<int> one{1, 2, 4, 4, 4, 5};
  EXPECT_EQ(one.count(3), 0);
  EXPECT_EQ(one.count(4), 3);
}