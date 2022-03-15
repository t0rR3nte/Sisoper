import socket

#Asegura que se cree el socket con valores por defecto
try: 
    main = socket.socket()
    print("Socket created")
except socket.error() as err:
    print("Socket failed" %(err))


host = socket.gethostname()
#Establece la conexion del ip y puerto
main.bind (('127.0.0.1', 65535 ))

#Cantidad de conexiones en cola posibles
main.listen(6)

check = True

while check == True:
    #Establece conexion con el cliente
    conection, address = main.accept() #address es el puerto desde donde se establece
    print("New conection added")
    print('-> ', address)

    #Enviar mensaje al cliente (en bytes)
    conection.send('Server: I see you bitch'.encode())

    #Recibe el request del cliente( en bytes)
    print(conection.recv(1024).decode())

    #Cerrar conexion con el cliente
    conection.close()

