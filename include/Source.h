/*
 * Source.h
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#ifndef SOURCE_H_
#define SOURCE_H_
#include <string>
#include <vector>
#include "Lamp.h"
#include <crafter.h>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Lamp;

/*
 * This is the base class for the different data storage types.
 * So hopefully the lamp will go through and get dynamic cast to the correct type and update or probe
 * for the right information then it will be displayed by the lamp.
 */
class Source {
private:

protected:
    Lamp *model;
    int statues;
public:
	Source();
	virtual ~Source();
	virtual void update();
	Lamp* getLamp();
	int getStatues();
};

/*
 * Dedicated to probing the wifi connection vier the dongle and ping a set IP address.
 */
class Wifi : public Source {
public:
	Wifi(Lamp* mod, int stat, std::string IPadr,std::string mac);
	virtual ~Wifi();
	void update();
protected:
private:
	bool ping();
	std::string IPaddress;
	std::string MAC;
	long lastCheck;
	int statues;
	std::string interf;
};


/*
 * This will get the information for the webUI and keep the lamp upto date. Tranfer by text or xml files.
 */
class File : public Source {
public:
	File(Lamp* mod, int stat, std::string fileLoc);
	virtual ~File();
	void update();
protected:
    std::string FileLoc;
private:
	std::vector<std::string> Data;
	void readFile();
	void writeFile();
};

/*
 * This is the web server which transfers the information between the different devices.
 */
class Server : public Source {
public:
	Server(Lamp* mod, int stat, std::string ServUrl, std::string User, std::string Pwd);
	virtual ~Server();
	void update(); // May need some handskake and time checker here to make sure the information is the right one propergated
	void setUser(std::string uname);
	void setPwd(std::string pass);
	void setURL(std::string url);
	std::string getUsr();
	std::string getPss();
	std::string getURL();

protected:
    int PersonStates;

private:
	std::string ServerURL;
	std::string Username;
	std::string Password;
	std::string Port;
	void connect(std::string You, int YourSt, std::string Person);
};

#endif /* SOURCE_H_ */
