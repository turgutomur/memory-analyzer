CC = gcc
CFLAGS = -Wall -Wextra -g -I./src/common


SRC1 = src/q1/main.c src/q1/memory_analyzer.c src/q1/proc_parser.c src/q1/leak_detector.c src/common/utils.c
OBJ1 = $(SRC1:.c=.o)
CFLAGS1 = $(CFLAGS) -I./src/q1


SRC2 = src/q2/main.c src/q2/code_parser.c src/q2/security_checker.c src/q2/recommender.c src/common/utils.c
OBJ2 = $(SRC2:.c=.o)
CFLAGS2 = $(CFLAGS) -I./src/q2


all: app1 app2


app1: $(OBJ1)
	$(CC) $(CFLAGS1) -o app1 $(OBJ1)

src/q1/%.o: src/q1/%.c
	$(CC) $(CFLAGS1) -c $< -o $@


app2: $(OBJ2)
	$(CC) $(CFLAGS2) -o app2 $(OBJ2)

src/q2/%.o: src/q2/%.c
	$(CC) $(CFLAGS2) -c $< -o $@


src/common/%.o: src/common/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/q1/*.o src/q2/*.o src/common/*.o app1 app2

.PHONY: all clean