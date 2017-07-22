#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	//randomize character returned from predefined array by randomizing the index
	//possible inputs: [ ( {  a x } ) ]
	char inputs[13] = {'[','(','{',' ','a','x','}',')',']', 'l', 'r','4','/'};

	int randNum = rand() % 13;

	return inputs[randNum];

    //return ' ';
}

char *inputString()
{
    // TODO: rewrite this function
	// vary the input length and the input characters. the full list of characters is defined in terms of the ascii chart and can be randomly generated
	// *s has 6 indexes that are tested
	// possible inputs are: r e s t \0
	// randomize order and length, if \0 is chosen as the character then set the remaining characters to null
	//
	// first random number to determine length, second random number to determine the character that goes into the random index
	
	int i, randNum2;
	int randNum1 = rand() % 7;
	char inputString[randNum1];
	char inputs[9] = {'r','e','s','t','\0', 'u', 'p', '-', '?'};

	for(i = 0; i <= randNum1; i++)
	{
		randNum2 = rand() % 6;
		inputString[i] = inputs[randNum2];
	}
	 



    return inputString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error \n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
