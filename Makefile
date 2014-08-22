osm: clean parsehellosm.cpp
	g++ parsehellosm.cpp -o osm
	./osm
	./osm abcd
	./osm hella
	./osm q;
	./osm \;
	./osm hi hello how r u
	
.PHONY: clean
clean :
	rm -f osm
