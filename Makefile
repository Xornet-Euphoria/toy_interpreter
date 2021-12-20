CC = gcc
PRG = interpreter
OBJ = interpreter.c tokenize.c

$(PRG): $(OBJ)
	$(CC) -o $@ $^

clean:
	$(RM) $(PRG)