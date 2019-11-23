/**
	18/11/19 Created by George Cox
**/

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

//----------------------------------- part 1 start ----------------------------------- 

void PowerFunction(int &value, int base, int exponent)
{
	exponent--;
	if (exponent > 0)
	{
		value *= base;
		PowerFunction(value, base, exponent);
	}
}

//toms function
long PowerFunction(int base, int exponent)
{
	if (exponent > 0) {
		if (exponent == 1)
		{
			return exponent;
		}
		else if (exponent <= 0)
		{
			return 0;
		}
		int remainder = exponent % 2;
		int extra = remainder == 1 ? exponent : 1;
		return PowerFunction(exponent * exponent, exponent / 2) * extra;
	}
	else if (exponent == 0)
	{
		return 1;
	}
}

void PowerFunction(double &value, double base, int exponent)
{
	exponent--;
	if (exponent > 0)
	{
		value *= base;
		PowerFunction(value, base, exponent);
	}
}

void Part1()
{
	std::cout << "Enter a value: ";
	int value;
	std::cin >> value;

	std::cout << "Enter an exponent: ";
	int exponent;
	std::cin >> exponent;

	PowerFunction(value, value, exponent);

	std::cout << "Value: " << value << std::endl;
}

//----------------------------------- part 1 end ----------------------------------- 

enum class Balls {
	RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE
};

//pick a random number between 0 and (size array - 1)
//find color based on random number
//add that color to selectedBallsArray
//remove that color from ballsChooseArray
// ?? should I return the Ball or make method void??
void RandomBall(Balls* ballsChooseFromArray, Balls* selectedBallsArray, int selectionSize)
{
	int indexSelected = rand() % selectionSize;
	//std::cout << indexSelected << std::endl;
	Balls randomlySelectedBall = ballsChooseFromArray[indexSelected];

	selectedBallsArray[6 - selectionSize] = randomlySelectedBall;

	for (int i = indexSelected; i < selectionSize - 1; i++)
	{
		ballsChooseFromArray[i] = ballsChooseFromArray[i + 1];
	}
}

std::string GuessNumber(Balls* ballsGuessed, int number)
{
	char guess;
	std::string guessString;
	std::cout << "Guess a color " << number << " : " ;
	std::cin >> guess;

	switch (guess) {
	case 'R': case 'r':
		guessString = "R";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::RED;
		break;
	case 'B': case 'b':
		guessString = "B";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::BLUE;
		break;
	case 'G': case 'g':
		guessString = "G";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::GREEN;
		break;
	case 'Y': case 'y':
		guessString = "Y";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::YELLOW;
		break;
	case 'P': case 'p':
		guessString = "P";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::PURPLE;
		break;
	case 'O': case 'o':
		guessString = "O";
		//std::cout << "guessed: " << guess << std::endl;
		ballsGuessed[number] = Balls::ORANGE;
		break;
	}

	return guessString;
}

std::string CompareArrays(Balls* ballsChosen, Balls* ballsGuessed, int arraySize, bool &lost)
{
	int correctPosColor = 0; //black ball
	int correctColor = 0; //white ball

	//need to account for guessing same colo multiple times
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			if (ballsChosen[i] == ballsGuessed[j])
			{
				if (i == j)
				{
					correctPosColor++;
				}
				else
				{
					correctColor++;
				}
				break;
			}
		}
	}

	std::string correctPosColorString = "black balls: " + std::to_string(correctPosColor);
	std::string correctColorString = " white balls: " + std::to_string(correctColor);
	std::cout << correctPosColorString << std::endl;
	std::cout << correctColorString << std::endl;

	if (correctPosColor == 4)
	{
		lost = false;
	}

	correctPosColorString += correctColorString + "\n";
	return correctPosColorString;
}

int main()
{
	srand(time(0));

	//(RED(R), BLUE(B), GREEN(G), YELLOW(Y), PURPLE(P) and ORANGE(O))
	Balls ballsSelection[6] = { Balls::RED, Balls::BLUE, Balls::GREEN, Balls::YELLOW, Balls::PURPLE, Balls::ORANGE };
	Balls ballsChosen[4];
	Balls ballsGuessed[4];

	//computer picking random balls
	RandomBall(ballsSelection, ballsChosen, 6);
	RandomBall(ballsSelection, ballsChosen, 5);
	RandomBall(ballsSelection, ballsChosen, 4);
	RandomBall(ballsSelection, ballsChosen, 3);

	//for testing random values are correct
#if 0
	for (int i = 0; i < 4; i++)
	{
		std::cout << i << std::endl;
		Balls b = ballsChosen[i];
		switch (b)
		{
		case(Balls::RED):
			std::cout << "RED" << std::endl;
			break;
		case(Balls::BLUE):
			std::cout << "BLUE" << std::endl;
			break;
		case(Balls::GREEN):
			std::cout << "GREEN" << std::endl;
			break;
		case(Balls::YELLOW):
			std::cout << "YELLOW" << std::endl;
			break;
		case(Balls::PURPLE):
			std::cout << "PURPLE" << std::endl;
			break;
		case(Balls::ORANGE):
			std::cout << "ORANGE" << std::endl;
			break;
		}
	}
#endif


	//guessing till win loop
	bool lost = true;
	std::vector<std::string> vectorStringGuesses;
	int attempts = 0;

	while (lost)
	{
		std::cout << "Guess a color by typing the first letter of the color" << std::endl;
		std::cout << "(RED(R), BLUE(B), GREEN(G), YELLOW(Y), PURPLE(P) and ORANGE(O))" << std::endl;
		
		attempts++;
		std::string guessList;

		//player guessing colors
		guessList = GuessNumber(ballsGuessed, 0);
		guessList += "," + GuessNumber(ballsGuessed, 1);
		guessList += "," + GuessNumber(ballsGuessed, 2);
		guessList += "," + GuessNumber(ballsGuessed, 3) + ",";


		//compare guessed to selected
		guessList += CompareArrays(ballsChosen, ballsGuessed, 4, lost);

		//std::cout << "Guess list is: " << guessList << std::endl;
		vectorStringGuesses.push_back(guessList);
	}

	vectorStringGuesses.push_back("Won in " + std::to_string(attempts) + " attempts.");
	std::cout << "Won! atttempts: " << attempts << std::endl;

	//write result to csv file
	std::ofstream file;
	file.open("results.csv");
	for (std::string s : vectorStringGuesses)
	{
		file << s;
	}
	file.close();
}