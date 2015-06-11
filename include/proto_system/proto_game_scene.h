#pragma once

#include <NBase.h>
#include <NDrawable.h>

class ProtoGameScene : public NDrawable {

private:
    //Has the Scene finished?
    bool  m_finished = false;

public:
    //Ctor
    ProtoGameScene(ProtoGameScene *prev){ cout << "Constructed ProtoGameScene (or Derivate Class) Entity" << endl; (void)prev; }

    //Routine called upon entering the Scene
    virtual void onEnter(ProtoGameScene *prev) = 0;

    //Update the Scene
    virtual void update(float dt) = 0;

    //Draw the Scene
    virtual void draw(NRenderer &renderer) = 0;

    //Routine called upon exiting (deleting) the Scene
    virtual void onExit(void){ }

    //Return whether the Scene finished
    inline bool hasFinished(void) const { return m_finished; }

    //Set whether the Scene has finished
    inline void finish(void){ m_finished = true; }

    //Dtor
    virtual ~ProtoGameScene(void){ cout << "Deleted ProtoGameScene (or Derivate Class) Entity" << endl; onExit(); }
};
