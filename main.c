#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int sudoku [9][9];            // global variable 2d array to store input.
int flag;
int counter = 0 ;
char c;
char filename [200] = "invalid2.txt" ;       //change filename when needed.

void parseFile ()
{
    // int counter =0 ;        // counter for errors in file
    FILE* p = fopen(filename,"r");
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            char c;
            if (fscanf(p," %c ", &c) != 1)
                printf("error in reading from file ");

            else if (isdigit(c))    // if a number is found. .
            {
                sudoku[i][j] = c-'0';
            }
            else if (!isdigit(c))   // anything that is found rather than a number.
            {
                counter++;
                sudoku[i][j] = c;
            }
        }
    }
    if (counter == 0)    // if the file is correct check the solution.
    {
        printf("the puzzle is valid and has no non-numerical signs\n");
        check_sudoku();
        print_sudoku();  // prints the puzzle.

    }
    else if(counter>0)  // else end the program
    {
        printf("the puzzle is invalid and has %d non-numerical signs\n",counter);  // prints number of irregularities found

    }
    fclose(p);
}
void print_sudoku()
{

    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            printf("%2d", sudoku[i][j]);
        }
        printf("\n");
    }
}
bool check_ROWS()
{
// CHECK ROWS.
    for(int i=0; i<9; i++)
    {
        flag=0x0000;
        for(int j=0; j<9; j++)
        {
            flag|=1<<(sudoku[i][j]-1);
        }
        if(flag!=0x01FF) // not equal to 511 that is the result of last 9 bits being different.
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}
bool check_COLS()
{
// CHECK ROWS.
    for(int j=0; j<9; j++)
    {
        flag=0x0000;
        for(int i=0; i<9; i++)
        {
            flag|=1<<(sudoku[i][j]-1);
        }
        if(flag!=0x01FF) // not equal to 511 that is the result of last 9 bits being different.
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}
bool check_BOX()
{
    for(int si=0; si<3; si++)
    {
        for(int sj=0; sj<3; sj++)
        {
            flag=0x0000;
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    flag|=1<<(sudoku[si*3+i][sj*3+j]-1);
                }

            }
            if(flag!=0x01FF) // not equal to 511 that is the result of last 9 bits being different.
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    }

}
void check_sudoku()
{
    bool r_state = check_ROWS();
    bool c_state = check_COLS();
    bool b_state = check_BOX();
    if(r_state == true && c_state == true && b_state== true )
    {
        printf("THE SOLUTION IS CORRECT \n");
    }
    else
    {
        printf("THE SOLUTION IS NOT CORRECT\n");
    }
}


int main()
{
    parseFile();   // reads the file in 2d array and checks for validity .
    return 0;
}
