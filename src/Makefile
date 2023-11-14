CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest -lgmock -pthread
SOURCE = s21_matrix_oop.cc s21_constructors.cc s21_operators.cc s21_operations.cc
.PHONY: test

all: clean s21_matrix_oop.a gcov_report check

clean:
	rm -f *.o *.a *..out *.info *.gcda *.gcno
	rm -rf ./tests/*.o ./tests/*.a
	rm -rf test
	rm -rf report

test:
	gcc --coverage ./tests/*.cc $(SOURCE) -o test $(TFLAGS) -lstdc++ -lm
	./test

s21_matrix_oop.a:
	gcc $(CFLAGS) -c $(SOURCE) -lstdc++ -lm
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a
	rm -f *.o

gcov_report: test
	lcov -t "coverage" -o unit_test.info -c -d .
	genhtml --output-directory=report unit_test.info
	open report/index.html

check:
	clang-format -style=google -n *.cc *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	valgrind -s ./test
endif

clang_format:
	clang-format -style=google -i *.cc *.h tests/*.cc tests/*.h