# Define the compiler and the flags
CC = gcc
CFLAGS = -O0 -g -Wall -Wextra -Werror -lm

# Define the directory paths for source, include, client, binary, and objects
SOURCEDIR = source
INCLUDEDIR = include
CLIENTDIR = client
BINARYDIR = binary
OBJECTDIR = objects
LIBDIR = library

# Find all the source files in the source and client directories
SOURCES = $(wildcard $(SOURCEDIR)/*.c $(CLIENTDIR)/*.c)

# Create object files for each source file in the source directory
OBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(OBJECTDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c))

# Define the names of the executables
EXECUTABLE1 = nlprog1
EXECUTABLE2 = nlprog2

all: directories nlprog.a $(EXECUTABLE1) $(EXECUTABLE2)

# Create the directories for binary and objects if they do not exist
directories:
	mkdir -p $(BINARYDIR) $(OBJECTDIR) $(LIBDIR)

nlprog.a: $(OBJECTS)
	ar rcs $(LIBDIR)/nlprog.a $(OBJECTS)

# Link the object files for each executable
$(EXECUTABLE1): $(OBJECTDIR)/main1.o $(LIBDIR)/nlprog.a
	$(CC) $(OBJECTDIR)/main1.o -o $(EXECUTABLE1) -L. $(LIBDIR)/nlprog.a $(CFLAGS)

$(EXECUTABLE2): $(OBJECTDIR)/main2.o $(LIBDIR)/nlprog.a
	$(CC) $(OBJECTDIR)/main2.o -o $(EXECUTABLE2) -L. $(LIBDIR)/nlprog.a $(CFLAGS)

# Compile the object files for each source file in the source directory
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

# Compile the object files for the main1 and main2 files in the client directory
$(OBJECTDIR)/main1.o: $(CLIENTDIR)/main1.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

$(OBJECTDIR)/main2.o: $(CLIENTDIR)/main2.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDEDIR)

# Clean up the project
clean:
	rm -rf $(BINARYDIR) $(OBJECTDIR) $(EXECUTABLE1) $(EXECUTABLE2) $(LIBDIR)
