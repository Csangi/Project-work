all: mydriver.x driver.x
mydriver.x: mydriver.cpp tvector.hpp
	g++ -Wall -std=c++11 -o mydriver.x mydriver.cpp
driver.x: driver.cpp tvector.hpp
	g++ -Wall -std=c++11 -o driver.x driver.cpp
clean:
	rm -f *.o *.x core.*
