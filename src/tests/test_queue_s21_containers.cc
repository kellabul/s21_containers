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

TEST(queue_test, Constructor_Default) {
  s21::queue<int> queue_test;
  std::queue<int> std_queue;
  EXPECT_EQ(queue_test.size(), std_queue.size());
  EXPECT_EQ(queue_test.empty(), std_queue.empty());
}

TEST(queue_test, Constructor_Initializer_queue) {
  s21::queue<int> queue_test{1, 2, 3, 4};
  EXPECT_EQ(queue_test.front(), 1);
  EXPECT_EQ(queue_test.back(), 4);
  EXPECT_EQ(queue_test.size(), size_t(4));
  EXPECT_EQ(queue_test.empty(), false);
}

TEST(queue_test, Constructor_Copy) {
  s21::queue<char> queue_test_1{'a', 'b', 'c', 'd'};
  s21::queue<char> queue_test_2 = queue_test_1;

  EXPECT_EQ(queue_test_1.size(), queue_test_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(queue_test_1.front(), queue_test_2.front());
    EXPECT_EQ(queue_test_1.size(), queue_test_2.size());
    queue_test_1.pop(), queue_test_2.pop();
  }
}

TEST(queue_test, Constructor_Move) {
  s21::queue<char> queue_test_1{'a', 'b', 'c', 'd'};
  s21::queue<char> queue_test_2 = std::move(queue_test_1);
  s21::queue<char> queue_test_3{'a', 'b', 'c', 'd'};

  EXPECT_EQ(queue_test_2.size(), queue_test_3.size());
  EXPECT_EQ(queue_test_1.size(), size_t(0));
  EXPECT_EQ(queue_test_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(queue_test_3.front(), queue_test_2.front());
    EXPECT_EQ(queue_test_3.size(), queue_test_2.size());
    queue_test_3.pop(), queue_test_2.pop();
  }
}

TEST(queue_test, Modifier_Push) {
  s21::queue<int> queue_test;
  std::queue<int> std_queue;
  queue_test.push(5);
  queue_test.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(queue_test.front(), std_queue.front());
  EXPECT_EQ(queue_test.back(), std_queue.back());
  EXPECT_EQ(queue_test.size(), std_queue.size());
  EXPECT_EQ(queue_test.empty(), std_queue.empty());
}

TEST(queue_test, Modifier_Pop) {
  s21::queue<int> queue_test;
  std::queue<int> std_queue;
  queue_test.push(5);
  queue_test.push(0);
  std_queue.push(5);
  std_queue.push(0);
  queue_test.pop();
  queue_test.pop();
  std_queue.pop();
  std_queue.pop();
  queue_test.push(15);
  queue_test.push(10);
  std_queue.push(15);
  std_queue.push(10);
  queue_test.pop();
  std_queue.pop();
  EXPECT_EQ(queue_test.front(), std_queue.front());
  EXPECT_EQ(queue_test.back(), std_queue.back());
  EXPECT_EQ(queue_test.size(), std_queue.size());
  EXPECT_EQ(queue_test.empty(), std_queue.empty());
}

TEST(queue_test, Modifier_Swap) {
  s21::queue<std::string> queue_test_1{"one", "two", "three", "four"};
  s21::queue<std::string> queue_test_2{"aaaaa", "bbbbb", "ccccc"};
  s21::queue<std::string> queue_test_3{"one", "two", "three", "four"};
  s21::queue<std::string> queue_test_4{"aaaaa", "bbbbb", "ccccc"};

  queue_test_1.swap(queue_test_2);

  EXPECT_EQ(queue_test_1.size(), queue_test_4.size());
  EXPECT_EQ(queue_test_2.size(), queue_test_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(queue_test_3.front(), queue_test_2.front());
    EXPECT_EQ(queue_test_3.size(), queue_test_2.size());
    queue_test_3.pop(), queue_test_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(queue_test_1.front(), queue_test_4.front());
    EXPECT_EQ(queue_test_1.size(), queue_test_4.size());
    queue_test_1.pop(), queue_test_4.pop();
  }
}

TEST(queue_test, test1) {
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

TEST(queue_test, test2) {
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

TEST(queue_test, test3) {
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

TEST(queue_test, test4) {
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

TEST(queue_test, test5) {
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

TEST(queue_test, insert_many_back) {
  s21::queue<int> my_queue{6, 7, 9};
  s21::queue<int> res_queue{6, 7, 9, 1, 2, 8};
  my_queue.insert_many_back(1, 2, 8);
  for (size_t i = 0; i <= res_queue.size(); i++) {
    ASSERT_EQ(my_queue.back(), res_queue.back());
    my_queue.pop();
    res_queue.pop();
  }
}

TEST(queue_test, operators) {
  s21::queue<int> q1{6, 7, 9};
  s21::queue<int> q2;
  s21::queue<int> q3{6, 7, 9};
  const s21::queue<int> const_q2;
  q1 = q2;
  q3 = q2;
  EXPECT_EQ(q1, q2);
  EXPECT_EQ(q3, const_q2);
  EXPECT_EQ(q3 == const_q2, true);
  EXPECT_EQ(q3 != const_q2, false);
}

TEST(queue_test, move_operator) {
  s21::queue<int> const q1{6, 7, 9};
  EXPECT_EQ(q1.front(), 6);
  EXPECT_EQ(q1.back(), 9);
  s21::queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.front(), 6);
  EXPECT_EQ(q2.back(), 9);
}
