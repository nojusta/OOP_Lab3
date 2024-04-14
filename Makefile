# Kompiliatorius
CXX = g++

# Kompiliatoriaus parametrai
CXXFLAGS = -std=c++14 -O3

# Vykdymo failo pavadinimas
TARGET = v1_1

# Šaltinio failai
SRCS = main.cpp functionality.cpp input.cpp calculations.cpp student.cpp

# Objektų failai
OBJS = $(SRCS:.cpp=.o)

# Taisyklė programa susieti
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Taisyklė kompiliuoti šaltinio failus
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

# Taisyklė išvalyti tarpinius failus
clean:
	$(RM) $(OBJS)

# Taisyklė išvalyti viską
distclean: clean
	$(RM) $(TARGET)