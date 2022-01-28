
#
# Makefile for miniNFS, ecs251 and ecs36b
#

CC = g++ -std=c++17

# CFLAGS = -g

# for most Linux environments, but might need to be changed to find json stuff
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# the following, RPCG, are JSONRPC generated files
RPCG_INCS =	mininfs_client.h mininfs_server.h

# all files inherited from Core objects plus the RPCG stuff
CORE_INCS =	Core.h Directory.h Shadow_Directory.h $(RPCG_INCS)
CORE_OBJS =	Core.o Directory.o Shadow_Directory.o

# libraries needed for JSON and JSONRPC
LDFLAGS_SV = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = 	-ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client

# rules

all: 	mininfs_client mininfs_server

# why do I need this line?

mininfs_client.h:	mininfs.json
	jsonrpcstub mininfs.json --cpp-server=mininfs_Server --cpp-client=mininfs_Client

mininfs_server.h:	mininfs.json
	jsonrpcstub mininfs.json --cpp-server=mininfs_Server --cpp-client=mininfs_Client

Core.o:			Core.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Core.cpp

Directory.o:		Directory.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Directory.cpp

Shadow_Directory.o:	Shadow_Directory.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Directory.cpp

mininfs_client.o:	mininfs_client.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) mininfs_client.cpp

mininfs_server.o:	mininfs_server.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) mininfs_server.cpp

mininfs_server:		$(CORE_OBJS) mininfs_server.o
	$(CC) -o mininfs_server $(CORE_OBJS) mininfs_server.o $(LDFLAGS_SV) $(LDFLAGS_CL)

mininfs_client:		$(CORE_OBJS) mininfs_client.o
	$(CC) -o mininfs_client $(CORE_OBJS) mininfs_client.o $(LDFLAGS_SV) $(LDFLAGS_CL)

clean:
	rm -f *.o *~ core mininfs_client mininfs_server $(RPCG_INCS)

# end of the Makefile