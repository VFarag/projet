#pragma once

#include "../registration/models.hpp"

class Card;
class Location;
class Client;


class Bank {

};


class Account {
    private:
        Bank &bank;
        Client &client;
        Card &card;
        double amount;
};


class Advisor: public User {
    private:
        Bank &bank;
};


class Client: public User {
    private:
        Advisor &advisor;
        double cash;
};


class ATM {
    private:
        Bank &bank;
        Location &location;

    public:
        explicit ATM();

};
