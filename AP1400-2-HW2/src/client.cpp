#include "client.h"
#include "crypto.h"

Client::Client(std::string id, const Server& server): id(id), server(&server) {    
    std::string public_key = "", private_key = "";
    crypto::generate_key(public_key, private_key);
    this->public_key = public_key;
    this->private_key = private_key;
}

std::string Client::get_id() {
    return this->id;
}

/*
    Returns the Client's public key.
*/
std::string Client::get_publickey() const {
    return this->public_key;
}

/*
    Returns the amount of money the client has.
*/
double Client::get_wallet() {
    Server *tempServer =  (Server *)this->server;
    return tempServer->get_wallet(id);
}

/*
    signs the input with the private key 
    and returns the signature.
*/
std::string Client::sign(std::string txt) const {
    return crypto::signMessage(this->private_key, txt);
}

/*
    Creates a transaction in the server according 
    to its inputs. To create a transaction use the 
    specified string format described in above
    sections and sign the final transaction string 
    with your private key. use both your signature 
    and your transaction signature to create a pending
    transaction in the Server using *add_pending_trx* 
    function.
*/
bool Client::transfer_money(std::string receiver, double value) {
    std::string trx = this->get_id() + "-" + receiver + "-" + std::to_string(value);

    std::string signature = crypto::signMessage(this->private_key, trx);

    return this->server->add_pending_trx(trx, signature);
}

/*
    Returns a random number as a 
    nonce so the server uses it for mining.
*/
size_t Client::generate_nonce() {

}