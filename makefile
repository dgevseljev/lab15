all: server client
server: server.c common.h
	gcc server.c -o server
client: client.c common.h
	gcc client.c -o client
clean:
	-rm server client *.o