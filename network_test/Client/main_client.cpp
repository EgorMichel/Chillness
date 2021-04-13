//
// Created by egorchan on 12.04.2021.
//

using namespace std;
#include <iostream>
#include <SFML/Network.hpp>
#include <string>

int main(){
    sf::TcpSocket socket;
    char buffer[2000];
    string text = "Connected to: ";
    size_t received;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    cout << "CLIENT" << endl;
    socket.connect(ip, 2000);
    text += "client";
    socket.send(text.c_str(), text.length());
    socket.receive(buffer, sizeof(buffer), received);
    cout << buffer << endl;
    return 0;
}