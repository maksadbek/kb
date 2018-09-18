## Sockets
### C API.

```C
int s = socket(domain, type, protocol)
```
- domain can be `AF_INET` for IPv4, `AF_INET6` for IPv6, `AF_UNIX` for unix sockets.
- type can be `SOCK_STREAM` for `TCP` and `SOCK_DGRAM` for `UDP`.
- protocol have many values, mostly it is `IPPROTO_TCP` and `IPPROTO_UDP`.

The variable `s` is a file descriptor.
The file descriptors are the pointers to the entities in the kernel. The `s` variable is kept in the runtime of the application.
Each application have a layer of file descriptor table. The same can be `open` function. It returns a file descriptor to the kernel entity.

### Binding a socket to the IP address.

The is a function `bind` that connects some IP address to the socket.
```C
	bind(socket, (struct sockaddr *)sockAddr, sizeof(sockAddr));
```

Lets create a address.
```C
struct sockaddr_in sockAddr;
sockAddr.sin_family = AF_INET;
```

Set the port
```C
sockAddr.sin_port = 12345;
```
This does not work, because there is such a notations like big endian and little endian byte orders.

That is why we use `htons` function:
```C
sockAddr.sin_port = htons(12345);
```

Now we setup IP address. There are builtin values for address:
- INADDR_LOOPBACK is the loopback address, localhost, 127.0.0.1.
- INADDR_ANY is the any address, 0.0.0.0

```
sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
```

But if we want out custom IP address, we have 2 choices:
- We use `inet_addr`:
```C
ip = inet_addr("10.10.10.1");
inet_pton(AF_INET, "
```
- Or we use `inet_pton`:
```C
inet_pton(AF_INET, "10.10.10.1", &(sockAddr.sin_addr));
```

### Unix sockets

```C
struct sockaddr_un unixSockAddr;
unixSockAddr.sin_family = AF_UNIX;
// set the file path
strcpy(unixSockAddr.sun_path, "/tmp/huy.sock");
```

### Listen sockets
We can listen a address and receives and send bytes in/out using.
But in the beginning we must start listening. This is done using `listen` function.
```C
listen(s, SOMAXCONN);
```
What the fuck is this ```SOMAXCONN```?
The standart C library does not work concurrently and can receive connections only synchronously.
That is why incoming connections are kept in the queue. So the SOMAXCONN is the capacity of this queue.
**By default it is equal to 128**
For example, we can receive 128 connections simultaniously, the next connections will be dropped.

Accept connections:
```C
while(s1 = accept(s, 0, 0)) {
// ...
}
```

The `accept` function receives the socket file descriptor, sockaddr pointer and its length.

### Read & Write from connection.
```
// read from the socket - fd, into buffer - buf.
size_t read(int fd, void *buf, size_t count);

// write from buf into socket
size_t write(int fd, const void *buf, size_t count);
```

If we try to read and write into closed connection we will get a `SIGPIPE` signal.
We can ignore this signal with `signal(SIGPIPE, SIG_IGN)`

But this is not the good. The better way is with:
```C
size_t recv(int fd, void *buf, size_t count, int flags);
size_t send(int fd, void *buf, size_t count, int flags);
```

We will pass a `MSG_NOSIGNAL` flag into the flag param.

### Client

So how it works:

```
server		| 		|client
----------------|		|---------------
socket()	| 		| socket()	
		|		|
bind()		|		|
		|		|
listen()	|		| 
		|		|
accept()	|<    SYN j  	|connect(int fd, struct sockaddr*, size_t)
		|		|
		|SYN k,ACK j+1 >|
		|		|
		|<   ACK k+1  	|
-----------------------------------------------
		send / recv
```

### Closing connections
We open a file with `open` and close it with `close` functions.
With connection we must call the `shutdown` function.
```C
shutdown(s, int how)
```

The `how` flag can be as follows:
- `SHUT_ROWR` close for writing and reading.
- `SHUT_RD` close for reading
- `SHUT_WR` close for write

How it works in context:
```
server		| 		|client
----------------|		|---------------
		| <   FIN m  	|
		|		|
		|     ACK m+1 > |
		|		|
		|     FIN n   > |
		|		|
		| <   ACK n+1   |
```

### UDP and datagram 
