
INC=-I/usr/local/include/CUnit
LIB=-L/usr/local/lib/

test:main.c func.c testcase.c 
	gcc -o $@  $(LIB) -lcunit $^

clean:
	rm -rf *.o test *.xml
