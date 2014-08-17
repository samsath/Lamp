/*
 * Lamp.h
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#ifndef LAMP_H_
#define LAMP_H_
#include <string>
#include <vector>
#include "View.h"
#include "Source.h"

class Source;

class Lamp {
public:
	Lamp(std::string name);
	virtual ~Lamp();
	void attach (Source* src);
	void setStatues (int val);
	int getStatues ();
	void checker (); // This will go through the sources and call their update method.
	bool getLamp ();
	void setLamp (bool statues);
	bool getShade ();
	void setShade (bool statues);
	void setLampName(std::string Name);
	std::string getLampName ();

	std::string getYourName();
	void setYourName(std::string name);
	std::string getYourDeviceIP();
	void setYourDeviceIP(std::string ip);
	int getYourStatues();
	void setYourStatues(int state);
	std::string getYourDeviceMAC();
	void setYourDeviceMAC(std::string mac);
	std::string getPersonName();
	void setPersonName(std::string name);
	int getPersonStatues();
	void setPersonStatues(int state);
	std::string getServerURL();
	void setServerURL(std::string url);
    std::string getServerUsername();
    void setServerUsername(std::string name);
    std::string getServerPassword();
    void setServerPassword(std::string pwd);
    std::vector<std::string> getFileContent();
    void setFileContent(std::vector<std::string> lis);

protected:
	std::string LampName;
	int statues;
	std::vector<Source*> source;
	std::string YourName;
	std::string YourDeviceIP;
	int YourStatues;
	std::string YourDeviceMAC;
	std::string PersonName;
	int PersonStatues;
	std::string ServerURL;
	std::string ServerUsername;
	std::string ServerPassword;
	std::vector<std::string> filecontent;

private:
	bool UseLamp; // this will be to turn the light on or off
	bool UseShade; // This will be if to rotate the shade
	View* partView { };


};

#endif /* LAMP_H_ */
