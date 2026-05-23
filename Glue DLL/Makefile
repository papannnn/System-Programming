TARGET:exe

exe:application.o libdll.a
	g++ application.o -L . libdll.a -o exe

dll.o:dll.cpp dll.hpp
	g++ -c -o dll.o -I . dll.cpp

libdll.a:dll.o
	ar rs libdll.a dll.o

application.o:application.cpp
	g++ -I . -c -o application.o application.cpp

clean:
	rm dll.o
	rm libdll.a
	rm application.o
	rm exe