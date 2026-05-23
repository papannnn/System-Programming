TARGET:exe

bitmap.o:bitmap.hpp bitmap.cpp
	g++ -c -I . bitmap.cpp -o bitmap.o

application.o:application.cpp bitmap.hpp
	g++ -c -I . application.cpp -o application.o

libbitmap.a:bitmap.o
	ar rs libbitmap.a bitmap.o

exe:libbitmap.a application.o
	g++ application.o libbitmap.a -o exe

clean:
	rm bitmap.o
	rm application.o
	rm libbitmap.a
	rm exe