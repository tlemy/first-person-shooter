
main:
	g++ \
	./src/main.cpp ./src/Game.cpp ./src/SDL_Error.cpp \
	-I./include \
	-std=c++17 -lSDL2 -lSDL2main -fext-numeric-literals -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -Wshadow -o ./build/main
	./build/main

clean:
	rm build/*
