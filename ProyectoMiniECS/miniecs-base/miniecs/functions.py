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
    client.connect(('127.0.0.1', 9090 ))

    #Mensaje para el admin-container
    client.send(name.encode())

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
    client.connect(('127.0.0.1', 9090 ))

    #Mensaje para el admin-container
    client.send(name.encode())

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
    client.connect(('127.0.0.1', 9090 ))

    #Mensaje para el admin-container
    client.send(name.encode())

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
    client.connect(('127.0.0.1', 9090 ))

    #Mensaje para el admin-container
    client.send(name.encode())

    #Recibir lo que envia el admin-container
    print(client.recv(1024).decode())




