SOURCE   := main.cpp
CXXFLAGS := -std=c++20
INCLUDE  := -I/usr/local/include -L/usr/local/lib -lusb-1.0
EXE      := program
.PHONY:
	build clean

build: 
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(EXE) $(INCLUDE)

clean:
	rm -f $(EXE)
