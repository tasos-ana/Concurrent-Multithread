CC = gcc
  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
LIBS = -pthread

  # the build target executable:
default: prog clean_o

prog: main.o client.o updater.o utils.o stack.o list.o
	$(CC) $(CFLAGS) -o prog main.o client.o updater.o utils.o stack.o list.o $(LIBS)
 
main.o: ../src/main.c ../src/utils.h ../src/client.h ../src/updater.h ../src/stack.h
	$(CC) $(CFLAGS) -c ../src/main.c

client.o: ../src/client.c ../src/client.h ../src/stack.h ../src/utils.h
	$(CC) $(CFLAGS) -c ../src/client.c

updater.o: ../src/updater.c ../src/updater.h ../src/utils.h
	$(CC) $(CFLAGS) -c ../src/updater.c

utils.o: ../src/utils.c ../src/utils.h
	$(CC) $(CFLAGS) -c ../src/utils.c

stack.o: stack.c ../src/stack.h ../src/utils.h
	$(CC) $(CFLAGS) -c stack.c

list.o: list.c ../src/list.h
	$(CC) $(CFLAGS) -c list.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) prog *.o *~

clean_o: 
	$(RM) *.o *~