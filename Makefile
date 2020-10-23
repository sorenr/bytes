CXX=g++
CXXFLAGS=-Iinclude # -DDEBUG
DEPS=Makefile

test: bytes.cpp
	$(CXX) $^ -o bytes

%.o: %.cpp %.h $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o
