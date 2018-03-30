/*
This is the header file for the FBullCowGame class.
This declares all the methods and variables which
control the backend of the game.
*/
#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// enum with values to use when validating a guess
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString);


// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};