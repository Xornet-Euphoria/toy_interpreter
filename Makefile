CC = gcc
PRG = interpreter
TESTPRG = test_tokenize
OBJ = interpreter.c tokenize.c ast.c eval.c

$(PRG): $(OBJ)
	$(CC) -o $@ $^

clean:
	$(RM) $(PRG) $(TESTPRG)

test:
	$(CC) -o test_tokenize test_tokenize.c tokenize.c