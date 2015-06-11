#pragma once

#include "proto_enums.h"
#include "proto_game.h"

typedef struct protodialogmsg_t
{
    string msg;
    bool question;

} ProtoDialogMsg;

class ProtoDialogSystem
{
private:
    static vector<ProtoDialogMsg> m_messageQueue;
    static vector<string> m_choiceList;
    static float m_textSpeed;
    static float m_textPosition;
    static bool  m_active;
    static bool  m_dispatchingMessage;
    static bool  m_dispatchingQuestion;
    static ubyte m_selectedAnswer;
    static bool  m_answerConfirmed;

public:
    static bool isActive(void);
    static bool isDispatchingQuestion(void);
    static bool isDispatchingMessage(void);
    static bool wasQuestionAnswered(string &answer);
    static void dispatch(const ProtoGame &game, float dt);
    static void draw(ProtoGame &game);
    static void enqueueMessage(const string &msg);
    static void enqueueQuestion(const string &msg, const vector<string> &choices);
};
