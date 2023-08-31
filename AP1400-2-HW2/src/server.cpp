#include "server.h"
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <random>
#include <regex>

using std::runtime_error;
/*
class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id);
	double get_wallet(std::string id);
	bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
	bool add_pending_trx(std::string trx, std::string signature);
	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};
*/
Server::Server() {
    this->clients = {};
}

std::string randNums() {
    std::string nums = "";

    for (int i = 0; i < 4; i++) {
        nums += std::to_string(rand() % 10);
    }

    return nums;
}
/*
    This function will create a new *Client* with the specified `id`. 
    If this `id` already exists, the server should add a random 4 
    digit number at the end of it automatically.
    UPDATE:each client should be assigned with 5 coins at the begining.
    note.do not use *srand* for your random numbers.
 */
std::shared_ptr<Client> Server::add_client(std::string id) {
    bool isExist = false;

    for (const auto& [client, amount] : this->clients) {
        if (client->get_id() == id) {
            isExist = true;
            break;
        }
    }

    std::string ID = id;
    if (isExist)
    {
        ID = id + randNums();
    }
    //shared_ptr Instantiation
    std::shared_ptr<Client> ptrClient(new Client(ID, *this));
    this->clients[ptrClient] = 5;
    return ptrClient;
}

/*
    Using this function you can get a 
    pointer to a Client using its `id`.
*/
std::shared_ptr<Client> Server::get_client(std::string id) {
    for (const auto& [client, amount] : this->clients) {
        if (client->get_id() == id) {
            return client;
        }
    }
}

/*
    Using this function will return the wallet 
    value of the client with username `id`.
*/
double Server::get_wallet(std::string id) {
    for (const auto& [client, amount] : this->clients) {
        if (client->get_id() == id) {
            return amount;
        }
    }
}

/*
    Each transaction has 3 properties:  id of the sender 
    ii)id of the receiver iii)value of money to transfer.
    We will show each transaction with a string, 
    concatenating each of these properties with a `-`. 
    For example if *ali* sends *1.5* coins to *hamed* the 
    transaction will be shown by a string `"ali-hamed-1.5"`.
    This function will parse this string format and 
    outputting each property separately, if the string is not
    standard you should throw a runtime error
*/
bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value) {
    
    std::regex pattern(R"((\w+)-(\w+)-((\w+).*(\w+)))");

    std::smatch match;

    if (std::regex_match(trx, match, pattern)) {
        sender = match[1];
        receiver = match[2];
        value = std::stod(match[3]);
        return true;
    } else {
        throw runtime_error("Something wrong.");
    }
    return false;
}

/*
    Each Client  can add a pending transaction using the 
    transaction format described in the above section.
    Only accept a pending transaction by authenticating the
    sender's signature and if he has enough money in his 
    wallet.
    define the below variable <ins>outside</ins> the 
    `Server` class and save the pending transactions in it.
    std::vector<std::string> pending_trxs;
*/
bool Server::add_pending_trx(std::string trx, std::string signature) {
    
}


size_t Server::mine() {

}

