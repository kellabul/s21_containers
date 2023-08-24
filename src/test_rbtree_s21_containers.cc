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
#include <set>
#include <string>

#include "s21_containers.h"

using std::cout;
using std::endl;
using std::string;


 TEST(RBTree, find) {
   s21::RBTree<string> alpha;
   auto p = alpha.insert("one");
   alpha.insert("two");
   alpha.insert("three");
   p = alpha.insert("four");
   EXPECT_EQ(*p.first, "four");
   EXPECT_EQ(p.second, true);
   auto p2 = alpha.insert("three");
   EXPECT_EQ(*p2.first, "three");
   EXPECT_EQ(p2.second, false);
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
  two.erase(two.find("apple"));
  EXPECT_EQ(two.MinKey(), "bee");
  EXPECT_EQ(two.MaxKey(), "lemon");
  two.erase(two.find("lemon"));
  EXPECT_EQ(two.MinKey(), "bee");
  EXPECT_EQ(two.MaxKey(), "kite");
  two.erase(two.find("bee"));
  two.erase(two.find("egg"));
  two.erase(two.find("fish"));
  two.erase(two.find("grapes"));
  two.erase(two.find("hat"));
  two.erase(two.find("igloo"));
  two.erase(two.find("jug"));
  two.erase(two.find("kite"));
  EXPECT_EQ(two.MinKey(), "cat");
  EXPECT_EQ(two.MaxKey(), "dog");
  two.erase(two.find("dog"));
  EXPECT_EQ(two.MinKey(), "cat");
  EXPECT_EQ(two.MaxKey(), "cat");
}

TEST(RBTree, print) {
  s21::RBTree<int> one;
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

TEST(RBTree, big_tree) {
  s21::RBTree<int> one;
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 60000; ++i) one.erase(one.find(rand() % 20000));
  for (int i = 0; i < 20000; ++i) one.insert(rand() % 20000);
  for (int i = 0; i < 20000; ++i) one.erase(one.find(rand() % 20000));
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

TEST(RBTree, initializer_list) {
  const s21::RBTree<std::string> alpha{"one", "two", "three", "four"};
  auto iter = alpha.find("one");
  EXPECT_EQ(*iter, "one");
  iter = alpha.find("three");
  EXPECT_EQ(*iter, "three");
  iter = alpha.find("five");
  EXPECT_EQ(iter, alpha.end());
}

 TEST(RBTree, contains) {
   s21::RBTree<std::string> one {"one", "two", "three", "four"};
   EXPECT_EQ(one.contains("two"), true);
   EXPECT_EQ(one.contains("five"), false);
 }

// TEST(RBTree, max_size) {
//   s21::RBTree<int> one;
//   std::set<int> two;
//   EXPECT_EQ(one.max_size(), two.max_size());
// }
