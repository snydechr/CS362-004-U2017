/**********************************************************************
 *						Test for Great Hall
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

	int handPos, currentPlayer, initSuccess, i, j;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	int numPlayers = 2;
	struct gameState game1, game2;
	int caseSuccess = 0;
	int otherPlayerIDX;
	int testCase = 0;
	int numSuccess = 0;
	int playerCompSuccess = 0;
	int supplySuccess = 0;
	int bonus = 0;

	printf(">>>>>>    GREAT HALL TESTING    <<<<<<\n");
	for(numPlayers = 2; numPlayers < (MAX_PLAYERS+1); numPlayers++)
	{
		for(currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
		{
			supplySuccess = 0;
			playerCompSuccess = 0;
			caseSuccess = 0;
			initSuccess = initializeGame(numPlayers, kingCards, seed, &game1);
			
			game1.hand[currentPlayer][3] = great_hall; 
		    game1.whoseTurn = currentPlayer; //This is necessary if calling the cardEffect() function in order to set the current player correctly
			copyGameState(&game1,&game2);	//copy the initial gamestate  for comparison later
			

			//now play great hall
			//
			//great_hall_action(&game1, currentPlayer, 3);	//This is the call for Chris's code

			//The card effect version of the great hall requires the currentPlayer, the state, and the handposition.
			//All other options for card effect arguments may be left as fixed values...
			
			cardEffect(great_hall, 0, 0, 0, &game1, 3, &bonus);

			//check that 1 additional cards are drawn meaning the number of cards currently in the hand should be larger by 0
			if((game2.handCount[currentPlayer]  ) == (game1.handCount[currentPlayer]))
			{
				caseSuccess++;
				printf("great_hall_action(): PASS for handCount\n");
			}
			else
				printf("great_hall_action(): FAIL for handCount\n");

			//check that the new deck count is larger 
			//printf("deck count game 2: %d\n",game2.deckCount[currentPlayer]);
			//printf("deck count game 1: %d\n",game1.deckCount[currentPlayer]);
			if((game2.deckCount[currentPlayer] - 1) == game1.deckCount[currentPlayer])
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
			for(j = 0; j < numPlayers; j++)
			{
				if(j != currentPlayer)
				{

					if(comparePlayerState(&game1, &game2, j) > 0)
						printf("great_hall_action(): FAIL for external player maintenance\n");
					else
						playerCompSuccess = 1;
				}
			}
			if(playerCompSuccess > 0)
				caseSuccess++;
			
			//printf("numActions game1: %d\n", game1.numActions);
			//printf("numActions game2: %d\n", game2.numActions);
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

				
		}
	
	}

	printf("%d PASSED test cases out of %d\n", numSuccess, testCase);
	printf("%d FAILED test cases out of %d\n", testCase-numSuccess, testCase);

	if((testCase-numSuccess) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");


	printf(">>>>>>    GREAT HALL TESTING COMPLETE    <<<<<<\n");
	

	//printf("The number of players in this game is: %d\n", game1.numPlayers);
	//game1.numPlayers = 100;
	//printf("The number of players in this game is: %d\n", game1.numPlayers);

	return 0;
}
