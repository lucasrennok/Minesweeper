import socket, pickle
import threading
import time
import game_view

host_server = ""
port = 1500
server_socket = -1
finalized = False
game_view_aux_g = ""
result = 0
close = False
vector = []

def put_in_vector(but):
    global vector
    for i in range(len(vector)):
        if(vector[i]==but):
            return 0
    vector+=[but]
    return 1

def receive_data():
    global result
    global finalized
    global server_socket
    global close
    global game_view_aux_g
    global vector
    mesage = ""
    while(finalized==False or close==False):
        receive,client = server_socket.recvfrom(2048)
        mesage = receive.decode()
        if(mesage==""):
            print("ARRAY SENT")
            arr = pickle.dumps(vector)
            server_socket.sendto(arr, client)
        elif(mesage=="000"):
            print("BREAK RECEIVE")
            break
        elif(mesage=="GAME"):
            print("OBJ GAME SENT")
            game = pickle.dumps(game_view_aux_g.game)
            server_socket.sendto(game, client)
        else:
            print("Selecting button: ", mesage)
            put_in_vector(mesage)
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
    global vector
    host_server = ip
    finalized=False
    game_view_aux_g = game_view_aux

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(("", port))
    print("Socket and Bind created")

    t1 = threading.Thread(target=receive_data)
    t1.start()

    while(finalized==False):
        but_clicked = game_view_aux_g.get_button()
        if(but_clicked!="upd"):
            put_in_vector(but_clicked)
        for i in range(len(vector)):
            result = game_view_aux_g.play(vector[i])
            if(result>0):
                finalized=True
                break

    print("\nClosing in 3 secs...")
    time.sleep(3)
    nothing = "000"
    server_socket.sendto(nothing.encode(), (host_server,port))
    print("sent mesage to close(2 secs)")
    time.sleep(2)
    vector.clear()
    close = True
    server_socket.close()
    return result

def receive_vector():
    global client_socket
    global host_server
    global port
    global finalized
    global vector
    req = ""
    timer = 0
    while(finalized == False):
        if(timer%2==0):
            timer=0
            client_socket.sendto(req.encode(), (host_server,port))
            print("REQ SENT")
            arr,server = client_socket.recvfrom(2048)
            vector = pickle.loads(arr)
            print(vector)
        time.sleep(1)
        timer+=1

def connect_to_server(game_view_aux,ip):
    global game_view_aux_g
    global client_socket
    global finalized
    global host_server
    global port
    global vector
    host_server = ip
    game_view_aux_g = game_view_aux
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print("Socket created")

    print("Creating matrix...")
    req = "GAME"
    client_socket.sendto(req.encode(), (host_server,port))
    buffer,server = client_socket.recvfrom(2048)

    obj_game = pickle.loads(buffer)
    game_view_aux_g.set_game(obj_game)
    print("Game setted.")

    time.sleep(1)

    t1 = threading.Thread(target=receive_vector)
    t1.start()
    print("Thread started")
    result=0

    while(finalized == False):
        but_clicked = game_view_aux_g.get_button()
        if(but_clicked!="upd"):
            client_socket.sendto(but_clicked.encode(),(host_server,port))
        print(vector)
        for i in range(len(vector)):
            result = game_view_aux_g.play(vector[i])
            if(result>0):
                finalized=True
                break

    print("Closing")
    client_socket.close()
    return result