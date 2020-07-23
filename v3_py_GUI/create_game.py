import socket
import threading
import time

buffer = ""
host_server = ""
port = 1500
server_socket = ""

def receive_data():
    mesage = ""
    while(1):   #enquanto jogo não acabar
        receive,client = server_socket.recvfrom(2048)
        mesage = receive.decode() 
        if(mesage==""):
            server_socket.sendto(buffer.encode(), client)
        else:
            pass    #tem que pegar esses dados e enviar pra matriz

def create_server():
    global server_socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(("", port))

    t1 = threading.Thread(target=receive_data)
    t1.start()

    while(1):   #enquanto jogo não acabar
        pass # le botao clicado e coloca no buffer e na matriz

    print("\nClosing in 5 secs...")
    time.sleep(5)

    server_socket.close()
