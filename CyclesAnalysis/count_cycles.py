with open('/home/emilio/ACAProjC/CyclesAnalysis/cycles_out.txt','r') as source:

    #var to count the number of instruction of the type specified by the user
    count = 0
    #var to store the total number of cycles
    cycles = 0
    #bool var to know if need to make the sub
    need = False
    #var to store the previous number
    prev = 0
    #var to store the type of instruction
    instr = input("Insert the name of the instruction:")    
  
    #loop the whole file
    for line in source:
        words = line.split()
        if (need):
            count += 1
            cycles += int(words[1]) - prev
        if (instr in words[8]):
            need = True
            prev = int(words[1])
        else:
            need = False
    #print summary
    print("Cycle analysis performed for instructions containing ["+instr+"] : \n")
    print("cycles = [" + str(cycles) + "]\n")
    print("number of instructions = [" + str(count) + "]\n")
    print("### cycles/instructions = [" + str(cycles/count) + "]\n\n")



