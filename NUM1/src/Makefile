.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

NAME = main

EXEC = $(NAME).x
OBJ = $(NAME).o

LFLAGS = -lm

CO = g++
LD = $(CO)

.PHONY: %.o
%.o: %.cpp %.h
	@$(CO) -c $<
.PHONY: %.o
%.o: %.cpp
	@$(CO) -c $<

$(EXEC): $(OBJ1)
	@$(LD) -o $@ $(NAME).cpp $(LFLAGS) $^

.PHONY: all
all: $(EXEC)
 
.PHONY: run
run: $(EXEC)  
	./$(EXEC)

.PHONY: clean tar 
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))
