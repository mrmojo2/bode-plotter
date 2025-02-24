build:
	g++ -Wall -I ./include -o ./bin/out ./src/*.cpp -lSDL2
run:
	./bin/out
