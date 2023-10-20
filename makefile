LIBCALC = lib_calc_c.a
CC = gcc -Wall -Werror -Wextra -std=c11 
CFLAGS = -c $(shell pkg-config --cflags check)
TEST_LIBS = $(shell pkg-config --libs check)

PREF_TESTS = ./tests/*.c
PREF_BACKEND = ./src/backend/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_BACKEND)*.c)
OBJ = $(patsubst $(PREF_BACKEND)%.c, $(PREF_OBJ)%.o, $(SRC))

all: clean $(LIBCALC)

$(LIBCALC): $(OBJ)
	ar rcs $(LIBCALC) $(OBJ)

$(PREF_OBJ)%.o: $(PREF_BACKEND)%.c
	$(CC) $(CFLAGS) $< -o $@

test: clean $(LIBCALC)
	$(CC) -g $(PREF_TESTS) $(LIBCALC) $(TEST_LIBS) -o test
	./test

clean:
	rm -rf $(LIBCALC) $(PREF_OBJ)*.o ./test.* ./test
