CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

build:
	gcc -c $(CFLAGS) -lstdc++ -std=c++17 s21_matrix_oop.cc -o s21_matrix_oop.o -pedantic 

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

clean:
	rm -rf *.o s21_matrix_oop.a test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: test
	leaks -atExit -- ./test

clang:
	clang-format -i --style=google *.cc *.h
	cp ../materials/linters/.clang-format ../src/.clang-format;
	clang-format -style=Google -n *.cc *.h;
	rm .clang-format
# # for mac
# test: s21_matrix_oop.a
# 	gcc -c $(CFLAGS) s21_matrix_oop_test.cc -o s21_matrix_oop_test.o -pedantic -fsanitize=address 
# 	gcc -lgtest -lstdc++ -std=c++17 s21_matrix_oop.a s21_matrix_oop_test.o -o test -pedantic -fsanitize=address
# 	./test

# for linux
test: s21_matrix_oop.a
	gcc -c -Wall -Werror -Wextra s21_matrix_oop_test.cc -o s21_matrix_oop_test.o -pedantic -fsanitize=address 
	gcc s21_matrix_oop_test.o -o test -L/path/to/gtest/lib -lgtest -lstdc++ -std=c++17 s21_matrix_oop.a -lm -pedantic -fsanitize=address
	./test

gcov_report: clean
	gcc  --coverage s21_matrix_oop_test.cc s21_matrix_oop.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

install_lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

main: 
	gcc  -lstdc++ -std=c++17 s21_matrix_oop.cc -pedantic 
	./a.out

.PHONY: all clang s21_matrix_oop test install_lcov leaks gcov_report clean build