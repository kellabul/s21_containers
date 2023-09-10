CC := g++
FLAGS := -std=c++17 -Wall -Werror -Wextra -I .
GTEST_FLAGS := -lgtest_main -lgtest -pthread 
NAME := s21_containers
TEST_NAME := test_$(NAME)
ASAN_FLAGS := -g -fsanitize=address,undefined,leak
GCOV_FLAGS := -fprofile-arcs -ftest-coverage -fPIC -O0
LCOV_REPORT_FOLDER := $(NAME)_report
TEST_FOLDER := tests


COVERAGE_FILES := tests/*.gcno *.gcno
COVERAGE_RESULTS := tests/*.gcda *.gcda
GCOV_FILES := tests/*.gcov *.gcov *.gcov
LCOV_FILES := tests/*.info *.info *html *css
TEST_COVERAGE_FILES := $(COVERAGE_FILES) $(COVERAGE_RESULTS) $(GCOV_FILES) $(LCOV_FILES)

GTEST_SRC := $(wildcard tests/test_*.cc)
GTEST_OBJ := $(GTEST_SRC:.cc=.o)
GCDA_FILES := $(GTEST_SRC:.cc=.gcda)
HEADERS := $(shell find . -name "*.h" -o -name "*.tpp")
SRC := $(HEADERS) $(GTEST_SRC)

.PHONY: all
all: test

.PHONY: clean
clean:
	rm -rf *.o tests/*.o $(TEST_NAME) $(TEST_COVERAGE_FILES) $(LCOV_REPORT_FOLDER) 

.PHONY: test
test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(GTEST_OBJ)
	$(CC) $(GTEST_FLAGS) $^ -o $@ -fprofile-arcs

.cc.o:
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(GCDA_FILES): $(GTEST_OBJ)
	make test

.PHONY: gcov_report
gcov_report: $(GCDA_FILES)
	lcov -t "$(NAME)" -o gcov.info -c -d . --no-external
	genhtml -o  $(LCOV_REPORT_FOLDER)  gcov.info
	open $(LCOV_REPORT_FOLDER)/index.html

.PHONY: gcovr_html
gcovr_html: test
	gcovr --html-details $(TEST_NAME).details.html
	open $(TEST_NAME).details.html

.PHONY: gcovr
gcovr: test
	gcovr

.PHONY: gcov
gcov: $(TEST_NAME)
	gcov -k -r $(GTEST_SRC) 

.PHONY: asan
asan: compile_with_asan
	./$(TEST_NAME)

.PHONY: compile_with_asan
compile_with_asan: clean
	$(CC) $(FLAGS) $(GTEST_SRC) -o $(TEST_NAME) $(GTEST_FLAGS) $(ASAN_FLAGS)

.clang-format:
	cp ../materials/linters/.clang-format .

.PHONY: clang
clang: .clang-format
	clang-format -n $(SRC) --verbose

.PHONY: doclang
doclang: .clang-format
	clang-format -i $(SRC) --verbose

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC)

.PHONY: valgrind
valgrind: $(TEST_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_NAME)

.PHONY: valgrind2
valgrind2: $(TEST_NAME)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_NAME)

.PHONY: leaks
leaks: $(TEST_NAME)
	leaks -e . --atExit -- ./$(TEST_NAME) 

.PHONY: install_lcov
install_lcov:
	brew install lcov