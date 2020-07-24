import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
req = "2"
client_socket.sendto(req.encode(), ("192.168.1.3",1500))
#req = ""
#client_socket.sendto(req.encode(), ("192.168.1.3",1500))
#buffer,server = client_socket.recvfrom(2048)

#print(buffer)