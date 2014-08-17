/*
 * Source.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#include "Source.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <crafter.h>

// for the database
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

Source::Source() {
	std::cout << "Source Created" << std::endl;

}

Source::~Source() {
	std::cout << "Source Deleted" << std::endl;
}

void Source::update(){
}

Lamp* Source::getLamp(){
	return model;
}

int Source::getStatues(){
	return statues;
}

Wifi::Wifi(Lamp* mod, int stat, std::string IPadr, std::string mac){
    std::cout << "Wifi created" << std::endl;
	IPaddress = IPadr;
	MAC = mac;
	model = mod;
	statues = stat;
	lastCheck = 0;
	interf = "wlan0";
}

Wifi::~Wifi(){
    std::cout << "Wifi Deleted" << std::endl;
}

void Wifi::update(){
    // First it gets the required values from the LAMP class.
    IPaddress = model->getYourDeviceIP();
    MAC = model->getYourDeviceMAC();

    // sees if the right person is close to the lamp and sets the statues on the LAMP class.
	if(ping()){
        model->setYourStatues(2);
	}else{
        model->setYourStatues(1);
	}

	//updates the MAC address on the LAMP file.
	model->setYourDeviceMAC(MAC);
}

bool Wifi::ping(){
    /*
    * This will be the program that pings the mobile device and then see what is then returned.
    * Code comes from an example for http://code.google.com/p/libcrafter/
    */
    // This sets up the ping
	std::string myIP = Crafter::GetMyIP(interf);
	std::string myMAC = Crafter::GetMyMAC(interf);

	Crafter::Ethernet ether_Header;
	ether_Header.SetSourceMAC(myMAC);
	ether_Header.SetDestinationMAC("ff:ff:ff:ff:ff:ff");

	Crafter::ARP arp_header;
	arp_header.SetOperation(Crafter::ARP::Request);
	arp_header.SetSenderIP(myIP);
	arp_header.SetSenderMAC(myMAC);

	// Define Network Scan
	std::vector<std::string> net = Crafter::GetIPs("192.168.1.*");
	std::vector<std::string>::iterator ip_adr;

	// Set up the Packets and then send them out and wait for the reply
	std::vector<Crafter::Packet*> request_packets;

	for(ip_adr = net.begin() ; ip_adr != net.end() ; ++ip_adr){
        arp_header.SetTargetIP(*ip_adr);

        Crafter::Packet* packet = new Crafter::Packet;
        packet->PushLayer(ether_Header);
        packet->PushLayer(arp_header);

        request_packets.push_back(packet);

	}

	std::vector<Crafter::Packet*> replies_packets(request_packets.size());
	Crafter::SendRecv(request_packets.begin(),request_packets.end(), replies_packets.begin(), interf,0.1,2,48);

	std::vector<Crafter::Packet*>::iterator it_pk;
	int counter = 0;
	bool found = false;
	for(it_pk = replies_packets.begin() ; it_pk < replies_packets.end() ; ++it_pk){
        Crafter::Packet* reply_packet = (*it_pk);

        if(reply_packet){
            Crafter::ARP* arp_Pack = reply_packet->GetLayer<Crafter::ARP>();
            std::string rp_IP = arp_Pack->GetSenderIP();
            std::string rp_MAC = arp_Pack->GetSenderMAC();
            if(rp_IP == IPaddress){
                if(!MAC.compare(NULL)){
                    MAC = rp_MAC;
                }else{
                    if(MAC == rp_MAC){
                        found = true;
                        break;

                    }
                }
            }else{
                // This then see's if the device is registered on a different IP
                if(MAC == rp_MAC){
                    found = true;
                    break;

                }
            }
            counter++;

        }

        // Delete the container content
        for(it_pk = request_packets.begin() ; it_pk < request_packets.end(); ++it_pk){
            delete (*it_pk);
        }
        for(it_pk = replies_packets.begin() ; it_pk < replies_packets.end(); ++it_pk){
            delete (*it_pk);
        }

        if(found){
            // return here saying the device was found
            return true;
        }else{
            return false;
        }
	}

}

File::File(Lamp* mod, int stat, std::string fileLoc){
    std::cout << "File created" << std::endl;
	model = mod;
	statues = stat;
	FileLoc = fileLoc;
}

File::~File(){
    std::cout << "File Deleted" << std::endl;
}

void  File::update(){
    // This reads the file and then returns it as a vector
    readFile();
    writeFile();

}

void File::writeFile(){
	std::ofstream outputFile;
	outputFile.open(FileLoc.c_str());

	outputFile << model->getYourName() << std::endl;
	outputFile << model->getYourDeviceIP() << std::endl;
	outputFile << model->getPersonName() << std::endl;
	outputFile << model->getServerURL() << std::endl;
	outputFile << model->getServerUsername() << std::endl;
	outputFile << model->getServerPassword() << std::endl;
	outputFile << model->getYourDeviceMAC() << std::endl;

	outputFile.close();
}

void File::readFile(){
	std::vector<std::string>results;
	std::ifstream myFile(FileLoc.c_str()); // /var/www/LampData.dat
	/*
	*   this file will consist of different strings, with each one on a different line.
	*   YourName
	*   DeviceIP
	*   PersonName
	*   ServerURL
	*   ServerUsername
    *   ServerPassword
    *   YourMacAddress
	*/
	std::string line;
	while(std::getline(myFile,line)){
        std::stringstream s(line);
        while(!s.eof()){
            std::string tmp;
            s >> tmp;
            results.push_back(tmp);
        }
	}
	std::cout << results.size() << std::endl;
	if(results.size() >= 1){
        model->setYourName(results.at(0));
        model->setYourDeviceIP(results.at(1));
        model->setPersonName(results.at(2));
        model->setServerURL(results.at(3));
        model->setServerUsername(results.at(4));
        model->setServerPassword(results.at(5));
        if(results.size() == 7){
            if(!model->getYourDeviceMAC().compare("")){
                model->setYourDeviceMAC(results.at(6));
            }
        }else{
        model->setYourDeviceMAC("");
        }
	} else {
	std::cout << "No files loaded to results file is = " << FileLoc.c_str() << std::endl;
	}

}

Server::Server(Lamp* mod, int stat, std::string ServUrl, std::string User, std::string Pwd){
    std::cout << "Server Created" << std::endl;
	model = mod;
	statues = stat;
	ServerURL = ServUrl;
	Username = User;
	Password = Pwd;
	Port = ":3306";
	PersonStates = 0;

}

Server::~Server(){
    std::cout << "Server Deleted" << std::endl;
}

void Server::update(){
    setUser(model->getServerUsername());
    setPwd(model->getServerPassword());
    setURL(model->getServerURL());
    connect(model->getYourName(),model->getYourStatues(),model->getPersonName());
	model->setPersonStatues(PersonStates);
}

void Server::setUser(std::string uname){
	Username = uname;
}

void Server::setPwd(std::string pass){
	Password = pass;
}

void Server::setURL(std::string url){
	ServerURL = url;
}



std::string Server::getUsr(){
	return Username;
}

std::string Server::getPss(){
	return Password;
}

std::string Server::getURL(){
	return ServerURL;
}



void Server::connect(std::string You, int YourSt, std::string Person){

    /*
    * 	The Database schema
    *
    *	==============================
    *	==			DataBase		==
    *	==__________________________==
    *	==		   lamppeople		==
    *	==	Name	  ==	Statues	==
    *	==	1		  ==	Home	==
    *	==	2		  ==	Work	==
    *	==	3	 	  ==	Out		==
    *	==============================
    *
    */

	try{
	    sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        // Create a connection
	    driver = get_driver_instance();
	    con = driver->connect(ServerURL+Port,Username,Password);
	    con->setSchema("test");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT Statues From lamppeople WHERE Name ='" + Person + "';");
        while (res->next()){
                // this then gets the statues of the person from the database.
            PersonStates = res->getInt("Statues");
        }

        std::ostringstream oss;
        oss << "UPDATE lamppeople SET Statues=" << YourSt << " WHERE Name='" << You << "';";

        stmt->executeQuery(oss.str());
        delete res;
        delete stmt;
        delete con;

        } catch (sql::SQLException &e) {
          std::cout << "# ERR: SQLException in " << __FILE__;
          std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
          std::cout << "# ERR: " << e.what();
          std::cout << " (MySQL error code: " << e.getErrorCode();
          std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }



}


