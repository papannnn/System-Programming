#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/SocketTutorial"
#define BUFFER_SIZE 128

int main () {
    unlink(SOCKET_NAME);
    int connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connection_socket == -1) {
        std::cout << "Failed creating socket" << std::endl;
        return -1;
    }

    sockaddr_un name;
    memset(&name, 0, sizeof(name));
    name.sun_family = AF_UNIX;
    // strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
    strcpy(name.sun_path, SOCKET_NAME);

    int ret = bind(connection_socket, reinterpret_cast<const sockaddr*>(&name), sizeof(sockaddr_un));
    if (ret == -1) {
        std::cout << "Failed creating bind" << std::endl;
        return -1;
    }

    ret = listen(connection_socket, 1);
    if (ret == -1) {
        std::cout << "Failed creating listen" << std::endl;
        return -1;
    }

    while (true) {
        std::cout << "Waiting for accept()" << std::endl;

        int data_socket = accept(connection_socket, NULL, NULL);
        if (data_socket == -1) {
            std::cout << "Data socket failed" << std::endl;
            return -1;
        }

        int result = 0;
        char buffer[BUFFER_SIZE];
        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            std::cout << "Waiting data from client" << std::endl;
            ret = read(data_socket, buffer, BUFFER_SIZE);
            if (ret == -1) {
                std::cout << "Read failed" << std::endl;
                return -1;
            }
            int data;
            memcpy(&data, buffer, sizeof(int));
            if (data == 0) break;
            result += data;
        }

        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "Value is: %d", result);

        std::cout << "Result: " << result << std::endl;
        ret = write(data_socket, buffer, BUFFER_SIZE);
        if (ret == -1) {
            std::cout << "Failed write" << std::endl;
            return -1;
        }

        close(data_socket);
    }
    close(connection_socket);
    unlink(SOCKET_NAME);
}