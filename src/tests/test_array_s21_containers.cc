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

#include <iostream>
#include <list>
#include <string>
#include <initializer_list>

#include "s21_containers.h"

using std::cout;
using std::endl;

TEST(array, init_list) {
  s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
}

TEST(array, copy_const) {
  s21::array<int, 6> zero{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> one(zero);
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
}

TEST(array, copy_operator) {
  s21::array<int, 6> zero{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> one;
  one = zero;
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
}

TEST(array, move_const) {
  s21::array<int, 6> zero{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> one(std::move(zero));
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
}

TEST(array, move_operator) {
  s21::array<int, 6> zero{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> one;
  one = std::move(zero);
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
}






TEST(array, at_and_brackets) {
  s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(one.at(3), 4);
  EXPECT_ANY_THROW(one.at(6));
  EXPECT_EQ(one[3], 4);
}

TEST(array, swap) {
  s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> two{7, 8, 9, 10, 11, 12};
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(two.front(), 7);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(two.back(), 12);
  one.swap(two);
  EXPECT_EQ(one.front(), 7);
  EXPECT_EQ(two.front(), 1);
  EXPECT_EQ(one.back(), 12);
  EXPECT_EQ(two.back(), 6);
}

TEST(array, data_empty_size_max_size) {
  s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(one.size(), 6);
  EXPECT_EQ(one.max_size(), 6);
  EXPECT_EQ(one.empty(), false);

  s21::array<int, 0> two;
  EXPECT_EQ(two.empty(), true);
  EXPECT_EQ(two.size(), 0);

  auto pointer = one.data();
  EXPECT_EQ(pointer[5], 6);
}

TEST(array, fill) {
  s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  one.fill(99);
  auto iter = one.begin();
  for (size_t i = 0; i < one.size(); ++i) {
    EXPECT_EQ(*iter, 99);
    ++iter;
  }
  EXPECT_EQ(iter, one.end());
}


TEST(array, const) {
  const s21::array<int, 6> one{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one.front(), 1);
  EXPECT_EQ(one.back(), 6);
  EXPECT_EQ(*one.begin(), 1);
  EXPECT_EQ(*(one.end() - 1), 6);
  EXPECT_EQ(one.size(), 6);
  EXPECT_EQ(one.size(), 6);
  EXPECT_EQ(one.max_size(), 6);
}