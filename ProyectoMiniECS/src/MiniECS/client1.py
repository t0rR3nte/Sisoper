import socket

#Asegura que se cree el socket con valores por defecto
try: 
    client = socket.socket()
    print("Socket created")
except socket.error as err:
    print("Socket failed" %(err))

#host = socket.gethostname()

#Establece a donde conectarse
client.connect(('127.0.0.1', 65535 ))

#Mensaje para el otro socket (server)
client.send('Ok, bitch'.encode())

#Recibir lo que envia el otro socket (server)
print(client.recv(1024).decode())