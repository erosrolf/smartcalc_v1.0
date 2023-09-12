TARGET = stacknode
CC = gcc -Wall -Wextra -Werror -std=c11 
CFLAGS =
LIBS =

PREF_SRC = ./backend/
PREF_OBJ = ./obj/

SRCS = $(wildcard $(PREF_SRC)*.c)
OBJS = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm $(TARGET) $(PREF_OBJ)*.o
