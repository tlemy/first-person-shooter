
main:
	g++ \
	./src/** ./lib/** \
	-std=c++17 \
	-I./include -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl \
	-o ./build/main

clean:
	rm build/*
