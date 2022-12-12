#include <iostream>
#include <thread>
#include <TCPNetworking/client/tcp_client.h>



using namespace TCP;

int main(int argc, char* argv[]) {
    TCPClient client {"localhost", 1337};

    client.onMessage= [](const std::string& message) {
        std::cout << message;
    };

    std::thread t { [&client] () {
        client.Run();
    }};

    while (true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);
    }

    client.Stop();
    t.join();
    return 0;
}