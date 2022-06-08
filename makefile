CXX = gcc
CXXFLAGS = -g

CCR = riscv64-unknown-elf-gcc -O3
LINKR = riscv64-unknown-elf-gcc

CCRFLAGS = -fno-common -fno-builtin-printf -specs=htif_nano.specs 
LINKRFLAGS = -static -specs=htif_nano.specs

EXEC = main
EXECR = mainrisc

OBJS =  main.o function.o print.o
OBJR =  main.riscv.o function.riscv.o print.riscv.o
INC = types.h atom.h function.h print.h

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
	@if [ ! -d Compile ]; then mkdir Compile; fi
	@mv $(OBJS) Compile;

$(EXECR): $(OBJR)
# $(CCR) $(CCRFLAGS) -o $(EXECR).riscv $(OBJS)
	$(MAKE) -f makefile link

main.o: main.c
	${CXX} ${CXXFLAGS} -c main.c

function.o: function.c
	${CXX} ${CXXFLAGS} -c function.c

print.o: print.c
	${CXX} ${CXXFLAGS} -c print.c

main.riscv.o: main.c
	${CCR} ${CCRFLAGS} -c main.c

function.riscv.o: function.c
	${CCR} ${CCRFLAGS} -c function.c

print.riscv.o: print.c
	${CCR} ${CCRFLAGS} -c print.c	

link: $(OBJS)
	$(LINKR) $(LINKRFLAGS) $(OBJS) -o $(EXECR).riscv 
	@if [ ! -d CompileRISCV ]; then mkdir CompileRISCV; fi
	@mv $(OBJS) CompileRISCV;

$(OBJS): $(INC)

input: 
	python3 InputFile/read_atom.py
	python3 InputFile/read_neigh.py

#	$(EXEC)

clean:
	rm -f -r Compile CompileRISCV main mainrisc.riscv *.o