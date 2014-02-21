#include <iostream>
#include <conio.h>
#include <string>
#include "hw5.h"
using namespace std;

Move BattleMage::move(const std::vector<Object>& list){
	if( getToughness() < 3 ){
		Move heal;
		heal.mType = HEAL;
		heal.relativeX = 0;
		heal.relativeY = 0;
		return heal;
	}
	else{ // like a wizard
		if (getMana() > 0){
			Wizard::move(list);
		}
		else
		{
			Cleric::move(list);
		}
	}
}
void BattleMage::operator++(){
	increaseToughness( getActionPower()   );
}
