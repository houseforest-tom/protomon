#include "../../include/proto_world/proto_player.h"

ProtoPlayer::ProtoPlayer(NTextureManager &texmgr, const NKeyboard &keyboard)
    : ProtoNPC(texmgr, "player", 0),
      m_pKeyboard(&keyboard)
{
    setTileX(0);
    setTileY(0);
    setCameraPosition(0, 0);
    setDrawSize(PROTO_TILE_SIZE, PROTO_TILE_SIZE / 4 * 5);

    //Fill Player's Bag
    for(uint i=0; i<100; ++i){

        ushort id = 1 + rand() % (ProtoItemList::getItemCount());
        m_bag.addItemQuantity({ id, (ushort)(1 + rand() % 10) });
    }

    //Create a Team for the Player to inspect / battle with
    for(uint i=0; i<PROTO_TEAM_SIZE; ++i){

        ushort species = 1 + (rand() % ProtoSpeciesList::getSpeciesCount());

        ProtoMonster *monster = nullptr;
        if( i < PROTO_TEAM_SIZE - 1 )
            monster = new ProtoMonster(species, 100);
        else ( monster = new ProtoMonster(3, 100) )->setShiny( true );

        for(uint stat=0; stat<ProtoPrimStats::COUNT; ++stat){
            monster->setIV(stat, IV_MAX);
            monster->setEV(stat, EV_MAX);
        }

        for(uint slot=0; slot<PROTO_MOVESET_SIZE; ++slot){
            while(!monster->getMoveset().setMove(slot, 1 + (rand() % (ProtoMoveList::getMoveCount()))));
        }

        m_team.addMember(monster);
    }
}

void ProtoPlayer::update(float dt)
{
    if(!m_pRenderer || m_frozen) return;

    if(!isWalking())
    {
        //Press LSHIFT to run
        if(PROTOKEYDN(*m_pKeyboard, LShift)) setWalkSpeed(5);
        else setWalkSpeed(2);

             if(m_pKeyboard->isKeyDown(sf::Keyboard::W)) { setDirection(ProtoDirections::UP);      if(getTileY() > 0) walk(1); }
        else if(m_pKeyboard->isKeyDown(sf::Keyboard::A)) { setDirection(ProtoDirections::LEFT);    if(getTileX() > 0) walk(1); }
        else if(m_pKeyboard->isKeyDown(sf::Keyboard::S)) { setDirection(ProtoDirections::DOWN);    if(getTileY() < m_currentMapHeight - 1) walk(1); }
        else if(m_pKeyboard->isKeyDown(sf::Keyboard::D)) { setDirection(ProtoDirections::RIGHT);   if(getTileX() < m_currentMapWidth  - 1) walk(1); }
    }

    ProtoNPC::update(dt);
}

void ProtoPlayer::draw(NRenderer &renderer)
{
    if(!m_pRenderer) m_pRenderer = &renderer;
    ProtoMapObject::draw(renderer);
}
