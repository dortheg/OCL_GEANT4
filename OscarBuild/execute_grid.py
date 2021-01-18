import os
import numpy as np
from subprocess import Popen, PIPE, call

#Do this first time, else Geant4 will not run
#Cannot get script to run it, " scl enable devtoolset-8 "bash" "
#call(["scl", "enable", "devtoolset-8", "bash"])

#Create energy grid
energy_grid = np.arange(50, 10010, 10)
N = 10000

for i in range(len(energy_grid)):

    print("Now simulating energy %.d out of %.d" % (i, len(energy_grid)))
    
    #Create executeable file 
    infile=open("grid_sim.mac", "w")

    infile.write("/control/execute exp_setup_actinides_2018.mac")
    infile.write("\n")

    infile.write("/run/initialize")
    infile.write("\n")

    infile.write("/gps/particle gamma")
    infile.write("\n")
    infile.write("/gps/number 1")
    infile.write("\n")

    infile.write("/gps/pos/type Plane")
    infile.write("\n")
    infile.write("/gps/pos/shape Ellipse")
    infile.write("\n")
    infile.write("/gps/pos/centre 0. 0. 0. mm")
    infile.write("\n")
    infile.write("/gps/pos/halfx 0.75 mm")
    infile.write("\n")
    infile.write("/gps/pos/halfy 1.25 mm")
    infile.write("\n")

    energy_string = "/gps/energy " + str(energy_grid[i]) + " keV"
    infile.write(energy_string)
    infile.write("\n")
    infile.write("/gps/ang/type iso")
    infile.write("\n")
    
    filename_string = "/OCL/setOutName grid_for_response/grid_" + str(int(energy_grid[i]))+"keV_n" + str(N) + ".root"

    infile.write(filename_string)
    infile.write("\n")

    N_str = "/run/beamOn " + str(N)
    infile.write(N_str)

    infile.close()

    call(["./OCL", "grid_sim.mac"])
