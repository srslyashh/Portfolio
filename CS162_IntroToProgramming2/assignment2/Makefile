
CC = g++
BIN = driver
ARG = --std=c++11 -g

All: $(BIN)

$(BIN): Driver.o Card.o Deck.o Hand.o Game.o Player.o
	$(CC) $(ARG) Driver.o Card.o Deck.o Hand.o Game.o Player.o -o ass2

Driver.o: Driver.cpp
	$(CC) $(ARG) -c Driver.cpp

Card.o: Card.cpp Card_hf.hpp
	$(CC) $(ARG) -c Card.cpp

Deck.o: Deck.cpp Deck_hf.hpp
	$(CC) $(ARG) -c Deck.cpp

Hand.o: Hand.cpp Hand_hff.hpp
	$(CC) $(ARG) -c Hand.cpp

Game.o: Game.cpp Game_hf.hpp
	$(CC) $(ARG) -c Game.cpp

Player.o: Player.cpp Player_hf.hpp
	$(CC) $(ARG) -c Player.cpp

clean:
	rm –f *.out *.o $(BIN)
