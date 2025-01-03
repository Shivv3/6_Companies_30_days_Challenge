#include<iostream>
#include<queue>
using namespace std;

/*
PROBLEM STATEMENT:
There are n friends that are playing a game.
The friends are sitting in a circle and are numbered from 1 to n in clockwise order.
More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n,
and moving clockwise from the nth friend brings you to the 1st friend.

The rules of the game are as follows:
1. Start at the 1st friend.
2. Count the next k friends in the clockwise direction including the friend you started at. The counting wraps around the circle and may count some friends more than once.
3. The last friend you counted leaves the circle and loses the game.
4. If there is still more than one friend in the circle, go back to step 2 starting from the friend immediately clockwise of the friend who just lost and repeat.
5. Else, the last friend in the circle wins the game.
Given the number of friends, n, and an integer k, return the winner of the game.
*/

/*
APPROACH-1: Using doubly-ended queue:
T.C = O(n*k);
S.C = O(n);
*/
class Solution1 {
public:
    int findTheWinner(int n, int k){

        //Creating a double-ended queue:
        deque<int> dq;

        //Inserting first 'n' elements:
        for(int i = 1 ; i <= n ; i++){

            //Inserting the element:
            dq.push_back(i);
        }

        //Creating a variable to keep the track of number of shifts:
        int t = 0;

        //Untill the size of the dequeue is 1:
        while(dq.size() > 1){

            //Obtaining the frontmost element of the queue:
            int frnt = dq.front();

            //Popping the frontmost element:
            dq.pop_front();

            //Increasing the value the shift:
            t++;

            //If the value of t is equal to k:
            if(t==k){

                //Re-initilizing the shift to be 0:
                t = 0;

                continue;
            }

            //Pushing the frontmost element at the back again:
            dq.push_back(frnt);
        }

        //Returning the only left element:
        return dq.front();
    }
};

/*
Approach-2: Using recursion
T.C = O(n)
S.C = O(n)
*/
class Solution2 {
public:
    //A recursive function to find the winner:
    int winner(int n, int k){

        //If the number of participants is 1: Then the answer must be index = 0 where the first participant lies:
        if(n==1){

            return 0;
        }

        //Applying the recursive formula:
        return (winner(n-1,k)+k)%n;
    }
    
    int findTheWinner(int n, int k){

        //Increased one to convert the indexing from 0-based to 1-based:
        return winner(n,k)+1;
    }
};

/*
Approach-3: Using Iteration through loop
T.C = O(n)
S.C = O(1)
*/
class Solution3 {
public:
    int findTheWinner(int n, int k){

        //Initialy for i = 1 students: The winner_index = 0:
        int winner_index = 0;

        //Increasing the number of participants = i  and building up the answer index:
        for(int i = 2 ; i <= n ; i++){

            //Updating the winner_index:
            winner_index = (winner_index+k)%i;
        }

        //Returning the winner index in 1-based indexing:
        return winner_index+1;
    }
};
int main(){

return 0;
}