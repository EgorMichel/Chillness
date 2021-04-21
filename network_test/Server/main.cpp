//Chat Server
//#include "server_network.h"

using namespace std;
#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>

int main(){
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    struct player{
        string old_m = "";
        string username;
    };

    vector<player> clients;
    sf::TcpSocket socket1, socket2;
    char buffer[2000];

    size_t received;
    sf::TcpListener listener;
    listener.listen(2000, ip);
    for(int i = 0; i < 2; i++) {
        cout << "SERVER on IP: " << ip << endl;
        player p;
        clients.push_back(p);
        string text = "Connected to server!";
        if(i == 0) {
            listener.accept(socket1);
            socket1.send(text.c_str(), text.length() + 1);
            socket1.receive(buffer, sizeof(buffer), received);
            cout << buffer << endl;
            clients[i].username = buffer;
        }
        else
        {
            listener.accept(socket2);
            socket2.send(text.c_str(), text.length() + 1);
            socket2.receive(buffer, sizeof(buffer), received);
            cout << buffer << endl;}
            clients[i].username = buffer;

    }
    std::string text = "We are starting!";
    socket1.send(text.c_str(), text.length() + 1);
    socket2.send(text.c_str(), text.length() + 1);

    bool done = false;
    std::string received_1, received_2;
    while(!done){
        //text = "sent from server...";
        //socket.send(text.c_str(), text.length() + 1);
        for(int i = 0; i < clients.size(); i++) {
            if(i == 0) {
                socket1.receive(buffer, sizeof(buffer), received);
                received_1 = buffer;
                if (buffer != clients[i].old_m)
                    std::cout << "Received from " << clients[i].username << ": " << buffer << endl;
                clients[i].old_m = buffer;
                if (buffer == "stop") done = true;
            }
            else {
                socket2.receive(buffer, sizeof(buffer), received);
                received_2 = buffer;
                if (buffer != clients[i].old_m)
                    std::cout << "Received from " << clients[i].username << ": " << buffer << endl;
                clients[i].old_m = buffer;
                if (buffer == "stop") done = true;
            }
        }

        for(int i = 0; i < clients.size(); i++) {
            if(i == 0) {
                socket1.send(received_2.c_str(), received_2.length() + 1);
            }
            else {
                socket2.send(received_1.c_str(), received_1.length() + 1);
            }
        }

    }
    return 0;
}