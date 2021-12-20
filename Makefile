CC = gcc
PRG = interpreter
OBJ = interpreter.c tokenize.c ast.c eval.c

$(PRG): $(OBJ)
	$(CC) -o $@ $^

clean:
	$(RM) $(PRG)