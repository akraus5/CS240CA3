#TODO
#
# Specifiy the target

all: LLC

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
LLC: main.o
	g++ main.o -o LLC

# Specify how the object files should be created from source files
main.o: main.cpp
	g++ -g -c main.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-cor 1
#mpile the whole thing
clean:
	rm -f *.o LLC
