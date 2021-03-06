/***
 * network_wrapper.c
 */

#include "network_wrappers.h"

#include "macros.h"

#include <errno.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* -------------------------------------------------- */

int net_get_public_ip(struct sockaddr_in *addr)
{
  struct ifaddrs * addrs;
  getifaddrs(&addrs);

  struct ifaddrs * node = addrs;
  while (node) {
    if (node->ifa_addr
        && node->ifa_addr->sa_family == AF_INET) {
      memcpy(addr, (struct sockaddr_in *)node->ifa_addr, sizeof(struct sockaddr_in));
      if (((struct sockaddr_in *)node->ifa_addr)->sin_addr.s_addr != htonl(INADDR_LOOPBACK)) {
        // chooses first one which is not loopback
        break;
      }
    }

    node = node->ifa_next;
  }

  return 0;
}

/* -------------------------------------------------- */

int  net_start_listen_socket(const char *server_addr, int server_port, int *listen_socket)
{
  *listen_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (*listen_socket < 0) {
    perror("socket");
    return -1;
  }

  int reuse = 1;
  if (setsockopt(*listen_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0) {
    perror("setsockopt");
    return -1;
  }

  struct sockaddr_in my_addr;
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = inet_addr(server_addr);
  my_addr.sin_port = htons(server_port);

  if (bind(*listen_socket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) != 0) {
    if (errno == EADDRINUSE)
      fprintf(stderr, "net_start_listen_socket: port %d already in use\n", server_port);
    else
      perror("bind");

    return -1;
  }

  // start accept client connections
  if (listen(*listen_socket, 40) != 0) {
    perror("listen");
    return -1;
  }
  printf("Accepting connections on port %d.\n", server_port);

  return 0;
}

/* -------------------------------------------------- */

const char * net_get_my_ipv4_addr(void)
{
  static char ip[INET_ADDRSTRLEN];
  static const char *ptr = NULL;

  if (ptr) return ptr;

  struct ifaddrs * addrs;
  getifaddrs(&addrs);
  struct ifaddrs * node  = addrs;

  while (node) {
    if (node->ifa_addr
        && node->ifa_addr->sa_family == AF_INET) {
      struct sockaddr_in *this_address =  (struct sockaddr_in *) node->ifa_addr;
      inet_ntop(node->ifa_addr->sa_family, &(this_address->sin_addr), ip, INET_ADDRSTRLEN);
      ptr = ip;

      if (node->ifa_name[0] == 'w') { // hack!!!! FIXME
        break;
      }
    }

    node = node->ifa_next;
  }

  freeifaddrs(addrs);
  return ptr;
}

