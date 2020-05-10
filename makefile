all: Gambling_Trail clean

Gambling_Trail: map1.cpp combat.o slots.o Memorize_Bananza.o flip_the_ladder.o hi_lo.o
	g++ map1.cpp combat.o slots.o Memorize_Bananza.o flip_the_ladder.o hi_lo.o -o Gambling_Trail

combat.o: combat.cpp character.cpp Enemies.txt Players.txt 
	g++ -c combat.cpp

slots.o: slots.cpp
	g++ -c slots.cpp

Memorize_Bananza.o: Memorize_Bananza.cpp
	g++ -c Memorize_Bananza.cpp

flip_the_ladder.o: flip_the_ladder.cpp
	g++ -c flip_the_ladder.cpp

hi_lo.o: hi_lo.cpp
	g++ -c hi_lo.cpp

clean: 
	rm -f *.o

.PHONY: clean