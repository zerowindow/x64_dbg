#ifndef _SIMPLESCRIPT_H
#define _SIMPLESCRIPT_H

#include "command.h"

//structures
struct SCRIPTBP
{
    int line;
    bool silent; //do not show in GUI
};

struct LINEMAPENTRY
{
    SCRIPTLINETYPE type;
    char raw[256];
    union
    {
        char command[256];
        SCRIPTBRANCH branch;
        char label[256];
        char comment[256];
    } u;
};

//functions
void scriptload(const char* filename);
void scriptunload();
void scriptrun(int destline);
void scriptstep();
bool scriptbptoggle(int line);
bool scriptbpget(int line);
bool scriptcmdexec(const char* command);
void scriptabort();
SCRIPTLINETYPE scriptgetlinetype(int line);
void scriptsetip(int line);
void scriptreset();
bool scriptgetbranchinfo(int line, SCRIPTBRANCH* info);

//script commands
CMDRESULT cbScriptLoad(int argc, char* argv[]);
CMDRESULT cbScriptMsg(int argc, char* argv[]);
CMDRESULT cbScriptMsgyn(int argc, char* argv[]);

#endif // _SIMPLESCRIPT_H
