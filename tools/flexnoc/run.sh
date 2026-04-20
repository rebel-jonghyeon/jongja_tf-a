gcc -c main_read.c -o  main_read.o
gcc -c main_write.c -o main_write.o
gcc -c shm_read.c -o   shm_read.o
gcc -c shm_write.c -o  shm_write.o
gcc -c control_bus.c -o  	control_bus.o
gcc -c pcie_bus.c -o  		pcie_bus.o
gcc -c error_logger.c -o 	error_logger.o
gcc main_read.o main_write.o shm_read.o shm_write.o pcie_bus.o control_bus.o error_logger.o -o errlog

