TARGET: exe

exe:main.o mylibmath.a
	g++ main.o -o exe -L . mylibmath.a

mylibmath.a:common_math/common_math.o complex_math/complex_math.o trig_math/trig_math.o
	ar rs mylibmath.a common_math/common_math.o complex_math/complex_math.o trig_math/trig_math.o

common_math.o:common_math/common_math.cpp
	g++ -c -I common_math common_math/common_math.cpp -o common_math.o 

complex_math.o:complex_math/complex_math.cpp
	g++ -c -I complex_math complex_math/complex_math.cpp -o complex_math.o

trig_math.o:trig_math/trig_math.cpp
	g++ -c -I trig_math trig_math/trig_math.cpp -o trig_math.o

main.o:main.cpp
	g++ -c -I common_math -I complex_math -I trig_math main.cpp -o main.o

clean:
	rm common_math/common_math.o
	rm complex_math/complex_math.o
	rm trig_math/trig_math.o
	rm main.o
	rm mylibmath.a
	rm exe