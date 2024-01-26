#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <time.h>
#include "utils/split.h"
#include <stdio.h>
#include <regex.h>
#include <cstring> 
#include <string>
#include <cstdio>
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define MAX_LINE 4096

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using str = std::string;

const str vers = "0.1.1";
const str flavortexts[] = {"Chocolate", "Vanilla", "Strawberry","I'm rich honey","ME MONEY","make this progam with make.sh, just like money.","delicous","If your wondering what this text is it's called flavortext and it's meant to be funny and entertainig"};
const float expansionValue = 1.15;

bool playing = true;

int munmuns = 0;
int munmunsAMake = 1;

float joeGain = 1;
float joePrice = 10;

struct OldSave {
	float money;
	float moneyAMake;
	int joeCount;
};

struct Save {
	float money;
	int joeCount;
};

class string {
	str* addr;
public:
	string(str content) {
		addr = new str(content);
	}
	void set(str content) {
		delete addr;
		addr = new str(content);
	}
	str get() {
		return *addr;
	}
	~string() {
		delete addr;
	}
};

Save gameState = {0, 0};

string defsave = string("def-save");

int system(str __command) {
	return system(__command.data());
}

str SetDBKey(str key, str value) {
	str step1 = "curl $REPLIT_DB_URL -d " + key + " = ";
	str step2 = step1 + value;
	system(step2);
	return value;
}

str GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  str current_working_dir(buff);
  return current_working_dir;
}

int randint(int min, int max) {
	srand(time(NULL));
	return rand() % (max - min + 1) + min;
}

void changeMoney(float change) {
	gameState.money += change;
	munmuns = gameState.money;
}

float getJoeProfit() {
	return joeGain * gameState.joeCount;
}

float getProfit() {
	float profit = 1;
	profit += getJoeProfit();
	return profit;
}

void updateCash() {
	munmuns = gameState.money;
	munmunsAMake = getProfit();
}

void save(Save s, str savename) {
	void* bindata = &s;
	std::ofstream savefile("saves/" + savename + ".cash", std::ios::binary);
	savefile.write((char*)bindata, sizeof(s));
	savefile.close();
}

Save load(str savename) {
	std::ifstream savefile("saves/" + savename + ".cash", std::ios::binary);
	Save s;
	savefile.read((char*)&s, sizeof(Save));
	return s;
}

OldSave oldLoad(str savename) {
	std::ifstream savefile("saves/" + savename + ".cash", std::ios::binary);
	OldSave s;
	savefile.read((char*)&s, sizeof(OldSave));
	return s;
}

float expansionFunction(int count, float startPrice) {
	return startPrice * pow(expansionValue, count);
}

int strArrayLen(str& array) {
	return sizeof(array) / sizeof(str);
}

int crash(int exitcode) {
	save(gameState, defsave.get());
	return exitcode;
}

int main() {
	//title card
	std::cout << BOLDGREEN << "Monymaking Simulator! " << RESET << "version " << vers << "\n";
	str flavortext = flavortexts[randint(0,strArrayLen(flavortext)-1)];
	std::cout << BOLDYELLOW << flavortext << "\n\n\n";

	//game loop
	while(playing) {
		str command;
		std::cout << BOLDBLUE << "Moneymaker" << RESET << "$ ";
		std::getline(std::cin, command);
		string jerry = string("jerry");

		std::vector<str> tokens = split(command, " ");
		
		if(tokens[0] == "exit") {
			//escapes game loop
			playing = false;
		} else if(tokens[0] == "clear") {
			//clears screen
			system("clear");
			//reprints title card
			std::cout << BOLDGREEN << "Monymaking Simulator! " << RESET << "version " << vers << "\n";
			str flavortext = flavortexts[randint(0,strArrayLen(flavortext)-1)];
			std::cout << BOLDYELLOW << flavortext << "\n\n\n";
		} else if(tokens[0] == "help") {
			int legnth = tokens.size();
			//detects if command given
			if (legnth > 1) {
			if(tokens[1] == "exit") {
				//gives help on exit command
				std::cout << BOLDWHITE << "EXIT\n" << RESET << "Exits the game, what more could you ask.\n";
			} else if(tokens[1] == "help") {
				//gives help on help command
				std::cout << BOLDWHITE << "HELP\n";
				std::cout << RESET <<"Gives help on the specified command, if no command is specified it gives help on all commands\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "help [command]\n";
			} else if(tokens[1] == "clear") {
				//gives help on clear command
				std::cout << BOLDWHITE << "CLEAR\n" << RESET << "Clears the console, then reprints the game title\n";
			} else if(tokens[1] == "make") {
				//gives help on make command
				std::cout << BOLDWHITE << "MAKE\n" << RESET << "Makes specified thing, if you have enough money\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "make [thing]\n";
			} else if(tokens[1] == "save") {
				//gives help on save command
				std::cout << BOLDWHITE << "SAVE\n" << RESET << "Saves the game to the chosen save file\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "save [savename]\n";
			} else if(tokens[1] == "load") {
				//gives help on load command
				std::cout << BOLDWHITE << "LOAD\n" << RESET << "Loads the game from the chosen save file\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "load [savename]\n";
			} else if(tokens[1] == "delete") {
				//gives help on delete command
				std::cout << BOLDWHITE << "DELETE\n" << RESET << "Deletes the chosen save file\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "delete [savename]\n";
			} else if(tokens[1] == "balance") {
				//gives help on balance command
				std::cout << BOLDWHITE << "BALANCE\n" << RESET << "Shows balance of specified thing, if no thing is specified it shows your cash balance\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "balance [thing]\n";
			} else if(tokens[1] == "info") {
				//gives help on info command
				std::cout << BOLDWHITE << "INFO\n" << RESET << "Shows info on specified thing, if no thing is specified shows info on the most recent update\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "info [thing]\n";
			} else if(tokens[1] == "update") {
				//gives help on update command
				std::cout << BOLDWHITE << "UPDATE\n" << RESET << "Updates the selected save, if no save is specified gives error\n";
				std::cout << BOLDBLUE << "Usage:\n" << RESET << "update [save]\n";
			} else {
				//informs user that they have specified an invalid command
				std::cout << BOLDRED << "ERROR: " << RESET << "Command not found, we can't help you with a command that does't exist\n";
			};
			} else {
				//gives help on all commands
				std::cout << BOLDBLUE << "Commands:\n";
				std::cout << BOLDBLUE << "exit" << RESET << " - Exit the game\n";
				std::cout << BOLDBLUE << "clear" << RESET << " - Clear the screen\n";
				std::cout << BOLDBLUE << "help" << RESET << " - Get help\n";
				std::cout << BOLDBLUE << "make" << RESET << " - Make something\n";
				std::cout << BOLDBLUE << "save" << RESET << " - Saves your game\n";
				std::cout << BOLDBLUE << "load" << RESET << " - Loads chosen save\n";
				std::cout << BOLDBLUE << "delete" << RESET << " - Deletes chosen save\n";
				std::cout << BOLDBLUE << "balance" << RESET << " - Shows your balance\n";
				std::cout << BOLDBLUE << "info" << RESET << " - Shows info about the game\n";
				std::cout << BOLDBLUE << "update" << RESET << " - Updates the save\n";
			};
		} else if(tokens[0] == "make") {
			if(tokens[1] == "money") {
				//makes money
				changeMoney(getProfit());
				std::cout << BOLDBLUE << "You made" << RESET << ": " << BOLDGREEN << munmunsAMake << "$\n";
			} else if(tokens[1] == "joe") {
				if(tokens.size() > 2) {
					float totalPrice = 0;
					int countToBuy = stoi(tokens[2]);
					//calculates total price of joes
					for(int count = 0; count < countToBuy; count++) {
						totalPrice += expansionFunction(gameState.joeCount + count, joePrice);
					};
					//purchases joes
					if (gameState.money >= totalPrice) {
						changeMoney(-totalPrice);
						gameState.joeCount += countToBuy;
					} else {
					std::cout << RED << "You don't have enough money to make " << countToBuy << " joe(s).\n";
				};
			} else {
				//buys as many joes as it can
				int bought = 0;
				float totalPrice = 0;
				while(gameState.money >= expansionFunction(gameState.joeCount, joePrice)/*checks if you can afford a joe*/) {
					//purchases 1 joe
					changeMoney(-expansionFunction(gameState.joeCount, joePrice));
					totalPrice += expansionFunction(gameState.joeCount, joePrice);
					gameState.joeCount++;
					bought++;
				};
				//displays total joes boght along with total price
				std::cout << BOLDBLUE << "You bought: " << BOLDGREEN << bought << BOLDBLUE << " Joe(s) for " << BOLDGREEN << ceil(totalPrice) << "$\n";
			};
			} else {
				std::cout << BOLDRED << "ERRROR: " << tokens[1] << " is not somthing you can make\n";
			};
		} else if(tokens[0] == "save") {
			//checks if user specified save
			str savename;
			if(tokens.size() > 1) {
				//sets the deafualt save to the selected save
				savename = tokens[1];
				defsave.set(savename);
			} else {
				//selects the current defualt save
				savename = defsave.get();
			};
			//saves game
			save(gameState, savename);
			std::cout << BOLDGREEN << "Saved game to " << savename << ".cash!\n";
		} else if(tokens[0] == "load") {
			//checks if user specified save
			str savename;
			if(tokens.size() > 1) {
				//sets the deafualt save to the selected save
				savename = tokens[1];
				defsave.set(savename);
			} else {
				//selects the current defualt save
				savename = defsave.get();
			};
			//loads game
			Save save = load(savename);
			gameState = save;
			updateCash();
			std::cout << BOLDGREEN << "Loaded save " << savename << " succecfully!\n";
		} else if(tokens[0] == "delete") {
			//checks if user specified save
			str savename;
			if(tokens.size() < 1) {
				//if not gives error
				std::cout << "ERROR: did not provide save";
			} else {
				//deletes specified save
				savename = tokens[1];
				str path = "saves/" + savename + ".cash";
				std::remove(path.c_str());
				std::cout << BOLDGREEN << "Successfully deleted save " << savename << "!\n";
			};
		} else if(tokens[0] == "balance") {
			//checks if user specified thing
			if(tokens.size() > 1) {
			//if so checks which thing
			if(tokens[1] == "joe") {
				//displays joe count
				std::cout << BOLDBLUE << "Joe Count: " << BOLDGREEN << gameState.joeCount << "\n";
				//displays current joe price
				std::cout << BOLDBLUE << "Joe Price: " << BOLDGREEN << ceil(expansionFunction(gameState.joeCount, joePrice)) << "$\n";
				//finds how many joes you can buy
				int canBuy = 0;
				float totalPrice = totalPrice += expansionFunction(gameState.joeCount + canBuy, joePrice);;
				while(gameState.money >= totalPrice) {
					totalPrice += expansionFunction(gameState.joeCount + canBuy, joePrice);
					canBuy++;
				};
				//displays how many joes you can buy
				std::cout << BOLDBLUE << "Can Buy: " << BOLDGREEN << canBuy << "\n";
			} else {
				//notifys user that they have specified an invalid thing
				std::cout << BOLDRED << "ERROR: " << tokens[1] << " is not somthing you can check balance of as it does not exist.\n";
			};
			} else {
			//shows cash balance
			std::cout << BOLDBLUE << "You have" << RESET << ": " << BOLDGREEN << munmuns << "$\n";
			std::cout << BOLDBLUE << "You make" << RESET << ": " << BOLDGREEN << "+" << munmunsAMake << "$\n";
			};
		} else if(tokens[0] == "info") {
			//checks if user specified thing
			if(tokens.size() > 1) {
				//checks which thing they specified
				if(tokens[1] == "joe") {
					//diplays info about joe
					std::cout << BOLDWHITE << "JOE\n";
					std::cout << BOLDCYAN << "Description:\n";
					std::cout << RESET << "Joe is your average joe, not to tall, not to short, just average.\n";
					std::cout << BOLDCYAN << "Properties:\n";
					std::cout << RESET << "A Joe intialy costs ten dollars and,\n"
					<< "increases your income by one dollar every time you make a joe.\n";
				}  else if(tokens[1] == "money") {
					//displays info about money
					std::cout << BOLDWHITE << "MONEY\n";
					std::cout << BOLDCYAN << "Description";
					std::cout << RESET << "Money is of course ye's FREEDOM DOLLARS, and it\n"
					<< "is also the main currency of the game!";
					std::cout << BOLDCYAN << "Properties:\n";
					std::cout << RESET << "Money can be made by typing out 'make money'.\n"
					<< "It is used to puchase most things in-game\n";
				};
			} else{
				//displays info about the most recent update
				std::cout << BOLDGREEN << "Moneymaking Simulator! " << RESET << "version " << vers << "\n";
				std::cout << BOLDBLUE << "Changelog:\n";
				std::cout << RESET << "Added INFO command\nAdded save caching\nAdded update command\n";
			};
		} else if(tokens[0] == "update") {
			//updates game save
			//checks if user specified save
			if(tokens.size() > 1) {
				//sets the deafualt save to the selected save
				defsave.set(tokens[1]);
				//loads old save file
				OldSave Old = oldLoad(tokens[1]);
				//creates new temporary save
				Save tsave = {0,0};
				//populates it witht the old save's data
				tsave.money = Old.money;
				tsave.joeCount = Old.joeCount;
				//saves updated save
				save(tsave, defsave.get());
				//loads updated save
				gameState = tsave;
				updateCash();
				//tauts it's succsess
				std::cout << BOLDGREEN << "Successfully updated save " << tokens[1] << "!\n";
			};
		} else{
			std::cout << BOLDRED << "Error: Unknown command: " << command << "\n";
		};
	};
	return 0;
}
