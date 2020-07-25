import socket,pickle
import time
from minesweeper import Minesweeper

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
req = "18"
client_socket.sendto(req.encode(), ("192.168.1.3",1500))
reqq = ""

time.sleep(1)
client_socket.sendto(reqq.encode(), ("192.168.1.3",1500))
buffer,server = client_socket.recvfrom(2048)

vector = pickle.loads(buffer)
print(vector)

time.sleep(1)
reqqq = "GAME"
client_socket.sendto(reqqq.encode(), ("192.168.1.3",1500))
buffer,server = client_socket.recvfrom(2048)

obj = pickle.loads(buffer)
print(obj.matrix[2][1].mines_around)