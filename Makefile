# Создание директории build, если она не существует
CC = g++

CFLAGS = -Wall -Wextra -std=c++20

all:
# Сборка объектных файлов
	mkdir -p build
	$(CC) $(CFLAGS) -c src/dataparser.cpp -o build/dataparser.o
	$(CC) $(CFLAGS) -c src/datatypes.cpp -o build/datatypes.o
	$(CC) $(CFLAGS) -c src/eventsprocessing.cpp -o build/eventsprocessing.o
	$(CC) $(CFLAGS) -c app/main.cpp -o build/main.o
	g++ build/dataparser.o build/datatypes.o build/eventsprocessing.o build/main.o -o task


# Очистка: удаление объектных файлов и исполняемого файла
clean:
	rm -f task
	rm -rf build

.PHONY: all clean