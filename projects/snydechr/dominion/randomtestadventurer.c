/**********************************************************************
 *						Test for Adventurer
 *
 * 1. current player should recieve exactly 2 treasures
 * 2. cards should come from his own pile
 * 3. No state change should occur for other players
 * 4. No state change should occur to the victory and kingdom card piles
 ***********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//check player deck before drawing
	//check player deck after drawing
	//make sure that the number of cards in the deck decreases and the number of discards increases
	//
	//check the state of other players prior to playing of smithy
	//check the state of other players after playing smithy
	//
	//check the state of the victory piles (estate 1, duchy 2, province 3)
	//check the state of the kingdom piles (get the indices from the chosen kingdom cards in the init)
	//

	srand(time(NULL));
	int handPos, randPlayerIdx, initSuccess, i, j, randNumPlayers, randCardIdx;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	//int randNumPlayers = 2;
	struct gameState game1, game2;
	int caseSuccess = 0;
	int otherPlayerIDX;
	int testCase = 0;
	int numSuccess = 0;
	int playerCompSuccess = 0;
	int supplySuccess = 0;
	int r;

	printf(">>>>>>    ADVENTURER TESTING    <<<<<<\n");



	//start of random testing
	int caseCounter = 0;
	while(caseCounter <= 100)
	{
		//randomize number of players
		//randomize the current player from within the set of available players
		//randomize the hand index at which the adventurer is stored		//	
		//make sure to take note of the index where the adventurer card is at
		//
		//test the conditions mentioned above
		randNumPlayers = 2 + (rand() % 3);
		randPlayerIdx = rand() % (randNumPlayers);
		randCardIdx = rand() % 6;

		supplySuccess = 0;
		playerCompSuccess = 0;
		caseSuccess = 0;
		initSuccess = initializeGame(randNumPlayers, kingCards, seed, &game1);
		
		game1.hand[randPlayerIdx][randCardIdx] = adventurer;
		

		//The for loop below fills the discard pile so that when the deck appears to be empty it has cards to reshuffle
		for(r = 0; r < 5; r++)
		{
			game1.discard[randPlayerIdx][r] = rand() % 26;
			game1.discardCount[randPlayerIdx]++;
		}
		game1.deckCount[randPlayerIdx] = rand() % 2;	//randomize the deck count available
		//game1.deckCount[randPlayerIdx] = 0;	//testing the deck count to step into the desired reshuffle conditional
		//game1.hand[randPlayerIdx][game1.handCount[randPlayerIdx]-1] = 4 + (rand() % 5);
		
		copyGameState(&game1,&game2);	//copy the initial gamestate  for comparison later
		

		//now play adventurer
		//
		adventurer_action(&game1, randCardIdx, randPlayerIdx);

		//check that 2 additional cards are drawn meaning the number of cards currently in the hand should be larger by 1
		if((game2.handCount[randPlayerIdx] + 1 ) == (game1.handCount[randPlayerIdx]))
		{
			caseSuccess++;
			printf("adventurer_action(): PASS for handCount\n");
		}
		else
			printf("adventurer_action(): FAIL for handCount\n");
		if(game2.deckCount[randPlayerIdx] > game1.deckCount[randPlayerIdx])
		{
			caseSuccess++;
			printf("adventurer_action(): PASS for deckCount\n");

		}
		else
			printf("adventurer_action(): FAIL for deckCount\n");

		//check that discard increases
		
		//check to make sure the supplies don't change
		for(i = 0; i < (treasure_map + 1); i++)
		{
			if(game2.supplyCount[i] == game1.supplyCount[i])
			{
				supplySuccess++;
				//printf("supplySuccess: %d\n", supplySuccess);

			}
			else
				printf("adventurer_action(): FAIL for supply\n");

		}
		if(supplySuccess ==  treasure_map + 1)
		{
			printf("adventurer_action(): PASS for supply\n");
			caseSuccess++;
		}
		//compare other players states
		for(j = 0; j < randNumPlayers; j++)
		{
			//printf("j: %d\n", j);
			//printf("randNumPlayers: %d\n", randNumPlayers);
			if((j != randPlayerIdx) && (randNumPlayers > 1))
			{

				if(comparePlayerState(&game1, &game2, j) > 0)
					printf("adventurer_action(): FAIL for external player comparison\n");
				else
					playerCompSuccess += 1;
			}
			else
				playerCompSuccess += 1;
		}
		if(playerCompSuccess > 0)
		{
			caseSuccess++;
			printf("adventurer_action(): PASS for external player comparison\n");
		}
		
		//printf("caseSuccess: %d\n", caseSuccess);
		if(caseSuccess >= 4)
			numSuccess++;
		testCase++;
		caseCounter++;
	}

	printf("%d PASSED test cases out of %d\n", numSuccess, testCase);
	printf("%d FAILED test cases out of %d\n", testCase-numSuccess, testCase);

	if((testCase-numSuccess) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");



	printf(">>>>>>    ADVENTURER TEST COMPLETE    <<<<<<\n");

	//printf("The number of players in this game is: %d\n", game1.randNumPlayers);
	//game1.randNumPlayers = 100;
	//printf("The number of players in this game is: %d\n", game1.randNumPlayers);

	return 0;
}
