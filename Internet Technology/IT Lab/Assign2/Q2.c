#include <stdio.h>
#include <netdb.h>

int main() {
    char input[100];
    printf("Enter a service name or port number: ");
    scanf("%s", input);

    struct servent *service;
    int port;

    // Check if the input is a port number
    if (sscanf(input, "%d", &port) == 1) {
        service = getservbyport(htons(port), NULL);
    } else {
        service = getservbyname(input, NULL);
    }

    if (service == NULL) {
        herror("getservbyname/getservbyport");
        return 1;
    }

    printf("Official Service Name: %s\n", service->s_name);
    printf("Alias List: \n");
    char **alias;
    for (alias = service->s_aliases; *alias != NULL; alias++) {
        printf("%s\n", *alias);
    }
    printf("Port Number: %d\n", ntohs(service->s_port));
    printf("Protocol Used: %s\n", service->s_proto);

    return 0;
}
