"""
Description: 小缓存服务器
Usage: 运行后访问对应端口（默认7999), 在地址栏后输入相应地址
        例： localhost:7999/www.baidu.com
Author: CC
Date: May 9 2020
"""
from socket import *


class ProxyServer:
    def __init__(self, port=7999):
        self.server_port = port  # default port
        self.server_socket = socket(AF_INET, SOCK_STREAM)
        # automatically change the port if binding failed
        while 1:
            try:
                self.server_socket.bind(('0.0.0.0', self.server_port))
                print('Succefully binded the socket to port ' +
                      str(self.server_port))
                break
            except OSError:
                print('Port ' + str(self.server_port) + ' is being used...')
                self.server_port += 1
        self.server_socket.listen(5)  # start listening

    def response(self, code, message=''):
        status = {
            404: '404 Not Found',
            400: '400 Bad Request'
        }
        response_data = 'HTTP/1.1 ' + status[code]
        return response_data.encode(encoding='utf-8')

    def read_from_cache(self, filename):
        with open(filename, 'r') as f:
            outputdata = f.read()
            print('Read from cache')
        return outputdata.encode(encoding= 'utf-8')

    def request_from_internet(self, url):
        filename = url.replace('/', '_')
        host_name = url.partition('/')[0]
        host_url = url.partition('/')[2]
        # Create a socket on the proxyserver
        c = socket(AF_INET, SOCK_STREAM)
        # Connect to the socket to port 80
        try:
            c.connect((host_name, 80))
        except:
            print('Connection to host server failed')
            return self.response(404)
        print('Socket connected to port 80 of the host ' + host_name)
        # Create a temporary file on this socket and ask port 80
        # for the file requested by the client
        # fileobj = c.makefile('r', 0)
        # fileobj.write("GET" + "http://" + filename + " HTTP/1.0\n\n")
        # fileobj.close()
        request = ("GET " + "/" + host_url + " HTTP/1.0\r\n"
                   + "Host: " + host_name + "\r\n\r\n")
        c.sendall(request.encode())
        # Read the response into buffer
        with open(filename, "wb") as tmpFile:
            outputdata = b''
            response = c.recv(2048)
            while response:
                outputdata += response
                response = c.recv(2048)
            tmpFile.write(outputdata)
        c.close()
        # Create a new file in the cache for the requested file.
        # ProxyServer finds a cache hit and generates a response message
        return outputdata

    def run(self):
        while True:
            # start receiving data from the client
            print('Ready to serve...')
            cli_socket, addr = self.server_socket.accept()
            print('Received a connection from:', addr)
            cli_message = cli_socket.recv(1024).decode(encoding= 'utf-8')
            cli_request_request = cli_message.split('\r\n')[0]
            print('Request: ' + cli_request_request)  # print the header
            # Extract the filename from the given message
            try:
                url = cli_message.split()[1][1:]
                filename = url.replace('/', '_')
            except IndexError:
                cli_socket.sendall(self.response(400))
                cli_socket.close()
                continue

            try:  # try to read from cache file
                cli_socket.sendall(self.read_from_cache(filename))
            except IOError:  # try to download from the internet
                cli_socket.sendall(self.request_from_internet(url))
            cli_socket.close()


if __name__ == "__main__":
    server = ProxyServer()
    server.run()
