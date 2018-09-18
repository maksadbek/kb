#include <iostream>
#include <algorithm>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

// MSG_NOSIGNAL does not exists on OS X
#if defined(__APPLE__) || defined(__MACH__)
	#ifndef MSG_NOSIGNAL
		#define MSG_NOSIGNAL SO_NOSIGPIPE
	#endif
#endif

int set_nonblock(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	if(-1 == (flags = fcntl(fd, F_GETFL, 0))) {
		flags = 0;
	}
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	flags = 1;
	return ioctl(fd, FIOBIO, &flags);
#endif
}

int main(int argc, char **argv) {
	int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::set<int> slave_sockets;
	
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(master_socket, (struct sockaddr*)(&sock_addr), sizeof(sock_addr));

	set_nonblock(master_socket);

	listen(master_socket, SOMAXCONN);

	int ep = epoll_create(0);

	struct epoll_event event;
	event.data.fd = master_socket;
	event.events = EPOLLIN;
	epoll_ctl(ep, EPOLL_CTL_ADD, master_socket, &event);

	while(true) {
		struct epoll_event events[MAX_EVENTS];
		int N = epoll_wait(ep, events, MAX_EVENTS, -1);

		for(unsigned int i = 0; i < N; i++) {
			if(events[i].data.fd == master_socket) {
				int slave = accept(master_socket, 0, 0);
				set_nonblock(slave);


				struct epoll_event slave_event;
				slave_event.data.fd = slave;
				slave_event.events = EPOLLIN;
				epoll_ctl(ep, EPOLL_CTL_ADD, slave, slave_event);
			} else {
				static char buf[1024];
				int recvResult = recv(events[i].data.fd, buf, 1024, MSG_NOSIGNAL);
				if((recvResult == 0) && (errno != EAGAIN)) {
					shutdown(events[i].data.fd, SHUT_RDWR);
					close(events[i].data.fd);
				} else if (recvResult > 0) {
					send(events[i].data.fd, buf, recvResult, MSG_NOSIGNAL);
				}
			}
		}
	}

}
