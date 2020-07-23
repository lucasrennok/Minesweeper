import socket
import threading
import time

buffer = ""
host_server = ""
port = 1500

def receive_data():
    while(1):#enquanto jogo não acabar
        mesage = ""
        receive,client = server_socket.recvfrom(2048)
        #tem que pegar esses dados e enviar pra matriz
        mesage = receive.decode() 
        if(mesage==""):
            server_socket.sendto(buffer.encode(), client)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
local = ("",port)
server_socket.bind(local)

t1 = threading.Thread(target=receive_data)
t1.start()

while(1):#enquanto jogo não acabar
    if(buffer=="nothing"):
        pass

print("\nClosing in 3 secs...")
time.sleep(3)

server_socket.close()
