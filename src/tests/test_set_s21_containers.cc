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

TEST(set, find) {
  s21::set<string> alpha;
  alpha.insert("one");
  alpha.insert("two");
  alpha.insert("three");
  auto iter = alpha.insert("four");
  EXPECT_EQ(*iter.first, "four");
  EXPECT_EQ(iter.second, true);
  iter = alpha.insert("three");
  EXPECT_EQ(*iter.first, "three");
  EXPECT_EQ(iter.second, false);
}

TEST(set, print) {
  s21::set<int> one;
  for (int i = 0; i < 10; ++i) one.insert(i);
  testing::internal::CaptureStdout();
  one.print();
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

TEST(set, iterator) {
  s21::set<int> one;
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

TEST(set, const_iterator) {
  s21::set<int> const one{1, 2, 3, 4, 5, 6, 7, 8, 9};
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

TEST(set, delete_node) {
  s21::set<string> one;
  one.insert("apple");
  one.erase(one.find("apple"));
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
  one.erase(one.find("bee"));
  EXPECT_EQ("dog", *iter--);
  EXPECT_EQ("cat", *iter--);
  EXPECT_EQ("apple", *iter--);
  iter--;
  EXPECT_EQ("lemon", *iter);
}

TEST(set, big_tree) {
  s21::set<int> one;
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 60000; ++i) one.erase(one.find(rand() % 20000));
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 20000; ++i) one.erase(one.find(rand() % 20000));
}

TEST(set, copy_constructor) {
  s21::set<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::set<int> two(one);
  auto iter_one = one.begin();
  auto iter_two = two.begin();
  for (; iter_one != one.end(); ++iter_one, ++iter_two) {
    EXPECT_EQ(*iter_one, *iter_two);
    EXPECT_NE(iter_one, iter_two);
  }
}

TEST(set, copy_operator) {
  s21::set<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::set<int> two{5, 2, 3, 5, 6};
  two = one;
  auto iter_one = one.begin();
  auto iter_two = two.begin();
  for (; iter_one != one.end(); ++iter_one, ++iter_two) {
    EXPECT_EQ(*iter_one, *iter_two);
    EXPECT_NE(iter_one, iter_two);
  }
}

TEST(set, size_empty) {
  s21::set<int> one;
  EXPECT_EQ(true, one.empty());
  EXPECT_EQ(0, one.size());
  for (int i = 0; i < 8; ++i) one.insert(i);
  EXPECT_EQ(false, one.empty());
  EXPECT_EQ(8, one.size());
  one.clear();
  EXPECT_EQ(true, one.empty());
}

TEST(set, swap) {
  s21::set<int> one;
  s21::set<int> two;
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

TEST(set, copy_and_move_constructors) {
  s21::set<int> one;
  for (int i = 0; i < 8; ++i) one.insert(i);
  s21::set<int> two(one);
  auto iter = two.begin();
  for (auto const &elem : one) {
    EXPECT_EQ(elem, *iter);
    iter++;
  }
  EXPECT_EQ(two.size(), one.size());
  iter = two.begin();
  s21::set<int> three(std::move(one));
  for (auto const &elem : three) {
    EXPECT_EQ(elem, *iter);
    iter++;
  }
  EXPECT_EQ(two.size(), three.size());
  EXPECT_EQ(0, one.size());
}

TEST(set, initializer_list) {
  const s21::set<std::string> alpha{"one", "two", "three", "four"};
  auto iter = alpha.find("one");
  EXPECT_EQ(*iter, "one");
  iter = alpha.find("three");
  EXPECT_EQ(*iter, "three");
  iter = alpha.find("five");
  EXPECT_EQ(iter, alpha.end());
}

TEST(set, contains) {
  s21::set<std::string> const one{"one", "two", "three", "four"};
  EXPECT_EQ(one.contains("two"), true);
  EXPECT_EQ(one.contains("five"), false);
  s21::set<std::string> two{};
  EXPECT_EQ(two.contains("five"), false);

  s21::set<std::string> three{"one", "two", "three", "fouer"};
  three.erase(three.find("one"));
}

TEST(set, insert_many) {
  s21::set<std::string> one;
  auto v_pair = one.insert_many("aaa", "bbb", "ccc", "ddd");
  auto iter = one.begin();
  for (auto &elem : v_pair) {
    EXPECT_EQ(elem.first, iter);
    EXPECT_EQ(elem.second, true);
    ++iter;
  }
  v_pair = one.insert_many("aaa", "eee", "bbb", "fff");

  iter = one.find("aaa");
  EXPECT_EQ(v_pair[0].first, iter);

  iter = one.find("eee");
  EXPECT_EQ(v_pair[1].first, iter);

  iter = one.find("fff");
  EXPECT_EQ(v_pair[3].first, iter);

  EXPECT_EQ(v_pair[0].second, false);
  EXPECT_EQ(v_pair[1].second, true);
  EXPECT_EQ(v_pair[2].second, false);
  EXPECT_EQ(v_pair[3].second, true);
}

TEST(set, max_size) {
  s21::set<int> one;
  std::set<int> two;
  EXPECT_EQ(one.max_size(), two.max_size());
}
