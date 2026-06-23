#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int ReadNumberInRange(string message ,int from, int to)
{
    int number;

    do
    {

        cout << message;
        cin >> number;
    
    } while (number < from || number > to);

    return number;
}

int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

enum enWinState {Win=1,Draw=2,Lose=3};

enum enRockPaperScissors {Rock=1,Paper=2,Scissors=3};

struct stGameResults
{
    int playerWins = 0;
    int computerWins = 0;
    int draws = 0;
    int playerLosses = 0;
    int computerLosses = 0;
    int rounds = 0;
};

string Tabs(short tabsNum)
{
    string tabs;
    for (int i = 1; i <= tabsNum; i++)
    {
        tabs += "\t";
    }
    return tabs;
}

void CleanScreen()
{
    system("cls");
    system("color 0F");
}

int ReadRoundsNum()
{
    int rounds = ReadNumberInRange("Enter how many rounds ( 1 to 10 ) : ", 1, 10);
    return rounds;
}

enRockPaperScissors ReadPlayerChoice()
{ 
    int choice = ReadNumberInRange("Your Choice : [1] Rock, [2] Paper, [3] Scissors : ", 1, 3);
    return (enRockPaperScissors)choice;
}

enRockPaperScissors GetCompChoice()
{
    return (enRockPaperScissors)RandomNumber(1,3);
}

enWinState CheckWin(enRockPaperScissors playerChoice, enRockPaperScissors compChoice)
{
    switch (playerChoice)
    {
    case enRockPaperScissors::Paper:
        if (compChoice == enRockPaperScissors::Paper)
            return enWinState::Draw;
        if (compChoice == enRockPaperScissors::Rock)
            return enWinState::Win;
        return enWinState::Lose;
    case enRockPaperScissors::Rock:
        if (compChoice == enRockPaperScissors::Paper)
            return enWinState::Lose;
        if (compChoice == enRockPaperScissors::Rock)
            return enWinState::Draw;
        return enWinState::Win;
    case enRockPaperScissors::Scissors:
        if (compChoice == enRockPaperScissors::Paper)
            return enWinState::Win;
        if (compChoice == enRockPaperScissors::Rock)
            return enWinState::Lose;
        return enWinState::Draw;
    }
}

string GetChoice(enRockPaperScissors choice)
{
    if (choice == enRockPaperScissors::Paper)
        return "Paper";
    else if (choice == enRockPaperScissors::Rock)
        return "Rock";
    else
        return "Scissors";
}

string GetRoundWinner(enWinState playerWins)
{
    if (playerWins == enWinState::Win)
        return "Player1";
    else if (playerWins == enWinState::Draw)
        return "No Winner";
    else
        return "Computer";
}

string GetGameWinner(stGameResults results)
{
    if (results.computerWins > results.playerWins)
        return "Computer";
    else if (results.computerWins == results.playerWins)
        return "No Winner";
    else
        return "Player1";
        
}

string ReadChoice(string message)
{
    string choice;

    cout << message;
    cin >> choice;

    return choice;
}

bool isPlayingAgain(string choice)
{
    char choiceChar = choice[0];
    switch (choiceChar)
    {
    case 'y':
    case'Y':
        return true;
        break;
    default:
        return false;
    }
    
}

void UpdateResult(stGameResults& result, enWinState win)
{
    if (win == enWinState::Win)
    {
        result.playerWins++;
        result.computerLosses++;
    }
    else if (win == enWinState::Draw)
    {
        result.draws++;
    }
    else
    {
        result.computerWins++;
        result.playerLosses++;
    }
}

void ChangeScreen(enWinState win)
{
    if (win == enWinState::Win)
    {
        system("color 2F");
    }
    else if (win == enWinState::Draw)
    {
        system("color 6F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

void PrintRound(enRockPaperScissors playerChoice, enRockPaperScissors compChoice, enWinState winner,int roundCounter)
{
    cout << "\n\n";
    cout << "-----------------------------Round [" << roundCounter << "]-------------------------------------\n\n";
    cout << "Player 1 Choice : " << GetChoice(playerChoice) << endl;
    cout << "Computer Choice : " << GetChoice(compChoice) << endl;
    cout << "Round Winner : " << GetRoundWinner(winner) << endl;
    cout << "---------------------------------------------------------------------------\n\n";
}

void PrintGameResult(stGameResults result)
{
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
    cout << Tabs(7) << "***G a m e  O v e r***\n\n";
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
    cout << Tabs(3) << "---------------------------------[ Game Results ]-----------------------------\n\n";
    cout << Tabs(3) << "Game Rounds              :" << result.rounds << endl;
    cout << Tabs(3) << "Player1 Won Times        :" << result.playerWins << endl;
    cout << Tabs(3) << "Computer Won Times       :" << result.computerWins << endl;
    cout << Tabs(3) << "Draw Times               :" << result.draws << endl;
    cout << Tabs(3) << "Game Winner              :" << GetGameWinner(result) << endl;
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
}

void TheGame()
{
    bool isPlaying = true;
    while (isPlaying)
    {
        int rounds = ReadRoundsNum();
        int roundCounter = 1;
        stGameResults results;
        results.rounds = rounds;
        do
        {


            cout << "\nRound [" << roundCounter << "] begins : \n" << endl;


            enRockPaperScissors playerChoice = ReadPlayerChoice();
            enRockPaperScissors computerChoice = GetCompChoice();

            enWinState checkPlayerWin = CheckWin(playerChoice, computerChoice);

            ChangeScreen(checkPlayerWin);
            UpdateResult(results, checkPlayerWin);

            PrintRound(playerChoice, computerChoice, checkPlayerWin, roundCounter);

            roundCounter++;

            rounds--;
        } while (rounds != 0);

        PrintGameResult(results);
        
        if (isPlayingAgain(ReadChoice("Do you want to play again ? Y/N : ")) == false)
            break;
        CleanScreen();
    }

}

int main()
{
    srand((unsigned)time(NULL));
    
    TheGame();

    return 0;
}

