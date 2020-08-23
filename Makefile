CXX = g++
VERSION = -std=c++14
CFLAGS = -pedantic -Wall -Wextra $(VERSION)
LFLAGS = -Wall $(VERSION) 

INCS = GridFill.h
SRCS = GridFill.cpp \
	fill.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = fill

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@

# for Windows
clean:
	del *.o  $(EXEC).exe
	@echo clean done

# for UNIX / Linux 
remove:
	\rm -f *.o  $(EXEC)
	@echo clean done
