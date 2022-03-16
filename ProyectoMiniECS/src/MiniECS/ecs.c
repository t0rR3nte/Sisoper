
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main() {
    int id = fork();
    
    
    char agentInfo[14] = "127.0.0.1 7070";
    int ordinaryPipe1[2];
    int ordinaryPipe2[2];

    pipe(ordinaryPipe1);
    pipe(ordinaryPipe2);
    
    
    //Subscribe-host (proceso hijo con socket server)
    if (id == 0) {
        //Variables and Structures
        int socket_desc1 , client_sock1 , c1 , read_size1;
        struct sockaddr_in server1 , client1;
        char client_message1[2000];

        // Close the unwanted ordinary_pipe read side
        close(ordinaryPipe1[0]);
        // Close write
        close(ordinaryPipe2[1]);      

        //Create socket server
        // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol) 
        // SOCK_STREAM: TCP(reliable, connection oriented)
        // SOCK_DGRAM: UDP(unreliable, connectionless)
        // Protocol value for Internet Protocol(IP), which is 0
        socket_desc1 = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc1 == -1) {
            printf("Error: Could not create socket for child process");
        }
        puts("Success: Socket created for child process");
        
        //Prepare the sockaddr_in structure
        server1.sin_family = AF_INET;
        //server.sin_addr.s_addr = INADDR_ANY;
        server1.sin_addr.s_addr = inet_addr("127.0.0.1");
        server1.sin_port = htons( 6161 );
        
        //Bind the socket to the address and port number specified
        if( bind(socket_desc1, (struct sockaddr *)&server1 , sizeof(server1)) < 0) {
            //print the error message
            perror("Error: bind failed for child process.");
            return 1;
        }
        puts("Success: bind for child process done");
        puts("==============================================================================");
        
        //Listen
        listen(socket_desc1 , 3);
        
        //Accept and incoming connection
        puts("Subscribe-host: Waiting for incoming connections...");
        
        while(1) {
            puts("entro al while");
            c1 = sizeof(struct sockaddr_in);
        
            //accept connection from an incoming client
            client_sock1 = accept(socket_desc1, (struct sockaddr *)&client1, (socklen_t*)&c1);
            if (client_sock1 < 0) {
                perror("Subscribe-host: accept failed");
                return 1;
            }
            puts("Subscribe-host: connection accepted");
            memset ( client_message1, 0, 2000 );
            //Receive a message from client
            if (recv(client_sock1 , client_message1 , 2000 , 0) > 0) {
                printf("Subscribe-host received message: %s\n", client_message1);
                
                //printf("Se metio al if hijo");

                //Send the message back to client
                send(client_sock1 , client_message1 , strlen(client_message1), 0);           

                write(ordinaryPipe1[1], agentInfo, strlen(agentInfo));
                
            } 
            else{
                puts("Subscribe-host: recv failed");
            }
        }
    }
    // Admin-Container (proceso padre con socket server)
    else {
        //Variables and Structures
        int socket_desc2 , client_sock2 , c2 , read_size2;
        struct sockaddr_in server2 , client2;
        char client_message2[2000];
        
        //Create socket server
        // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol) 
        // SOCK_STREAM: TCP(reliable, connection oriented)
        // SOCK_DGRAM: UDP(unreliable, connectionless)
        // Protocol value for Internet Protocol(IP), which is 0
        socket_desc2 = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc2 == -1) {
            printf("Error: Could not create socket for parent process");
        }
        puts("Success: Socket created for parent process");
        
        //Prepare the sockaddr_in structure
        server2.sin_family = AF_INET;
        //server.sin_addr.s_addr = INADDR_ANY;
        server2.sin_addr.s_addr = inet_addr("127.0.0.1");
        server2.sin_port = htons( 9292 );
        
        //Bind the socket to the address and port number specified
        if( bind(socket_desc2, (struct sockaddr *)&server2 , sizeof(server2)) < 0) {
            //print the error message
            perror("Error: bind failed for parent process");
            return 1;
        }
        puts("Success: bind for parent process done");
        puts("==============================================================================");
        
        //Listen
        listen(socket_desc2 , 3);
        
        //Accept and incoming connection
        puts("Admin-Container: Waiting for incoming connections...");
        
        while(1) {
            c2 = sizeof(struct sockaddr_in);
        
            //accept connection from an incoming client
            client_sock2 = accept(socket_desc2, (struct sockaddr *)&client2, (socklen_t*)&c2);
            if (client_sock2 < 0) {
                perror("Admin-Container: accept failed");
                return 1;
            }
            puts("Admin-Container: Connection accepted");
            memset ( client_message2, 0, 2000 );
            //Receive a message from client
            if (recv(client_sock2 , client_message2 , 2000 , 0) > 0) {
                printf("Admin-Container received message: %s\n", client_message2);

                
                // Parent process closes the unwanted ordinary_pipe write side
                close(ordinaryPipe1[1]);
                // Close read
                close(ordinaryPipe2[0]);

                if((read(ordinaryPipe1[0], agentInfo, strlen(agentInfo))) > 0){
                    printf("Received string in child: %s ", agentInfo);
                }
                printf("pipe done\n");

                write(ordinaryPipe2[1], agentInfo, strlen(agentInfo));
                
                //puts("Se metio al if padre");
                //Send the message back to client
                send(client_sock2 , client_message2 , strlen(client_message2), 0);
            } else {
                puts("Admin-Container: recv failed");
            }
            
        }
    }
    return 0;
}

/*
    fork()  if == 0: child (hijo)
    fork()  if > 0: parent (padre)
    fork()  if < 0: error
*/
