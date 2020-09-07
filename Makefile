crackcipher: crackcipher.o cipher.o analysis.o
	g++ -o CrackCipher crackcipher.o cipher.o analysis.o

crackcipher.o: crackcipher.cc
	g++ -c crackcipher.cc

cipher.o: cipher.cc cipher.h
	g++ -c cipher.cc

analysis.o: analysis.cc analysis.h
	g++ -c analysis.cc

dirclean:
	del *.o *.out *.exe
