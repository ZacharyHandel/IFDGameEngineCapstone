#ifndef HPSPP_H
#define HPSPP_H
    #include "Player.h"
    //#include "Map.h"
#endif

class BasicPlayer : public Player
{
    private:
        //no new private attributes
        string type = "basic";
    public:

        string getType()
        {
            return type;
        }

        int getHP()
        {
            return -1;
        }

        int isGameOver()
        {
            if(currentLocation->info->getID() == 1)
            {
                return 2;
            }
            else if(currentLocation->info->getGoal() == 1)
            {
                return 1;
            }
            else if(currentLocation->info->getID() == 0 && currentLocation->info->getGoal() == 0)
            {
                return 0;
            }
            else
            {
                return 0;
            }
        }

		void resetPlayerStats()
        {
            cout << "Basic players do not have stats to reset." << endl;
        }

		void reportStats()
        {
            cout << "Basic players do not have stats to report." << endl;
        }

		void consume(Map* mapptr)
        {
            cout << "Basic Players cannot consume items." << endl;
        }

        void use(Map* mapptr)
        {
            bool found = false;
            bool goodLocation = false;
            string n;

            nodeType<Item*>* temp = items.getFirst();

            if(temp == NULL)
            {
                cout << "You have no items in your inventory." << endl;
            }
            else
            {
                cout << "Use what item?" << endl;
                getline(cin, n);
                
                while(temp != NULL && !found)
                {
                    if(n == temp->info->getName())
                    {
                        found = true;
                        if(temp->info->getActiveArea() == 0 || temp->info->getActiveArea() == mapptr->reverseLookUp(currentLocation))
                        {
                            goodLocation = true;
                        }
                    }
                    else
                    {
                        temp = temp->link;
                    }
                }

                if(!found)
                {
                    cout << "No items by that name in your inventory." << endl;
                }
                else if(temp->info->getType().find("use") == string::npos)
                {
                    cout << "There's no way to use this item." << endl;
                }
                else
                {
                    if(goodLocation)
                    {
                        cout << temp->info->getActiveMessage() << endl;
                        dealWithRules(temp->info->getItemUseRules(), mapptr);
                    }
                    else if(!goodLocation)   //not the right room
                    {
                        cout << "This might work in another location, but not here." << endl;
                    }
                }
            }
        }

        void dealWithRules(vector<Rule*> rules, Map* mapptr)
        {
            for(int i = 0; i < rules.size(); i++)
            {
                mapptr->updateRule(rules[i]);
            }
        }

        void takeCombatDamage()
        {
            //impliment basic player combat
            cout << "THIS IS A TEMPORARY DEBUG***" << endl;
        }
};