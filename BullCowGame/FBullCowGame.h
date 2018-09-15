#pragma once
#include <string>

using FString = std :: string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

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
			FBullCowGame(); // Constructor
			void Reset(); //TODO make a more rich value return.

			int32 GetMaxTries() const;
			int32 GetCurrentTry() const;
			int32 GetHiddenWordLength() const;
			bool IsGameWon() const;
			EGuessStatus CheckGuessValidity(FString) const;
			// Counts Bulls & Cows, and increasing turns # assuming valid guess
	

			FBullCowCount SubmitValidGuess(FString);

			// ^^ please try to ignore this and focus on interface above ^^

	private:

		int32 MyCurrentTry;
		int32 MyMaxTries;
		FString MyHiddenWord;
		bool bGameIsWon;

		bool IsIsogram(FString) const;
		bool IsLowerCase(FString) const;
};
