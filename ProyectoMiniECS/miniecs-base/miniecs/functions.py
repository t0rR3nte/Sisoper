import socket
import sys
from threading import local
from typing import Container

#Libreria miniecs
#Funciones para contenedores Docker

def create(name):
    #Asegura que se cree el socket con valores por defecto
    try: 
        client = socket.socket()
        print("Socket created")
    except socket.error as err:
        print("Socket failed" %(err))

    #host = socket.gethostname()

    #Establece a donde conectarse
    client.connect(('127.0.0.1', 9292 ))

    #Mensaje para el admin-container
    message = 'create. {0}'.format(name)
    print('sending {!r}'.format(message))
    client.sendall(message)

    #Recibir lo que envia el admin-container
    print(client.recv(1024).decode())


def stop(name):
    #Asegura que se cree el socket con valores por defecto
    try: 
        client = socket.socket()
        print("Socket created")
    except socket.error as err:
        print("Socket failed" %(err))

    #host = socket.gethostname()

    #Establece a donde conectarse
    client.connect(('127.0.0.1', 9292 ))

    #Mensaje para el admin-container
    message = 'stop. {0}'.format(name)
    print('sending {!r}'.format(message))
    client.sendall(message)

    #Recibir lo que envia el admin-container
    print(client.recv(1024).decode())


def start(name):
    #Asegura que se cree el socket con valores por defecto
    try: 
        client = socket.socket()
        print("Socket created")
    except socket.error as err:
        print("Socket failed" %(err))

    #host = socket.gethostname()

    #Establece a donde conectarse
    client.connect(('127.0.0.1', 9292 ))

    #Mensaje para el admin-container
    message = 'start. {0}'.format(name)
    print('sending {!r}'.format(message))
    client.sendall(message)

    #Recibir lo que envia el admin-container
    print(client.recv(1024).decode())


def delete(name):
    #Asegura que se cree el socket con valores por defecto
    try:
        client = socket.socket()
        print("Socket created")
    except socket.error as err:
        print("Socket failed" %(err))

    #host = socket.gethostname()

    #Establece a donde conectarse
    client.connect(('127.0.0.1', 9292 ))

    #Mensaje para el admin-container
    message = 'delete. {0}'.format(name)
    print('sending {!r}'.format(message))
    client.sendall(message)

    #Recibir lo que envia el admin-container
    print(client.recv(1024).decode())


    def listar(name):
        #Asegura que se cree el socket con valores por defecto
        try:
            client = socket.socket()
            print("Socket created")
        except socket.error as err:
            print("Socket failed" %(err))

        #host = socket.gethostname()

        #Establece a donde conectarse
        client.connect(('127.0.0.1', 9292 ))

        #Mensaje para el admin-container
        message = 'listar. {0}'.format(name)
        print('sending {!r}'.format(message))
        client.sendall(message)

        #Recibir lo que envia el admin-container
        print(client.recv(1024).decode())




