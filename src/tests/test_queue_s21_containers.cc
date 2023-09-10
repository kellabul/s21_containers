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
#include <queue>
#include <string>

#include "s21_containers.h"

using std::cout;
using std::endl;

TEST(S21_queueTest, Constructor_Default) {
  s21::queue<int> S21_queueTest;
  std::queue<int> std_queue;
  EXPECT_EQ(S21_queueTest.size(), std_queue.size());
  EXPECT_EQ(S21_queueTest.empty(), std_queue.empty());
}

TEST(S21_queueTest, Constructor_Initializer_queue) {
  s21::queue<int> S21_queueTest{1, 2, 3, 4};
  EXPECT_EQ(S21_queueTest.front(), 1);
  EXPECT_EQ(S21_queueTest.back(), 4);
  EXPECT_EQ(S21_queueTest.size(), size_t(4));
  EXPECT_EQ(S21_queueTest.empty(), false);
}

TEST(S21_queueTest, Constructor_Copy) {
  s21::queue<char> S21_queueTest_1{'a', 'b', 'c', 'd'};
  s21::queue<char> S21_queueTest_2 = S21_queueTest_1;

  EXPECT_EQ(S21_queueTest_1.size(), S21_queueTest_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(S21_queueTest_1.front(), S21_queueTest_2.front());
    EXPECT_EQ(S21_queueTest_1.size(), S21_queueTest_2.size());
    S21_queueTest_1.pop(), S21_queueTest_2.pop();
  }
}

TEST(S21_queueTest, Constructor_Move) {
  s21::queue<char> S21_queueTest_1{'a', 'b', 'c', 'd'};
  s21::queue<char> S21_queueTest_2 = std::move(S21_queueTest_1);
  s21::queue<char> S21_queueTest_3{'a', 'b', 'c', 'd'};

  EXPECT_EQ(S21_queueTest_2.size(), S21_queueTest_3.size());
  EXPECT_EQ(S21_queueTest_1.size(), size_t(0));
  EXPECT_EQ(S21_queueTest_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(S21_queueTest_3.front(), S21_queueTest_2.front());
    EXPECT_EQ(S21_queueTest_3.size(), S21_queueTest_2.size());
    S21_queueTest_3.pop(), S21_queueTest_2.pop();
  }
}

TEST(S21_queueTest, Modifier_Push) {
  s21::queue<int> S21_queueTest;
  std::queue<int> std_queue;
  S21_queueTest.push(5);
  S21_queueTest.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(S21_queueTest.front(), std_queue.front());
  EXPECT_EQ(S21_queueTest.back(), std_queue.back());
  EXPECT_EQ(S21_queueTest.size(), std_queue.size());
  EXPECT_EQ(S21_queueTest.empty(), std_queue.empty());
}

TEST(S21_queueTest, Modifier_Pop) {
  s21::queue<int> S21_queueTest;
  std::queue<int> std_queue;
  S21_queueTest.push(5);
  S21_queueTest.push(0);
  std_queue.push(5);
  std_queue.push(0);
  S21_queueTest.pop();
  S21_queueTest.pop();
  std_queue.pop();
  std_queue.pop();
  S21_queueTest.push(15);
  S21_queueTest.push(10);
  std_queue.push(15);
  std_queue.push(10);
  S21_queueTest.pop();
  std_queue.pop();
  EXPECT_EQ(S21_queueTest.front(), std_queue.front());
  EXPECT_EQ(S21_queueTest.back(), std_queue.back());
  EXPECT_EQ(S21_queueTest.size(), std_queue.size());
  EXPECT_EQ(S21_queueTest.empty(), std_queue.empty());
}

TEST(S21_queueTest, Modifier_Swap) {
  s21::queue<std::string> S21_queueTest_1{"aboba", "shleppa", "amogus",
                                          "abobus"};
  s21::queue<std::string> S21_queueTest_2{"shtirlits", "vovochka", "poruchik"};
  s21::queue<std::string> S21_queueTest_3{"aboba", "shleppa", "amogus",
                                          "abobus"};
  s21::queue<std::string> S21_queueTest_4{"shtirlits", "vovochka", "poruchik"};

  S21_queueTest_1.swap(S21_queueTest_2);

  EXPECT_EQ(S21_queueTest_1.size(), S21_queueTest_4.size());
  EXPECT_EQ(S21_queueTest_2.size(), S21_queueTest_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(S21_queueTest_3.front(), S21_queueTest_2.front());
    EXPECT_EQ(S21_queueTest_3.size(), S21_queueTest_2.size());
    S21_queueTest_3.pop(), S21_queueTest_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(S21_queueTest_1.front(), S21_queueTest_4.front());
    EXPECT_EQ(S21_queueTest_1.size(), S21_queueTest_4.size());
    S21_queueTest_1.pop(), S21_queueTest_4.pop();
  }
}

TEST(S21_queueTest, test1) {
  s21::queue<int> my_queue;
  std::queue<int> lib_queue;
  my_queue.push(3);
  my_queue.push(5);
  lib_queue.push(3);
  lib_queue.push(5);
  ASSERT_EQ(lib_queue.front(), my_queue.front());
  ASSERT_EQ(lib_queue.back(), my_queue.back());
  ASSERT_EQ(lib_queue.size(), my_queue.size());
}

TEST(S21_queueTest, test2) {
  s21::queue<int> my_queue({1, 2, 3, 4});
  std::queue<int> lib_queue({1, 2, 3, 4});
  ASSERT_EQ(lib_queue.front(), my_queue.front());
  ASSERT_EQ(lib_queue.back(), my_queue.back());
  lib_queue.pop();
  my_queue.pop();
  ASSERT_EQ(lib_queue.front(), my_queue.front());
  ASSERT_EQ(lib_queue.back(), my_queue.back());
  lib_queue.pop();
  my_queue.pop();
  ASSERT_EQ(3, my_queue.front());
  ASSERT_EQ(3, lib_queue.front());
  ASSERT_EQ(4, my_queue.back());
  ASSERT_EQ(4, lib_queue.back());
}

TEST(S21_queueTest, test3) {
  s21::queue<int> test_queue;
  test_queue.push(500);
  test_queue.push(1000);
  std::queue<int> test_queue1;
  test_queue1.push(500);
  test_queue1.push(1000);
  s21::queue<int> my_queue(test_queue);
  std::queue<int> lib_queue(test_queue1);
  ASSERT_EQ(lib_queue.size(), my_queue.size());
  ASSERT_EQ(lib_queue.front(), my_queue.front());
  ASSERT_EQ(lib_queue.back(), my_queue.back());
}

TEST(S21_queueTest, test4) {
  s21::queue<int> test_queue;
  test_queue.push(500);
  test_queue.push(1000);
  std::queue<int> test_queue1;
  test_queue1.push(500);
  test_queue1.push(1000);
  s21::queue<int> my_queue = std::move(test_queue);
  std::queue<int> lib_queue = std::move(test_queue1);
  ASSERT_EQ(lib_queue.size(), my_queue.size());
  ASSERT_EQ(lib_queue.front(), my_queue.front());
  ASSERT_EQ(lib_queue.back(), my_queue.back());
  ASSERT_EQ(0, test_queue.size());
  ASSERT_EQ(0, test_queue1.size());
}

TEST(S21_queueTest, test5) {
  s21::queue<int> my_queue({1, 2, 3, 4});
  std::queue<int> lib_queue({1, 2, 3, 4});
  s21::queue<int> to_swap({15, 125, 20});
  std::queue<int> to_swap1({15, 125, 20});
  my_queue.swap(to_swap);
  lib_queue.swap(to_swap1);
  ASSERT_EQ(3, my_queue.size());
  ASSERT_EQ(3, lib_queue.size());
  ASSERT_EQ(15, my_queue.front());
  ASSERT_EQ(15, lib_queue.front());
  ASSERT_EQ(4, to_swap.size());
  ASSERT_EQ(4, to_swap1.size());
  ASSERT_EQ(4, to_swap.back());
  ASSERT_EQ(4, to_swap1.back());
}

TEST(S21_queueTest, insert_many_back) {
  s21::queue<int> my_queue{6, 7, 9};
  s21::queue<int> res_queue{6, 7, 9, 1, 2, 8};
  my_queue.insert_many_back(1, 2, 8);
  for (size_t i = 0; i <= res_queue.size(); i++) {
    ASSERT_EQ(my_queue.back(), res_queue.back());
    my_queue.pop();
    res_queue.pop();
  }
}
