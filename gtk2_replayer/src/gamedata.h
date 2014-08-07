/****************************************************************
 * This file is part of the "2048cc GTK+2 Replayer".
 *
 * Copyright:    2014 (c) migf1 <mig_f1@hotmail.com>
 * License:      Free Software (see comments in main.c for limitations)
 * Dependencies: 
 * --------------------------------------------------------------
 *
 * The public interface of the Gamedata "class".
 ****************************************************************
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdbool.h>

/* forward declaration of the Gamedata "class" as an opaque data-type */
typedef struct _Gamedata Gamedata;

#ifndef GAMEDATA_C
extern Gamedata      *make_gamedata( void );
extern Gamedata      *gamedata_free( Gamedata *gd );

extern char          *gamedata_get_fname( Gamedata *gd );
extern int           gamedata_get_didundo( Gamedata *gd );
extern long int      gamedata_get_nmoves( Gamedata *gd );
extern int           gamedata_get_dim( Gamedata *gd );
extern int           gamedata_get_sentinel( Gamedata *gd );
extern int           gamedata_get_nrandom( Gamedata *gd );
extern unsigned long gamedata_get_delay( Gamedata *gd );
extern int           gamedata_get_gamewon( Gamedata *gd );
extern long int      gamedata_get_tile_of_move(
                           Gamedata *gd,
			   int      itile,
			   long int imove
			   );
extern long int      gamedata_get_score_of_move(
                           Gamedata *gd,
                           long int imove
                     );
extern long int      gamedata_get_bestscore_of_move(
                           Gamedata *gd,
                           long int imove
                     );
extern int           gamedata_get_prevmv_of_move(
                           Gamedata *gd,
                           long int imove
                           );
extern int           gamedata_get_nextmv_of_move(
                           Gamedata *gd,
                           long int imove
                           );

extern void          dbg_gamedata_print_tiles_of_move(
                           Gamedata *gd,
                           long int imove
                           );
extern void          dbg_gamedata_print_tiles( Gamedata *gd );

extern bool          gamedata_set_from_fname(
			   Gamedata *gd, const char *fname
			   );
#endif

#endif