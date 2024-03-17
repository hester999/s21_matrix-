CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
COVFLAGS = --coverage
LIB = s21_matrix_oop.a
TEST_EXEC = test
GTEST_LIB = -lgtest -lgtest_main -pthread

all: $(LIB) test gcov_report

$(LIB):
	$(CC) $(CFLAGS) -c s21_matrix_oop.cpp
	ar rc $(LIB) s21_matrix_oop.o
	rm s21_matrix_oop.o

test: clean $(LIB)
	$(CC) $(CFLAGS) $(COVFLAGS) -c matrix_tests/test.cpp
	$(CC) $(CFLAGS) $(COVFLAGS) -c s21_matrix_oop.cpp
	$(CC) $(CFLAGS) $(COVFLAGS) -o $(TEST_EXEC) *.o $(LIB) $(GTEST_LIB)
	./$(TEST_EXEC)

gcov_report:
	lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
	genhtml coverage.info --output-directory coverage-html --ignore-errors inconsistent
	open coverage-html/index.html


clean:
	rm -rf $(LIB) $(TEST_EXEC) *.o *.gcda *.gcno coverage.info coverage-html
