#include<stdio.h> 
#include<sys/types.h> 
#include<unistd.h> 
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[]) {
    //==============================================================================
    //Socket-Client para el agent1
	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1) {
		printf("Error: Could not create socket-client for agent1");
	}
	puts("Success: Socket-client for agent1 created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(6262);

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
		perror("Error: connection for agent1 (Socket-Client) failed");
		return 1;
	}
	
	puts("Success: Agent 1 (Socket-Client) Connected\n");
    puts("==============================================================================");
	
	//keep communicating with server
	printf("Agent1(Socket-Client) Enter message : ");
	scanf("%s" , message);
		
	//Send some data
	if( send(sock , message , strlen(message) , 0) < 0) {
		puts("Agent1(Socket-Client): Send failed");
		return 1;
	} else {
        puts("Agent1(Socket-Client): Send Done");
    }
		
	//Receive a reply from the server
    memset ( server_reply, 0, 2000 );
	if( recv(sock , server_reply , 2000 , 0) < 0) {
		puts("Agent1(Socket-Client): recv failed");
	} 
    else {
        puts("Agent1(Socket-Client): recv ok");
    }
		
	puts("Agent1(Socket-client): Server reply : ");
	puts(server_reply);
    puts("==============================================================================");
	close(sock);
    //==============================================================================
    //Socket Server del agent1

    //Variables and Structures
    int socket_descA , client_sockA , cA , read_sizeA;
    struct sockaddr_in serverA , clientA;
    char client_messageA[2000];
    
    //Create socket server
    // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol) 
    // SOCK_STREAM: TCP(reliable, connection oriented)
    // SOCK_DGRAM: UDP(unreliable, connectionless)
    // Protocol value for Internet Protocol(IP), which is 0
    socket_descA = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_descA == -1) {
        printf("Error: Could not create socket server for agent1");
    }
    puts("Success: Socket-server for agent1 created");
    
    //Prepare the sockaddr_in structure
    serverA.sin_family = AF_INET;
    //server.sin_addr.s_addr = INADDR_ANY;
    serverA.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverA.sin_port = htons( 5050 );
    
    //Bind the socket to the address and port number specified
    if( bind(socket_descA, (struct sockaddr *)&serverA , sizeof(serverA)) < 0) {
        //print the error message
        perror("Error: Bind with agent1 socket-server failed");
        return 1;
    }
    puts("Success: Bind with agent1 socket-server done");
    puts("==============================================================================");
    //Listen
    listen(socket_descA , 3);
    
    //Accept and incoming connection
    puts("Agent1(Socket-server): Waiting for incoming connections...");
    
    while(1) {
        cA = sizeof(struct sockaddr_in);
    
        //accept connection from an incoming client
        client_sockA = accept(socket_descA, (struct sockaddr *)&clientA, (socklen_t*)&cA);
        if (client_sockA < 0) {
            perror("Agent1(Socket-server): accept failed");
            return 1;
        }
        puts("Agent1(Socket-server): Connection accepted");
        memset ( client_messageA, 0, 2000 );
        
        //Receive a message from client
        if (recv(client_sockA , client_messageA , 2000 , 0) > 0) {
            /*
            char * m1 = strtok(client_messageA, '.');
            char * m2 = strtok(NULL, '.');
            if(strcmp(m1, "create") == 0){
                char *args[]={"./bin/Docker", "create", "--t", "--i", m2, NULL};
                //execv()
            }
            else if(strcmp(m1, "stop") == 0){
                char *args[]={"./bin/Docker", "stop", m2, NULL};
                
            }
            else if(strcmp(m1, "start") == 0){
                char *args[]={"./bin/Docker", "run",  m2, NULL};
            }
            else if(strcmp(m1, "delete") == 0){
                char *args[]={"./bin/Docker", "rm",  "--f", m2, NULL};
            }
            */
            printf("Agent1(Socket-server) received message: %s\n", client_messageA);
            //Send the message back to client
            send(client_sockA , client_messageA , strlen(client_messageA), 0);
        } else {
            puts("Agent1(Socket-server) recv failed");
        }
        puts("__________________________________________________________________________");
    }
	return 0;
}