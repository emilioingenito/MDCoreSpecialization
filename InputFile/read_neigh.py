with open('/home/emilio/ACAProjC/InputFile/source_neigh.txt','r') as source, open('/home/emilio/ACAProjC/InputFile/neigh_data.h','w') as dest, open('/home/emilio/MD/miniMD/ref/neighbors.txt') as data:
           
    #first line -- save maxneighs
    sr = source.readline().split("#")[0]
    dt = data.readline().rstrip('\n')
    maxneighs = 2
    dest.write(sr+str(maxneighs)+";\n")
    #second line -- save nmax
    sr = source.readline().split("#")[0]
    dt = data.readline().rstrip('\n')
    nmax = int(dt)
    dest.write(sr+dt+";\n")
    #save arrays
    nu = "int* f_numneigh = malloc (f_nmax * sizeof(int));\n"
    ne = "int* f_neighbors = malloc (f_nmax * f_maxneighs * sizeof(int));\n"
    dest.write(nu)
    dest.write(ne)
    #save each element of arrays
    loop_range = (nmax*maxneighs)
    for i in range(nmax):
        dest.write("f_numneigh["+str(i)+"] = "+data.readline().rstrip('\n')+";\n")
    for i in range(loop_range):
        dest.write("f_neighbors["+str(i)+"] = "+data.readline().rstrip('\n')+";\n")

source.close()
dest.close()
data.close()


