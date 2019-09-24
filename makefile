CC = gcc
DEBUG = -g
CFLAGS = -Wall $(DEBUG)
LDFLAGS = -Wall $(DEBUG)
EXEC = Tarea1
OBJS = Tarea1.o DirectoryHandler.o 
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $< -o $@

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)

Tarea1.o: Tarea1.c
	$(CC) $(CFLAGS) -c $<

DirectoryHandler.o: DirectoryHandler.c DirectoryHandler.h
	$(CC) $(CFLAGS) -c $<

Tarea: Tarea1.o DirectoryHandler.o 
	gcc Tarea1.o DirectoryHandler.o  -o Tarea

run:
	./Tarea
