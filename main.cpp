#include <iostream>
#include <string>
#include "Lamp.h"
#include "Source.h"
#include "View.h"


int main()
{
    // this allows the program to run
    bool run = true;

    // this sets up all the classes so that the program runs
    Lamp* lampy = new Lamp("lampy");
    File* spec = new File(lampy,0,"../../html/LampHTML/LampData.dat");
    lampy->attach(spec);
    Wifi* wif = new Wifi(lampy,0,0,0);
    lampy->attach(wif);
    Server* sev = new Server(lampy,0,"db525534725.db.1and1.com","dbo525534725","lcar1990");
    lampy->attach(sev);

    // so while the program runs it will go through the list and check all the updates
    while(run){

        lampy->checker();
    }

    // deletes the classes after wards
    delete sev;
    delete wif;
    delete spec;
    delete lampy;


}
