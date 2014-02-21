#include <iostream>
#include <conio.h>
#include <string>
#include "hw5.h"
using namespace std;

//-----------------------------------------------------------------Human  --------------------------------------------------------------------------------------                          
Move Human::move(const std::vector<Object>& list){
	Side currentSide = getSide();
	vector<ObjectType> unwanted;unwanted.push_back(WALL);unwanted.push_back(FOOD);
	vector<int> sight = findSightArea(list,currentSide,5);
	vector<int> act = findActArea(list,sight,unwanted,currentSide,3);
	vector<int> eliminatedEnemys ;
	int mostImportantForAct ;


	for(int i=0 ; i < act.size() ; i++ ){
		mostImportantForAct = findTheMostImportant(list,act,unwanted,eliminatedEnemys);
		if(mostImportantForAct != -1){						
			Move attack ;
			attack.mType = HUMANATTACK;
			attack.relativeX = list[mostImportantForAct].relativeX;
			attack.relativeY = list[mostImportantForAct].relativeY;
			return attack;
		}
		eliminatedEnemys.push_back(act[i]);
	}
	int mostImportantForSight;
	eliminatedEnemys.clear();
	for(int i=0 ; i< sight.size() ; i++){
		// close the most important
		mostImportantForSight =  findTheMostImportant(list,sight,unwanted,eliminatedEnemys);
		if(mostImportantForSight != -1){
		///--------------------------------------------- find the closest position of the most important --------------------------------------------------------------- 
			vector<int> act_positions = generatePositions(3);
			int result = findClosestPosition(list,act_positions,mostImportantForSight);
			//----------------------------------------------------------------------------------------------------------------------------------------------------------
			if ( result != -1){ 
				Move close ;
				close.mType = WALK;
				close.relativeX = act_positions[2*result];
				close.relativeY = act_positions[2*result + 1];
				return close;
				// end of close the most important enemy
			}		
		}
		eliminatedEnemys.push_back(sight[i]);
	}





    //-------------------------------------------------------------------------------------------------------------------
	// move the food
	int foodIndex = -1;
	for(int i=0;i<list.size() ; i++){
		if(list[i].objType == FOOD && (abs(list[i].relativeX)<2) && (abs(list[i].relativeY)<2) ){
			Move food;
			food.mType = WALK;
			food.relativeX = list[i].relativeX;
			food.relativeY = list[i].relativeY;
			return food;
		}
	}
	// end of the move the food
	
	// move randomly
	int act_positions[16] = {-1,1, -1,0 ,-1,-1 ,0,1 ,0,-1, 1,1, 1,0, 1,-1};
	for(int i=0;i<8 ; i++){
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
void Human::operator++(){
	increaseToughness(1);
}