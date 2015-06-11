#include "../../include/proto_monsters/proto_move_effects.h"

bool protoUpdateMoveEffect(ushort moveID, ProtoBattle &battle, bool enemyTurn){


    //Caster
    ProtoMonster            &caster    = enemyTurn ? battle.getEnemyMon() : battle.getPlayerMon();
    const ProtoSpecies      &casterSpc = ProtoSpeciesList::getSpecies(caster.getSpecies());

    //Targeted Enemy
    ProtoMonster            &target    = enemyTurn ? battle.getPlayerMon() : battle.getEnemyMon();
    const ProtoSpecies      &targetSpc = ProtoSpeciesList::getSpecies(target.getSpecies());

    //Used Move
    const ProtoMove         &move      = ProtoMoveList::getMove(moveID);



    //Abort Damage Calculation if the Move is a Status-Move or has Base Power 0 for another Reason
    if( (move.getClass() == ProtoMoveClasses::STATUS || move.getPower() == 0) ) return true;

    //Abort if the Move misses
    if( !battle.moveWillHit(!enemyTurn, moveID) ) return true;



    //Determine what Stats to use for Attack and Defense
    bool    isPhysical;
    ushort  damage, level, attack, defense, base;
    float   modifier, stab, type, crit, other, random;

    //Read Battler- & Move-dependent Values
    isPhysical  = (move.getClass() == ProtoMoveClasses::PHYSICAL);
    level       = caster.getLevel();
    attack      = caster.getCurrentStat( ProtoPrimStats::ATK + (!isPhysical) * 1 ); //Physical -> use ATK, Special -> use SPATK.
    defense     = target.getCurrentStat( ProtoPrimStats::DEF + (!isPhysical) * 1 ); //Physical -> use DEF, Special -> use SPDEF.
    base        = move.getPower();

    //Calculate Stab Factor
    if(move.getType() == casterSpc.getType1() || move.getType() == casterSpc.getType2()){
      stab = 1.5f;
    } else stab = 1.0f;

    //Calculate Type Effectiveness by multiplying both Factors
    type =    protoGetTypeEff(move.getType(), targetSpc.getType1())
            * protoGetTypeEff(move.getType(), targetSpc.getType2());

    //Crit Chance 1/16
    crit    = 1.0f + ((rand() % 10000) < 10000 / 16) * 1.0f; //C: 1.0f + (hits critically?) * 1.0f

    //Other Modifiers \TBI
    other   = 1.0f;

    //Random Modifier [.85; 1.0]
    random  = .85f + ((float)rand() / (float)RAND_MAX) * .15f;

    //Calculate Modifier (Stab x Type x Crit x Other x Random[.85,..,1]
    modifier = stab * type * crit * other * random;

    //Calculate final Damage
    damage = (ushort)(modifier * floor(floor(floor(2.0f * level / 5.0f + 2.0f) * (float)attack * (float)base / (float)defense) / 50.0f) + 2.0f);

    return true;
}


bool protoDrawMoveEffect(ushort moveID, ProtoBattle &battle, bool enemyTurn){

        //Caster
        ProtoMonster            &caster    = enemyTurn ? battle.getEnemyMon() : battle.getPlayerMon();
        const ProtoSpecies      &casterSpc = ProtoSpeciesList::getSpecies(caster.getSpecies());

        //Targeted Enemy
        ProtoMonster            &target    = enemyTurn ? battle.getPlayerMon() : battle.getEnemyMon();
        const ProtoSpecies      &targetSpc = ProtoSpeciesList::getSpecies(target.getSpecies());

        //Used Move
        const ProtoMove         &move      = ProtoMoveList::getMove(moveID);

        switch(move.getEffect()){

            default:
                return true;
        }

        return true;
}
