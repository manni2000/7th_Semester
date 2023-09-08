#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int main() {
    char hostname[100], service[100];

    printf("Enter a hostname: ");
    scanf("%s", hostname);
    printf("Enter a service name or port number: ");
    scanf("%s", service);

    struct addrinfo hints, *res, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname, service, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    printf("IP Addresses:\n");
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        if (rp->ai_family == AF_INET) {  // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {  // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s\n", ipstr);
    }

    freeaddrinfo(res);

    return 0;
}
