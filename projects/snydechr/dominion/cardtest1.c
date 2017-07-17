/**********************************************************************
 *						Test for smithy
 *
 * 1. current player should recieve exactly 3 cards
 * 2. 3 cards should come from his own pile
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
	//
	//check the state of other players prior to playing of smithy
	//check the state of other players after playing smithy
	//
	//check the state of the victory piles (estate 1, duchy 2, province 3)
	//check the state of the kingdom piles (get the indices from the chosen kingdom cards in the init)
	//
	int handPos, currentPlayer, initSuccess, i, j;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	//struct gameState game1 = malloc(sizeof(struct gameState));
	//struct gameState game2 = malloc(sizeof(struct gameState));
	int numPlayers = 2;
	struct gameState game1, game2;
	int caseSuccess = 0;
	int otherPlayerIDX;
	int testCase = 0;
	int numSuccess = 0;
	int playerCompSuccess = 0;
	int supplySuccess = 0;

	printf(">>>>>>    SMITHY TESTING    <<<<<<\n");
	for(numPlayers = 2; numPlayers < (MAX_PLAYERS+1); numPlayers++)
	{
		for(currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
		{
			supplySuccess = 0;
			playerCompSuccess = 0;
			caseSuccess = 0;
			initSuccess = initializeGame(numPlayers, kingCards, seed, &game1);
			
			game1.hand[currentPlayer][3] = smithy; 

			copyGameState(&game1,&game2);	//copy the initial gamestate  for comparison later
			

			//now play smithy
			//
			smithy_action(&game1, 3, currentPlayer);

			//check that 3 additional cards are drawn meaning the number of cards currently in the hand should be larger by 2
			if((game2.handCount[currentPlayer] + 2) == (game1.handCount[currentPlayer]))
			{
				caseSuccess++;
				printf("smithy_action(): PASS for handCount\n");
			}
			else
				printf("smithy_action(): FAIL for handCount\n");
			if((game2.deckCount[currentPlayer] - 3) == game1.deckCount[currentPlayer])
			{
				caseSuccess++;
				printf("smithy_action(): PASS for deckCount\n");

			}
			else
				printf("smithy_action(): FAIL for deckCount\n");
			
			//check to make sure the supplies don't change
			for(i = 0; i < (treasure_map + 1); i++)
			{
				if(game2.supplyCount[i] == game1.supplyCount[i])
				{
					supplySuccess++;
					//printf("smithy_action(): PASS for supply\n");

				}
				else
					printf("smithy_action(): FAIL for supply\n");

			}
			if(supplySuccess == treasure_map +1)
			{
				printf("smithy_action(): PASS for supply \n");
			}

			//compare other players states
			for(j = 0; j < numPlayers; j++)
			{
				if(j != currentPlayer)
				{

					if(comparePlayerState(&game1, &game2, j) > 0)
						printf("smithy_action(): FAIL for external player maintenance\n");
					else
						playerCompSuccess = 1;	
				}
			}
			if(playerCompSuccess > 0)
				caseSuccess++;

			if(caseSuccess >= 4)
				numSuccess++;
			testCase++;

				
		}
	
	}

	printf("%d PASSED test cases out of %d\n", numSuccess, testCase);
	printf("%d FAILED test cases out of %d\n", testCase-numSuccess, testCase);

	if((testCase-numSuccess) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");



	printf(">>>>>>    SMITHY TEST COMPLETE    <<<<<<\n");

	//printf("The number of players in this game is: %d\n", game1.numPlayers);
	//game1.numPlayers = 100;
	//printf("The number of players in this game is: %d\n", game1.numPlayers);

	return 0;
}
