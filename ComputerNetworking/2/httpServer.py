"""
Description: 我来写个小http服务器2333
Author: C.C
Date: May 5 2020
"""
from socket import *


class Server():
    def __init__(self, port=12001):
        self.port = port
        self.socket = socket(AF_INET, SOCK_STREAM)
        try:
            self.socket.bind(('0.0.0.0', self.port))
        except OSError:
            print('OSError: Port has been used.')
            exit(0)
        self.socket.listen(1)
        print('The server is ready to receive')

    def run(self):
        while True:
            # start connection
            connection, addr = self.socket.accept()
            # get a request
            request = connection.recv(2048).decode()
            # split by line
            request = request.split('\r\n')
            print('request:', request)
            # get first line
            try:
                method = request[0].split(' ')[0]
                url = request[0].split(' ')[1][1:]
            except IndexError:
                print('empty request')
                continue
            # get the message
            message = self.get_message(url)
            if message != '':
                # handle respond
                respond_head = ("HTTP/1.1 200 OK\r\n"
                                + "Connection: close\r\n"
                                + "Content-Length = " + str(len(message))
                                + "\r\nContent-Type = text/html\r\n"
                                + "\r\n")
                respond = respond_head + message
                print(respond)
                connection.send(respond.encode(encoding='utf-8'))
            else:
                connection.send("HTTP/1.1 404 Not Found\r\n".encode())
            connection.close()
    def get_message(self, filename):
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                return file.read()
        except FileNotFoundError:
            print(filename + 'Not Found')
            return ''


if __name__ == "__main__":
    server = Server()
    server.run()
