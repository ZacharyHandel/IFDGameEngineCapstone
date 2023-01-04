#include "MapV2.h"
#include "Combat.h"

//#include "Player.h"

#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class Game{
	protected:
		MapV2* map = new MapV2;
		Player* player1;

		/************************************
		 COMBAT SYSTEM: NEW COMBAT OBJECT
		************************************/
		Combat* combat;
  	public:
		Game(){
			player1 = map->getPlayer();
			player1->setCurrent(map->getStart());
			
		}	
    
  		void play()
		{
      		string userInput = "u";
      		while(true)
			{		
				//check game status
				if(player1->isGameOver() != 0){
					player1->getCurrent()->info->displayArea();
					return;	// END THE GAME HERE
				}


				//CHECK FOR COMBAT HERE
				//if combatID == 1
				/****************************************
				 COMBAT SYSTEM: CHECK FOR COMBAT ID
				****************************************/
				if(player1->getCurrent()->info->getCombatID() == 1)	//If there is combat
				{
						combat->displayCombatMessage();	//display message
						combat->engageCombat(player1);	//starty combat event
				}
				//display area data
				if(player1->playerMoved() && (userInput == "u" || userInput == "d" || userInput == "l" || userInput == "r")){
	    				player1->getCurrent()->info->displayArea();
				}
				else{
					if(userInput == "u" || userInput == "d" || userInput == "l" || userInput == "r"){
						cout<<"There appears to be no way to go that direction."<<endl;
					}
				}
		
				//get movement selection
				cout<<"Which way would you like to go?  Enter u, d, l, or r"<<endl;
				getline(cin, userInput);
			
				//update area
				if(userInput == "u"){
					player1->setCurrent(player1->getCurrent()->u);
				}
				else if(userInput == "d"){
					player1->setCurrent(player1->getCurrent()->d);
				}
				else if(userInput == "l"){
					player1->setCurrent(player1->getCurrent()->l);
				}
				else if(userInput == "r"){
					player1->setCurrent(player1->getCurrent()->r);
				}
				else if(userInput == "iseedeadpeople"){ //issdeadpeople cheat code to reveal map
					cout<<map;
				}
				else if(userInput == "reset"){
					resetGame();
				}
				else if(userInput == "exit"){
					cout<<"Good bye!"<<endl;
					return;
				}
				else if(userInput == "search"){
					player1->getCurrent()->info->search();
				}
				else if(userInput == "inventory"){
					player1->inventory();
				}
				else if(userInput == "take"){
					player1->take();
				}
				else if(userInput == "leave"){
					player1->leave();
				}
				else if(userInput == "examine"){
					player1->examine();
				}
				else if(userInput == "use")
				{
					player1->use(map);
				}
				else if(userInput == "consume")
				{
					player1->consume(map);
				}
				else if(userInput == "stats")
				{
					player1->reportStats();
				}
				else if(userInput == "help"){
					cout<<"You may type: "<<endl;
					cout<<"\t u, d, l, or r: to move up, down, left or right on the map,"<<endl;
					cout<<"\t search: to search for items in current area,"<<endl;	
					cout<<"\t take: to attempt to take an item,"<<endl;
					cout<<"\t leave: to attempt to leave an item,"<<endl;
					cout<<"\t examine: to examine an item in your inventory,"<<endl;
					cout<<"\t use: to use an item in your inventory,"<<endl;	
					cout<<"\t consume: to consume an item in your inventory,"<<endl;
					cout<<"\t stats: to report players stats,"<<endl;			
					cout<<"\t reset: to reset the game,"<<endl;
					cout<<"\t exit: to exit the game."<<endl;
					cout << endl << endl;
					cout << "Combat Rules: " << endl;
					cout << "You are given 3 options to type (1, 2, or 3)." << endl;
					cout << "At random, if you choose the correct number, you will deal damage to the enemy." << endl;
					cout << "However, if you choose the wrong number, you take damage." << endl;
					cout<<endl;
				}
				else{
					cout<<"I do not understand: "<<userInput<<endl<<endl;
				}

				
			}//end while		
    	}//end play()

		void resetGame(){
			player1->setCurrent(map->getStart());
			//remove item from player list
			player1->items.destroyList();
			//remove item from each area in turn
			player1->resetPlayerStats();
			map->resetItems();
			map->resetCombat();	//added comat reset!!!
		}
};