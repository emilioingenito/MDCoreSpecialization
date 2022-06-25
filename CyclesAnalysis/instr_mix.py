with open('/home/emilio/ACAProjC/CyclesAnalysis/200Atoms_O3/disassMainInnerO3.txt','r') as source, open('/home/emilio/ACAProjC/CyclesAnalysis/200Atoms_O3/cycles03formatted.txt','r') as disass:

    max_cc = 146396
    min_cc = 110102

    #dictionary  PC -> (INSTR, #TIMES)
    dic = dict()
    #dictionary INTR, #TIMES
    final_dic = dict()

    for line in source:
        words = line.split()
        dic[words[0]] = (words[2],0)

    for line in disass:
        words = line.split()
        curr_pc = ((words[3])[12:])[:8]
        curr_cc = int(words[1])
        if curr_pc in dic:
            if( (curr_cc > min_cc) and (curr_cc < max_cc) ):
                instr = dic[curr_pc][0]
                times = dic[curr_pc][1]
                dic[curr_pc] = (instr, (times+1))

    for element in dic:
        instr = dic[element][0]
        times = dic[element][1]
        if instr in final_dic:
            final_dic[instr] += times
        else:
            final_dic[instr] = times

    tot = 0
    for element in final_dic:
        print(element +":\t\t#Inst=["+ str(final_dic[element])+"],\t\tClockCycles=[]")
        tot += final_dic[element]

    print (str(tot))