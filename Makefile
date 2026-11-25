FLAGS = -g -DFIBTYPE=double 

main: util.o display.o main.o 
	g++ main.o util.o display.o $(FLAGS) -o main 

clean:
	rm *.o 

main.o: main.cc display.o util.o 
	g++ main.cc -c $(FLAGS) -o main.o 

#util.o updates whenever any of graph's supports are changed, and that cascades to main* 
util.o: util.h util.cc graph.h array.h list.h queues.h 
	g++ util.cc -c $(FLAGS) -o util.o 

display.o: display.cc display.h colors.h 
	g++ display.cc -c $(FLAGS) -o display.o 
