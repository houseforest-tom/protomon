#include "../../include/proto_battle/proto_gsc_wildbattleitem.h"

ProtoGScWildBattleItem::ProtoGScWildBattleItem(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){
    onEnter(prev);
}

void ProtoGScWildBattleItem::onEnter(ProtoGameScene *prev){

    //Store previous Scene (Main Menu)
    this->prev = prev;
}

void ProtoGScWildBattleItem::update(float dt){

    if(!hasFinished()){

        m_accumTime += dt;

        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Escape)){
            m_pBattle->setBattleSceneAndDelete(prev, this); //Return to Main Scene
        }

        //Manouver one Item down
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::S)){
            m_itemSelection = (m_itemSelection + 1) % (m_pBattle->getItemBag().getElementCount(m_bagSelection) + 1);
        }

        //Manouver one Item up
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::W)){
            m_itemSelection = (m_itemSelection == 0 ? (m_pBattle->getItemBag().getElementCount(m_bagSelection)) : m_itemSelection - 1);
        }

        //Manouver to the next Sub-Bag (right)
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::D)){
            m_bagSelection = (m_bagSelection + 1) % ProtoItemTypes::COUNT;
            m_itemSelection = 0;
        }

        //Manouver to the previous Sub-Bag (left)
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::A)){
            if(m_bagSelection == 0) m_bagSelection = ProtoItemTypes::COUNT - 1;
            else m_bagSelection--;
            m_itemSelection = 0;
        }

        //[SPACE] pressed -> Do something according to Selection
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Space)){

            //'CANCEL' selected
            if(m_itemSelection >= m_pBattle->getItemBag().getElementCount(m_bagSelection)){
                m_pBattle->setBattleSceneAndDelete(prev, this); //Return to Main Scene
            }
        }
    }
}

void ProtoGScWildBattleItem::draw(NRenderer &renderer){

    NTextBuffer<128> buf;
    const NFont &fnt = m_pBattle->getFontMgr().getAsset("default");
    float ww = renderer.getWindowWidth();
    float wh = renderer.getWindowHeight();

    //Render White BG Boxes (for Bag Sprite, Sub-Bag Name Panel & Item Preview Panel)
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(5, 5, ww / 3 - 5, wh / 2 - 10);
    renderer.renderQuad(5, wh / 2, ww / 3 - 5, 48);
    renderer.renderQuad(5, wh / 2 + 48 + 5, ww / 3 - 5, wh / 2 - 48 - 10);

    //Render Backpack Sprite
    renderer.renderTexQuad(m_pBattle->getTexMgr().getAsset("bag"), 20, 20, ww / 3 - 40, wh / 2 - 45);

    //Render currently opened Sub-Bag's Name (and adjecant)
    renderer.renderString(fnt, 20, 5 + ww / 6 - 40,  wh / 2 + 12, 0x000000FF, m_bagNames[m_bagSelection]);
    renderer.renderString(fnt, 16, 5 + ww / 6 - 180, wh / 2 + 6,  0x555555FF, m_bagNames[(m_bagSelection > 0 ? (m_bagSelection - 1) : ProtoItemTypes::COUNT-1)]);
    renderer.renderString(fnt, 16, 5 + ww / 6 + 100, wh / 2 + 6,  0x555555FF, m_bagNames[(m_bagSelection + 1) % ProtoItemTypes::COUNT]);


    //-------
    uint  n             = 12;               //Number of displayed Items
    float h             = (wh - 10.0f) / n; //Height of each Segment
    bool  cancelDrawn   = false;            //Cancel Option drawn yet?
    uint  beginN        = (m_itemSelection / n) * n;

    for(uint i=beginN; i<beginN+n; ++i){

        //White BG Box
        renderer.renderQuad(ww / 3 + 5, 5 + h * (i-beginN), ww / 3 * 2 - 10, h - 1);

        //Item Name and Quantity
        if(m_pBattle->getItemBag().getElementCount(m_bagSelection) > i){

            sprintf(buf, "%s%s", (m_itemSelection == i ? " > " : ""), ProtoItemList::getItem(m_pBattle->getItemBag().getElement(m_bagSelection, i).id).name.c_str());

            //Name
            float y = 5 + h * (i-beginN) + 18;
            renderer.renderString(fnt, 20, ww / 3 + 25, y,
                                  (i == m_itemSelection ? 0x000000FF : 0x555555FF),
                                  string(buf));

            sprintf(buf, "x%03u", m_pBattle->getItemBag().getElement(m_bagSelection, i).count);

            //Quantity
            renderer.renderString(fnt, 20, ww - 100, y,
                                  (i == m_itemSelection ? 0x000000FF : 0x555555FF),
                                  string(buf));
        }

        else if(!cancelDrawn){

            //Render Cancel Option
            renderer.renderString(fnt, 20, ww / 3 + 25, 5 + h * (i-beginN) + 18, (i == m_itemSelection ? 0x000000FF : 0x555555FF), (m_itemSelection == m_pBattle->getItemBag().getElementCount(m_bagSelection) ? " > CANCEL" : "CANCEL"));
            cancelDrawn = true;
        }

        //Render Description Text
        const uint charsPerRow = 30;
        if(i == m_itemSelection && i < m_pBattle->getItemBag().getElementCount(m_bagSelection)){

            ushort itemID = m_pBattle->getItemBag().getElement(m_bagSelection, i).id;

            sprintf(buf, "item_%u", itemID);
            string alias = string(buf);

            const NTexture &itemSpr = m_pBattle->getTexMgr().getAsset(alias);

            renderer.renderTexQuad(itemSpr, 220 - itemSpr.getWidth(), 530 - itemSpr.getHeight(), itemSpr.getWidth() * 2, itemSpr.getHeight() * 2);

            const string &desc = ProtoItemList::getItem(itemID).description;
            uint descLen = desc.length();
            uint pos = 0;

            while(pos < descLen){
                renderer.renderString(fnt, 16, 60, 640 + 20 * pos / charsPerRow, 0x000000FF, desc.substr(pos, charsPerRow));
                pos += charsPerRow;
            }
        }
    }
    //-------
}

void ProtoGScWildBattleItem::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleItem::~ProtoGScWildBattleItem(void){
    onExit();
}
