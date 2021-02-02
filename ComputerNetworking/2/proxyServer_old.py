from socket import *
import sys

serverPort = 7999
# Create a server socket, bind it to a port and start listening
tcpSerSock = socket(AF_INET, SOCK_STREAM)
# Fill in start.
while 1:
    try:
        tcpSerSock.bind(('0.0.0.0', serverPort))
        break
    except OSError:
        serverPort += 1
        continue
tcpSerSock.listen(1)

# Fill in end.
while 1:
    # Strat receiving data from the client
    print('Ready to serve... Port ', serverPort)
    tcpCliSock, addr = tcpSerSock.accept()
    print('Received a connection from:', addr)
    message = tcpCliSock.recv(1024).decode()
    print(message)
    # Extract the filename from the given message
    try:
        print('request: ', message.split()[1])
    except IndexError:
        continue
    filename = message.split()[1].partition("/")[2].replace('/', '_')
    address = message.split()[1].partition("/")[2].partition('/')[2]
    print(filename)
    if filename == 'favicon.ico':
        continue
    fileExist = "false"

    try:
        f = open(filename, 'r')
        outputdata = f.read()
        fileExist = "true"
        # ProxyServer finds a cache hit and generates a response message
        # Fill in start
        tcpCliSock.sendall(outputdata.encode())
        # Fill in end
        print('Read from cache')
    # Error handling for file not found in cache
    except IOError:
        if fileExist == 'false':
            # Create a socket on the proxyserver
            c = socket(AF_INET, SOCK_STREAM)
            hostn = message.split()[1].partition("/")[2].partition('/')[0]
            print(hostn)
            # Connect to the socket to port 80
            c.connect((hostn, 80))
            print('Socket connected to port 80 of the host')
            # Create a temporary file on this socket and ask port 80
            # for the file requested by the client
            # fileobj = c.makefile('r', 0)
            # fileobj.write("GET" + "http://" + filename + " HTTP/1.0\n\n")
            # fileobj.close()
            request = ("GET " + "/" + address + " HTTP/1.0\r\n"
                       + "Host: " + hostn + "\r\n\r\n")
            c.sendall(request.encode())
            # Read the response into buffer
            tmpFile = open(filename, "wb")
            response = c.recv(4096)
            while response:
                tmpFile.write(response)
                response = c.recv(4096)
            c.close()
            tmpFile.close()
            # Create a new file in the cache for the requested file.
            # Also send the response in the buffer to client socket and the corresponding file in the cache
            # Fill in start.'
            f = open(filename, 'r')
            outputdata = f.read()
            # ProxyServer finds a cache hit and generates a response message
            # Fill in start
            tcpCliSock.sendall(outputdata.encode())
            # Fill in end.

        # Close the client and the server sockets
    tcpCliSock.close()
    # Fill in start.
tcpSerSock.close()
# Fill in end.
