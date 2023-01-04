#ifndef AREA_H
#define AREA_H

#include <string>
#include <iostream>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	//#include "Item.h"
    #include "UseItem.h"
    #include "ConsumeItem.h"
#endif

using namespace std;

class Area{
  public:

    /******************************
  	ASCII GRAPHICS: initialize type
  	******************************/
  	Area()
  	{
  		type = "basic";
	}
	//END OF: initialize type

    void setDescription (string desc){
    	description = desc;
    }

    void setGoal(bool g){
	goal = g;		
    }
    
    void setID(bool id){
	instadeath = id;		
    }

    string getDescription(){
    	return description;
    }

    bool getID(){
    	return instadeath;
    }

    bool getGoal(){
	return goal;
    }

    /********************************************
     COMBAT SYSTEM: CREATEING SETTERS AND GETTERS
    ********************************************/
    void setCombatID(bool cID)
    {
        combatID = cID;
    }

    bool getCombatID()
    {
        return combatID;
    }
    
    /********************************************************
    ASCII GRAPHICS: Necessary method alterations/declerations
    ********************************************************/
    virtual void displayArea(){
	cout<<description<<endl;		
    }
    
    virtual void setImage(string s)
    {
    	cout << "DEBUG WARNING: Objects of the Area (basic area) class don't have images. \n";
	}
	//END OF: Necessary method alterations/declerations
    
    uLList<Item*> items;

    void search()
    {
        if(items.isEmptyList())
        {
            cout << "No items in this area." << endl;
        }
        else
        {
            nodeType<Item*> *tempPointer = items.getFirst();
            cout << "The following items are in this area: " << endl;
            while(tempPointer != NULL)
            {
                cout << "\t" << tempPointer->info->getName() << endl;
                tempPointer = tempPointer -> link;
            }
            
        }
    }

    
  protected:
     string description;
     bool instadeath;
     bool goal;	
     /************************************
      COMBAT SYSTEM: SETTING COMBAT ID ATTRIBUTE
     ************************************/
     bool combatID;
     /*******************
     ASCII GRAPHICS: type
     *******************/
     string type;
     //END OF: type
};

#endif