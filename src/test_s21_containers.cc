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
EXPECT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает погрешность abs_error
Вызов отказа или успеха
SUCCEED();
FAIL();
ADD_FAILURE();
ADD_FAILURE_AT(«file_path», line_number);
*/

#include <gtest/gtest.h>
#include "s21_containers.h"

#include <iostream>
#include <list>
#include <string>

using std::cout;
using std::endl;

TEST(list, push_back_and_iterator) {
  s21::list<int> one;
  one.push_back(111);
  one.push_back(222);
  one.push_back(444);
  auto iter = one.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
}


TEST(list, initializer_list) {
  s21::list<int> one{111, 222, 444};
  auto iter = one.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
}

TEST(list, erase) {
  s21::list<std::string> alpha{"one", "two", "three"};
  alpha.erase(alpha.begin());
  EXPECT_EQ("two", *alpha.begin());

  s21::list<std::string> beta{"one", "oneone", "oneoneone"};
  auto iter = beta.begin();
  ++iter;
  alpha.erase(iter);
  iter = beta.begin();
  EXPECT_EQ("one", *iter);
  ++iter;
  EXPECT_EQ("oneoneone", *iter);
}

// TEST(list, insert) {
//   s21::list<std::string> alpha{"one", "two", "three"};
//   alpha.insert(alpha.begin());
//   EXPECT_EQ("two", *alpha.begin());

//   s21::list<std::string> beta{"one", "oneone", "oneoneone"};

// }


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
