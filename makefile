# Define the compiler and the flags
CC = gcc
CFLAGS = -O0 -g -Wall -Wextra -lm

# Define the directory paths for source, include, client, binary, and objects
SOURCEDIR = source
INCLUDEDIR = include
CLIENTDIR = client
BINARYDIR = binary
OBJECTDIR = objects

# Find all the source files in the source and client directories
SOURCES = $(wildcard $(SOURCEDIR)/*.c $(CLIENTDIR)/*.c)

# Create object files for each source file in the source directory
OBJECTS1 = $(patsubst $(SOURCEDIR)/%.c, $(OBJECTDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c)) $(OBJECTDIR)/main1.o
OBJECTS2 = $(patsubst $(SOURCEDIR)/%.c, $(OBJECTDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c)) $(OBJECTDIR)/main2.o
OBJECTS3 = $(patsubst $(SOURCEDIR)/%.c, $(OBJECTDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c)) $(OBJECTDIR)/main3.o

# Define the names of the executables
EXECUTABLE1 = nlprog1
EXECUTABLE2 = nlprog2
EXECUTABLE3 = nlprog3

all: directories $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

# Create the directories for binary and objects if they do not exist
directories:
	mkdir -p $(BINARYDIR) $(OBJECTDIR)

# Link the object files for each executable
$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $^ -o $(EXECUTABLE1) $(CFLAGS)

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $^ -o $(EXECUTABLE2) $(CFLAGS)

$(EXECUTABLE3): $(OBJECTS3)
	$(CC) $^ -o $(EXECUTABLE3) $(CFLAGS)

# Compile the object files for each source file in the source directory
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

# Compile the object files for the main1, main2, and main3 files in the client directory
$(OBJECTDIR)/main1.o: $(CLIENTDIR)/main1.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

$(OBJECTDIR)/main2.o: $(CLIENTDIR)/main2.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

$(OBJECTDIR)/main3.o: $(CLIENTDIR)/main3.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

# Clean up the project
clean:
	rm -rf $(BINARYDIR) $(OBJECTDIR) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)