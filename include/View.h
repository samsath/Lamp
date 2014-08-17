/*
 * View.h
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#ifndef VIEW_H_
#define VIEW_H_

/*
 * This will be the class that controls the lamp shades and light bulb on/off
 */
class View {
public:
	View();
	virtual ~View();
	void change(bool light, int stat);
	int getStatues();
	bool getLight();
private:
	int statues;
	bool lightStat;
	void setStatues(int state);
	void setLigth(bool type);

};

#endif /* VIEW_H_ */
