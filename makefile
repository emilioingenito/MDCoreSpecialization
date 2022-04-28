CXX = gcc
CXXFLAGS = -g

CCR = riscv64-unknown-elf-gcc
LINKR = riscv64-unknown-elf-gcc

#CCRFLAGS = -static -fno-common -fno-builtin-printf -fno-use-cxa-atexit -specs=htif_nano.specs -O3 -I./
#LINKRFLAGS = -static -specs=htif_nano.specs -O3
CCRFLAGS = -fno-builtin-printf -specs=htif_nano.specs -fno-common 
LINKRFLAGS = -static -specs=htif_nano.specs
EXEC = main
EXECR = mainrisc

OBJS =  main.o function.o
OBJR =  main.riscv.o function.riscv.o 
INC = atom.h function.h neighbor.h types.h

#regola:
#	python3 ...
#	$(EXEC)

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

main.riscv.o: main.c
	${CCR} ${CCRFLAGS} -c main.c

function.riscv.o: function.c
	${CCR} ${CCRFLAGS} -c function.c	


link: $(OBJS)
	$(LINKR) $(LINKRFLAGS) $(OBJS) -o $(EXECR).riscv 
	@if [ ! -d CompileRISCV ]; then mkdir CompileRISCV; fi
	@mv $(OBJS) CompileRISCV;

$(OBJS): $(INC)

clean:
	rm -f -r Compile CompileRISCV main mainrisc.riscv *.o