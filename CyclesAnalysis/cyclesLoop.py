with open('/home/emilio/ACAProjC/CyclesAnalysis/200Atoms_O3/cycles03formatted.txt','r') as source, open('/home/emilio/ACAProjC/CyclesAnalysis/200Atoms_O3/disassMainInnerO3.txt','r') as source2:

    #var to count the number of instruction of the type specified by the user
    count = 0
    #var to store the total number of cycles
    cycles = 0
    #bool var to know if need to make the sub
    need = False
    #var to store the previous number
    prev = 0
    #static variables
    tot_cycles = 160059
    tot_instr = 69490
    #var to store the type of instruction
    instr = input("Insert the name of the instruction: ") 
    min_c = 300  
    #know the range
    max_cc = 146396
    min_cc = 110102 
    
    list_pc = []

    for line in source2:
        words = line.split()
        list_pc.append(words[0])

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
        curr_pc = ((words[3])[12:])[:8]
        curr_cc = int(words[1])
        if((curr_cc > min_cc) and (curr_cc < max_cc) and (curr_pc in list_pc)):
            if(instr == cur_instr[0]):
                need = True
            elif((len(cur_instr) > 1) and instr == cur_instr[1]):
                need = True
            else:
                need = False
        else:
            need = False
        prev = int(words[1])
            

    #print summary
    print("cycles = [" + str(cycles) + "]\n")
    print("number of instructions = [" + str(count) + "]\n")



