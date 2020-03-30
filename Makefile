exe: main.o curvature.o 
	g++ -o exe.o main.o curvature.o -std=c++11 -I/usr/include/python2.7 -lpython2.7

main.o: main.cpp ./include/data_type.h
	g++ -c main.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7

curvature.o: curvature.cpp ./include/data_type.h
	g++ -c curvature.cpp -std=c++11 

clean:
	rm -rf *.o 