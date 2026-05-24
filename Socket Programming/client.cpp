#include <sys/un.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

#define SOCKET_NAME "/tmp/SocketTutorial"
#define BUFFER_SIZE 128
int main () {
    int socket_connection = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_connection == -1) {
        std::cout << "Failed creating socket connection" << std::endl;
        return -1;
    }

    sockaddr_un addr;
    memset(&addr, 0, sizeof(sockaddr_un));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_NAME);

    int ret = connect(socket_connection, reinterpret_cast<const sockaddr*>(&addr), sizeof(sockaddr_un));
    if (ret == -1) {
        std::cout << "Failed to connect socket" << std::endl;
        return -1;
    }

    int val = -1;
    while (val != 0) {
        std::cout << "Enter value to send to the server: ";
        std::cin >> val;
        ret = write(socket_connection, &val, sizeof(int));
        if (ret == -1) {
            std::cout << "Failed sending value to server" << std::endl;
            return -1;
        }
    }
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    ret = read(socket_connection, buffer, BUFFER_SIZE);
    if (ret == -1) {
        std::cout << "Failed to read from the server" << std::endl;
        return -1;
    }

    std::cout << buffer << std::endl;
    close(socket_connection);
}