CC =  gcc
CFLAGS = -Wall
SUFFIX = -c
EXEFILE = gonzo

all : common.c page.c gonzo.c
	$(CC) $(CFLAGS) common.c $(SUFFIX)
	$(CC) $(CFLAGS) page.c $(SUFFIX)
	$(CC) $(CFLAGS) gonzo.c $(SUFFIX)
	$(CC) $(CFLAGS) -o $(EXEFILE) common.o page.o gonzo.o
	chmod 755 $(EXEFILE)
common : common.c
	$(CC) $(CFLAGS) common.c -c
page : page.c
	$(CC) $(CFLAGS) page.c -c
gonzo : gonzo.c
	$(CC) $(CFLAGS) gonzo.c -c
clean :
	rm -f gonzo gonzo.o page.o
