# Kompiliatorius
CXX = g++

# Kompiliatoriaus parametrai
CXXFLAGS = -std=c++14 -O3 -mmacosx-version-min=14.3 -arch arm64

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
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Creating app bundle..."
	@mkdir -p lab3.app/Contents/MacOS
	@mkdir -p lab3.app/Contents/Resources
	@cp $(TARGET) lab3.app/Contents/MacOS/
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > lab3.app/Contents/Info.plist
	@echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> lab3.app/Contents/Info.plist
	@echo '<plist version="1.0">' >> lab3.app/Contents/Info.plist
	@echo '<dict>' >> lab3.app/Contents/Info.plist
	@echo '  <key>CFBundleExecutable</key>' >> lab3.app/Contents/Info.plist
	@echo '  <string>v3_launcher.sh</string>' >> lab3.app/Contents/Info.plist
	@echo '  <key>CFBundleIconFile</key>' >> lab3.app/Contents/Info.plist
	@echo '  <string>icon.icns</string>' >> lab3.app/Contents/Info.plist
	@echo '  <key>CFBundleIdentifier</key>' >> lab3.app/Contents/Info.plist
	@echo '  <string>com.vilniaus-universitetas.lab3</string>' >> lab3.app/Contents/Info.plist
	@echo '  <key>CFBundleName</key>' >> lab3.app/Contents/Info.plist
	@echo '  <string>lab3</string>' >> lab3.app/Contents/Info.plist
	@echo '  <key>CFBundleVersion</key>' >> lab3.app/Contents/Info.plist
	@echo '  <string>3.0</string>' >> lab3.app/Contents/Info.plist
	@echo '</dict>' >> lab3.app/Contents/Info.plist
	@echo '</plist>' >> lab3.app/Contents/Info.plist
	@cp v3_launcher.sh lab3.app/Contents/MacOS/
	@chmod +x lab3.app/Contents/MacOS/v3_launcher.sh

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
	$(RM) $(OBJS) $(TEST_OBJS)
	@rm -rf lab3.app

# Taisyklė išvalyti viską
distclean: clean
	$(RM) $(TARGET) myVector_test student_test
