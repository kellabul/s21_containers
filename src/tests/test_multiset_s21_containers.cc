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

TEST(multiset, insert_many) {
  s21::multiset<int> one;
  EXPECT_EQ(one.count(3), 0);
  auto iter = one.begin();
  EXPECT_EQ(iter, one.end());
  EXPECT_EQ(one.size(), 0);
  one.insert_many(4, 4, 4, 4, 4, 4, 4, 10);
  iter = one.begin();
  for (int i = 1; i < 8; ++i, ++iter) {
    EXPECT_EQ(*iter, 4);
  }
  EXPECT_EQ(*iter, 10);
  ++iter;
  EXPECT_EQ(one.size(), 8);
  EXPECT_EQ(one.count(4), 7);
  EXPECT_EQ(iter, one.end());
  one.clear();
  iter = one.begin();
  EXPECT_EQ(iter, one.end());
  EXPECT_EQ(one.size(), 0);
}

TEST(multiset, swap) {
  s21::multiset<int> one{4, 4, 4, 4, 4, 4, 4, 10};
  s21::multiset<int> two;
  two.swap(one);
  auto iter = two.begin();
  for (int i = 1; i < 8; ++i, ++iter) {
    EXPECT_EQ(*iter, 4);
  }
  EXPECT_EQ(*iter, 10);
}

TEST(multiset, find) {
  s21::multiset<int> one{4, 4, 4, 4, 4, 4, 4, 10};
  auto iter = one.find(4);
  EXPECT_EQ(*iter, 4);
}

TEST(multiset, contains) {
  s21::multiset<int> one{4, 4, 4, 4, 4, 4, 4, 10};
  EXPECT_EQ(one.contains(4), true);
  EXPECT_EQ(one.contains(10), true);
  EXPECT_EQ(one.contains(0), false);
}

TEST(multicet, upperBound_1) {
  s21::multiset<int> keka{1, 1, 2, 3, 3, 3, 4, 8, 99, 100, 99, 102, 243};
  std::multiset<int> std_keka{1, 1, 2, 3, 3, 3, 4, 8, 99, 100, 99, 102, 243};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, upperBound_2) {
  s21::multiset<int> keka{1, 1};
  std::multiset<int> std_keka{1, 1};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_3) {
  s21::multiset<int> keka{};
  std::multiset<int> std_keka{};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_4) {
  s21::multiset<int> keka{1, 2, 2, 2, 2, 3};
  std::multiset<int> std_keka{1, 2, 2, 2, 2, 3};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_5) {
  s21::multiset<int> keka{1, 2, 3, 3, 3, 3, 3};
  std::multiset<int> std_keka{1, 2, 3, 3, 3, 3, 3};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_6) {
  s21::multiset<int> keka{1, 6, 6, 6, 6, 27};
  std::multiset<int> std_keka{1, 6, 6, 6, 6, 27};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_7) {
  s21::multiset<int> keka{3, 3, 3, 3, 3, 9, 11};
  std::multiset<int> std_keka{3, 3, 3, 3, 3, 9, 11};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_8) {
  s21::multiset<int> keka{9, 19, 23, 23, 23, 23, 23};
  std::multiset<int> std_keka{9, 19, 23, 23, 23, 23, 23};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, UpperBound_9) {
  s21::multiset<int> keka{13};
  std::multiset<int> std_keka{13};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.upper_bound(key);
    auto std_iter = std_keka.upper_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_1) {
  s21::multiset<int> keka{1, 1, 2, 3, 3, 3, 4, 8, 99, 100, 99, 102, 243};
  std::multiset<int> std_keka{1, 1, 2, 3, 3, 3, 4, 8, 99, 100, 99, 102, 243};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_2) {
  s21::multiset<int> keka{1, 1};
  std::multiset<int> std_keka{1, 1};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_3) {
  s21::multiset<int> keka{};
  std::multiset<int> std_keka{};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_4) {
  s21::multiset<int> keka{1, 2, 2, 2, 2, 3};
  std::multiset<int> std_keka{1, 2, 2, 2, 2, 3};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_5) {
  s21::multiset<int> keka{1, 2, 3, 3, 3, 3, 3};
  std::multiset<int> std_keka{1, 2, 3, 3, 3, 3, 3};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_6) {
  s21::multiset<int> keka{1, 6, 6, 6, 6, 27};
  std::multiset<int> std_keka{1, 6, 6, 6, 6, 27};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_7) {
  s21::multiset<int> keka{3, 3, 3, 3, 3, 9, 11};
  std::multiset<int> std_keka{3, 3, 3, 3, 3, 9, 11};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_8) {
  s21::multiset<int> keka{9, 19, 23, 23, 23, 23, 23};
  std::multiset<int> std_keka{9, 19, 23, 23, 23, 23, 23};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, LowerBound_9) {
  s21::multiset<int> keka{13};
  std::multiset<int> std_keka{13};
  auto end_iter = keka.end();
  auto std_end_iter = std_keka.end();

  for (const auto &key : keka) {
    auto iter = keka.lower_bound(key);
    auto std_iter = std_keka.lower_bound(key);
    if (iter == end_iter) {
      ASSERT_EQ(std_end_iter, std_iter);
    } else {
      ASSERT_EQ(*iter, *std_iter);
    }
  }
}

TEST(multicet, EqualRange_1) {
  std::multiset<int> std_keka{3, 4,   5,   5,   7,   7,   7,   7,
                              9, 198, 200, 200, 200, 200, 200, 232};
  s21::multiset<int> keka{3, 4,   5,   5,   7,   7,   7,   7,
                          9, 198, 200, 200, 200, 200, 200, 232};

  auto range = keka.equal_range(7);
  auto std_range = std_keka.equal_range(7);
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(*range.second, *std_range.second);
}

TEST(multicet, EqualRange_2) {
  std::multiset<int> std_keka{3, 4,   5,   5,   7,   7,   7,   7,
                              9, 198, 200, 200, 200, 200, 200, 232};
  s21::multiset<int> keka{3, 4,   5,   5,   7,   7,   7,   7,
                          9, 198, 200, 200, 200, 200, 200, 232};

  auto range = keka.equal_range(3);
  auto std_range = std_keka.equal_range(3);
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(*range.second, *std_range.second);
}

TEST(multicet, EqualRange_3) {
  std::multiset<int> std_keka{3, 4,   5,   5,   7,   7,   7,   7,
                              9, 198, 200, 200, 200, 200, 200, 232};
  s21::multiset<int> keka{3, 4,   5,   5,   7,   7,   7,   7,
                          9, 198, 200, 200, 200, 200, 200, 232};

  auto range = keka.equal_range(198);
  auto std_range = std_keka.equal_range(198);
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(*range.second, *std_range.second);
}

TEST(multicet, EqualRange_4) {
  std::multiset<int> std_keka{3, 4,   5,   5,   7,   7,   7,   7,
                              9, 198, 200, 200, 200, 200, 200, 232};
  s21::multiset<int> keka{3, 4,   5,   5,   7,   7,   7,   7,
                          9, 198, 200, 200, 200, 200, 200, 232};

  auto range = keka.equal_range(5);
  auto std_range = std_keka.equal_range(5);
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(*range.second, *std_range.second);
}

TEST(multicet, EqualRange_5) {
  std::multiset<int> std_keka{3, 4,   5,   5,   7,   7,   7,   7,
                              9, 198, 200, 200, 200, 200, 200, 232};
  s21::multiset<int> keka{3, 4,   5,   5,   7,   7,   7,   7,
                          9, 198, 200, 200, 200, 200, 200, 232};

  auto range = keka.equal_range(232);
  auto std_range = std_keka.equal_range(232);
  auto ms_end = keka.end();
  auto std_end = std_keka.end();
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(range.second, ms_end);
  ASSERT_EQ(std_end, std_range.second);
}

TEST(multicet, EqualRange_6) {
  std::multiset<int> std_keka{};
  s21::multiset<int> keka{};

  auto range = keka.equal_range(232);
  auto std_range = std_keka.equal_range(232);
  auto ms_end = keka.end();
  auto std_end = std_keka.end();
  ASSERT_EQ(range.first, ms_end);
  ASSERT_EQ(range.second, ms_end);
  ASSERT_EQ(std_end, std_range.first);
  ASSERT_EQ(std_end, std_range.second);
}

TEST(multicet, EqualRange_7) {
  std::multiset<int> std_keka{3, 3, 3, 3, 3, 3, 3, 3, 3};
  s21::multiset<int> keka{3, 3, 3, 3, 3, 3, 3, 3, 3};

  auto range = keka.equal_range(3);
  auto std_range = std_keka.equal_range(3);
  auto ms_end = keka.end();
  auto std_end = std_keka.end();
  auto ms_begin = keka.begin();
  auto std_begin = std_keka.begin();
  ASSERT_EQ(*range.first, *std_range.first);
  ASSERT_EQ(range.first, ms_begin);
  ASSERT_EQ(std_range.first, std_begin);
  ASSERT_EQ(range.second, ms_end);
  ASSERT_EQ(std_end, std_range.second);
}

TEST(multicet, EqualRange_8) {
  std::multiset<int> std_keka{3, 3, 3, 3, 3, 3, 3, 3, 3};
  s21::multiset<int> keka{3, 3, 3, 3, 3, 3, 3, 3, 3};

  auto range = keka.equal_range(198);
  auto std_range = std_keka.equal_range(198);
  auto ms_end = keka.end();
  auto std_end = std_keka.end();
  ASSERT_EQ(range.first, ms_end);
  ASSERT_EQ(range.second, ms_end);
  ASSERT_EQ(std_range.first, std_end);
  ASSERT_EQ(std_range.second, std_end);
}
