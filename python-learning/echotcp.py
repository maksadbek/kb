#!/usr/bin/env python3

import socket
import selectors
import types


HOST = '127.0.0.1'
PORT = 6543


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen()
s.setblocking(False)

print('listening on', (HOST, PORT))

sel = selectors.DefaultSelector()
sel.register(s, selectors.EVENT_READ, data=None)


while True:
    events = sel.select(timeout=100)
    for key, mask in events:
        sock = key.fileobj
        data = key.data

        # new connection
        if data is None:
            conn, addr = sock.accept()
            print("accepted connection from", addr)

            conn.setblocking(False)
            data = types.SimpleNamespace(addr=addr, inb=b'', outb=b'')
            events = selectors.EVENT_READ | selectors.EVENT_WRITE
            sel.register(conn, events, data=data)
        else:
            if mask & selectors.EVENT_READ:
                recv_data = sock.recv(1024)
                if recv_data:
                    data.outb += recv_data
                else:
                    print("closing connection", data.addr)
                    sel.unregister(sock)
                    sock.close()
            if mask & selectors.EVENT_WRITE:
                if data.outb:
                    print("echoing", repr(data.outb), "to", data.addr)
                    sent = sock.send(data.outb)
                    data.outb = data.outb[sent:]
