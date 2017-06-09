#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <unistd.h>
using namespace std;

class army{
private:
	int territories;
	int soldiers;
public:
	army(int territory, int soldier){
		this->territories = territory;
		this->soldiers = soldier;
	}
	int getTerritoryCount(){
		return this->territories;
	}
	int getSoldierCount(){
		return this->soldiers;
	}
	void setTerritoryCount(int newTerritories){
		this->territories += newTerritories;
	}
	void setSoldierCount(int newSoldiers){
		this->soldiers -= newSoldiers;
	}
	void getArmyStats(){
		cout << "Number of Territories: " << getTerritoryCount() << endl;
		cout << "Number of Soldiers: " << getSoldierCount() << endl;
	}
};



void printBanner(){
	cout << "Welcome to the RISK Battle Game!\n";
	cout << "Initially both the armies will have the same number of territories and soldiers.\n";
	cout << "The player picks an army; comp gets the other.\n";
	cout << "We roll a dice and whoever gets the highest, begins the game\n";
	cout << "On your turn, you can either attack enemy territory or defend your territory\n.";
	cout << "The size of your contigent will be decided based on the outcome of 2 dice.\n";
	cout << "The army with the highest outcome wins the round and the territory.\n";
	cout << "The winning army loses 1 soldier for every 2 enemy soldier.\n";
	cout << "The losing side loses the contigent and the territory.\n";
	cout << "The side which loses all its territories first or is left with less than 12 soldiers,\n";
	cout << "loses the game.\n";
	cout << "Good Luck! Let the battle begin...\n";
}

/* 
 * Random dice rolling generator function
 * If dice is 1, roll 1 dice
 * else roll both the dice and return sum.
 *
 */
int rollDice(int dice){
	int die1 = rand()%6 + 1;
	int die2 = rand()%6 + 1;
	if (dice == 1){
		return die1;
	} else {
		return die1 + die2;
	}
}

/* 
 * Print Game stats
 *
 */

void printStats(army &User, army &Comp){
	cout << "The army stats are:\n";
	cout << "Team User: \n";
	User.getArmyStats();
	cout << "Team Comp: \n";
	Comp.getArmyStats();
}

/* 
 * Player and Comp armies battle out in this method().
 * If player has a greater count, player wins the territory.
 * Player loses half the number of soldiers as the enemy's.
 * Same with Comp.
 * If both team get same dice outcome, decide with coin toss. 
 *
 */

void battle(int playercount, int enemycount, army &User, army &Comp){
	if(playercount == enemycount){
		int outcome = rollDice(2);
		bool playerwins = false;
		if(outcome%2 == 0){
			playerwins = true;
		}
		for(int i=0; i<= enemycount/2; i++){
			cout << "Enemy lost a soldier!\n";
			usleep(1000000);
			cout << "You lost a soldier!\n";
			usleep(1000000);
			cout << "Enemy lost a soldier!\n";
			usleep(1000000);
		}
		if(playerwins){
			cout << "Your army has won this round and the territory.\n";
			cout << "You lost " << enemycount/2 << " soldiers in this round.\n";
			usleep(1000000);
			User.setTerritoryCount(1);
			User.setSoldierCount(enemycount);
			Comp.setTerritoryCount(-1);
			Comp.setSoldierCount(enemycount);
		} else{
			cout << "Comp has won this round and the territory.\n";
			cout << "You lost " << enemycount << " soldiers in this round.\n";
			usleep(1000000);
			User.setTerritoryCount(-1);
			User.setSoldierCount(enemycount);
			Comp.setTerritoryCount(1);
			Comp.setSoldierCount(enemycount);
		}
	} else if(playercount > enemycount){
		cout << "The battle is underway\n";
		for(int i=0; i<= enemycount/2; i++){
			cout << "Enemy lost a soldier!\n";
			usleep(1000000);
			cout << "You lost a soldier!\n";
			usleep(1000000);
			cout << "Enemy lost a soldier!\n";
			usleep(1000000);
		}
		cout << "Your army has won this round and the territory.\n";
		cout << "You lost " << enemycount/2 << " soldiers in this round.\n";
		usleep(1000000);
		User.setTerritoryCount(1);
		User.setSoldierCount(enemycount/2);
		Comp.setTerritoryCount(-1);
		Comp.setSoldierCount(enemycount);
	} else {
		cout << "The battle is underway\n";
		for(int i=0; i<= playercount/2; i++){
			cout << "You lost a soldier!\n";
			usleep(1000000); 
			cout << "Enemy lost a soldier!\n";
			usleep(1000000);
			cout << "You lost a soldier!\n";
			usleep(1000000); 
		}
		cout << "Comp has won this round and the territory.\n";
		cout << "You lost " << playercount << " soldiers in this round.\n";
		usleep(1000000);
		User.setTerritoryCount(-1);
		User.setSoldierCount(playercount);
		Comp.setTerritoryCount(1);
		Comp.setSoldierCount(playercount/2);
		}
}

/* 
 * For Player's turn, call this method.
 * Ask if player wants to attack or defend.
 * Player and Comp roll dice and call battle()
 * for the fight. 
 *
 */

void playerBegins(army &User, army &Comp){
	int action;
	cout << "Select your action:\n";
	cout << "1. Attack\n";
	cout << "2. Defend\n";
	cin >> action;
	int playercount, compcount, result;
	if(action == 1){
		cout << "You have decided to attack.\n";
		cout << "User rolling dice: \n";
		playercount = rollDice(2);
		usleep(1000000);
		cout << "You get: " << playercount << endl;
		cout << "You will attack with " << playercount << " soldiers.\n";
		cout << "Comp rolling dice: \n";
		compcount = rollDice(2);
		usleep(1000000);
		cout << "Comp gets: " << compcount << endl;
		cout << "Comp will defend with " << compcount << " soldiers.\n";
		cout << "The battle begins.\n";
		battle(playercount, compcount, User, Comp);
		usleep(1000000);
	} else if (action == 2){
		cout << "You have decided to defend.\n";
		cout << "Comp rolling dice: \n";
		compcount = rollDice(2);
		usleep(1000000);
		cout << "Comp gets: " << compcount << endl;
		cout << "Comp will attack with " << compcount << " soldiers.\n";
		cout << "User rolling dice: \n";
		playercount = rollDice(2);
		usleep(1000000);
		cout << "You get: " << playercount << endl;
		cout << "You will defend with " << playercount << " soldiers.\n";
		cout << "The battle begins.\n";
		battle(playercount, compcount, User, Comp);
		usleep(1000000);
	}
}

/* 
 * For Comp's turn, call this method.
 * Decide if Comp wants to attack or defend.
 * Player and Comp roll dice and call battle()
 * for the fight. 
 *
 */

void compBegins(army &User, army &Comp){
	int action = rollDice(2);
	int playercount, compcount, result;
	if(action % 2 == 0){
		cout << "Comp has decided to attack.\n";
		cout << "Comp rolling dice: \n";
		compcount = rollDice(2);
		usleep(1000000);
		cout << "Comp gets: " << compcount << endl;
		cout << "Comp will attack with " << compcount << " soldiers.\n";
		cout << "User rolling dice: \n";
		playercount = rollDice(2);
		usleep(1000000);
		cout << "You get: " << playercount << endl;
		cout << "You will defend with " << playercount << " soldiers.\n";
		cout << "The battle begins.\n";
		battle(playercount, compcount, User, Comp);
		usleep(1000000);
	} else {
		cout << "Comp has decided to defend.\n";
		cout << "Comp rolling dice: \n";
		compcount = rollDice(2);
		usleep(1000000);
		cout << "Comp gets: " << compcount << endl;
		cout << "Comp will defend with " << compcount << " soldiers.\n";
		cout << "User rolling dice: \n";
		playercount = rollDice(2);
		usleep(1000000);
		cout << "You get: " << playercount << endl;
		cout << "You will attack with " << playercount << " soldiers.\n";
		cout << "The battle begins.\n";
		battle(playercount, compcount, User, Comp);
		usleep(1000000);
	}
}


int checkstats(army& User, army& Comp, bool& stat){
	if(User.getSoldierCount() < 12 || User.getTerritoryCount() == 0){
		stat = false;
		return 1;
	}
	if(Comp.getSoldierCount() < 12 || Comp.getTerritoryCount() == 0){
		stat = true;
		return 1;
	} else return 0;
}

int main(){
	srand(time(0));
	army User(3, 50);
	army Comp(3, 50);
	int armyselect;
	bool playerwins = false;
	printBanner();
	usleep(1000000);
	printStats(User, Comp);
	cout << "Press anykey to roll a dice\n";
	cin.ignore();
	usleep(1000000);
	int player = rollDice(1);
	usleep(1000000);
	int comp = rollDice(1);
	while(player == comp){
		player = rollDice(1);
		usleep(1000000);
		comp = rollDice(1);
	}
	usleep(1000000);
	cout << "You got " << player << endl;
	usleep(1000000);
	cout << "The opponent got " << comp << endl;
	usleep(1000000);
	if(player > comp){
		cout << "You will begin the battle.\n";
		usleep(1000000);
		while(1){
			usleep(1000000);
			if(checkstats(User, Comp, playerwins) == 1) break;
			playerBegins(User, Comp);
			usleep(1000000);
			printStats(User, Comp);
			if(checkstats(User, Comp, playerwins) == 1) break;
			usleep(1000000);
			cout << "Comp's turn!\n";
			compBegins(User, Comp);
			printStats(User, Comp);
		}
	} else {
		cout << "Comp will begin the battle\n";
		usleep(1000000);
		while(1){
			usleep(1000000);
			if(checkstats(User, Comp, playerwins) == 1) break;
			compBegins(User, Comp);
			usleep(1000000);
			printStats(User, Comp);
			if(checkstats(User, Comp, playerwins) == 1) break;
			usleep(1000000);
			cout << "Your turn!\n";
			playerBegins(User, Comp);
			printStats(User, Comp);
		}	
	}
	cout << "The final stats are:\n";
	printStats(User, Comp);
	usleep(100000);
	if(User.getTerritoryCount() > Comp.getTerritoryCount()){
		playerwins = true;
	} else if(User.getTerritoryCount() == Comp.getTerritoryCount()){
		if(User.getSoldierCount() >= Comp.getSoldierCount()){
			playerwins = true;
		} else playerwins = false;
	} else {
		playerwins = false;
	}
	usleep(100000);
	if(playerwins){
		cout << "You have won the battle. Comp loses.\n";
	} else {
		cout << "You have lost the battle. Comp wins.\n";
	}
	return 0;
}
