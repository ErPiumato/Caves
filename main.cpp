#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

enum MainAction {newgame, record, credits, endgame};
enum InGameAction {w, a, s, d, attack, grab, drink, inventory, talk, give, help, escape};
enum MapObject {nothing, skeleton, trap, potion, gold, stair, amulet, yondor};

struct Player
{
	int health_point = 100;
	int gold = 0;
	int potions = 0;
	bool amulet = 0;
	bool yondor = 0;
	bool finish = 0;
	int position;
};

struct Skeleton
{
	int health_point = 12;
	int damange = 2;
};

struct CaveNode
{
	MapObject object;
	bool discovered = 0;
	Skeleton skeleton;
	bool trap = 0;
	CaveNode* next;
};

CaveNode* createListOfCaveNode(MapObject object);
void pushACaveNode(MapObject object, CaveNode* head);
MapObject returnAObjectInACaveNodeByIndex(CaveNode* head, int position);
bool returnIfACaveNodeIsDiscoveredByIndex(CaveNode* head, int position);
void turnACaveNodeObjectToNothing(CaveNode* head, int position);
void discoverACaveNodeByIndex(CaveNode* head, int position);
void printListOfCaveNode(CaveNode* head);
void deleteACaveNodeByIndex(CaveNode* &head, int position);

MainAction takeUserChoiceByPrintingMenu();
InGameAction takeUserInGameChoiceByPrintingMenu();
CaveNode* mapGenerator(int seed);
void mapDrestructor(CaveNode* first_cave); //da sistemare--------------------------------------------
void activateATrapInACaveNode(CaveNode* head, int position);
void deactivateATrapInACaveNode(CaveNode* head, int position);
bool returnIfATrapInACaveNodeIsActivated(CaveNode* head, int position);
void inizializeATrapInACaveNode(CaveNode* head, int position);
void inizializeASkeletonInACaveNode(CaveNode* head, int position);
void demangeSkeletonInACaveNode(CaveNode* head, Player &player);
int returnHealthPointOfASkeletonIACaveNode(CaveNode* head, int position);
int findStair(CaveNode* first_cave);
int findAmulet(CaveNode* first_cave);
void showMap(CaveNode* first_cave, Player player);

void wAction(Player &player);
void aAction(Player &player);
void sAction(Player &player);
void dAction(Player &player);
void attackAction(CaveNode* first_cave, Player &player);
void drinkAction(Player &player);
void grabAction(CaveNode* first_cave, Player &player);
void inventoryAction(Player player);
void talkAction(CaveNode* first_cave, Player &player);
void giveAction(CaveNode* first_cave, Player &player);
void helpAction();
void exitAction(CaveNode* first_cave, Player &player);

void saveGameInHistory(Player player, int seed);
int returnGoldInRecord();
void saveGameAsARecord(Player player, int seed);
void showRecord();
void showCredits();



int main()
{
	srand(time(NULL));
	MainAction choice;
	InGameAction action;
	CaveNode* map_first_cave;
	int seed;
	Player player;
	string enter;

	do
	{	
		system("clear");
		choice = takeUserChoiceByPrintingMenu();
		
		if(choice == newgame)
		{
			system("clear");
			seed = rand();
			map_first_cave = mapGenerator(seed);
			player.position = findStair(map_first_cave);
			discoverACaveNodeByIndex(map_first_cave, player.position);
			player.health_point = 100;
			player.gold = 0;
			player.potions = 0;
			player.amulet = 0;
			player.yondor = 0;
			player.finish = 0;
			
			while((player.health_point > 0) && (player.finish == 0))
			{
				showMap(map_first_cave, player);
				action = takeUserInGameChoiceByPrintingMenu();

				switch(action)
				{
					case w:
						system("clear");
						wAction(player);
						discoverACaveNodeByIndex(map_first_cave, player.position);
						if(returnAObjectInACaveNodeByIndex(map_first_cave, player.position) == trap)
						{
							if(returnIfATrapInACaveNodeIsActivated(map_first_cave, player.position))
							{
								cout<<endl<<"a trap demange you: -25 health point"<<endl<<endl;
								player.health_point -= 25;
								deactivateATrapInACaveNode(map_first_cave, player.position);
							}
						}
						
						break;
					case a:
						system("clear");
						aAction(player);
						discoverACaveNodeByIndex(map_first_cave, player.position);
						if(returnAObjectInACaveNodeByIndex(map_first_cave, player.position) == trap)
						{
							if(returnIfATrapInACaveNodeIsActivated(map_first_cave, player.position))
							{
								cout<<endl<<"a trap demange you: -25 health point"<<endl<<endl;
								player.health_point -= 25;
								deactivateATrapInACaveNode(map_first_cave, player.position);
							}
						}
						
						break;
					case s:
						system("clear");
						sAction(player);
						discoverACaveNodeByIndex(map_first_cave, player.position);
						if(returnAObjectInACaveNodeByIndex(map_first_cave, player.position) == trap)
						{
							if(returnIfATrapInACaveNodeIsActivated(map_first_cave, player.position))
							{
								cout<<endl<<"a trap demange you: -25 health point"<<endl<<endl;
								player.health_point -= 25;
								deactivateATrapInACaveNode(map_first_cave, player.position);
							}
						}
						
						break;
					case d:
						system("clear");
						dAction(player);
						discoverACaveNodeByIndex(map_first_cave, player.position);
						if(returnAObjectInACaveNodeByIndex(map_first_cave, player.position) == trap)
						{
							if(returnIfATrapInACaveNodeIsActivated(map_first_cave, player.position))
							{
								cout<<endl<<"a trap demange you: -25 health point"<<endl<<endl;
								player.health_point -= 25;
								deactivateATrapInACaveNode(map_first_cave, player.position);
							}
						}
						
						break;
					case attack:
						system("clear");
						attackAction(map_first_cave, player);
						
						break;
					case drink:
						system("clear");
						drinkAction(player);
						
						break;
					case grab:
						system("clear");
						grabAction(map_first_cave, player);
						
						break;
					case inventory:
						system("clear");
						inventoryAction(player);
						
						break;
					case talk:
						system("clear");
						talkAction(map_first_cave, player);
						
						break;
					case give:
						system("clear");
						giveAction(map_first_cave, player);
						
						break;
					case help:
						system("clear");
						helpAction();
						
						break;
					case escape:
						system("clear");
						exitAction(map_first_cave, player);
						
						break;
				}
			}

			if(player.health_point <= 0)
			{
				cout<<endl<<"game over"<<endl<<endl;
			}

			saveGameInHistory(player, seed);

			if(returnGoldInRecord() < player.gold)
			{
				saveGameAsARecord(player, seed);
			}
			
			cout<<endl<<"click enter to continue"<<endl<<endl;
			getline(cin, enter);

			//mapDrestructor(map_first_cave);
		}
		else if(choice == record)
		{
			system("clear");
			showRecord();
			
			cout<<endl<<"click enter to continue"<<endl<<endl;
			getline(cin, enter);
		}
		else if(choice == credits)
		{
			system("clear");
			showCredits();

			cout<<endl<<"click enter to continue"<<endl<<endl;
			getline(cin, enter);
		}
		else if (choice == endgame)
		{
			system("clear");
			
		}
		else
		{
			cout<<endl<<"signal: unexpected choice"<<endl<<endl;
		}
	}
	while(choice != endgame);

	cout<<endl<<"see you next time"<<endl<<endl;
}

CaveNode* createListOfCaveNode(MapObject object) //fatto
{
	CaveNode* head = (CaveNode*)malloc(sizeof(CaveNode));
		head->object = object;
		head->next = NULL;

	return head;
}

void pushACaveNode(MapObject object, CaveNode* head) //fatto
{
	int i=1;
	CaveNode* current = head;
	
	CaveNode* body = (CaveNode*)malloc(sizeof(CaveNode));
		body->object = object;
		body->next = NULL;

	while(i == 1)
	{
		if(current->next == NULL)
		{
			current->next = body;
			i=0;
		}
		else
		{
			current = current->next;
		}
	}
}

MapObject returnAObjectInACaveNodeByIndex(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		return current->object;
}

bool returnIfACaveNodeIsDiscoveredByIndex(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		return current->discovered;
}

void turnACaveNodeObjectToNothing(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->object = nothing;
}

void discoverACaveNodeByIndex(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->discovered = 1;
}

void printListOfCaveNode(CaveNode* head) //fatto
{
	int i=1;
	CaveNode* current = head;

	while(i == 1)
	{
		if(current->next == NULL)
		{
			i=0;
		}
		cout<<current->object<<endl;
		current = current->next;
	}
	cout<<endl;
}

void deleteACaveNodeByIndex(CaveNode* &head, int position) //fatto
{
	int i;
	CaveNode* current = head, *del;
	
	for(i=0; i<position-1; i++)
	{
		current = current->next;

		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL) || (current->next == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else if(position == 0)
	{
		del = head;
		head = head->next;
		free(del);
	}
	else
	{
		del = current->next;
		current->next = current->next->next;
		free(del);
	}
}

//--------------------------------------------------------------------------------

MainAction takeUserChoiceByPrintingMenu() //fatto
{
	string choice;
	MainAction action;
	
	cout<<endl<<"----------- Menu -----------"<<endl<<"choose one of the following options by entering the corresponding number"<<endl<<"1 = start a new game"<<endl<<"2 = show current record"<<endl<<"3 = show credits"<<endl<<"4 = exit"<<endl<<endl;
	getline(cin, choice);

	while((choice != "1") && (choice != "2") && (choice != "3") && (choice != "4"))
	{
		cout<<endl<<"the choice entered does not match an existing one, try again"<<endl<<endl;
		getline(cin, choice);
	}

	if(choice == "1")
	{
		action = newgame;
	}
	else if(choice == "2")
	{
		action = record;
	}
	else if(choice == "3")
	{
		action = credits;
	}
	else if(choice == "4")
	{
		action = endgame;
	}
	else
	{
		cout<<endl<<"signal: unexpeted input bypass error checking"<<endl<<endl;
	}

	return action;
}

InGameAction takeUserInGameChoiceByPrintingMenu() //fatto
{
	string choice;
	InGameAction action;
	
	cout<<endl<<"enter the action to be performed"<<endl<<"enter Help for the list of action"<<endl<<endl;
	getline(cin, choice);

	while((choice != "W") && (choice != "w") && (choice != "A") && (choice != "a") && (choice != "S") && (choice != "s") && (choice != "D") && (choice != "d") && (choice != "Attack") && (choice != "attack") && (choice != "Grab") && (choice != "grab") && (choice != "Drink") && (choice != "drink") && (choice != "Inventory") && (choice != "inventory") && (choice != "Talk") && (choice != "talk") && (choice != "Give") && (choice != "give") && (choice != "Help") && (choice != "help") && (choice != "Exit") && (choice != "exit"))
	{
		cout<<endl<<"the action entered does not match an existing one, try again"<<endl<<endl;
		getline(cin, choice);
	}

	if((choice == "W") || (choice == "w"))
	{
		action = w;
	}
	else if((choice == "A") || (choice == "a"))
	{
		action = a;
	}
	else if((choice == "S") || (choice == "s"))
	{
		action = s;
	}
	else if((choice == "D") || (choice == "d"))
	{
		action = d;
	}
	else if((choice == "Attack") || (choice == "attack"))
	{
		action = attack;
	}
	else if((choice == "Grab") || (choice == "grab"))
	{
		action = grab;
	}
	else if((choice == "Drink") || (choice == "drink"))
	{
		action = drink;
	}
	else if((choice == "Inventory") || (choice == "inventory"))
	{
		action = inventory;
	}
	else if((choice == "Talk") || (choice == "talk"))
	{
		action = talk;
	}
	else if((choice == "Give") || (choice == "give"))
	{
		action = give;
	}
	else if((choice == "Help") || (choice == "help"))
	{
		action = help;
	}
	else if((choice == "Exit") || (choice == "exit"))
	{
		action = escape;
	}
	else
	{
		cout<<endl<<"signal: unexpeted input bypass error checking"<<endl<<endl;
		return help;
	}

	return action;
}

CaveNode* mapGenerator(int seed) //fatto
{
	srand(seed);
	CaveNode* first_cave;
	int i, random_num;
	bool stair_chek = 0, amulet_chek = 0, yondor_chek = 0, chek;
	MapObject random_object;

	for(i = 0; i < 64; i++)
	{
		do
		{
			chek = 0;
			random_num = (rand() % 541) + 1;

			if((random_num >= 1) && (random_num <= 100))
			{
				random_object = nothing;
				chek = 1;
			}
			else if((random_num >= 101) && (random_num <= 200))
			{
				random_object = skeleton;
				chek = 1;
			}
			else if((random_num >= 201) && (random_num <= 300))
			{
				random_object = trap;
				chek = 1;
			}
			else if((random_num >= 301) && (random_num <= 400))
			{
				random_object = potion;
				chek = 1;
			}
			else if((random_num >= 401) && (random_num <= 500))
			{
				random_object = gold;
				chek = 1;
			}
			else if((random_num >= 501) && (random_num <= 520) && (stair_chek == 0))
			{
				random_object = stair;
				chek = 1;
				stair_chek = 1;
			}
			else if((random_num >= 521) && (random_num <= 540) && (amulet_chek == 0))
			{
				random_object = amulet;
				chek = 1;
				amulet_chek = 1;
			}
			else if((random_num == 541) && (yondor_chek == 0))
			{
				random_object = yondor;
				chek = 1;
				yondor_chek = 1;
			}
			else
			{
				chek = 0;
			}
		}
		while(chek == 0);

		if(((stair_chek == 0) || (amulet_chek == 0)) && ((i == 62) || (i == 63)))
		{
			if(stair_chek == 0)
			{
				random_object = stair;
				stair_chek = 1;
			}
			else
			{
				random_object = amulet;
				amulet_chek = 1;
			}
		}
		
		if(i == 0)
		{
			first_cave = createListOfCaveNode(random_object);
		}
		else
		{
			pushACaveNode(random_object, first_cave);
		}

		if(random_object == skeleton)
		{
			inizializeASkeletonInACaveNode(first_cave, i);
		}

		if(random_object == trap)
		{
			inizializeATrapInACaveNode(first_cave, i);
		}
	}
		
	return first_cave;
}

void mapDrestructor(CaveNode* first_cave) //fatto
{
	int i;

	for(i = 0; i < 64; i++)
	{
		deleteACaveNodeByIndex(first_cave, 63 - i);
	}
}

void activateATrapInACaveNode(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->trap = 1;
}

void deactivateATrapInACaveNode(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->trap = 0;
}

bool returnIfATrapInACaveNodeIsActivated(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		return current->trap;
}

void inizializeATrapInACaveNode(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->trap = 1;
}

void inizializeASkeletonInACaveNode(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		current->skeleton.health_point = 12;
		current->skeleton.damange = 2;
}

void demangeSkeletonInACaveNode(CaveNode* head, Player &player) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<player.position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((player.position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		if(current->object == skeleton)
		{
			cout<<endl<<"you attacked the skeleton: you do 5 damage to it"<<endl<<endl;
			
			current->skeleton.health_point -= 5;
			
			if(current->skeleton.health_point > 0)
			{
				cout<<endl<<"skeleton: "<<current->skeleton.health_point<<"/12"<<endl<<endl;

				cout<<endl<<"the skeleton attack you: it do 2 damenge to you"<<endl<<endl;
				player.health_point -= current->skeleton.damange;
			}
			else
			{
				cout<<endl<<"you defeated the skeleton: +3 gold"<<endl<<endl;
				turnACaveNodeObjectToNothing(head, player.position);
				player.gold += 3;
			}
		}
}

int returnHealthPointOfASkeletonIACaveNode(CaveNode* head, int position) //fatto
{
	int i;
	CaveNode* current = head;
	
	for(i=0; i<position; i++)
	{
		current = current->next;
		
		if(current == NULL)
			break;
	}
	
	if((position < 0) || (current == NULL))
		cout<<endl<<"<signal: out of list>"<<endl<<endl;
	else
		if(current->object == skeleton)
			return current->skeleton.health_point;
		else
			return -1;
}

int findStair(CaveNode* first_cave) //fatto
{
	int i;

	for(i = 0; i < 64; i++)
	{
		if(returnAObjectInACaveNodeByIndex(first_cave, i) == stair)
		{
			return i;
		}
		else if(i >= 63)
		{
			//cout<<endl<<"signal: there are not stair in this map"<<endl<<endl;
			return -1;
		}
	}
}

int findAmulet(CaveNode* first_cave) //fatto
{
	int i;

	for(i = 0; i < 64; i++)
	{
		if(returnAObjectInACaveNodeByIndex(first_cave, i) == amulet)
		{
			return i;
		}
		else if(i >= 63)
		{
			//cout<<endl<<"signal: there are not amulet in this map"<<endl<<endl;
			return -1;
		}
	}
}

void showMap(CaveNode* first_cave, Player player) //fatto
{
	int i, j;
	MapObject current_object;
	

	for(i = 0; i < 8; i++)
	{
		cout<<"---------------------------------"<<endl;
		cout<<"|";
		
		for(j = 0; j < 8; j++)
		{
			cout<<" ";

			current_object = returnAObjectInACaveNodeByIndex(first_cave, i * 8 + j);
			
			if((returnIfACaveNodeIsDiscoveredByIndex(first_cave, i * 8 + j) == 1) && (player.position != i * 8 + j))
			{
				if(current_object == nothing)
				{
					cout<<"  |";
				}
				else if(current_object == skeleton)
				{
					cout<<"K |";
				}
				else if(current_object == trap)
				{
					cout<<"T |";
				}
				else if(current_object == potion)
				{
					cout<<"H |";
				}
				else if(current_object == gold)
				{
					cout<<"G |";
				}
				else if(current_object == stair)
				{
					cout<<"S |";
				}
				else if(current_object == amulet)
				{
					cout<<"A |";
				}
				else
				{
					cout<<"Y |";
				}	
			}
			else if(player.position == i * 8 + j)
			{
				cout<<"P |";
			}
			else
			{
				cout<<"? |";
			}
		}
		cout<<endl;
	}
	cout<<"---------------------------------"<<endl;
	cout<<"HP: "<<player.health_point<<"/100  current objeck in the cave: ";

	switch(returnAObjectInACaveNodeByIndex(first_cave, player.position))
	{
		case nothing:
			cout<<"nothing"<<endl;
			break;
		case skeleton:
			cout<<"skeleton"<<endl;
			break;
		case trap:
			cout<<"trap"<<endl;
			break;
		case potion:
			cout<<"health potion"<<endl;
			break;
		case gold:
			cout<<"gold"<<endl;
			break;
		case stair:
			cout<<"stair"<<endl;
			break;
		case amulet:
			cout<<"amulet"<<endl;
			break;
		case yondor:
			cout<<"yondor"<<endl;
			break;
	}
}

void wAction(Player &player) //fatto
{
	if(player.position > 7)
	{
		player.position -= 8;
	}
	else
	{
		cout<<endl<<"hit your head against the wall: you take 1 damage"<<endl<<endl;
		player.health_point--;
	}
}

void aAction(Player &player) //fatto
{
	if(player.position % 8 != 0)
	{
		player.position--;
	}
	else
	{
		cout<<endl<<"hit your head against the wall: you take 1 damage"<<endl<<endl;
		player.health_point--;
	}
}

void sAction(Player &player) //fatto
{
	if(player.position < 56)
	{
		player.position += 8;
	}
	else
	{
		cout<<endl<<"hit your head against the wall: you take 1 damage"<<endl<<endl;
		player.health_point--;
	}
}

void dAction(Player &player) //fatto
{
	if((player.position - 7) % 8 != 0)
	{
		player.position++;
	}
	else
	{
		cout<<endl<<"hit your head against the wall: you take 1 damage"<<endl<<endl;
		player.health_point--;
	}
}

void attackAction(CaveNode* first_cave, Player &player) //fatto
{
	MapObject object = returnAObjectInACaveNodeByIndex(first_cave, player.position);
	
	if(object == skeleton)
	{
		demangeSkeletonInACaveNode(first_cave, player);
	}
	else
	{
		if(object == yondor)
		{
			cout<<endl<<"you are not a bad person"<<endl<<endl;
		}
		else
		{
			cout<<endl<<"there is no one around you"<<endl<<endl;
		}
	}
}

void drinkAction(Player &player) //fatto
{
	if((player.potions > 0) && (player.health_point != 100))
	{
		cout<<endl<<"you drank a health potion"<<endl<<endl;
		player.potions--;
		player.health_point += 20;
		
		if(player.health_point > 100)
		{
			player.health_point = 100;
		}
	}
	else if((player.potions > 0) && (player.health_point == 100))
	{
		cout<<endl<<"you already have the maximum health point"<<endl<<endl;
	}
	else
	{
		cout<<endl<<"you have no health potion to drink"<<endl<<endl;
	}
}

void grabAction(CaveNode* first_cave, Player &player) //fatto
{
	MapObject object = returnAObjectInACaveNodeByIndex(first_cave, player.position);
	
	if(object == potion)
	{
		cout<<endl<<"you grab a health potion from the ground"<<endl<<endl;
		player.potions++;
		turnACaveNodeObjectToNothing(first_cave, player.position);
	}
	else if(object == gold)
	{
		cout<<endl<<"you grab a gold coin from the ground"<<endl<<endl;
		player.gold++;
		turnACaveNodeObjectToNothing(first_cave, player.position);
	}
	else if(object == amulet)
	{
		cout<<endl<<"you grab a strange amulet from the ground"<<endl<<endl;
		player.amulet = 1;
		turnACaveNodeObjectToNothing(first_cave, player.position);
	}
	else
	{
		cout<<endl<<"there is nothing to grab here"<<endl<<endl;
	}
}

void inventoryAction(Player player) //fatto
{
	cout<<endl<<"inventory:"<<endl;
	cout<<"gold: "<<player.gold<<endl;
	cout<<"potions: "<<player.potions<<endl;

	if(player.amulet == 1)
	{
		cout<<"amulet: 1"<<endl<<endl;
	}
	else
	{
		cout<<"amulet: 0"<<endl<<endl;
	}
}

void talkAction(CaveNode* first_cave, Player &player) //fatto
{
	MapObject object = returnAObjectInACaveNodeByIndex(first_cave, player.position);
	
	if((object == yondor) && (player.yondor == 0))
	{
		cout<<endl<<"oh traveler, i lost my amulet around here,"<<endl<<"but it's very dark and i can't find it,"<<endl<<"could you help me?"<<endl<<endl;
	}
	else if((object == yondor) && (player.yondor == 1))
	{
		cout<<endl<<"thanks for the help traveler,"<<endl<<"the way out is now open"<<endl<<endl;
	}
	else
	{
		cout<<endl<<"there is no one to talk to here"<<endl<<endl;
	}
}

void giveAction(CaveNode* first_cave, Player &player) //fatto
{
	MapObject object = returnAObjectInACaveNodeByIndex(first_cave, player.position);
	
	if((object == yondor) && (player.yondor == 0) && (player.amulet == 1))
	{
		cout<<endl<<"thanks for the help traveler,"<<endl<<"the way out is now open"<<endl<<endl;
		player.amulet = 0;
		player.yondor = 1;
	}
	else if((object == yondor) && (player.yondor == 0) && (player.amulet == 0))
	{
		cout<<endl<<"traveler, you haven't found my amulet yet"<<endl<<endl;
	}
	else if((object == yondor) && (player.yondor == 1))
	{
		cout<<endl<<"thanks for the help traveler,"<<endl<<"the way out is now open"<<endl<<endl;
	}
	else
	{
		cout<<endl<<"there is no one here you can give something to"<<endl<<endl;
	}
}

void helpAction() //fatto
{
	cout<<endl<<"list of action:"<<endl;
	cout<<"w: move up"<<endl;
	cout<<"a: move left"<<endl;
	cout<<"s: move down"<<endl;
	cout<<"d: move right"<<endl;
	cout<<"attack: attack a monster"<<endl;
	cout<<"drink: drink a potion from your inventory"<<endl;
	cout<<"grab: grab a item from the ground"<<endl;
	cout<<"inventory: show your inventory"<<endl;
	cout<<"talk: talk to a NPC"<<endl;
	cout<<"give: give something to a NPC"<<endl;
	cout<<"help: show list of action"<<endl;
	cout<<"exit: ends the game if the conditions are met (can only be used near stair)"<<endl<<endl;
}

void exitAction(CaveNode* first_cave, Player &player) //fatto
{
	MapObject object = returnAObjectInACaveNodeByIndex(first_cave, player.position);
		
	if((object == stair) && ((player.amulet == 1) || (player.yondor == 1)))
	{
		cout<<endl<<"you managed to escape from the caves"<<endl<<endl;
		player.finish = 1;
	}
	else if((object == stair) && (player.amulet == 0) && (player.yondor == 0))
	{
		cout<<endl<<"you can't leave the caves yet"<<endl<<endl;
	}
	else
	{
		cout<<endl<<"you cannot leave the caves from here"<<endl<<endl;
	}
}

void saveGameInHistory(Player player, int seed)
{
	ofstream file;
	file.open("Game/User/history.txt", ios::app);

	file<<"seed: "<<seed<<endl;
	
	if(player.health_point < 0)
	{
		player.health_point = 0;
	}
	
	file<<"health point: "<<player.health_point<<endl;
	file<<"gold: "<<player.gold<<endl;
	file<<"potions: "<<player.potions<<endl;
	file<<"amulet: "<<player.amulet<<endl;
	file<<"yondor: "<<player.yondor<<endl;
	file<<"finish: "<<player.finish<<endl<<endl;
	
	file.close();
}

int returnGoldInRecord()
{
	string line;
	int gold = 0;
	ifstream file;
	file.open("Game/User/record.txt");

	while(getline(file, line))
	{
		if((int)line.find("gold: ") == 0)
		{
			gold = stoi(line.replace(0, 6, ""));
		}
	}
	
	file.close();
	return gold;
}

void saveGameAsARecord(Player player, int seed)
{
	ofstream file;
	file.open("Game/User/record.txt");

	file<<"seed: "<<seed<<endl;
	
	if(player.health_point < 0)
	{
		player.health_point = 0;
	}
	
	file<<"health point: "<<player.health_point<<endl;
	file<<"gold: "<<player.gold<<endl;
	file<<"potions: "<<player.potions<<endl;
	file<<"amulet: "<<player.amulet<<endl;
	file<<"yondor: "<<player.yondor<<endl;
	file<<"finish: "<<player.finish<<endl<<endl;
	
	file.close();
}

void showRecord()
{
	string line;
	ifstream file;
	file.open("Game/User/record.txt");

	cout<<endl;
	
	while(getline(file, line))
	{
		cout<<line<<endl;
	}
	
	cout<<endl;
	
	file.close();
}

void showCredits()
{
	string line;
	ifstream file;
	file.open("Game/credits.txt");

	cout<<endl;
	
	while(getline(file, line))
	{
		cout<<line<<endl;
	}
	
	cout<<endl;
	
	file.close();
}
