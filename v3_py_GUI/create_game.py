import socket
import threading
import time
import game_view

buffer = ""
host_server = ""
port = 1500
server_socket = -1
finalized = False
game_view_aux_g = ""
result = None
close = False

def receive_data():
    global result
    global finalized
    global server_socket
    global close
    mesage = ""
    while(finalized==False or close==False):   #enquanto jogo não acabar
        receive,client = server_socket.recvfrom(2048)
        mesage = receive.decode() 
        if(mesage==""):
            server_socket.sendto(buffer.encode(), client)
        else:
            result = game_view_aux_g.play(mesage)
        if(result>0):
            finalized=True

def create_server(game_view_aux, ip):
    global result
    global game_view_aux_g
    global server_socket
    global finalized
    global port
    global host_server
    global close
    host_server = ip
    finalized=False
    game_view_aux_g = game_view_aux

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(("", port))

    t1 = threading.Thread(target=receive_data)
    t1.start()

    while(finalized==False):   #enquanto jogo não acabar
        but_clicked = game_view_aux_g.get_button()
        result = game_view_aux_g.play(but_clicked) # le botao clicado e coloca no buffer e na matriz
        if(result>0):
            finalized=True

    print("\nClosing in 5 secs...")
    time.sleep(5)
    nothing = ""
    server_socket.sendto(nothing.encode(), (host_server,port))
    close = True
    server_socket.close()
    return result

