TARGET = tp2
OBJECTS = registro.o arquivo.o resolucao.o main.o
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
TMP = ./tmp/
default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	-mkdir -p $(TMP)

registro.o: registro.c registro.h
	$(CC) $(CFLAGS) -c registro.c

arquivo.o: arquivo.c arquivo.h registro.h
	$(CC) $(CFLAGS) -c arquivo.c

resolucao.o: resolucao.c resolucao.h arquivo.h registro.h
	$(CC) $(CFLAGS) -c resolucao.c

main.o: main.c resolucao.h
	$(CC) $(CFLAGS) -c main.c

clean:
	-rm -f *.o

cleantmp:
	-rm -f $(TMP)/*