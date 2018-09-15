/* This is a console executable , that makes use of BullCow Class 
This acts as view in the MVC pattern, and is responsible for all user interaction.
For logic see the FBullCowGame class.*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std :: string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// Entering application
int main() 
{
	std::cout << BCGame.GetCurrentTry();

	bool bWannaPlay = false;
	do
	{
		PrintIntro();
		PlayGame();
		bWannaPlay = AskToPlayAgain();
	} while (bWannaPlay);
	std :: cout << "THEN FUCK OFF!\n";

	return 0; // exit the application
}

void PrintIntro() 
{
	// introducing the game
	std :: cout << "\n\n Welcome to Bulls & Cows, a fun game." << std :: endl;
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
}

void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game 
	// is NOT won and there are still tries remaining
	while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// Print number of Bulls And Cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

	}
	PrintGameSummary();
}

// Loop continually until user gives valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
			// getting geuss from user
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << "Try " << CurrentTry << ". Enter your geuss: ";
			getline(std::cin, Guess);

			Status = BCGame.CheckGuessValidity(Guess);
				switch (Status)
				{
					
					case EGuessStatus::Wrong_Length:
						std::cout << "Please enter " << BCGame.GetHiddenWordLength() << " letter(s) word!\n";
						break;

					case EGuessStatus::Not_Isogram:
						std::cout << "Please enter word without repeating letter(s).\n";
						break;

					case EGuessStatus::Not_Lowercase:
						std::cout << "Please enter all lowercase letter(s).\n";
						break;

					default:
						// assume no errors
						break;
				}
				std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
			return Guess;
}

bool AskToPlayAgain()
{
	std :: cout << "Wanna Play Again With The Same Hidden Word (y/n) ?";
	FText Response = "";
	getline(std :: cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Congratulations! You Won this game.\n";

	else
		std::cout << "\n Sorry... Better luck next time!";
}
