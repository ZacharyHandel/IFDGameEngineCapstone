#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //??
#include <stdlib.h>

#ifndef MAN_H
#define MAP_H
#include "IFDParser.h"
#include "LinkData.h"
#include "Area.h"
//#include "Item.h"
#endif

/***************************************
ASCII GRAPHICS: Graphical Area Inclusion
***************************************/
#include "GraphicalArea.h"
//END: Graphical Area Inclusion

using namespace std;

struct areaNode
{
	/***************************
	ASCII GRAPHICS: Area pointer
	***************************/
	Area *info;
	//END OF: Area pointer

	areaNode *u;
	areaNode *d;
	areaNode *l;
	areaNode *r;
};


class Map{
	protected:
		vector<areaNode*> areasVec;
		int areacnt;

		//Here is the instance of IFDParser
	  	IFDParser parser;

		//Some additional class attributes here
        vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;

	public:
		//Map();

		/************************************
		ASCII GRAPHICS: makeArea() to virtual
		************************************/
		virtual void makeArea(){
			int id;
			int goal;
			string xstr;

			areaNode* tempNodePtr = new areaNode;

			while(nextToken != "</area>"){
				if(nextToken == "<desc>"){
					parser.eatToken();
					nextToken = parser.getNext();

					tempNodePtr->info->setDescription(nextToken);    //go to the object pointed to by tempNodePtr
				}
				else if(nextToken == "<feats>"){
					parser.eatToken();
					nextToken = parser.getNext();

					istringstream ss(nextToken);
          				getline(ss, xstr, ',');
          				tempNodePtr->info->setID(atoi(xstr.c_str()));

          				getline(ss, xstr, ',');
					tempNodePtr->info->setGoal(atoi(xstr.c_str()));
				}
				else if(nextToken == "</desc>" || nextToken == "</feats>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}

				parser.eatToken();
				nextToken = parser.getNext();
			}//while !</area>

			//add area to vector
			areasVec.push_back(tempNodePtr);

		} //end makeArea()

		void makeLinks(){
			//cout << "Inside makeLinks***" << endl;
			string xstr;
			int u, d, l, r;
			//cout << "Outside while !</links>***" << endl;
			while(nextToken != "</links>"){
				//cout << "Inside while != </links>***" << endl;
				if(nextToken == "<linkset>"){
					//cout << "Inside if <linkset>***" << endl;
					parser.eatToken();
			  		nextToken = parser.getNext();

					//cout << "Creating new linkDataPointer***" << endl;
					LinkData* tempLDPtr = new LinkData;

					//cout << "Before Assigning directions***" << endl;
					istringstream ss(nextToken);
        				getline(ss, xstr, ',');
        				u = atoi(xstr.c_str());
        				getline(ss, xstr, ',');
        				d = atoi(xstr.c_str());
					getline(ss, xstr, ',');
        				l = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					r = atoi(xstr.c_str());
					//cout << "After Assigning directions***" << endl;

					//cout << "Before setDigits***" << endl;
					tempLDPtr->setDigits(u, d, l, r);
					//cout << "After setDigits***" << endl;
						//cout << "Pushing to linkVec***" << endl;
          				linkVec.push_back(tempLDPtr);

				}
				else if(nextToken == "</linkset>"){
					//cout << "DETECTION OF DO NOTHING FOR </linkset>***" << endl;
					//do nothing
				}
				else{
					cout<<"Parse Error Location 3"<<endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
			  	nextToken = parser.getNext();
			}//while !</links>
		}//makeLinks()

		void linkNewLinks(int curRm, int destRm, char dir)	//member function to link new links from use items
		{
			if(dir == 'u')
				areasVec[curRm-1]->u = areasVec[destRm-1];
			else if(dir == 'd')
				areasVec[curRm-1]->d = areasVec[destRm-1];
			else if(dir = 'l')	
				areasVec[curRm-1]->l = areasVec[destRm-1];
			else if(dir = 'r')
				areasVec[curRm - 1]->r = areasVec[destRm-1];
			else
				cout << "ERROR: INCORRECT DIRECITON INDICATION IN IFD FILE! Check rule for correct letter (u,d,l,r)." << endl;

		}

		void linkLinks(){
			for(int i=0; i<linkVec.size(); i++){
					areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
					areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
					areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
					areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
			}
		}


		areaNode* getStart(){
			return areasVec[0];  //returns a pointer to the first area listed
		}

		areaNode* getVecAtIndex(int i){
			return areasVec[i];
		}

		int reverseLookUp(areaNode* addy){
			for(int i=0; i<areasVec.size(); i++){
				if(areasVec[i] == addy){
					return i+1;
				}
			}
			//this should not happen
			return -1;
		}

		void updateRule(Rule* rlptr)
		{
			if(rlptr->direction == 'u')
			{
				areasVec[rlptr->beginRm -1]->u = areasVec[rlptr->destRm -1];
			}
			if(rlptr->direction == 'd')
			{
				areasVec[rlptr->beginRm -1]->d = areasVec[rlptr->destRm -1];
			}
			if(rlptr->direction == 'l')
			{
				areasVec[rlptr->beginRm -1]->l = areasVec[rlptr->destRm -1];
			}
			if(rlptr->direction == 'r')
			{
				areasVec[rlptr->beginRm -1]->r = areasVec[rlptr->destRm -1];
			}
		}

		friend ostream& operator << (ostream& output, Map& map)	//new output overload (GRADE HERE)
		{
			output<<"******************************************************************"<<endl;
			output<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			output<<"******************************************************************"<<endl;
			for(int i=0; i<map.areasVec.size(); i++){
				cout<<"This is area: "<<i+1<<endl;
				cout<<map.areasVec[i]->info->getDescription()<<endl;
				if(map.areasVec[i]->info->getID() == 1){
					cout<<"Area is INSTADEATH."<<endl;
				}
				if(map.areasVec[i]->info->getGoal() == 1){
					cout<<"Area is GOAL."<<endl;
				}
				output<<"Connections:"<<endl;
				output<<"\t u: Area #"<<map.reverseLookUp(map.areasVec[i]->u)<<endl;
				output<<"\t d: Area #"<<map.reverseLookUp(map.areasVec[i]->d)<<endl;
				output<<"\t l: Area #"<<map.reverseLookUp(map.areasVec[i]->l)<<endl;
				output<<"\t r: Area #"<<map.reverseLookUp(map.areasVec[i]->r)<<endl;
			}
			return output;
		}
/*
		void print(){
			cout<<"******************************************************************"<<endl;
			cout<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			cout<<"******************************************************************"<<endl;
			for(int i=0; i<areasVec.size(); i++){
				cout<<"This is area: "<<i+1<<endl;
				cout<<areasVec[i]->info.getDescription()<<endl;
				if(areasVec[i]->info.getID() == 1){
					cout<<"Area is INSTADEATH."<<endl;
				}
				if(areasVec[i]->info.getGoal() == 1){
					cout<<"Area is GOAL."<<endl;
				}
				cout<<"Connections:"<<endl;
				cout<<"\t u: Area #"<<reverseLookUp(areasVec[i]->u)<<endl;
				cout<<"\t d: Area #"<<reverseLookUp(areasVec[i]->d)<<endl;
				cout<<"\t l: Area #"<<reverseLookUp(areasVec[i]->l)<<endl;
				cout<<"\t r: Area #"<<reverseLookUp(areasVec[i]->r)<<endl;
			}
		}

*/
};
