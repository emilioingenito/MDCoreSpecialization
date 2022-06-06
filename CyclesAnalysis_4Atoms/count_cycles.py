with open('/home/emilio/ACAProjC/CyclesAnalysis_200Atoms/cycle200.txt','r') as source:

    #var to count the number of instruction of the type specified by the user
    count = 0
    #var to store the total number of cycles
    cycles = 0
    #bool var to know if need to make the sub
    need = False
    #var to store the previous number
    prev = 0
    #static variables
    tot_cycles = 373988
    tot_instr = 195085
    #var to store the type of instruction
    instr = input("Insert the name of the instruction: ") 
    min_c = 300   
  
    #loop the whole file
    for line in source:
        words = line.split()
        if (need):
            count += 1
            cur_cycle = int(words[1])
            cur_upd = cur_cycle - prev
            cycles += cur_upd

            if( (cur_upd < min_c) and (cur_upd > 0)):
                min_c = int(words[1]) - prev
        
        cur_instr = words[8].strip().split(".")
        if(instr == cur_instr[0]):
            need = True
        elif((len(cur_instr) > 1) and instr == cur_instr[1]):
            need = True
        else:
            need = False
        prev = int(words[1])
            

    #print summary
    print("Cycle analysis performed for instruction ["+instr+"] : \n")
    print("cycles = [" + str(cycles) + "]\n")
    print("number of instructions = [" + str(count) + "]\n")
    print("min_cycles = [" + str(min_c) + "]\n")
    if (count != 0):
        print("### cycles/instructions = [" + str(round((cycles/count),1)) + "]\n")
        print("### cycles/TOT cycles = [" + str(round((cycles*100/tot_cycles),1)) + "%]\n")
        print("### occurrencies/TOT instructions = [" + str(round((count*100/tot_instr),1)) + "%]\n\n")



