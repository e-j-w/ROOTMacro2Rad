all: rootmacro2rad

rootmacro2rad: rootmacro2rad.c
	gcc rootmacro2rad.c -Wall -o2 -o rootmacro2rad

clean:
	rm -rf *~ rootmacro2rad
