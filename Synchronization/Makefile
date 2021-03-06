CC = gcc
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
LIBS = -pthread

# define file 
CLIENT_H = headers/client.h
CLIENT_C = source/client.c

UPDATER_H = headers/updater.h
UPDATER_C = source/updater.c

UTILS_H = headers/utils.h
UTILS_C = source/utils.c

STACK_H = headers/stack.h
STACK_C = source/stack.c

LIST_H = headers/list.h
LIST_C = source/list.c

STACKCG_C = StackCG/stackCG.c

STACKEL_C = StackCGWithElim/stackCGWithElim.c
STACKEL_H = StackCGWithElim/stackCGWithElim.h

LISTLAZY_C = ListLazySync/listLazySync.c
LISTLAZY_H = ListLazySync/listLazySync.h

LISTFG_C = ListFGSync/listFGSync.c

GENERAL_OBJECTS = .main.o .client.o .updater.o .utils.o .stack.o .list.o

GENERAL_OUTPUTS =  main.o client.o updater.o utils.o stack.o list.o

# the build target executable:
all: .stackCG_listLazy_compile .stackCG_listFG_compile .stackEl_listLazy_compile .stackEl_listFG_compile .clean_o
#-------------------------------------------------------------------------------

# the single build target:
stackCG_listLazy: .stackCG_listLazy_compile .clean_o

.stackCG_listLazy_compile: $(GENERAL_OBJECTS) .stackCG.o .listLazy.o
	$(CC) $(CFLAGS) -o stackCG_listLazy $(GENERAL_OUTPUTS) stackCG.o listLazy.o $(LIBS)
	
stackCG_listFG: .stackCG_listFG_compile .clean_o

.stackCG_listFG_compile: $(GENERAL_OBJECTS) .stackCG.o .listFG.o
	$(CC) $(CFLAGS) -o stackCG_listFG $(GENERAL_OUTPUTS) stackCG.o listFG.o $(LIBS)

stackEl_listLazy: .stackEl_listLazy_compile .clean_o

.stackEl_listLazy_compile:$(GENERAL_OBJECTS) .stackEl.o .listLazy.o
	$(CC) $(CFLAGS) -o stackEl_listLazy $(GENERAL_OUTPUTS) stackEl.o listLazy.o $(LIBS)

stackEl_listFG: .stackEl_listFG_compile .clean_o

.stackEl_listFG_compile:$(GENERAL_OBJECTS) .stackEl.o .listFG.o
	$(CC) $(CFLAGS) -o stackEl_listFG $(GENERAL_OUTPUTS) stackEl.o listFG.o $(LIBS)
#-------------------------------------------------------------------------------

#Create .o for 4 differed implementation of stack(2),list(2) 
.stackCG.o:$(STACKCG_C) $(STACK_H) $(UTILS_H)
	$(CC) $(CFLAGS) -o stackCG.o -c $(STACKCG_C)
	
.stackEl.o:$(STACKEL_C) $(STACKEL_H) $(STACK_H) $(UTILS_H)
	$(CC) $(CFLAGS) -o stackEl.o -c $(STACKEL_C)
	
.listLazy.o:$(LISTLAZY_C) $(LISTLAZY_H) $(LIST_H) $(UTILS_H) 
	$(CC) $(CFLAGS) -o listLazy.o -c $(LISTLAZY_C)
	
.listFG.o:$(LISTFG_C) $(LIST_H) $(UTILS_H)
	$(CC) $(CFLAGS) -o listFG.o -c $(LISTFG_C)
#-------------------------------------------------------------------------------

#Create the general .o that we need
.main.o: main.c $(UTILS_H) $(CLIENT_H) $(UPDATER_H) $(STACK_H) $(LIST_H)
	$(CC) $(CFLAGS) -c main.c

.client.o: $(CLIENT_C) $(CLIENT_H) $(STACK_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $(CLIENT_C)

.updater.o: $(UPDATER_C) $(UPDATER_H) $(STACK_H) $(LIST_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $(UPDATER_C)

.utils.o: $(UTILS_C) $(UTILS_H)
	$(CC) $(CFLAGS) -c $(UTILS_C)

.stack.o: $(STACK_C) $(STACK_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $(STACK_C)

.list.o: $(LIST_C) $(LIST_H) $(UPDATER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $(LIST_C)
#-------------------------------------------------------------------------------
 
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) stackCG_listLazy stackCG_listFG stackEl_listLazy stackEl_listFG *.o *~
#-------------------------------------------------------------------------------

.clean_o: 
	$(RM) *.o *~