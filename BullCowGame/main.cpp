/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>	
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}

 
void PrintIntro()
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "    _______________________________________" << std::endl;
	std::cout << "   |	 `                 -`              |" << std::endl;
	std::cout << "   |	 `.                .-              |" << std::endl;
	std::cout << "   |	 :``                .:``           |" << std::endl;
	std::cout << "   |	-:`                   -:` `        |" << std::endl;
	std::cout << "   |   `o .                    `/- `.`     | " << std::endl;
	std::cout << "   |   -o .        `.---.....-/ohs: `+/.   | " << std::endl;
	std::cout << "   |   `y/`````-oyyooyysssyyhdhdds: .+y/`  | " << std::endl;
	std::cout << "   |  `+s+//+mmmhyyyyhdddhhhyo/-``:hhs:`   |" << std::endl;
	std::cout << "   |  `ooooyddddmhssdhyhhddNNho/++syddys/` | " << std::endl;
	std::cout << "   |  -sdmNNmhdhshhyyyyhyyhdmmmmmNmmmhs.   |" << std::endl;
	std::cout << "   |     ``./dmdhddmmdddmmhhdNNNmdhhs:`    |" << std::endl;
	std::cout << "   |         ymhsshddhdmdhhdmMmmmhy+:`     |" << std::endl;
	std::cout << "   |         odyssymdyhhdhhhdNmdmdy+:      |" << std::endl;
	std::cout << "   |         -dysydmhssyyssydmddddy+.      |" << std::endl;
	std::cout << "   |        `ohssddhhyyhyyhdmmmhhho-       |" << std::endl;
	std::cout << "   |        hyso+oooyyhhdmNNmmddhy-        |" << std::endl;
	std::cout << "   |        smhysmo+sdhmNNNNNNNNh+`        |" << std::endl;
	std::cout << "   |          :yyyhy+:.  -ymNmdmds:`       |" << std::endl;
	std::cout << "   |                       `:+yy/`         |" << std::endl;
	std::cout << "   |_______________________________________|" << std::endl;
	std::cout << "\nCan you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n" << std::endl;
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!";
	}
	else
	{
		std::cout << "Better luck next time.";
	}
	std::cout << std::endl;
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
