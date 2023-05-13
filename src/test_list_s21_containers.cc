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

#include "s21_containers.h"

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

TEST(list, pop_back_and_empty) {
  s21::list<int> one;
  EXPECT_EQ(0, one.size());
  EXPECT_EQ(true, one.empty());
  one.push_back(111);
  one.push_back(555);
  EXPECT_EQ(2, one.size());
  EXPECT_EQ(false, one.empty());
  one.pop_back();
  one.pop_back();
  EXPECT_EQ(0, one.size());
  EXPECT_EQ(true, one.empty());
}

TEST(list, n_constructor) {
  s21::list<int> one(20);
  EXPECT_EQ(20, one.size());
}

TEST(list, front_and_back) {
  s21::list<int> one{11, 22, 33, 44, 55, 66, 77};
  EXPECT_EQ(11, one.front());
  EXPECT_EQ(77, one.back());
}

TEST(list, push_front_and_pop_front) {
  s21::list<int> one;
  EXPECT_EQ(0, one.size());
  EXPECT_EQ(true, one.empty());
  one.push_front(111);
  one.push_front(555);
  EXPECT_EQ(2, one.size());
  EXPECT_EQ(555, *one.begin());
  one.pop_front();
  EXPECT_EQ(1, one.size());
  EXPECT_EQ(111, *one.begin());
  one.pop_front();
  EXPECT_EQ(true, one.empty());
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

TEST(list, copy_constructor) {
  s21::list<int> zero{111, 222, 444};
  s21::list<int> one(zero);
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

TEST(list, max_size) {
  s21::list<std::string> s21_list_obj;
  std::list<std::string> std_list_obj;
  EXPECT_EQ(s21_list_obj.max_size(), std_list_obj.max_size());
  s21::list<char> s21_list_obj_2;
  std::list<char> std_list_obj_2;
  EXPECT_EQ(s21_list_obj_2.max_size(), std_list_obj_2.max_size());
}

TEST(list, insert) {
  s21::list<std::string> alpha{"one", "two", "three"};
  alpha.insert(alpha.begin(), "zero");
  EXPECT_EQ("zero", *alpha.begin());
  auto iter = alpha.insert(alpha.end(), "four");
  EXPECT_EQ("four", *iter);
  ++iter;
  EXPECT_EQ(true, iter == alpha.end());
  iter = alpha.begin();
  ++iter;
  iter = alpha.insert(iter, "zeroPointFive");
  EXPECT_EQ("zeroPointFive", *iter);
}

TEST(list, swap) {
  s21::list<std::string> alpha{"zero", "one", "two", "three"};
  s21::list<std::string> beta{"four", "five", "six"};
  alpha.swap(beta);
  auto iter = alpha.begin();
  EXPECT_EQ("four", *iter);
  ++iter;
  ++iter;
  EXPECT_EQ("six", *iter);
  iter = beta.end();
  --iter;
  EXPECT_EQ("three", *iter);
  beta.~list();
  EXPECT_EQ("four", *alpha.begin());
  {
    s21::list<std::string> gamma{"seven"};
    alpha.swap(gamma);
    EXPECT_EQ("four", *gamma.begin());
  }
  EXPECT_EQ("seven", *alpha.begin());

  s21::list<std::string> delta;
  alpha.swap(delta);
  EXPECT_EQ("seven", *delta.begin());
  EXPECT_EQ(true, alpha.empty());
}

TEST(list, move_constructor) {
  s21::list<int> zero{111, 222, 444};
  s21::list<int> one(std::move(zero));
  auto iter = one.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
  EXPECT_EQ(true, zero.empty());
}

TEST(list, reverse) {
  s21::list<int> zero{111, 222, 444};
  zero.reverse();
  auto iter = zero.begin();
  EXPECT_EQ(444, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(111, *iter);
}

TEST(list, unique) {
  s21::list<int> zero{111, 111, 111, 222, 222, 222, 444, 444, 444};
  zero.unique();
  auto iter = zero.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
  ++iter;
  EXPECT_EQ(iter, zero.end());

  s21::list<int> one{111, 222, 444};
  one.unique();
  iter = one.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(222, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);

  s21::list<int> two;
  EXPECT_NO_THROW(two.unique());
}

TEST(list, splice) {
  s21::list<int> zero{111, 123, 444};
  s21::list<int> one;
  one.splice(one.begin(), zero);
  EXPECT_EQ(true, zero.empty());
  auto iter = one.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(123, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
  EXPECT_EQ(3, one.size());

  s21::list<int> two{2, 3, 4};
  s21::list<int> three{1, 5, 6};
  three.splice(++three.begin(), two);
  iter = three.begin();
  for (int i = 1; i < 7; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
  EXPECT_EQ(0, two.size());
}

TEST(list, assignment_operator) {
  s21::list<int> one{111, 123, 444};
  s21::list<int> two;
  two = std::move(one);
  EXPECT_EQ(true, one.empty());
  auto iter = two.begin();
  EXPECT_EQ(111, *iter);
  ++iter;
  EXPECT_EQ(123, *iter);
  ++iter;
  EXPECT_EQ(444, *iter);
  two = std::move(two);
  EXPECT_EQ(444, *iter);
}

TEST(list, sort) {
  s21::list<int> one{222, 33, 111, 444, 333, 3213, 555};
  one.sort();
  auto iter = one.begin();
  EXPECT_EQ(33, *iter);
  --iter;
  --iter;
  EXPECT_EQ(3213, *iter);
  ++iter;
  ++iter;
  ++iter;
  EXPECT_EQ(111, *iter);

  s21::list<int> two{4, 0, 3, 2, 1, 7, 6, 5};
  two.sort();
  iter = two.begin();
  for (size_t i = 0; i < two.size(); ++i) {
    EXPECT_EQ(i, *iter);
    ++iter;
  }
  ++iter;
  EXPECT_EQ(0, *iter);
  ++iter;
  EXPECT_EQ(1, *iter);
  iter = two.end();
  for (int i = two.size() - 1; i >= 0; --i) {
    --iter;
    EXPECT_EQ(i, *iter);
  }
}

TEST(list, merge) {
  s21::list<int> one{4, 0, 3, 2};
  s21::list<int> two{1, 7, 6, 5};
  one.merge(two);
  auto iter = two.begin();
  for (size_t i = 0; i < two.size(); ++i) {
    EXPECT_EQ(i, *iter);
    ++iter;
  }
  EXPECT_EQ(true, two.empty());
}

TEST(list, sort_fast) {
  s21::list<int> one{222, 33, 111, 444, 333, 3213, 555};
  one.sort_fast();
  auto iter = one.begin();
  EXPECT_EQ(33, *iter);
  --iter;
  --iter;
  EXPECT_EQ(3213, *iter);
  ++iter;
  ++iter;
  ++iter;
  EXPECT_EQ(111, *iter);

  s21::list<int> two{4, 0, 3, 2, 1, 7, 6, 5};
  two.sort_fast();
  iter = two.begin();
  for (size_t i = 0; i < two.size(); ++i) {
    EXPECT_EQ(i, *iter);
    ++iter;
  }
  ++iter;
  EXPECT_EQ(0, *iter);
  ++iter;
  EXPECT_EQ(1, *iter);
  iter = two.end();
  for (int i = two.size() - 1; i >= 0; --i) {
    --iter;
    EXPECT_EQ(i, *iter);
  }
}


// s21::list<int> sort_list;

// TEST(list, fill_sort) {
//   for (int i = 0; i < 10'000'000; ++i) sort_list.push_back(rand());
// }

// TEST(list, sort_big_fast) {
//   s21::list<int> sort_list_fast(sort_list);
//   sort_list_fast.sort_fast();
//   auto iter = sort_list_fast.begin();
//   for (int i = 0; i < 11; ++i) {
//     cout << *iter << " ";
//     ++iter;
//   }
//   cout << endl;
//   iter = --sort_list_fast.end();
//   for (int i = 0; i < 5; ++i) {
//     cout << *iter << " ";
//     --iter;
//   }
//   cout << endl;
// }


// TEST(list, sort_big) {
//   s21::list<int> sort_list_iter(sort_list);
//   sort_list_iter.sort();
//   auto iter = sort_list_iter.begin();
//   for (int i = 0; i < 11; ++i) {
//     cout << *iter << " ";
//     ++iter;
//   }
//   cout << endl;
//   iter = --sort_list_iter.end();
//   for (int i = 0; i < 5; ++i) {
//     cout << *iter << " ";
//     --iter;
//   }
//   cout << endl;
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
