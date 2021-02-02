from socket import *

serverPort = 12000

serverSocket = socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(('',serverPort))
print('The server is ready to receive')

while True:
    message, client_address = serverSocket.recvfrom(2048)
    modified_message = message.decode().upper()
    serverSocket.sendto(modified_message.encode(), client_address)