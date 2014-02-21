#include "hw5.h"
#include <iostream>
#define N 7
#include <conio.h>
using namespace std;

void printmove(Move mv)
{
	switch(mv.mType)
	{
		case WALK: cout << "movetype: " << "WALK" << endl;break;
		case HUMANATTACK: cout << "movetype: " << "HUMANATTACK" << endl;break;
		case DWARFATTACK: cout << "movetype: " << "DWARFATTACK" << endl;break;
		case DRAGONPAW: cout << "movetype: " << "DRAGONPAW" << endl;break;
		case DRAGONFIRE: cout << "movetype: " << "DRAGONFIRE" << endl;break;
		case HEAL: cout << "movetype: " << "HEAL" << endl;break;
		case FREEZESPELL: cout << "movetype: " << "FREEZESPELL" << endl;break;
		case WEAKENSPELL: cout << "movetype: " << "WEAKENSPELL" << endl;break;
		case NOACT: cout << "movetype: " << "NOACT" << endl;break;
	}
	cout << "x: " << mv.relativeX << endl;
	cout << "y: " << mv.relativeY << endl;
}

void vectorprint(const std::vector<Object>& list)
{
	for(int i=0;i<list.size();i++)
	{
		cout << "*************creature: " << i << "**************" <<endl;
		if(list[i].teamSide == NORTH)
			cout << "side: " << "NORTH" << endl;
		if(list[i].teamSide == SOUTH)
			cout << "side: " << "SOUTH" << endl;
			
		switch(list[i].objType)
		{
			case BATTLEMAGE:cout << "objecttype: " << "BATTLEMAGE" << endl;break;
			case WIZARD:cout << "objecttype: " << "WIZARD" << endl;break;
			case CLERIC:cout << "objecttype: " << "CLERIC" << endl;break;
			case HUMAN:cout << "objecttype: " << "HUMAN" << endl;break;
			case DWARF:cout << "objecttype: " << "DWARF" << endl;break;
			case DRAGON:cout << "objecttype: " << "DRAGON" << endl;break;
			case FOOD:cout << "objecttype: " << "FOOD" << endl;break;
			case WALL:cout << "objecttype: " << "WALL" << endl;break;
		}
		
		cout << "x: " << list[i].relativeX << " and " << "y: " << list[i].relativeY << endl;
		cout << (list[i].bewitched) << endl;
		
		cout << "************************************************" << endl;
	}
}
void printTable(vector<Object> list){
	char table[N][N];
	for(int i=0;i<N;i++){
		for(int j = 0 ; j< N ; j++){
			table[i][j] = '-'; 	
		}
	}
	
	for(int i=0; i<list.size() ; i++){
		
		switch(list[i].objType){
		
			case BATTLEMAGE:
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2] = 'B';
				break;
			case WIZARD :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2]= 'W';
				break;
			case CLERIC :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2] = 'C';
				break;
			case HUMAN :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2] = 'H';
				break;
			case DWARF :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2] = 'D';
				break;
			case DRAGON :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2] = 'E';
				break;
			case FOOD:
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2]= 'F';
				break;
			case WALL :
				table[-list[i].relativeY + N/2][list[i].relativeX + N/2]= 'X';
				break;
		}
	}
	for(int i=0;i<N;i++){
		for(int j = 0 ; j< N ; j++){
			cout << table[i][j] << " ";  	
		}
		cout << endl;
	}
		
}
int main()
{
	vector<Object> s1;
	Object o1 = {NORTH,BATTLEMAGE,0,1,true};
	Object o2 = {SOUTH,DWARF,0,0,false}; //kendim
//	Object o3 = {NORTH,HUMAN,-1,-1,false};
//	Object o4 = {SOUTH,HUMAN,0,1,false};
	Object o5 = {NORTH,WIZARD,1,1,true};
	Object o6 = {SOUTH,BATTLEMAGE,-1,-1,true};
//	Object o7 = {SOUTH,WALL,1,-1,false};
	
	Dwarf dw1(SOUTH,2,10);
	
	s1.push_back(o1);
	s1.push_back(o2);
//	s1.push_back(o3);
//	s1.push_back(o4);
	s1.push_back(o5);
	s1.push_back(o6);
//	s1.push_back(o7);
	
	printmove(dw1.move(s1));


	printTable(s1);
	
	_getch();
	return 0;
}
