/*******************************************************************************
ASCII GRAPHICS: GraphicalBasicItem
*******************************************************************************/

#include <string>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class GraphicalBasicItem : public Item
{
private:
	
	string image;
	
public: 

	GraphicalBasicItem()
	{
		type = "graphicalbasic";
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
