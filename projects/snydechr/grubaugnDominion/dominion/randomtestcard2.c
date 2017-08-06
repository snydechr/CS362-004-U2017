/**********************************************************************
 *						Random Test for Great Hall
 *
 * 1. current player should recieve exactly one additional
 * 2. cards should come from his own pile
 * 3. No state change should occur for other players
 * 4. No state change should occur to the victory and kingdom card piles
 * 5. exactly one card should be discarded and it should be the great hall
 * 6. exactly one additional action should be created
 ***********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	srand(time(NULL));
	int randCardIdx, randPlayerIdx, initSuccess, i, j, u, q;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	int randNumPlayers;
	struct gameState game1, game2;
	int caseSuccess = 0;
	int otherPlayerIDX;
	int testCase = 0;
	int numSuccess = 0;
	int playerCompSuccess = 0;
	int supplySuccess = 0;
	int bonus = 0;

	printf(">>>>>>    GREAT HALL TESTING    <<<<<<\n");
	int caseCounter = 0;
	while(caseCounter <= 1000)
	{
		randNumPlayers = 2 + (rand() % 3);			//randomize the number of players
		randPlayerIdx = rand() % (randNumPlayers );	//randomize which player is playing the card
		randCardIdx = rand() % 6;					//randomize the placement of the card under test in the players hand

		supplySuccess = 0;
		playerCompSuccess = 0;
		caseSuccess = 0;
		initSuccess = initializeGame(randNumPlayers, kingCards, seed, &game1);
		
		game1.hand[randPlayerIdx][randCardIdx] = great_hall;
		game1.whoseTurn = randPlayerIdx;
		copyGameState(&game1,&game2);	//copy the initial gamestate  for comparison later
		

		//great_hall_action(&game1, randPlayerIdx, randCardIdx);	//play great hall card passing in the inital gamestate to be modified
		cardEffect(great_hall, 0, 0, 0, &game1, randCardIdx, &bonus);

		//check that 1 additional cards are drawn meaning the number of cards currently in the hand should be larger by 0
		if((game2.handCount[randPlayerIdx]  ) == (game1.handCount[randPlayerIdx]))
		{
			caseSuccess++;
			printf("great_hall_action(): PASS for handCount\n");
		}
		else
			printf("great_hall_action(): FAIL for handCount\n");

		//check that the new deck count is larger 
		if((game2.deckCount[randPlayerIdx] - 1) == game1.deckCount[randPlayerIdx])
		{
			caseSuccess++;
			printf("great_hall_action(): PASS for deckCount\n");

		}
		else
			printf("great_hall_action(): FAIL for deckCount\n");

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
				printf("great_hall_action(): FAIL for supply\n");

		}
		if(supplySuccess ==  treasure_map + 1)
		{
			printf("great_hall_action(): PASS for supply\n");
			caseSuccess++;
		}

		//compare other players states
		for(j = 0; j < randNumPlayers; j++)
		{
			if((j != randPlayerIdx) && (randNumPlayers > 1))
			{
				//printf("Other player %d comparison\n", j);
				//printf("random player index: %d\n\n", randPlayerIdx);
				if(comparePlayerState(&game1, &game2, j) > 0)
					printf("great_hall_action(): FAIL for external player comparison\n");
				else
					playerCompSuccess += 1;
			}
			else
				playerCompSuccess += 1;
		}
		if(playerCompSuccess > 0)
		{
			caseSuccess++;
			printf("great_hall_action(): PASS for external player comparison\n");

		}
		
		//test for additional action allowed
		if((game2.numActions + 1) == game1.numActions)
		{
			caseSuccess++;
			printf("great_hall_action(): PASS for additional action added\n");

		}
		else
			printf("great_hall_action(): FAIL for additional action added\n");


		if(caseSuccess >= 5)
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


	printf(">>>>>>    GREAT HALL TESTING COMPLETE    <<<<<<\n");
	

	//printf("The number of players in this game is: %d\n", game1.randNumPlayers);
	//game1.randNumPlayers = 100;
	//printf("The number of players in this game is: %d\n", game1.randNumPlayers);

	return 0;
}
