/*
 *  sprite_defines.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/29/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */


#ifndef _SPRITEDEFINES_H
#define _SPRITEDEFINES_H

#define BLOCK_VISIBILITY 1
#define BLOCK_MOVEMENT 2
#define ALIVE 3
#define EXPIRATION 4
#define EXPIRATION_TICK 5
#define PICKUP_SCORE 6
#define BUTTON_RETURN_VALUE 7 // to avoid collision with button logic
#define SPAWN_POINT 8
#define DETENTION_POINT 9
#define PLAYER_CAPTURED 10
#define PLAYER_LIVES 11

/****************
 WATCH DOG DEFINITIONS - for automation. win conditions, etc
 ****************/

#define DAWG_PLAYER_CAPTURED 100 // automation alert. watch dog can act on this.

#endif // _SPRITEDEFINES_H