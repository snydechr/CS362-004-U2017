CFLAGS =  -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

#isGameOverTest
unittest1: unittest1.c dominion.o rngs.o 
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

#getCostTest
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

#update coins test
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

#hand card test
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

#smithy card test
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

#adventurer card test
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

#great hall test
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

#village test
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

#random adventurer test
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

#random village test
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

#random great hall test
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 dominion.c
	echo "Results for running dominion tests" > unittestresults.out

	echo "unittest1.c" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "unittest2.c" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "unittest3.c" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "unittest4.c" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "cardtest1.c" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest2.c" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "cardtest3.c" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

	echo "cardtest4.c" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out


#randomTestResults
randomtestresults.out: randomtestcard1 randomtestcard2 randomtestadventurer dominion.c
	echo "Results for running dominion random tests" > randomtestresults.out

	echo "randomtestcard1.c" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov -b -c -f dominion.c >> randomtestresults.out

	echo "randomtestcard2.c" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov -b -c -f dominion.c >> randomtestresults.out

	echo "randomtestadventurer.c" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov -b -c -f dominion.c >> randomtestresults.out

#random test results for adventurer
randomtestadventurer.out: randomtestadventurer dominion.c
	echo "Results for running random adventurer test" > randomtestadventurer.out

	echo "randomtestadventurer.c" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b -c -f dominion.c >> randomtestadventurer.out


#random test for village
randomtestcard1.out: randomtestcard1 dominion.c
	echo "Results for running random village test" > randomtestcard1.out


	echo "randomtestcard1.c" >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -b -c -f dominion.c >> randomtestcard1.out

#random test for great hall
randomtestcard2.out: randomtestcard2 dominion.c
	echo "Results for running random great hall test" > randomtestcard2.out

	echo "randomtestcard2.c" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	gcov -b -c -f dominion.c >> randomtestcard2.out
	


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer
