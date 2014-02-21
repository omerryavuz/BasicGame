#include <iostream>
#include <conio.h>
#include <string>
#include "hw5.h"
using namespace std;


Move Cleric::move(const std::vector<Object>& list){
	Side currentSide = getSide();
	int mostImportantForAct;
	int mostImportantForSight;
	vector<ObjectType> unwanted;
	unwanted.push_back(CLERIC);
	unwanted.push_back(FOOD);
	unwanted.push_back(WALL);
	vector<int> sight;
	vector<int> act_positions ;

	if(currentSide == SOUTH){
		sight = findSightArea(list,NORTH,5);
	}
	else{
		sight = findSightArea(list,SOUTH,5);
	}
	vector<int> act = findActArea(list,sight, unwanted  ,currentSide,3);
	int theMostImportant;
	vector<int>  eliminatedEnemys ;

	for(int i=0 ; i< act.size() ; i++){
		theMostImportant = findTheMostImportant(list,act,unwanted,eliminatedEnemys);
		if(theMostImportant != -1){
			Move heal;
			heal.mType = HEAL;
			heal.relativeX = list[theMostImportant].relativeX;
			heal.relativeY = list[theMostImportant].relativeY;
			return heal;
		}
		eliminatedEnemys.push_back(act[i]);
	}

	eliminatedEnemys.clear();
	;
	for(int i=0 ; i< sight.size() ; i++){

		theMostImportant = findTheMostImportant(list,sight,unwanted,eliminatedEnemys);
 		if(theMostImportant != -1){
			// close the most important creature
			act_positions.clear();
			act_positions = generatePositions(3);
			int result = findClosestPosition(list,act_positions,theMostImportant);
			if(result != -1){
				Move close ;
				close.mType = WALK;
				close.relativeX = act_positions[2*result];
				close.relativeY = act_positions[2*result + 1];
				return close;
			}
		}
		eliminatedEnemys.push_back(sight[i]);
	}
	
	// move randomly
	act_positions  = generatePositions(3);
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
void Cleric::operator++(){
	
	increaseToughness( getActionPower()   );
}

