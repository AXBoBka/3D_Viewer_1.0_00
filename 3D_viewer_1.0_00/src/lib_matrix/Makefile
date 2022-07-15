CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c11
FLAGS_TEST_LIBS = -lcheck -lm -lpthread
#
SRC=s21_matrix.c

HEADER=s21_matrix.h
NAME=s21_matrix.a
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

.PHONY: all build s21_matrix test gcov_report clean m

all: build

build: $(NAME)

s21_matrix: build

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test: build s21_test.c
	$(CC) $(CFLAGS) -c s21_test.c -o s21_test.o
	$(CC) s21_test.o $(NAME) $(FLAGS_TEST_LIBS) -o s21_test
	./s21_test

gcov_report: clean build
	$(CC) $(CFLAGS) --coverage s21_test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	rm -rf CPPLINT.cfg
	make test
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif

clean:
	rm -rf *.gch *.out *.o *.a m *.gcda *.gcdo *.gcno test s21_test tests gcov_test unit_test gcov_test.info ./report CPPLINT.cfg

m: s21_matrix
	@ $(CC) m.c $(NAME)
	@./a.out
