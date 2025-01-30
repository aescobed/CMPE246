


#include "include/SimonSays.h"
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()




int main()
{

    int nCommands;              // number of possible commands that Simon will give
    int nPreSimonDoesSay;       // number of ways in which Simon will say that he said this before the command
    int nPostSimonDoesSay;      // number of ways in which Simon will say that he said this after the command
    int nPreSimonDoesntSay;     // number of ways in which it will be stated that Simon did not say this before the command
    int nPostSimonDoesntSay;     // number of ways in which it will be stated that Simon did not say this after the command

    const char* preSimonSaysStrs[] = 
    {
        "Simon says ",
        "Simon mentions to ",
        "Simon tells you to "
    };

    const char* postSimonSaysStrs[] = 
    {
        ", says Simon",
        ", Simon mentions"
    };

    const char* preSimonDoesntSayStrs[] =
    {
        "Simon did not say the following: ",
        ""
    }; 

    const char* postSimonDoesntSayStrs[] =
    {
        ", said Simon - just kidding he didn't say that",
        ", Simon intended to say but didn't",
        ""
    }; 

    const char* commandStrs[] = 
    {
        // TODO: Add command string here
        "press the button twice",
        "press the button once",
        "do nothing"
    };


    // get the number of strings 
    nPreSimonDoesSay = sizeof(preSimonSaysStrs) / sizeof(preSimonSaysStrs[0]);
    nPostSimonDoesSay = sizeof(postSimonSaysStrs) / sizeof(postSimonSaysStrs[0]);
    nPreSimonDoesntSay = sizeof(preSimonDoesntSayStrs) / sizeof(preSimonDoesntSayStrs[0]);
    nPostSimonDoesntSay = sizeof(postSimonDoesntSayStrs) / sizeof(postSimonDoesntSayStrs[0]);
    nCommands = sizeof(commandStrs) / sizeof(commandStrs[0]);

    int nSimonDoesntSay = nPreSimonDoesntSay + nPostSimonDoesntSay;
    int nSimonDoesSay = nPreSimonDoesSay +nPostSimonDoesSay;

    std::srand(std::time(nullptr)); // Seed random number generator

    int randomDoesSimonSay = std::rand() % 2;                       // generate a number between 0 and 1 (inclusive)
    int randomCommand = std::rand() % nCommands;                    // generate a random number to decide on the command
    
    Simon simonObj;

    simonObj.commandStr = commandStrs[randomCommand];

    // if Simon did say this statement
    if(randomDoesSimonSay)
    {

        simonObj.simonSaysBool = true;

        int randomSimonSaysStrInd = std::rand() % nSimonDoesSay;       // Generate a random number to decide on the Simon says string

        // If we choose a pre string
        if(randomSimonSaysStrInd < nPreSimonDoesSay)
        {
            simonObj.simonSaysBeforeCommandBool = true;

            simonObj.simonSaysStr = preSimonSaysStrs[randomSimonSaysStrInd];

        }
        else
        {

            simonObj.simonSaysBeforeCommandBool = false;

            simonObj.simonSaysStr = postSimonSaysStrs[randomSimonSaysStrInd - nPreSimonDoesSay];

        }

        simonObj.printSimonStatement();

    }
    else
    {

        simonObj.simonSaysBool = false;

        int randomSimonDoesntSayStrInd = std::rand() % nSimonDoesntSay;       // Generate a random number to decide on the Simon says string

        // If we choose a pre string
        if(randomSimonDoesntSayStrInd < nPreSimonDoesntSay)
        {
            simonObj.simonSaysBeforeCommandBool = true;

            simonObj.simonSaysStr = preSimonDoesntSayStrs[randomSimonDoesntSayStrInd];

        }
        else
        {

            simonObj.simonSaysBeforeCommandBool = false;

            simonObj.simonSaysStr = postSimonDoesntSayStrs[randomSimonDoesntSayStrInd - nPreSimonDoesntSay];

        }

        simonObj.printSimonStatement();

    }

    return 0;

}





















