/*
 * View.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#include "View.h"
#include "wiringPi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>
#include <iostream>

View::View() {
    std::cout << "View Created" << std::endl;
	statues = 0;
	lightStat =false;

}

View::~View() {
    std::cout << "View Deleted" << std::endl;
}


void View::change(bool light, int stat){
	setStatues(stat);
	setLigth(light);
}
int View::getStatues(){
	return statues;
}

bool View::getLight(){
	return lightStat;
}

void View::setStatues(int state){
	/*
	 * This will change the servo position on to the state
	 * these positions are all based on a 90degree servo, if the servo could move more
	 * then it would have higher position numbers.
	 */

	if (wiringPiSetup () ==-1){
		std::cout << "WiringPiSetup Failed" << std::endl;
		exit(1);
	}

	pinMode(17, OUTPUT);
	digitalWrite(17,LOW);

	softPwmCreate(0,0,200);
	int pos =0;
	switch(state){
					case 0:
						// starting and not home
						pos = 1;
						std::cout << "Shade is set to person NOT at Home" << std::endl;
						break;
					case 1:
						// midpoint maybe at work
						pos = 15;
						std::cout << "Shade is set to person at WORK" << std::endl;
						break;
					case 2:
						// full is home
						pos = 25;
						std::cout << "Shade is set to person at HOME" << std::endl;
						break;
					default:
						// go back to start
						pos =1;
						std::cout << "Shade is set to person NOT at home" << std::endl;
						break;
	}
	softPwmWrite(0,pos);

	delay(1000);


}

void View::setLigth(bool type){
	/*
	 * This wont be implemented in this prototype as need a greater hardware skill.
	 * But the idea was to have a Relay here which would then turn the lamp light
	 * on and off.
	 */
	if(type == true){
		std::cout << "Light is on" << std::endl;
	}else{
		std::cout << "Light is OFF" << std::endl;
	}
}
