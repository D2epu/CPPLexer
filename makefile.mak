# Makefile written by DeepuKumar

CC = bcc32


main: CLEX.exe clean

CLEX.exe:
	$(CC) -ebin\CLEX.exe src\cpplexer.cpp

clean:
	DEL *.obj
	DEL bin\*.tds