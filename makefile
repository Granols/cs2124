rns:	node.o	 rns.c	sim.o
		gcc rns.c node.o sim.o -o rns
node.o:	node.c
		gcc -c  node.c -o node.o
sim.o:	sim.c
		gcc -c sim.c -o sim.o
clean:
		rm -f *.o
		rm -f rns
	
