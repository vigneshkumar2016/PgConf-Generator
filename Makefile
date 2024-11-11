CC = gcc
CFLAGS = -Wall -g -Iinclude  # Add include directory to the search path

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

# Define object files with paths pointing to lib folder
OBJS = $(LIB_DIR)/main.o $(LIB_DIR)/config_generator.o $(LIB_DIR)/resource_check.o $(LIB_DIR)/defaults.o

all: pg_config_generator

pg_config_generator: $(OBJS)
	$(CC) $(CFLAGS) -o pg_config_generator $(OBJS)

# Compile each .c file into a .o file in the lib folder
$(LIB_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/config_generator.h $(INCLUDE_DIR)/resource_check.h $(INCLUDE_DIR)/defaults.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(LIB_DIR)/main.o

$(LIB_DIR)/config_generator.o: $(SRC_DIR)/config_generator.c $(INCLUDE_DIR)/config_generator.h $(INCLUDE_DIR)/resource_check.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/config_generator.c -o $(LIB_DIR)/config_generator.o

$(LIB_DIR)/resource_check.o: $(SRC_DIR)/resource_check.c $(INCLUDE_DIR)/resource_check.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/resource_check.c -o $(LIB_DIR)/resource_check.o

$(LIB_DIR)/defaults.o: $(SRC_DIR)/defaults.c $(INCLUDE_DIR)/defaults.h | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/defaults.c -o $(LIB_DIR)/defaults.o

# Ensure the lib directory exists
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	rm -f $(LIB_DIR)/*.o pg_config_generator