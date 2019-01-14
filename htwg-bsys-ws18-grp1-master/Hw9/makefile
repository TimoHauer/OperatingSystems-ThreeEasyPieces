#makefile
#Timo Hauer
#02.01.2019

.PHONY: all

all: TCP-Server TCP-Server-Time TCP-Server-Select TCP-Server-File TCP-Server-File-AIO TCP-Client TCP-Client-Time TCP-Client-Select TCP-Client-File TCP-Client-File-AIO TCP-Server-File-Sig

TCP-Server:
	gcc -g -o Server src/TCP-Server.c

TCP-Server-Time:
	gcc -g -o Server-Time src/TCP-Server-Time.c

TCP-Server-Select:
	gcc -g -o Server-Select src/TCP-Server-Select.c

TCP-Server-File:
	gcc -g -o Server-File src/TCP-Server-File.c

TCP-Server-File-AIO:
	gcc -g -o Server-File-AIO src/TCP-Server-File-AIO.c -lrt

TCP-Server-File-Sig:
	gcc -g -o Server-File-Sig src/TCP-Server-File_Sig.c

TCP-Client:
	gcc -g -o Client src/TCP-Client.c

TCP-Client-Time:
	gcc -g -o Client-Time src/TCP-Client-Time.c

TCP-Client-Select:
	gcc -g -o Client-Select src/TCP-Client-Select.c
	
TCP-Client-File:
	gcc -g -o Client-File src/TCP-Client-File.c

TCP-Client-File-AIO:
	gcc -g -o Client-File-AIO src/TCP-Client-File-AIO.c -lrt
