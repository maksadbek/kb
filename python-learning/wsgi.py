"""
WSGI server built on rspivak's tutorials -- https://ruslanspivak.com/lsbaws-part3/
"""


import io
import socket
import sys
import signal
import os
import errno

def grim_reaper(signum, frame):
    while True:
        try:
            # wait can miss some events, waitpid queues them.
            pid, status = os.waitpid(-1, os.WNOHANG)
        except OSError:
            return

        if pid == 0:
            return


class WSGIServer():
    address_family = socket.AF_INET
    socket_type = socket.SOCK_STREAM
    request_queue_size = 1024 * 4

    def __init__(self, server_address):
        self.listen_socket = listen_socket = socket.socket(self.address_family, self.socket_type)
        listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        listen_socket.bind(server_address)
        listen_socket.listen(self.request_queue_size)

        host, port = self.listen_socket.getsockname()[:2]

        self.server_name = socket.getfqdn(host)
        self.server_port = port

        self.header_set = []
    
    def set_app(self, application):
        self.application = application

    def serve_forever(self):
        listen_socket = self.listen_socket

        while True:
            try:
                conn, client_address = listen_socket.accept()
            except IOError as e:
                code, msg = e.args

                if code == errno.EINTR:
                    continue
                else:
                    raise

            pid = os.fork()

            if pid == 0: # child
                listen_socket.close()
                self.handle_request(conn)
                os._exit(0)
            else: # parent
                conn.close()

    def handle_request(self, conn):
        request_data = conn.recv(1024)
        self.request_data = request_data = request_data.decode('utf-8')

        print(''.join(f'> {line}\n' for line in request_data.splitlines()))

        self.parse_request(request_data)
        env = self.get_environ()

        result = self.application(env, self.start_response)
        self.finish_response(result)

    def parse_request(self, text):
        request_line = text.splitlines()[0]
        request_line = request_line.rstrip('\r\n')

        (self.request_method, self.path, self.request_version) = request_line.split()

    def get_environ(self):
       env = {}

       env['wsgi.version'] = (1, 0)
       env['wsgi.url_scheme'] = 'http'
       env['wsgi.input'] = io.StringIO(self.request_data)
       env['wsgi.errors'] = sys.stderr
       env['wsgi.multithread'] = False
       env['wsgi.multiprocess'] = False
       env['wsgi.run_once'] = False

       env['REQUEST_METHOD'] = self.request_method
       env['PATH_INFO'] = self.path
       env['SERVER_NAME'] = self.server_name
       env['SERVER_PORT'] = str(self.server_port)

       return env

    def start_response(self, status, response_headers, exc_info=None):
        server_headers = [
            ('Date', 'Mon, 15 Jul 2019 5:54:48 GMT'),
            ('Server', 'WSGIServer 0.2'),
        ]

        self.header_set = [status, response_headers + server_headers]
 
    def finish_response(self, result):
        try:
            status, response_headers = self.header_set
            response = f'HTTP/1.1 {status}\r\n'
          
            for header in response_headers:
                response += '{0}: {1}\r\n'.format(*header)

            response += '\r\n'

            for data in result:
                response += data.decode('utf-8')

            print(''.join(f'< {line}\n' for line in response.splitlines()))

            response_bytes = response.encode()
            self.client_connection.sendall(response_bytes)
        finally:
            self.client_connection.close()


SERVER_ADDRESS = (HOST, PORT) = '', 8088

def make_server(server_address, application):
    signal.signal(signal.SIGCHLD, grim_reaper)
    server = WSGIServer(server_address)
    server.set_app(application)
    
    return server

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit('Provide a WSGI application object as module:callable')

    app_path = sys.argv[1]

    module, application = app_path.split(':')

    module = __import__(module)
    application = getattr(module, application)

    httpd = make_server(SERVER_ADDRESS, application)
    print(f'WSGIServer: serving http on port {PORT}\n')

    httpd.serve_forever()

