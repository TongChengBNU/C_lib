BIN = server client
GEN = date_clnt.c date_svc.c date_xdr.c date.h
RPCGEN = rpcgen

CFLAGS = -Wall -O -DRPC_SVC_FG #-g
#LDLIBS =
#LDFLAGS =

#all: $(BIN)

client: date_client.c date_clnt.c
    #$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	gcc -o $@ $^
server: date_server.c date_svc.c
    #$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	gcc -o $@ $^

date_client.o: date.h
date_server.o: date.h

$(GEN): date.x
    #$(RPCGEN) -C $^
    $(RPCGEN) $^

#clean:
#    $(RM) *.o $(BIN) $(GEN)
