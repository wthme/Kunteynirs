FLAGS = -Wall -Wextra -Werror -std=c++17

all: test

gcov_report:test
	./test
	lcov -t test -o cunt.info -c -d .
	genhtml -o report cunt.info

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h */*.cc
	rm -f .clang-format

google_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.h *.cpp
	rm -f .clang-format

clean_src:
	rm -rf *.o *.gcda *.gcno *.gcov *.gch gcov_test

clean: clean_src
	rm -rf report *.a *_test *.info .clang-format test a.out

fun:
	g++ vector.cpp -c vector.h  && g++ *.o

my_test:
	g++ vector.cpp mytest.cpp vector.h queue.h queue.cpp -c
	g++ *.o -o mytest -lgtest -pthread

stack:
	g++ stack.cpp stack.h -c -std=c++17 && g++ stack.o && ./a.out

testqq:
	g++ queue.cpp q_test.cpp vector.cpp -c
	g++ *.o -o test -lgtest -pthread

queue: queue.h
	g++ queue.cpp -c
	g++ queue.o
	./a.out

test:
	g++ --coverage test.cc stack.cpp multiset.cpp set.cpp map.cpp array.cpp list.cpp queue.cpp vector.cpp -o test -lgtest -pthread -lgmock -std=c++17

map:
	g++ multiset.cpp Btree.cpp -c && g++ *.o

mtest:
	g++ maptest.cc map.cpp -o test -lgtest -pthread -lgmock -std=c++17

