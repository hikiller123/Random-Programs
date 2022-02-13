/*
Matthew
this is a program that pings provided address in c 
https://github.com/coding-fans/linux-network-programming/blob/master/src/c/icmp/ping/ping.c
this program uses a argument for address input and needs sudo permissions.
example:sudo ./ping 8.8.8.8
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>

int main() {
	char input[16];
	printf("input ip address\n");
	scanf("%s", &input);
	printf("You are pinging %s\n", input);
	//creating socket
	int rawsock = socket(AF_INET, SOCK_RAW, 1);
	if(rawsock <= 0)
		perror("Socket Error");
	
	//construct packet
	struct sockaddr_in sendaddress;
	sendaddress.sin_family = AF_INET;
	sendaddress.sin_port = 0;
	sendaddress.sin_addr.s_addr = inet_addr(input);
	//sendaddress.sin_addr.s_addr = inet_addr(argv[1]);
	typedef struct {
        uint16_t flags;
        uint16_t checksum;
        uint32_t payload;
    }icmpheader;
	icmpheader ping;
	ping.flags = 0x08;
	ping.checksum = 0xfff7;
	ping.payload = 0;
	
	for(int i=0;i<3;i++){
	//send ping
	int time = clock();
	if(sendto(rawsock, &ping, sizeof(ping), 0, (struct sockaddr*)&sendaddress, sizeof(sendaddress)) < 0)
		perror("Ping Error");
	
	//parse the response
	struct sockaddr respAddress;
	unsigned char resp[32];
	unsigned int respAddressSize;
	
	//read the response
	int response = recvfrom(rawsock, resp, sizeof(resp), 0, &respAddress, &respAddressSize);
	time = clock()-time;
	if(response > 0){
		printf("From=%s Bytes=%d Time=%dms TTL=%d\n", input, response, time, resp[8]);
		for(int ii = 0; ii < response; ii++)
			printf("%x ", resp[ii]);
		printf("\n");
	}
	else
		perror("Response Error");
	}
	return 0;
}