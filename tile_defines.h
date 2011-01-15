/*
 *  tile_defines.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef TILEDEFINES_H
#define TILEDEFINES_H

/*
#define TILESIZE 64
#define TILESETHEIGHT 20
#define TILESETWIDTH 20
*/

#define TILESIZE 64
#define TILESETHEIGHT 20
#define TILESETWIDTH 20


#define ZONETILES TILESETHEIGHT * TILESETWIDTH
#define QUADTILES ZONETILES / 4

#define ZONEHEIGHT TILESIZE * TILESETHEIGHT
#define ZONEWIDTH TILESIZE * TILESETWIDTH

#define QUADHEIGHT ZONEHEIGHT / 2
#define QUADWIDTH ZONEWIDTH / 2

/***********
 ANIMATION CRAP
 **********/
#define ANIM_MAX_FRAMES  6

#define ANIM_NONE  0
#define ANIM_IDLE  1
#define ANIM_WALK  2
#define ANIM_RUN  3
#define ANIM_ACTIVATE  4
#define ANIM_HIDE  5
#define ANIM_EXPLODE  6
#define ANIM_AMBIENT 7

#endif