all: proj5.x sproj5.x
sproj5.x: sproj5.cpp hashtable.hpp passserver.o
	g++ -Wall -std=c++11  -lcrypt -o sproj5.x sproj5.cpp
proj5.x: proj5.cpp hashtable.hpp passserver.o
	g++ -Wall -std=c++11  -lcrypt -o proj5.x proj5.cpp
passserver.o: passserver.cpp passserver.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp
clean:
	rm -f *.o *.x core.*