all: server.exe client.exe

server.exe: server.c
	gcc server.c -o server.exe -lws2_32

client.exe: client.c
	gcc client.c -o client.exe -lws2_32

clean:
	del *.exe
