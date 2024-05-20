# Kompiliatorius
CXX = g++

# Kompiliatoriaus parametrai
CXXFLAGS = -std=c++20 -O3 -mmacosx-version-min=14.3

# Vykdomo failo pavadinimas
TARGET = v3

# Source failai
SRCS = main.cpp functionality.cpp input.cpp calculations.cpp student.cpp

# Object failai
OBJS = $(SRCS:.cpp=.o)

# Google Test biblioteka
GTEST = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a

# Bibliotekos
LIBS = $(GTEST)

# Testuojami failai
TEST_SRCS = myVector_test.cpp student_test.cpp

# Testuojami objekto failai
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Testuojamo failo pavadinimas
TEST_TARGET = myVector_test student_test

# Taisyklė programa susieti
$(TARGET): $(OBJS) libmyVectorWrapper.dylib
	$(CXX) $(CXXFLAGS) -L. -lmyVectorWrapper -o $(TARGET) $(OBJS)

# Taisyklė bibliotekai sukurti
libmyVectorWrapper.dylib: myVector.o
	$(CXX) $(CXXFLAGS) -dynamiclib -o libmyVectorWrapper.dylib myVector.o

# Taisyklė testams susieti
myVector_test: student.o myVector_test.o
	$(CXX) $(CXXFLAGS) -o myVector_test student.o myVector_test.o $(LIBS)

student_test: student.o student_test.o
	$(CXX) $(CXXFLAGS) -o student_test student.o student_test.o $(LIBS)

# Taisyklė kompiliuoti failus
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

# Taisyklė išvalyti tarpinius failus
clean:
	$(RM) $(OBJS) $(TEST_OBJS) libmyVectorWrapper.dylib

# Taisyklė išvalyti viską
distclean: clean
	$(RM) $(TARGET) myVector_test student_test libmyVectorWrapper.dylib