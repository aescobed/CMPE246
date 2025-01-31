


#include "include/SimonSays.h"
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <iostream>


const int BUTTON_PIN = 23;  
const int LED_PIN = 18;



bool detectPress()
{
    static int lastState = 1;
    int currentState = gpioRead(BUTTON_PIN);

    if(currentState && !lastState)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        lastState = 1;
        return true;
    }

    lastState = currentState;
    return false;
}



int main()
{

    gpioInitialise();

    gpioSetMode(BUTTON_PIN, PI_INPUT);
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);


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
        "do nothing",
        "press the button once",
        "press the button twice"
        // TODO: Add command string here
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

    int pressCount = 0;

    // if Simon did say this statement
    if(randomDoesSimonSay)
    {

        simonObj.simonSaysBool = true;

        int randomSimonSaysStrInd = std::rand() % nSimonDoesSay;       // Generate a random number to decide on the Simon says string

        auto duration = std::chrono::seconds(5);

        // If we choose a pre string
        if(randomSimonSaysStrInd < nPreSimonDoesSay)
        {
            
            simonObj.simonSaysBeforeCommandBool = true;

            simonObj.simonSaysStr = preSimonSaysStrs[randomSimonSaysStrInd];

            simonObj.printSimonStatement();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            auto startTime = std::chrono::steady_clock::now();

            while(std::chrono::steady_clock::now() - startTime < duration)
            {

                if(detectPress())
                {

                    pressCount++;

                    printf("button press detected\n");

                }

            }


        }
        else
        {

            simonObj.simonSaysBeforeCommandBool = false;

            simonObj.simonSaysStr = postSimonSaysStrs[randomSimonSaysStrInd - nPreSimonDoesSay];

            simonObj.printSimonStatement();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            auto startTime = std::chrono::steady_clock::now();

            while(std::chrono::steady_clock::now() - startTime < duration)
            {

                if(detectPress())
                {

                    pressCount++;

                    printf("button press detected\n");

                }

            }

        }

        switch(randomCommand)
        {
            case 0:
                if(pressCount == 0)
                    printf("Success!\n");
                else
                    printf("Incorrect!\n");
                break;
            case 1:
                if(pressCount == 1)
                    printf("Success!\n");
                else
                    printf("Incorrect!\n");
                break;
            case 2:
                if(pressCount == 2)
                    printf("Success!\n");
                else
                    printf("Incorrect!\n");
                break;
            default:
                printf("Incorrect\n");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

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

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        // You should never do anything here


    }

    return 0;

}
