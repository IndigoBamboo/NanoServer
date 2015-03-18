CXX = clang++

INCLUDEDIRS = -I ./include

CXXFLAGS = $(INCLUDEDIRS)

LDFLAGS = -L ./ -lraknet 

SRC = 	main.cpp\
	Lobby.cpp

OBJ = $(SRC:.cpp=.o)

EXEC = test

$(EXEC) :	$(OBJ)
		$(CXX) -o $(EXEC) $(OBJ) $(LDFLAGS)

all :	$(EXEC)

clean :
	@rm -f $(OBJ)

mrproper :	clean
		@rm -f $(EXEC)

.PHONY :	all clean mrproper
