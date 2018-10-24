/*
 * song.c
 *
 *  Created on: Apr 21, 2018
 *      Author: saldanha
 */


#include "open_interface.h"
#include <Math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void play_song(int songNum)
{/*
    int numNotes, i, note;

    unsigned char * songNotes;
    unsigned char * duration;


    srand(time(NULL));

    if(songNum == 1)
    {
        numNotes = 4;
        unsigned char notes[numNotes];

        for(i = 0; i < numNotes; i++)
        {
            note = (rand() + 31)%(137+1);
            notes[i] = note;
        }

        songNotes = notes;

    }

    oi_loadSong(songNum, numNotes, songNotes, duration);
    oi_play_song(songNum);
*/

        srand(time(NULL));
        int numNotes = 14;

        if(songNum == 1){
            unsigned char songNotes[14]={60, 60, 67, 67, 69, 69, 67, 65, 65, 64, 64, 62, 62, 60};
            unsigned char songDurations[14]={32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 64};
            oi_loadSong(songNum, numNotes, songNotes, songDurations);
            oi_play_song(songNum);
        }

}

