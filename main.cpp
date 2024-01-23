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

const str vers = "0.1.0";
const str flavortexts[] = {"Chocolate", "Vanilla", "Strawberry","I'm rich honey","ME MONEY","make this progam with make.sh, just like money.","delicous","If your wondering what this text is it's called flavortext and it's meant to be funny and entertainig"};
const float expansionValue = 1.15;

bool playing = true;

int munmuns = 0;
int munmunsAMake = 1;

float joeGain = 1;
float joePrice = 10;

struct Save {
	float money;
	float moneyAMake;
	int joeCount;
};

Save gameState = {0, 1, 0};

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

void changeProfit(float change) {
	gameState.moneyAMake += change;
	munmunsAMake = gameState.moneyAMake;
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

float expansionFunction(int count, float startPrice) {
	return startPrice * pow(expansionValue, count);
}

int strArrayLen(str& array) {
	return sizeof(array) / sizeof(str);
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
			} else {
				//informs user that they have specified an invalid command
				std::cout << BOLDRED << "ERROR: " << RESET << "Command not found, we can't help you with a command that does't exist\n";
			};
			} else {
				std::cout << BOLDBLUE << "Commands:\n";
				std::cout << BOLDBLUE << "exit" << RESET << " - Exit the game\n";
				std::cout << BOLDBLUE << "clear" << RESET << " - Clear the screen\n";
				std::cout << BOLDBLUE << "help" << RESET << " - Get help\n";
				std::cout << BOLDBLUE << "make" << RESET << " - Make something\n";
				std::cout << BOLDBLUE << "save" << RESET << " - Saves your game\n";
				std::cout << BOLDBLUE << "load" << RESET << " - Loads chosen save\n";
				std::cout << BOLDBLUE << "delete" << RESET << " - Deletes chosen save\n";
				std::cout << BOLDBLUE << "balance" << RESET << " - Shows your balance\n";
			};
		} else if(tokens[0] == "make") {
			if(tokens[1] == "money") {
				changeMoney(gameState.moneyAMake);
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
						changeProfit(joeGain*countToBuy);
					} else {
					std::cout << RED << "You don't have enough money to make " << countToBuy << " joe(s).\n";
				};
			} else {
				//buys as many joes as it can
				int bought = 0;
				float totalPrice = 0;
				while(gameState.money >= expansionFunction(gameState.joeCount, joePrice)) {
					changeMoney(-expansionFunction(gameState.joeCount, joePrice));
					totalPrice += expansionFunction(gameState.joeCount, joePrice);
					gameState.joeCount++;
					bought++;
					changeProfit(joeGain);
				};
				//displays total joes boght along with total price
				std::cout << BOLDBLUE << "You bought: " << BOLDGREEN << bought << BOLDBLUE << " Joe(s) for " << BOLDGREEN << ceil(totalPrice) << "$\n";
			};
			} else {
				std::cout << BOLDRED << "ERRROR: " << tokens[1] << " is not somthing you can make\n";
			};
		} else if(tokens[0] == "save") {
			save(gameState, tokens[1]);
			std::cout << BOLDGREEN << "Saved game to " << tokens[1] << ".cash!\n";
		} else if(tokens[0] == "load") {
			Save save = load(tokens[1]);
			gameState = save;
			changeMoney(0);
			changeProfit(0);
			std::cout << BOLDGREEN << "Loaded save " << tokens[1] << " succecfully!\n";
		} else if(tokens[0] == "delete") {
			str path = "saves/" + tokens[1] + ".cash";
			std::remove(path.c_str());
			std::cout << BOLDGREEN << "Successfully deleted save " << tokens[1] << "!\n";
		} else if(tokens[0] == "balance") {
			if(tokens.size() > 1) {
			if(tokens[1] == "joe") {
				std::cout << BOLDBLUE << "Joe Count: " << BOLDGREEN << gameState.joeCount << "\n";
				std::cout << BOLDBLUE << "Joe Price: " << BOLDGREEN << ceil(expansionFunction(gameState.joeCount, joePrice)) << "$\n";
				int canBuy = 0;
				float totalPrice = 0;
				while(gameState.money >= totalPrice) {
					totalPrice += expansionFunction(gameState.joeCount + canBuy, joePrice);
				};
				std::cout << BOLDBLUE << "Can Buy: " << BOLDGREEN << canBuy << "\n";
			} else {
				std::cout << BOLDRED << "ERROR: " << tokens[1] << " is not somthing you can check balance of as it does not exist.\n";
			}
			} else {
			std::cout << BOLDBLUE << "You have" << RESET << ": " << BOLDGREEN << munmuns << "$\n";
			std::cout << BOLDBLUE << "You make" << RESET << ": " << BOLDGREEN << "+" << munmunsAMake << "$\n";
			};
		} else {
			std::cout << BOLDRED << "Error: Unknown command: " << command << "\n";
		};
	};
	return 0;
}
