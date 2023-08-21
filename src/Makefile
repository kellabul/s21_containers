CC := g++
FLAGS := -std=c++17 -Wall -Werror -Wextra
GTEST_FLAGS := -lgtest -pthread
NAME := s21_containers
TEST_NAME := test_$(NAME)
ASAN_FLAGS := -g -fsanitize=address,undefined,leak
GCOV_FLAGS := --coverage -fprofile-arcs
LCOV_REPORT_FOLDER := $(NAME)_report

COVERAGE_FILES := *.gcno
COVERAGE_RESULTS := *.gcda
GCOV_FILES := *.gcov
LCOV_FILES := *.info

GTEST_SRC := test_list_s21_containers.cc test_rbtree_s21_containers.cc
GTEST_OBJ := $(GTEST_SRC:.cc=.o)
HEADERS := $(shell find . -name "*.h" -or -name "*.tpp")
SRC := $(HEADERS) $(GTEST_SRC)


.PHONY: all, clean, test
.PHONY: gcov_report, gcov, asan, compile_test_with_asan
.PHONY: clang, doclang, cppcheck, valgrind, leaks

all: test

clean:
	rm -rf *.o *.a $(TEST_NAME) $(COVERAGE_RESULTS) $(COVERAGE_FILES) $(GCOV_FILES) \
	$(LCOV_FILES) $(LCOV_REPORT_FOLDER) 

test: $(TEST_NAME)
	./$(TEST_NAME)

$(GTEST_OBJ): $(GTEST_SRC) $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

$(TEST_NAME): $(GTEST_OBJ)
	$(CC) $(GTEST_OBJ) $(GTEST_FLAGS) $(GCOV_FLAGS) -o $(TEST_NAME) 

gcov_report: gcov
	lcov -t "$(NAME)" -o gcov_report.info -c -d . --rc lcov_branch_coverage=1 --no-external
	genhtml -o  $(LCOV_REPORT_FOLDER)  gcov_report.info --rc lcov_branch_coverage=1
	open $(NAME)_report/index.html

gcov: $(TEST_NAME)
	# @rm -f $(COVERAGE_RESULTS) $(GCOV_FILES)
	./$(TEST_NAME)
	gcov $(GTEST_SRC)

asan: compile_test_with_asan
	./$(TEST_NAME)

compile_test_with_asan: clean
	$(CC) $(FLAGS) $(GTEST_SRC) $(SOURCE_FILES) -o $(TEST_NAME) $(GTEST_FLAGS) \
	$(GCOV_FLAGS) $(ASAN_FLAGS)

.clang-format:
	cp ../materials/linters/.clang-format .

clang: .clang-format
	clang-format -n $(SRC) --verbose

	# --style=Google

doclang: .clang-format
	clang-format -i $(SRC) --verbose

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCE_FILES)

valgrind: $(TEST_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_NAME)

leaks: $(TEST_NAME)
	leaks -e . --atExit -- ./$(TEST_NAME) 

install_lcov:
	brew install lcov