CXX=g++
CXXFLAGS=-Wall # -DDEBUG
DEPS=Makefile

bytes: bytes.o
	$(CXX) $^ -o bytes

%.o: %.cpp %.h $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o
