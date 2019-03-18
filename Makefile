OBJECTS = main.o list.o hash.o skiplist.o student.o stucs.o

stucs: $(OBJECTS)
	gcc $(OBJECTS) -o stucs

	
main.o: main.c
	gcc -c main.c

stucs.o:stucs.c stucs.h
	gcc -c stucs.c
	
list.o: list.c list.h
	gcc -c list.c
	
hash.o: hash.c hash.h
	gcc -c hash.c
	
skiplist.o: skiplist.c skiplist.h
	gcc -c skiplist.c
	
student.o: student.c student.h
	gcc -c student.c
	

clean:
	rm *.o stucs
