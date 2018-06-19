all:
	gcc -o ./build/client client.c$ 
	gcc -o ./build/server server.c$

run:
	gnome-terminal -x bash -c "./build/server 2000"$
	gnome-terminal -x bash -c "./build/client 127.0.0.1 2000 && read"$
