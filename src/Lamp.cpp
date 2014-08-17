/*
 * Lamp.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#include <string>
#include <vector>
#include <stdlib.h>
#include "Lamp.h"
#include "Source.h"
#include "View.h"

Lamp::Lamp(std::string name) {
    std::cout << "Lamp created" << std::endl;
	LampName= name;
	statues = 0;
	UseLamp = true;
	UseShade = true;
	partView = new View();
	YourStatues = 0;
	PersonStatues = 0;
	YourName = "";


}

Lamp::~Lamp() {
    std::cout << "Lamp Deleted" << std::endl;
}

void Lamp::attach(Source* src){
	// TODO sort out this vector stuff
	source.push_back(src);
}

void Lamp::setStatues(int val){
	statues = val;
}

int Lamp::getStatues(){
	return statues;
}


void Lamp::checker(){
	/*
	 * TODO This will go through the source vector and run the update methods of all the devices.
	 */
	 for(unsigned i = 0; i < source.size(); i++){
            source.at(i)->update();

            /* dont think i need this to complicated
            try{
                File* fileget = dynamic_cast<File*>(source.at(i));
                fileget->update();
            }catch(std::bad_cast bcf) {
                std::cout << "Not a file class: " << bcf.what() << std::endl;
                try{
                    Wifi* wifiget = dynamic_cast<Wifi*>(source.at(i));
                    wifiget->update();
                }catch(std::bad_cast bcw) {
                    std::cout << "Not a wifi class: " << bcw.what() << std::endl;
                    try{
                        Server* serverget = dynamic_cast<Server*>(source.at(i));
                        serverget->update();
                    }catch(std::bad_cast bcs){
                        std::cout << "Not a Server class: " << bcs.what() << std::endl;
                    }
                }

            }
            */

    }
    if(getPersonStatues() == 2){
        partView->change(true,PersonStatues);
    }else{
        partView->change(false,PersonStatues);
    }


}

bool Lamp::getLamp(){
	return UseLamp;
}

bool Lamp::getShade(){
	return UseShade;
}

void Lamp::setLamp(bool statues){
	UseLamp = statues;
}

void Lamp::setShade(bool statues){
	UseShade = statues;
}

void Lamp::setLampName(std::string Name){
	LampName = Name;
}

std::string Lamp::getLampName(){
	return LampName;
}

void Lamp::setYourName(std::string name){
    YourName = name;
}

std::string Lamp::getYourName(){
    return YourName;
}

std::string Lamp::getYourDeviceIP(){
    return YourDeviceIP;
}

void Lamp::setYourDeviceIP(std::string ip){
    YourDeviceIP = ip;
}

int Lamp::getYourStatues(){
    return YourStatues;
}

void Lamp::setYourStatues(int state){
    YourStatues = state;
}

std::string Lamp::getYourDeviceMAC(){
    return YourDeviceMAC;
}

void Lamp::setYourDeviceMAC(std::string mac){
    YourDeviceMAC = mac;
}

std::string Lamp::getPersonName(){
    return PersonName;
}

void Lamp::setPersonName(std::string name){
    PersonName = name;
}

int Lamp::getPersonStatues(){
    return PersonStatues;
}

void Lamp::setPersonStatues(int state){
    PersonStatues = state;
}

std::string Lamp::getServerURL(){
    return ServerURL;
}

void Lamp::setServerURL(std::string url){
    ServerURL = url;
}

std::string Lamp::getServerUsername(){
    return ServerUsername;
}

void Lamp::setServerUsername(std::string name){
    ServerUsername = name;
}

std::string Lamp::getServerPassword(){
    return ServerPassword;
}

void Lamp::setServerPassword(std::string pwd){
    ServerPassword = pwd;
}

std::vector<std::string> Lamp::getFileContent(){
    return filecontent;
}

void Lamp::setFileContent(std::vector<std::string> lis){
    filecontent = lis;
}

