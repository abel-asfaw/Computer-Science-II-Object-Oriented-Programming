CXX = g++
CXXFLAGS = -Wall

proj4: Room.o Game.o proj4.cpp Entity.o Character.o Monster.o Paladin.o Rogue.o Wizard.o BabyDragon.o Goblin.o Skeleton.o
	$(CXX) $(CXXFLAGS) Room.o Game.o Entity.o Character.o Monster.o Paladin.o Rogue.o Wizard.o BabyDragon.o Goblin.o Skeleton.o proj4.cpp -o proj4

BabyDragon.o: BabyDragon.h BabyDragon.cpp Monster.o Entity.o
	$(CXX) $(CXXFLAGS) -c BabyDragon.cpp

Goblin.o: Goblin.h Goblin.cpp Monster.o Entity.o
	$(CXX) $(CXXFLAGS) -c Goblin.cpp

Skeleton.o: Skeleton.h Skeleton.cpp Monster.o Entity.o
	$(CXX) $(CXXFLAGS) -c Skeleton.cpp

Monster.o: Monster.h Monster.cpp Entity.o
	$(CXX) $(CXXFLAGS) -c Monster.cpp

Wizard.o: Wizard.h Wizard.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Wizard.cpp

Rogue.o: Rogue.h Rogue.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Rogue.cpp

Paladin.o: Paladin.h Paladin.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Paladin.cpp

Charater.o: Character.h Character.cpp Entity.o
	$(CXX) $(CXXFLAGS) -c Character.cpp

Entity.o: Entity.h Entity.cpp
	$(CXX) $(CXXFLAGS) -c Entity.cpp

Game.o: Game.h Game.cpp Room.o Entity.o Character.o Monster.o Paladin.o Rogue.o Wizard.o BabyDragon.o Goblin.o Skeleton.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

Room.o: Room.h Room.cpp
	$(CXX) $(CXXFLAGS) -c Room.cpp

run1:
	./proj4 map1_data.txt

run2:
	./proj4 map2_data.txt

val1:
	valgrind ./proj4 map1_data.txt

val2:
	valgrind ./proj4 map2_data.txt

clean:
	rm *o