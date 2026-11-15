CC = gcc
CFLAGS = -Wall -Wextra -std=c99
FONTES = main.c entrada.c banker.c

banker: $(FONTES) banker.h
	$(CC) $(CFLAGS) -o banker $(FONTES)

clean:
	rm -f banker

.PHONY: clean