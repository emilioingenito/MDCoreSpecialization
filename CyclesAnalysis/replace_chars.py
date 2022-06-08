#input file
fin = open("/home/emilio/ACAProjC/CyclesAnalysis200Atoms_03/cyclesO3.txt", "rt")
#output file to write the result to
fout = open("/home/emilio/ACAProjC/CyclesAnalysis200Atoms_03/cycles03formatted.txt", "wt")
#for each line in the input file
for line in fin:
	#read replace the string and write to output file
	fout.write(line.replace('r ', 'r1'))
#close input and output files
fin.close()
fout.close()