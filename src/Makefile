CC = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra
GTEST_FLAGS = -lgtest -pthread
NAME = s21_containers
TEST_NAME = test_$(NAME)
ASAN_FLAGS = -g -fsanitize=address,undefined,leak
GCOV_FLAGS = --coverage
LCOV_REPORT_FOLDER = $(NAME)_report

COVERAGE_FILES = *.gcno
COVERAGE_RESULTS= *.gcda
GCOV_FILES = *.gcov
LCOV_FILES = *.info

SOURCE_FILES =
GTEST_SOURCE_FILES = test_map_s21_containers.cc

.PHONY: all, clean, test
.PHONY: compile_test, gcov_report, gcov, asan, compile_test_with_asan
.PHONY: clang, doclang, cppcheck, valgrind, leaks

all: test

clean:
	rm -rf *.o *.a $(TEST_NAME) $(COVERAGE_RESULTS) $(COVERAGE_FILES) $(GCOV_FILES) \
	$(LCOV_FILES) $(LCOV_REPORT_FOLDER)

test: compile_test
	./$(TEST_NAME)

compile_test: clean
	$(CC) $(FLAGS) $(GTEST_SOURCE_FILES) $(SOURCE_FILES) -o $(TEST_NAME) $(GTEST_FLAGS) \
	$(GCOV_FLAGS)

gcov_report: gcov
	lcov -t "$(NAME)" -o gcov_report.info -c -d . --rc lcov_branch_coverage=1 --no-external
	genhtml -o  $(LCOV_REPORT_FOLDER)  gcov_report.info --rc lcov_branch_coverage=1
	open $(NAME)_report/index.html

gcov: compile_test
	# @rm -f $(COVERAGE_RESULTS) $(GCOV_FILES)
	./$(TEST_NAME)
	gcov $(GTEST_SOURCE_FILES) $(SOURCE_FILES)

asan: compile_test_with_asan
	./$(TEST_NAME)

compile_test_with_asan: clean
	$(CC) $(FLAGS) $(GTEST_SOURCE_FILES) $(SOURCE_FILES) -o $(TEST_NAME) $(GTEST_FLAGS) \
	$(GCOV_FLAGS) $(ASAN_FLAGS)

copy_clang:
	cp ../materials/linters/.clang-format .

clang: copy_clang
	clang-format --verbose -n *.cc; \
	clang-format --verbose -n *.h; \
	clang-format --verbose -n */*.cc; \
	clang-format --verbose -n */*.h

	# --style=Google

doclang: copy_clang
	clang-format --verbose -i *.cc; \
	clang-format --verbose -i *.h; \
	clang-format --verbose -i */*.cc; \
	clang-format --verbose -i */*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCE_FILES)

valgrind: compile_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_NAME)

leaks: compile_test
	leaks -e . --atExit -- ./$(TEST_NAME) 

install_lcov:
	brew install lcov