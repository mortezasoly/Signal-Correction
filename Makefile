# Compiler Setting
CXX = g++
CXXFLAGS = -std=c++11

# Setting the source and binary files

SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)

Data = ./Models/TimeSeriesData.cpp
Files_Third_Task = ./Models/Third_Task.cpp ./Models/MockFittedBackgroundModel.cpp
Files_Fourth_Task = ./Models/Fourth_Task.cpp ./Models/AverageDiscretizedModel.cpp

# Rules
all: Third_Task Fourth_Task

Third_Task: $(Files_Third_Task)
	$(CXX) $(CXXFLAGS) -o Third_Task $(Files_Third_Task) $(Data)
	
	
Fourth_Task: $(Files_Fourth_Task)
	$(CXX) $(CXXFLGAS) -o Fourth_Task $(Files_Fourth_Task) $(Data)

clean:
	rm -f Third_Task Fourth_Task


# Setting the independent commands
.PHONY: all clean



