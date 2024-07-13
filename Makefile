CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS_MAIN = main.cpp Graph.cpp Algorithms.cpp
OBJS_MAIN = $(SRCS_MAIN:.cpp=.o)
SRCS_TEST = Test.cpp Test2.cpp Graph.cpp Algorithms.cpp
OBJS_TEST = $(SRCS_TEST:.cpp=.o)
DEPS = Graph.hpp Algorithms.hpp
TARGET_MAIN = my_program
TARGET_TEST = test_program
TARGET_TEST2 = test2_program
all: $(TARGET_MAIN) $(TARGET_TEST) $(TARGET_TEST2)
test: clean $(TARGET_TEST)
test2: clean $(TARGET_TEST2)


# Rule to build the main program
$(TARGET_MAIN): $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(OBJS_MAIN)

# Rule to build the test program
$(TARGET_TEST): $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(OBJS_TEST)

$(TARGET_TEST2): $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST2) $(OBJS_TEST)

# Rule to build object files for main program
main.o: main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

# Rule to build object files for tests
Test.o: Test.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o Test.o Test.cpp

Test2.o: Test2.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o Test2.o Test2.cpp

# Generic rule to build object files for shared sources
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to clean the build
clean:
	rm -f $(OBJS_MAIN) $(OBJS_TEST) $(TARGET_MAIN) $(TARGET_TEST) $(TARGET_TEST2)
