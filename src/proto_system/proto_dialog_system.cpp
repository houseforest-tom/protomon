#include "../../include/proto_system/proto_dialog_system.h"

vector<ProtoDialogMsg>  ProtoDialogSystem::m_messageQueue;
vector<string>          ProtoDialogSystem::m_choiceList;
float                   ProtoDialogSystem::m_textSpeed              = 15.0f;
float                   ProtoDialogSystem::m_textPosition           = 0.0f;
bool                    ProtoDialogSystem::m_active                 = false;
bool                    ProtoDialogSystem::m_dispatchingMessage;
bool                    ProtoDialogSystem::m_dispatchingQuestion;
ubyte                   ProtoDialogSystem::m_selectedAnswer         = 0;
bool                    ProtoDialogSystem::m_answerConfirmed        = false;

bool ProtoDialogSystem::isActive(void)
{
    return m_active;
}

bool ProtoDialogSystem::isDispatchingQuestion(void)
{
    return m_dispatchingQuestion;
}

bool ProtoDialogSystem::isDispatchingMessage(void)
{
    return m_dispatchingMessage;
}

bool ProtoDialogSystem::wasQuestionAnswered(string &answer)
{
    if(m_answerConfirmed)
    {
        answer = m_choiceList[m_selectedAnswer];
        return true;
    }

    return false;
}

void ProtoDialogSystem::dispatch(const ProtoGame &game, float dt)
{
    if(m_active)
    {
        if(m_answerConfirmed)
        {
            m_answerConfirmed = false;
            m_selectedAnswer = 0;
        }

        if(m_messageQueue.size() == 0)
            m_active = false;

        //Still Messages left to dispatch
        else
        {
            const NKeyboard &kb = game.getKeyboard();
            const string &msg = m_messageQueue.front().msg;

            //Currently dispatching a Message
            if(m_dispatchingMessage)
            {
                m_textPosition += dt * m_textSpeed * (PROTOKEYDN(kb, Space) ? 3 : 1);
                if(m_textPosition >= msg.length())
                {
                    m_textPosition = msg.length();
                    if(PROTOKEYPR(kb, Space))
                    {
                        m_messageQueue.erase(m_messageQueue.begin());
                        m_dispatchingMessage = false;
                        m_textPosition = 0.0f;
                    }
                }

            }

            //Currently dispatching a Question
            else if(m_dispatchingQuestion)
            {
                m_textPosition += dt * m_textSpeed * (PROTOKEYDN(kb, Space) ? 3 : 1);
                if(m_textPosition >= msg.length())
                {
                    m_textPosition = msg.length();

                    if(PROTOKEYPR(kb, S))
                    {
                        m_selectedAnswer = ( (m_selectedAnswer + 1) % m_choiceList.size() );
                    }

                    else if(PROTOKEYPR(kb, W))
                    {
                        m_selectedAnswer = ( (m_selectedAnswer > 0) ? (m_selectedAnswer - 1) : (m_choiceList.size() - 1) );
                    }

                    else if(PROTOKEYPR(kb, Space))
                    {
                        m_messageQueue.erase(m_messageQueue.begin());
                        m_dispatchingMessage = false;
                        m_dispatchingQuestion = false;
                        m_textPosition = 0.0f;
                        m_answerConfirmed = true;
                    }
                }
            }

            //Not dispatching anything atm
            else
            {
                if(m_messageQueue.front().question)
                    m_dispatchingQuestion = true;
                else
                    m_dispatchingMessage = true;
            }
        }
    }
}

void ProtoDialogSystem::draw(ProtoGame &game)
{
    if(m_active)
    {
        NRenderer &rdr = game.getRenderer();
        const NTextureManager &txmgr = game.getTextureMgr();
        const NFont &fnt = game.getFontMgr().getAsset("default");
        const NTexture &arrow_txr = txmgr.getAsset("rarrow");

        //Render Textbox and Message
        protoRenderTextbox(rdr, txmgr, 0, PROTO_SCREEN_H - TEXTBOX_H, PROTO_SCREEN_W, TEXTBOX_H);
        rdr.renderString(
                            fnt,
                            TEXTBOX_TS,
                            10,
                            PROTO_SCREEN_H - TEXTBOX_H + 10,
                            0x000000FF,
                            m_messageQueue.front().msg.substr(0, (ushort)m_textPosition)
                        );

        if(m_dispatchingQuestion && m_textPosition >= m_messageQueue.front().msg.length())
        {
            //If currently dispatchng a Question, show Choices
            const uint numChoices = m_choiceList.size();
            protoRenderTextbox(rdr, txmgr, PROTO_SCREEN_W - 256, PROTO_SCREEN_H - TEXTBOX_H - 32 - numChoices * 32, 256, 32 + numChoices * 32);

            for(uint i=0; i<numChoices; ++i)
            {
                //Indicate current Selection by Arrow and Text Position
                if(m_selectedAnswer == i)
                {
                    rdr.renderTexQuad(
                                        arrow_txr,
                                        PROTO_SCREEN_W - 256 + 10,
                                        PROTO_SCREEN_H - TEXTBOX_H - 32 - numChoices * 32 + 16 + 32 * i,
                                        24,
                                        24,
                                        0
                                     );
                }

                //Print Choices
                rdr.renderString(
                                    fnt,
                                    TEXTBOX_TS,
                                    PROTO_SCREEN_W - 256 + 10 + (m_selectedAnswer != i ? 0 : 32),
                                    PROTO_SCREEN_H - TEXTBOX_H - 32 - numChoices * 32 + 16 + 32 * i,
                                    0x000000FF,
                                    m_choiceList[i]
                                );
            }
        }
    }
}

void ProtoDialogSystem::enqueueMessage(const string &msg)
{
    m_messageQueue.push_back( { msg, false } );
    m_active = true;
}

void ProtoDialogSystem::enqueueQuestion(const string &msg, const vector<string> &choices)
{
    m_messageQueue.push_back( { msg, true } );
    m_choiceList = choices;
    m_active = true;
}
