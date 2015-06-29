ZK_INC=-I/usr/local/include/zookeeper/
ZK_LIB=-L/usr/local/lib/ -lzookeeper_mt

all:server client

server:server.c
	gcc -g -o server server.c $(ZK_INC)  $(ZK_LIB)

client:client.c
	gcc -g -o client client.c $(ZK_INC) $(ZK_LIB)

clean:
	rm server client
