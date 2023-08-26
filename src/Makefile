CC := g++
FLAGS := -std=c++17 -pedantic -Wall -Werror -Wextra
GTEST_FLAGS := -lgtest_main -lgtest -pthread 
NAME := s21_containers
TEST_NAME := test_$(NAME)
ASAN_FLAGS := -g -fsanitize=address,undefined,leak
GCOV_FLAGS := --coverage
LCOV_REPORT_FOLDER := $(NAME)_report

COVERAGE_FILES := *.gcno
COVERAGE_RESULTS := *.gcd
GCOV_FILES := *.gcov
LCOV_FILES := *.info

GTEST_LIST_SRC := test_list_s21_containers.cc
GTEST_LIST_OBJ := $(GTEST_LIST_SRC:.cc=.o)
GTEST_SET_SRC := test_set_s21_containers.cc
GTEST_SET_OBJ := $(GTEST_SET_SRC:.cc=.o)
GTEST_SRC := $(GTEST_LIST_SRC) $(GTEST_SET_SRC)
GTEST_OBJ := $(GTEST_SRC:.cc=.o)
GCDA_FILES := $(GTEST_SRC:.cc=.gcda)
HEADERS := $(shell find . -name "*.h" -o -name "*.tpp")
SRC := $(HEADERS) $(GTEST_SRC)

.PHONY: all
all: test

.PHONY: clean
clean:
	rm -rf *.o *.a $(TEST_NAME) $(COVERAGE_RESULTS) $(COVERAGE_FILES) $(GCOV_FILES) \
	$(LCOV_FILES) $(LCOV_REPORT_FOLDER) 

.PHONY: test
test: $(TEST_NAME)
	./$(TEST_NAME)

$(GTEST_LIST_OBJ): $(GTEST_LIST_SRC) s21_containers.h $(shell find ./list -name "*.h" -o -name "*.tpp")
	$(CC) $(FLAGS)  -c $< -o $@ $(GCOV_FLAGS)

$(GTEST_SET_OBJ): $(GTEST_SET_SRC) s21_containers.h $(shell find ./rb_tree -name "*.h" -o -name "*.tpp")
	$(CC) $(FLAGS)  -c $< -o $@ $(GCOV_FLAGS)

$(TEST_NAME): $(GTEST_LIST_OBJ) $(GTEST_SET_OBJ)
	$(CC) $(GTEST_OBJ) $(GTEST_FLAGS) -o $(TEST_NAME) -fprofile-arcs

$(GCDA_FILES): $(GTEST_LIST_OBJ) $(GTEST_SET_OBJ)
	make test

.PHONY: gcov_report
gcov_report: $(GCDA_FILES)
	lcov -t "$(NAME)" -o gcov.info -c -d . --rc lcov_branch_coverage=1 --no-external
	genhtml -o  $(LCOV_REPORT_FOLDER)  gcov.info --rc lcov_branch_coverage=1
	open $(LCOV_REPORT_FOLDER)/index.html

.PHONY: gcov
gcov: $(TEST_NAME)
	gcov $(GTEST_SRC)

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