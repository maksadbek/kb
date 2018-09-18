#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <sys/event.h>
#include <sys/ioctl.h>

// MSG_NOSIGNAL does not exists on OS X
#if defined(__APPLE__) || defined(__MACH__)
	#ifndef MSG_NOSIGNAL
		#define MSG_NOSIGNAL SO_NOSIGPIPE
	#endif
#endif

int set_nonblock(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	if((flags = fcntl(fd, F_GETFL,0)) == -1) {
		flags = 0;
	}
	return fcntl(fd, F_SETFL, flags | O_NONBLOCKING);
#else
	flags = 1;
	return ioctl(fd, FIONBIO, &flags);
#endif
}

int main(int argc, char **argv) {
	int ms = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(12345);
	sockaddr.sin_addr.s_addr = 0;

	bind(ms, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	set_nonblock(ms);
	listen(ms, SOMAXCONN);

	int kq = kqueue();

	struct kevent ke;
	bzero(&ke, sizeof(ke));
	EV_SET(&ke, ms, EVFILT_READ, EV_ADD, 0, 0, 0);
	kevent(kq, &ke, 1, NULL, 0, NULL);

	while(true) {
		bzero(&ke, sizeof(ke));
		kevent(kq, NULL, 0, &ke, 1, NULL);
		
		if((ke.filter = EVFILT_READ)) {
			if(ke.ident == ms) {
				int ss = accept(ms, 0, 0);
				set_nonblock(ss);

				bzero(&ke, sizeof(ke));
				EV_SET(&ke, ss, EVFILT_READ, EV_ADD, 0, 0, 0);
				kevent(kq, &ke, 1, NULL, 0, NULL);
			} else {
				static char buf[1024];
				int count = recv(ke.ident, buf, 1024, MSG_NOSIGNAL);
				if(count <= 0) {
					close(ke.ident);
					printf("disconnected\n");
				} else {
					send(ke.ident, buf, count, MSG_NOSIGNAL);
				}
			}
		}
	}
}
