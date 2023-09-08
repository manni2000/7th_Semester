#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char input[100];
    printf("Enter a hostname or IP address: ");
    scanf("%s", input);

    struct hostent *host;
    struct in_addr **addr_list;
    
    // Using gethostbyname
    host = gethostbyname(input);

    if (host == NULL) {
        herror("gethostbyname");
        return 1;
    }

    printf("Official Name: %s\n", host->h_name);
    printf("Alias List: \n");
    char **alias;
    for (alias = host->h_aliases; *alias != NULL; alias++) {
        printf("%s\n", *alias);
    }
    printf("Address Type: %s\n", host->h_addrtype == AF_INET ? "IPv4" : "IPv6");
    printf("Address Length: %d\n", host->h_length);
    printf("Addresses: \n");
    addr_list = (struct in_addr **)host->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++) {
        printf("%s\n", inet_ntoa(*addr_list[i]));
    }

    return 0;
}
