/*
This is the cpp file for the FBullCowGame class.
This implements all the logic for the backend of
the game.
*/
#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// return max tries depending on length of the hidden word
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8} }; // map hidden word length to max tries given
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// resets game to initial state and provides default values for max tries and hidden word
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 4;
	const FString HIDDEN_WORD = "badgers"; // this MUST be an isogram

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase, return an error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong, return an error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count of bulls and cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;
	
	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}


// compare guess string against a hash table to determine if guess is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map

	for (auto Letter : Word) // loop through all the letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])// if the letter is in the map
		{
			return false;// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}
// check each letter to see if it is lowercase
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) // loop through each character in Word
	{
		if (!islower(Letter)) // check if Letter is lowercase
		{
			return false; // letter is NOT lowercase
		}
	}
	return true;
}


