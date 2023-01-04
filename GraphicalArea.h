/*******************************************************************************
ASCII GRAPHICS: GraphicalArea
*******************************************************************************/

#ifndef AREA
#define AREA
	#include "Area.h"
#endif

class GraphicalArea : public Area
{
private: 

	string image;

public: 

	GraphicalArea()
	{
		type = "graphicalarea";
	}
	
	void setImage(string s)
	{
		image = s;
	}
	
	void displayImage()
	{
		cout << image;
	}
	
	void displayArea()
	{
		displayImage();
		cout<<description<<endl;		
    }
};
