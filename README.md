# Abstract

Aim of this project was to analyze and optimize a portion of code belonging to
miniMD, a micro-application for molecular dynamics simulation. In particular, we
decided to extrapolate the function called compute original, which deals with the
computation of all the forces among each atom and its neighbors. Once correctly
isolated the function, we exploited the chipyard framework to simulate, test and
benchmark it. This work was was carried out through Verilator, an open source
RTL simulator, which enabled us to test and simulate our piece of code with dif-
ferent RTL generators, such as Rocket Chip. Taking advantage of the possible
customization that this framework allows, we modified its components: the main
customization was made with regard to the core, as we simulated Rocket Chip with
Rocket Core and the Berkeley Out-Of-Order Machine(BOOM). By analyzing and
accurately modifying the parameters of the simulation, we were able to reduce the
clock cycles needed to execute the core functionality of our function by more than 75%.

------------------------------------------------------------------------------------

Please refer to [link](/Report.pdf) for a detailed report of the project.
