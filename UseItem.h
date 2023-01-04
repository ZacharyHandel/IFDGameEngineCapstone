#ifndef CONSUME_H
#define CONSUME_H
#include "Item.h"
#endif

using namespace std;

class UseItem : public Item
{
    private:
        vector<Rule*> rulesVec;
    public:
        UseItem()
        {
            type = "use";
        }

        void setActiveMessage(string s)
        {
            activeMessage = s;
        }

        string getActiveMessage()
        {
            return activeMessage;
        }

        void setActiveArea(int a)
        {
            activeArea = a;
        }

        int getActiveArea()
        {
            return activeArea;
        }

        vector<Rule*> getItemUseRules()
        {
            return rulesVec;
        }

        void addRule(Rule* temp)
        {
            rulesVec.push_back(temp);
        }    
};