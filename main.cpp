#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

int balance = 100;

int red[] =   {1,3,5,7,9, 11,13,15,17,19,21,23,25,27,29};
int black[] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};


void drawBoard();
void spinRoulette(string bet, string betAmount);

bool isInteger(string input);

int main() {
	while (true) {
		system("CLS"); // clear console

		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		string bet;
		string betAmount;
		SetConsoleTextAttribute(hConsole, 15);

		drawBoard();
		cout << "Balance : " << balance << endl;
		if (balance == 0) {
			cout << "\nGame Over...\n";
			break;
		}

		do {
			cout << "\nPlace your bets on a color[R][B] or a number[1-30] : ";
			cin >> bet;
			if (isInteger(bet) && stoi(bet) > 0 && stoi(bet) <= 30) {
				break;
			}
			else {
				continue;
			}
		} while (bet != "r" && bet != "R" && bet != "b" && bet != "B");

		do {
			cout << "Place bet amount : ";
			cin >> betAmount;
		} while (!isInteger(betAmount) || stoi(betAmount) > balance || stoi(betAmount) <= 0);

		spinRoulette(bet, betAmount);
	}
}

void drawBoard() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "===================================Roulette=====================================\n\n";
	for (int i = 0; i <= 14; i++) { // 14 = nr of red/black 
		SetConsoleTextAttribute(hConsole, 4); // make console red
		cout << red[i];
		SetConsoleTextAttribute(hConsole, 1); // make console blue
		cout << " " << black[i] << " ";
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\n================================================================================\n";
}

void spinRoulette(string bet, string betAmount) {

	cout << "\nThe roulette is spinning...\n\n";
	Sleep(2000);

	srand(time(NULL));
	int landedOn = rand() % 29 + 1;
	string landedColour;

	if (!isInteger(bet)) {
		if (landedOn % 2 == 0) {
			cout << "The Roulette landed on " << landedOn << " BLUE\n";
			landedColour = "b";
		}
		else {
			cout << "The Roulette landed on " << landedOn << " RED\n";
			landedColour = "r";
		}
		if (bet == "b" && landedColour == "b" || bet == "B" && landedColour == "b") {
			cout << "You Win!\n";
			balance += stoi(betAmount);
		}
		else if (bet == "r" && landedColour == "r" || bet == "R" && landedColour == "r") {
			cout << "You Win!\n";
			balance += stoi(betAmount);
		}
		else {
			cout << "You Lose!\n";
			balance -= stoi(betAmount);
		}
	}
	else {
		if (stoi(bet) == landedOn) {
			cout << "The Roulette landed on " << landedOn;
			cout << "\nYou Win!\n";
			balance += stoi(betAmount) * 14;
		}
		else {
			cout << "The Roulette landed on " << landedOn;
			cout << "\nYou Lose!\n";
			balance -= stoi(betAmount);
		}
	}
	
	Sleep(2000);
}

bool isInteger(string input) {
	if (input[0] == '-') {
		return false;
	}
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}