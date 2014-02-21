#include <iostream>
#include <conio.h>
#include <string>
#include "hw5.h"
using namespace std;

Move Wizard::move(const std::vector<Object>& list){
	Side currentSide = getSide();
	int x,y;
	int mostImportantForAct;

	vector<int> eliminatedEnemys;
	vector<int> act_positions ;
	vector<int> act;
	vector<int> sight;
	vector<ObjectType> unwanted;

	if(getMana() > 0){
		unwanted;unwanted.push_back(WALL);unwanted.push_back(FOOD);unwanted.push_back(CLERIC);
		unwanted.push_back(DRAGON);unwanted.push_back(DWARF);unwanted.push_back(HUMAN);
		sight = findSightArea(list,currentSide,7);
		act = findActArea(list,sight,unwanted,currentSide,7);
		for(int i=0;i<act.size() ; i++){
			mostImportantForAct = findTheMostImportant(list,act,unwanted,eliminatedEnemys);
			if(mostImportantForAct != -1){						
				Move freeze ;
				freeze.mType = FREEZESPELL;
				freeze.relativeX = list[mostImportantForAct].relativeX;
				freeze.relativeY = list[mostImportantForAct].relativeY;
				mana--;
				return freeze;
			}
			eliminatedEnemys.push_back(act[i]);
		}
		unwanted.clear();
		unwanted.push_back(WALL);unwanted.push_back(FOOD);unwanted.push_back(WIZARD);
		unwanted.push_back(BATTLEMAGE);
		sight.clear();
		act.clear();
		sight = findSightArea(list,currentSide,7);
        act = findActArea(list,sight,unwanted,currentSide,7);
		eliminatedEnemys.clear();
		for(int i=0; i<act.size() ; i++){	
			mostImportantForAct = findTheMostImportant(list,act,unwanted,eliminatedEnemys);
			if(mostImportantForAct != -1){						
				Move freeze ;
				freeze.mType = WEAKENSPELL;
				freeze.relativeX = list[mostImportantForAct].relativeX;
				freeze.relativeY = list[mostImportantForAct].relativeY;
				mana--;
				return freeze;
			}
			eliminatedEnemys.push_back(act[i]);
		}
	}
	unwanted.clear();
	unwanted.push_back(WALL);unwanted.push_back(FOOD);
	sight.clear();
	sight = findSightArea(list,currentSide,7);
	eliminatedEnemys.clear();
	for(int i=0;i<sight.size() ; i++){
		mostImportantForAct = findTheMostImportant(list,sight,unwanted,eliminatedEnemys);
		if(mostImportantForAct != -1){
			// move close the most important enemy	
				act_positions = generatePositions(7);
				int result = findClosestPosition(list,act_positions,mostImportantForAct);
				if(result != -1){
					Move close ;
					close.mType = WALK;
					close.relativeX = act_positions[2*result];
					close.relativeY = act_positions[2*result + 1];
					return close;
				}
		}
		eliminatedEnemys.push_back(sight[i]);
			//end of the close the most important enemy
	}
	//move randomly
	act_positions  = generatePositions(7);
	for(int i=0;i< (act_positions.size())/2 ; i++){
		if( isAvailable(list,act_positions[2*i],act_positions[2*i+1] ) ){
			Move random;
			random.mType = WALK;
			random.relativeX = act_positions[2*i];
			random.relativeY = act_positions[2*i+1];
			return random;
		}
	}
	Move noact;
	noact.mType = NOACT;
	noact.relativeX = 0;
	noact.relativeY = 0;
	return noact;
	
}
void Wizard::operator++(){
	mana = mana + 2;
	increaseToughness(3);
}
int Wizard::getMana() const{
	return mana;
}