osm: clean parsehellosm.cpp
	g++ parsehellosm.cpp -o osm
	
.PHONY: clean
clean :
	rm -f osm
