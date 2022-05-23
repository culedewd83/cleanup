CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g
LDFLAGS = -fsanitize=address
LBLIBS = -lstdc++fs

SRC = main.cpp cleanup.cpp
EXEC = cleanup

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRC) -o $@ $(LBLIBS)

clean:
	rm -rf $(EXEC)