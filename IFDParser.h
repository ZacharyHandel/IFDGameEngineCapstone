#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class IFDParser{
	public:
	IFDParser(){
		pos = 0;
	   	cout << "Enter the name of the game file you want to play: ";
		//cin >> gameFile;	//This created a bug

		getline(cin, gameFile);		//New file input system (GRADE)
	}

	void tokenIt(){
		string token="";
		string nextLine;
		char c;

	   	ifstream inFile;
	   	inFile.open(gameFile.c_str());

		if(inFile.fail())	//detect for failed file or wrong input
		{
			cout << "This file was either not found or your input was wrong." << endl;
			exit(0);
		}


		while(!inFile.eof()){
			getline(inFile, nextLine);
			trim(nextLine);

			/*********************************
			ASCII GRAPHICS: Tokenizing Images
			*********************************/
			if(nextLine == "<image>")
			{
				token = "\n";
				tokenVec.push_back(nextLine);
				getline(inFile, nextLine);
				while(nextLine.find("</image>") == string::npos)
				{
					token = token + nextLine;
					token = token + "\n";
					getline(inFile, nextLine);
				}
				tokenVec.push_back(token);
				trim(nextLine);
				tokenVec.push_back(nextLine);
				getline(inFile, nextLine);
				trim(nextLine);
				token = "";
			}
			//END OF: Tokenizing Images

		    c=nextLine[0];

			//dump any comment or blank line (all comments exist alone on their lines)
			if(c=='%' || nextLine == ""){
				//do nothing
			}
			else{
				//tokenize the entire line
				//cout<<nextLine<<endl;
				for(int i=0; i<nextLine.length(); i++){
					if(nextLine[i] == '>'){
						token = token + nextLine[i];
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
					}
					else if(nextLine[i]=='<'){
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
						token = token + nextLine[i];
					}
					else{
						token = token + nextLine[i];
					}
				}
			}
		}//while !eof
		inFile.close();
		return;
	}// end of tokenIt()

	void eatToken(){
		pos++;
	}

	string getNext(){
		return tokenVec[pos];
	}

	//helpre function for trimming a string's white space
	void trim(string& s)
    	{
       	size_t p = s.find_first_not_of(" \t");
       	s.erase(0, p);
    		p = s.find_last_not_of(" \t");
       	if (string::npos != p)
          		s.erase(p+1);
    	}

	void printTokens(){
		cout<<":::Printing the Tokens in Order:::"<<endl;
		for(int i=0; i<tokenVec.size(); i++){
			cout<<i<<": "<<tokenVec[i]<<endl;
		}
	}



	private:
		int pos;
		string gameFile;
        vector<string> tokenVec;    //token- each unit of meaning is a token <game> </game>
};
