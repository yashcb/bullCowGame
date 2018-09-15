#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame :: FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {	return  MyHiddenWord.length();	}
bool FBullCowGame::IsGameWon() const {	return bGameIsWon;	}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{	
	if ( !IsIsogram(Guess)) // if the guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	}

	else if ( !IsLowerCase(Guess)) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}

	else if (Guess.length() != GetHiddenWordLength() ) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}

	else // otherwise
	{	// return OK
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess, increments turns and returns count

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
			MyCurrentTry++;
			FBullCowCount BullCowCount;
			int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

			// loop through all letters in hidden word 
			for (int32 MHWchar = 0; MHWchar < WordLength; MHWchar++)
			{
				// compare letters against the guess
				for (int32 GChar = 0; GChar < WordLength; GChar++)
				{
					// if they match then
					if (Guess[GChar] == MyHiddenWord[MHWchar])
					{
						if (MHWchar == GChar) // if they're in the same place
						{
							BullCowCount.Bulls++;// increment bulls
						}
						else {
							BullCowCount.Cows++;// must be a cow.
						}
					}
				}
				if (BullCowCount.Bulls == WordLength)
				{
					bGameIsWon = true;
				}
				else{
					bGameIsWon = false;
				}
			}
			return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as Isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;// setup our map

	for (auto letter : Word) // for all letters in word
	{
		letter = tolower(letter); //  handle mixed cases
		if (LetterSeen[letter])// if the letter is in the map
		{	
			return false;// we do NOT have an Isogram
		}
		else // otherwise 
		{	
			LetterSeen[letter] = true;// add the letter in the Map as seen(true)
		}
	}
	return true; // in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto letter : Word)
	{
		if ( !islower(letter))// if not a lowercase
		return false;
	}
	return true;
}
