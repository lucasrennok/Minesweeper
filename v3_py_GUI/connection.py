import socket
import threading
import time

buffer = ""
host_server = ""
port = 1500
client_socket = ""
finalized = False
game_view_aux_g = ""

def receiveMesage():
    global client_socket
    global host_server
    global port
    global finalized
    buffer_history = ""
    req = ""
    timer = 0
    while(finalized == False): #enquanto jogo continuar rodando
        if(timer%5==0):
            timer=0
            client_socket.sendto(req.encode(), (host_server,port))
            buffer,server = client_socket.recvfrom(2048)    #recebe dados no buffer pra atualizar o campo minado
            if(buffer.decode()!=buffer_history):
                pass    # envia dados pra matriz
            buffer_history = buffer.decode()
        time.sleep(1)
        timer+=1

def connect_to_server(game_view_aux,ip):
    global game_view_aux_g
    global client_socket
    global finalized
    global host_server
    host_server = ip
    game_view_aux_g = game_view_aux
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    t1 = threading.Thread(target=receiveMesage)
    t1.start()

    while(finalized == False): #enquanto jogo está rodando
        mesage = input("")    #recebe entrada do botão, envia pro server
        client_socket.sendto(mesage.encode(),(host_server,port))

    print("Closing")

    client_socket.close()