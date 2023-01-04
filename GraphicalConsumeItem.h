/*******************************************************************************
ASCII GRAPHICS: GraphicalConsumeItem
*******************************************************************************/

#include <string>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class GraphicalConsumeItem : public ConsumeItem
{
private:
	
	string image;
	
public: 

	GraphicalConsumeItem()
	{
		type = "graphicalconsume";
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
