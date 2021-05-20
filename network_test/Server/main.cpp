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
        string resolution;
    };

    vector<player> clients;
    sf::TcpSocket socket1, socket2;


    size_t received_1, received_2;
    sf::TcpListener listener;
    listener.listen(2000, ip);
    for(int i = 0; i < 2; i++) {
        cout << "SERVER on IP: " << ip << endl;
        player p;
        clients.push_back(p);
        string text = "Connected to server!";
        if(i == 0) {
            char buffer[2000];
            listener.accept(socket1);
            socket1.receive(buffer, sizeof(buffer), received_1);
            cout << buffer << endl;
            clients[i].username = buffer;

        }
        else
        {
            char buffer[2000];
            listener.accept(socket2);
            socket2.receive(buffer, sizeof(buffer), received_2);
            cout << buffer << endl;
            clients[i].username = buffer;
        }


        //clients[i].resolution = buffer;

    }
    std::string text_1 = "1";
    std::string text_2 = "-1";
    socket1.send(text_1.c_str(), text_1.length() + 1);
    socket2.send(text_2.c_str(), text_2.length() + 1);
/*    std::string text = "";
    if(std::stoi(clients[0].resolution) > std::stoi(clients[1].resolution)) text = clients[1].resolution;
    else text = clients[0].resolution;
    socket1.send(text.c_str(), text.length() + 1);
    socket2.send(text.c_str(), text.length() + 1);*/

    bool done = false;
    std::string message_1, message_2;
    while(!done){
        //text = "sent from server...";
        //socket.send(text.c_str(), text.length() + 1);
        for(int i = 0; i < clients.size(); i++) {
            if(i == 0) {
                char buffer[20000];
                socket1.receive(buffer, sizeof(buffer), received_1);
                message_1 = buffer;
                if (buffer != clients[i].old_m)
                    std::cout << "Received from " << clients[i].username << ": " << message_1 << endl;
                clients[i].old_m = buffer;
                if (buffer == "stop") done = true;
            }
            else {
                char buffer[20000];
                socket2.receive(buffer, sizeof(buffer), received_2);
                message_2 = buffer;
                if (buffer != clients[i].old_m)
                    std::cout << "Received from " << clients[i].username << ": " << message_2  << endl;
                clients[i].old_m = buffer;
                if (buffer == "stop") done = true;
            }
        }


        for(int i = 0; i < clients.size(); i++) {
            if(i == 0) {
                socket1.send(message_2.c_str(), message_2.length() + 1);
            }
            else {
                socket2.send(message_1.c_str(), message_1.length() + 1);
            }
        }

    }
    return 0;
}