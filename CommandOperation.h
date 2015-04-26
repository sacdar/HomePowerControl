#ifndef _COMMANDOPERATION_H_
#define _COMMANDOPERATION_H_

#define CMD_LEDON "on"
#define CMD_LEDOFF "off"

struct CommandOperation {
    char *command;
    bool (*operation)();
};

// operations
bool setLedOn();
bool setLedOff();

static CommandOperation commandOperations[] = {
    {CMD_LEDON, setLedOn},
    {CMD_LEDOFF, setLedOff},
};

#endif //_COMMANDOPERATION_H_
