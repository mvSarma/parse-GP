osm: clean parsehellosm.cpp parsehellovec.cpp
	g++ parsehellosm.cpp -o osm
	
.PHONY: clean
clean :
	rm -f osm
