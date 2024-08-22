CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lraylib -lm

OUTFILE = default

all:
	$(CC) $(CFLAGS) -o $(OUTFILE) main.c $(LDFLAGS)
 
outfile:
	@echo $(OUTFILE)

clean:
	rm $(OUTFILE)
