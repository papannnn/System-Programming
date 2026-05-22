TARGET:exe

exe:application.o libdll.a
	g++ application.o -L . libdll.a -o exe

dll.o:dll.hpp dll.cpp
	g++ -c -I . dll.cpp -o dll.o

dll_util.o:dll.hpp dll_util.cpp
	g++ -c -I . dll_util.cpp -o dll_util.o

libdll.a:dll.o dll_util.o
	ar rs libdll.a dll.o dll_util.o

application.o:application.cpp libdll.a
	g++ -c -I . application.cpp -o application.o

clean:
	rm application.o
	rm dll.o
	rm dll_util.o
	rm libdll.a
	rm exe