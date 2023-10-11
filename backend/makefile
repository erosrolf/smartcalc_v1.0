TARGET = libcalc
CC = gcc -Wall -Wextra -Werror -std=c11 
CFLAGS = -c $(shell pkg-config --cflags check)
TST_LIBS = $(shell pkg-config --libs check)

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_TEST = ./tests/

SRCS = $(wildcard $(PREF_SRC)*.c)
OBJS = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRCS))

$(TARGET).a: $(OBJS)
	ar rcs $(TARGET).a $(OBJS)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TARGET).a
	$(CC) -g $(PREF_TEST)*.c $(TARGET).a $(TST_LIBS) -o test
	./test

clean:
	rm -rf $(TARGET).a $(PREF_OBJ)*.o test

# CC = gcc -Wall -Werror -Wextra -std=c11
# PROJECT = s21_matrix
# TESTS = tests/*.c
# OS := $(shell uname)
#
# ifeq ($(OS),Linux)
# 	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
# 	OPEN_CMD = xdg-open
# else
# 	FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
# 	OPEN_CMD = open
# endif
#
# all: clean $(PROJECT).a
#
# $(PROJECT).a:
# 	$(CC) -c s21*.c
# 	ar -crs $(PROJECT).a s21_*.o
# 	
# test: clean $(PROJECT).a
# 	$(CC) -g $(TESTS) $(PROJECT).a $(FLAGS) -o test
# 	./test
#
# valgrind: test
# 	CK_FORK=no valgrind --tool=memcheck ./test
#
# gcov_report: clean
# 	$(CC) $(TESTS) s21*.c $(FLAGS) -o test
# 	./test
# 	lcov -t "./test" -o report.info --no-external -c -d .
# 	genhtml -o report report.info
# 	$(OPEN_CMD) ./report/index.html
# 	rm -rf *.gcno *gcda *.gco
#
# clean:
# 	rm -rf *.o $(PROJECT).a test *.dSYM *.gcno *gcda *.gcov gcov report report.info
#
# clang:
# 	clang-format -style=Google -n *.c *.h
