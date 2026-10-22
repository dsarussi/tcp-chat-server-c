CC = gcc
CFLAGS = -Wall -pthread

PROGRAMS = tcpServer tcpClient daytimeServer daytimeClient \
           sendfilesServer sendfilesClient chatroomServer chatroomClient

all: $(PROGRAMS)

# tcpServer.c and tcpClient.c use read/write/close and inet_addr
# without including their headers, so the headers are added here.
tcpServer tcpClient: CFLAGS += -include unistd.h -include arpa/inet.h

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGRAMS) recv.txt

.PHONY: all clean
