/*******************************************************************************
ASCII GRAPHICS: GraphicalUseItem
*******************************************************************************/

#include <string>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class GraphicalUseItem : public UseItem
{
private:
	
	string image;
	
public: 

	GraphicalUseItem()
	{
		type = "graphicaluse";
	}

	void setImage(string s)
	{
		image = s;
	}
	
	void displayImage()
	{
		cout << image;
	}
};
