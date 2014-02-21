#include <iostream>
#include <conio.h>
#include <string>
#include "hw5.h"
using namespace std;

Move Dragon::move(const std::vector<Object>& list){
	int neighbouring[16] = {-1,1, -1,0 ,-1,-1 ,0,1 ,0,-1, 1,1, 1,0, 1,-1};
	Side side = getSide();
	vector<int> neighbourList;
	vector<ObjectType> unwanted;
	unwanted.push_back(WALL);unwanted.push_back(FOOD);
	int x,y;
	for( int i=0 ; i < list.size()  ; i++ ){
		for(int k = 0  ; k < 8 ; k++){
			x = 0 + neighbouring[2*k];
			y = 0 + neighbouring[2*k + 1];
			if(x == list[i].relativeX && y == list[i].relativeY && list[i].teamSide != side && list[i].bewitched == false){                    //find the neighbours
				neighbourList.push_back(i);
				break;
			}
		}
	}
	vector<int> eliminatedEnemys;
	int theMostImportant = findTheMostImportant(list,neighbourList,unwanted,eliminatedEnemys);
	if(theMostImportant != -1){
		Move paw;
		paw.mType = DRAGONPAW;
		paw.relativeX = list[theMostImportant].relativeX;
		paw.relativeY = list[theMostImportant].relativeY;
		return paw;
	}

	vector<int> sight = findSightArea(list,side,7);
	vector<int> act   = findActArea(list,sight,unwanted,side,7);
	unwanted.push_back(DWARF);
	for(int i= 0 ; i< act.size() ; i++){

		theMostImportant = findTheMostImportant(list,act,unwanted,eliminatedEnemys);
		if(theMostImportant != -1 && getLeftFireCount() > 0 ){
			Move fire ;
			fire.mType = DRAGONFIRE;
			fire.relativeX = list[theMostImportant].relativeX;
			fire.relativeY = list[theMostImportant].relativeY;
			leftFireCount--;
			return fire;
		}
		eliminatedEnemys.push_back(act[i]);
	}
	
	unwanted.pop_back();
	eliminatedEnemys.clear();
	vector<int> act_positions;
	for(int i=0;i<sight.size() ; i++){	
		
		theMostImportant = findTheMostImportant(list,sight,unwanted,eliminatedEnemys);
		if(theMostImportant != -1){
			// move closer to most important enemy
			act_positions.clear();
			act_positions = generatePositions(7);
			int result = findClosestPosition(list,act_positions,theMostImportant);
			if(result != -1){
				Move close ;
				close.mType = WALK;
				close.relativeX = act_positions[2*result];
				close.relativeY = act_positions[2*result + 1];
				return close;
			}
			//end of the close the most important enemy

		}
		eliminatedEnemys.push_back(sight[i]);
	}

		// move the food
	int foodIndex = -1;
	for(int i=0;i<list.size() ; i++){
		if(list[i].objType == FOOD && (abs(list[i].relativeX)<4) && (abs(list[i].relativeY)<4) ){
			Move food;
			food.mType = WALK;
			food.relativeX = list[i].relativeX;
			food.relativeY = list[i].relativeY;
			return food;
		}
	}
	
	// end of the move the food
	// move randomly
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
void Dragon::operator++(){
	leftFireCount++;
	increaseToughness(1);
}
int Dragon::getLeftFireCount() const{
	return leftFireCount;
}


