#ifndef _RANDOMTESTING_H
#define _RANDOMTESTING_H

#include "dominion.h"
#include "dominion_helpers.h"

int randNum(int max);

int getStartingSupply(int card, int players);

void printState (struct gameState *state);

void randomState (struct gameState *state);

void copyState (struct gameState *original, struct gameState *copy);

int cardHandIndex (int card, struct gameState *state);

#endif


