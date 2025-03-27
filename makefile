
main:
	g++ \
	./src/main.cpp ./src/Game.cpp \
	-I./include \
	-std=c++17 -lSDL2 -lSDL2main -fext-numeric-literals -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -o ./build/main
	./build/main

clean:
	rm build/*
