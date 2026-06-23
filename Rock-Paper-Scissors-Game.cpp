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

enum enWinner {Player=1,Computer=2,Draw=3};

enum enRockPaperScissors {Rock=1,Paper=2,Scissors=3};

struct stGameResults
{
    int gameRounds = 0;
    int playerWins = 0;
    int computerWins = 0;
    int draws = 0;
    enWinner gameWinner;
    string winnerName;
};

struct stRoundInfo
{
    int gameRound = 0;
    enRockPaperScissors playerChoice;
    enRockPaperScissors computerChoice;
    enWinner roundWinner;
    string winnerName;
};


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

enWinner CheckWinner(stRoundInfo info)
{

    if (info.playerChoice == info.computerChoice)
        return enWinner::Draw;

    switch (info.playerChoice)
    {

    case enRockPaperScissors::Paper:
        if (info.computerChoice == enRockPaperScissors::Rock)
            return enWinner::Player;
        
    case enRockPaperScissors::Rock:
        if (info.computerChoice == enRockPaperScissors::Scissors)
            return enWinner::Player;

    case enRockPaperScissors::Scissors:
        if (info.computerChoice == enRockPaperScissors::Paper)
            return enWinner::Player;

    }
    return enWinner::Computer;
}

enWinner GetGameWinner(stGameResults results)
{
    if (results.computerWins > results.playerWins)
        return enWinner::Computer;
    else if (results.playerWins > results.computerWins)
        return enWinner::Player;
    else
        return enWinner::Draw;
}

string GetChoiceName(enRockPaperScissors choice)
{

    string choices[3] = { "Rock","Paper","Scissors" };

    return choices[choice - 1];
}

string GetWinnerName(enWinner winner)
{
    string winners[3] = {"Player","Computer","No Winner"};
    return winners[winner - 1];
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


void ChangeScreen(enWinner win)
{
    if (win == enWinner::Player)
    {
        system("color 2F");
    }
    else if (win == enWinner::Draw)
    {
        system("color 6F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

void PrintRound(stRoundInfo info,short rounds)
{
    cout << "\n\n";
    cout << "-----------------------------Round [" << rounds << "]-------------------------------------\n\n";
    cout << "Player 1 Choice : " << GetChoiceName(info.playerChoice) << endl;
    cout << "Computer Choice : " << GetChoiceName(info.computerChoice) << endl;
    cout << "Round Winner : " << GetWinnerName(info.roundWinner) << endl;
    cout << "---------------------------------------------------------------------------\n\n";
}

void PrintGameOver()
{
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
    cout << Tabs(3) << "                       ***G a m e  O v e r***\n\n";
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
}

void PrintGameResult(stGameResults result)
{
    
    cout << Tabs(3) << "---------------------------------[ Game Results ]-----------------------------\n\n";
    cout << Tabs(3) << "Game Rounds              :" << result.gameRounds << endl;
    cout << Tabs(3) << "Player1 Won Times        :" << result.playerWins << endl;
    cout << Tabs(3) << "Computer Won Times       :" << result.computerWins << endl;
    cout << Tabs(3) << "Draw Times               :" << result.draws << endl;
    cout << Tabs(3) << "Game Winner              :" << GetWinnerName(result.gameWinner) << endl;
    cout << Tabs(3) << "------------------------------------------------------------------------------\n\n";
}

stGameResults PlayGame(short roundsNum)
{
    short playerWins=0, computerWins=0, draws=0;
    stRoundInfo round;

    for (short rounds = 1; rounds <= roundsNum; rounds++)
    {
        cout << "\nRound [" << rounds << "] begins : \n" << endl;

        round.playerChoice = ReadPlayerChoice();
        round.computerChoice = GetCompChoice();
        round.roundWinner = CheckWinner(round);
        round.winnerName = GetWinnerName(round.roundWinner);

        PrintRound(round, rounds);
        
        if (round.roundWinner == enWinner::Player)
            playerWins++;
        else if (round.roundWinner == enWinner::Computer)
            computerWins++;
        else
            draws++;
    }

    return { roundsNum,playerWins,computerWins,draws };

}

void TheGame()
{
    bool isPlaying = true;
    while (isPlaying)
    {
        
        stGameResults game = PlayGame(ReadRoundsNum());

        game.gameWinner = GetGameWinner(game);

        ChangeScreen(game.gameWinner);

        PrintGameOver();

        PrintGameResult(game);
        
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

