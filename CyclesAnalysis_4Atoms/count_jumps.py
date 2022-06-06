with open('/home/emilio/ACAProjC/CyclesAnalysis/cycles_out.txt','r') as source, open('/home/emilio/ACAProjC/CyclesAnalysis/jumps.txt','w') as dest:

    #var to count the number of jumps found
    count = 0
    #var to store the previous cc
    prev_cc = 0
    #var to store the previous line
    prev_line = ""
  
    dest.write("Count number of jumps in the file considering 'n' as size of the jump\n")
    n = int(input("Please insert an integer n to be considered as jump size: "))
    dest.write("The parameter is : " + str(n) + "\n\n\n")

    #loop the whole file
    for line in source:
        words = line.split()
        if ((int(words[1]) - prev_cc) > n):
            dest.write("\n" + prev_line + line + "\n--------------------------------------------------------------------")
            count += 1
        prev_line = line
        prev_cc = int(words[1])
            
       
    #print summary
    dest.write("\nNumber of jumps detected: [" + str(count) + "]\n\n")



