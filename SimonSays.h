#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include <string>

class Simon {

    public:
        bool                simonSaysBeforeCommandBool;
        bool                simonSaysBool;
        const char*         commandStr;
        const char*         simonSaysStr;

        void printSimonStatement()
        {

            if(simonSaysBeforeCommandBool)
            {
                printf("%s%s", simonSaysStr, commandStr);
            }
            else
            {
                printf("%s%s", commandStr, simonSaysStr);
            }

        }


};



#endif
