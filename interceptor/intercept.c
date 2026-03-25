#include <netinet/in.h>
#define _GNU_SOURCE
#include "debug.h"
#include <arpa/inet.h>
#include <dlfcn.h>
#include <sys/socket.h>

int connect(int fd, const struct sockaddr *addr, socklen_t len) {
  printf("connect() intercepted\n");

  if (addr->sa_family == AF_INET) {
    struct sockaddr_in *in = (struct sockaddr_in *)addr;
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &in->sin_addr, ip, sizeof(ip));

    printf("ip: %s\n", ip);
    printf("port: %d\n", ntohs(in->sin_port));
    printf("raw data:\n");
    print_hex(addr->sa_data, sizeof(addr->sa_data));
    printf("\n");
  }

  // call real connect
  // clang-format off
  int (*real_connect)(int, const struct sockaddr *, socklen_t) = dlsym(RTLD_NEXT, "connect");
  // clang-format on
  return real_connect(fd, addr, len);
}

ssize_t send(int fd, const void *buf, size_t n, int flags) {
  // intercept outgoing data
  printf("send %zu bytes\n", n);
  print_hexdump(buf, n);
  printf("\n");

  // call real send
  // clang-format off
  ssize_t (*real_send)(int, const void *, size_t, int) = dlsym(RTLD_NEXT, "send");
  // clang-format on
  return real_send(fd, buf, n, flags);
}
