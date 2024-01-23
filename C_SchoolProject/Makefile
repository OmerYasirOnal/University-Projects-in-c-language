# Derleyiciyi tanımlama
CC=gcc

# Derleyici parametreleri
CFLAGS=-g -Wall

# Çalıştırılabilir dosya adı
TARGET=main

all: $(TARGET)

$(TARGET): main.o Project1.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o Project1.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

Project1.o: Project1.c Project1.h
	$(CC) $(CFLAGS) -c Project1.c

clean:
	rm -f $(TARGET) main.o Project1.o
