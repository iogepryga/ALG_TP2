all: a234

OPTIONS_COMPIL=-Wall -Wno-unused-value -g -c

a234: a234.o lire_affichage.o ajout_cle.o pile.o file.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o pile.o file.o

a234.o: a234.c a234.h
	gcc $(OPTIONS_COMPIL) a234.c

file.o: file.c file.h
	gcc $(OPTIONS_COMPIL) file.c

pile.o: pile.c pile.h
	gcc $(OPTIONS_COMPIL) pile.c

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

clean:
	rm -rf a234 *.o *~
