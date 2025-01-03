#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

/*
Problem statement:
Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
In one move, you can increment or decrement an element of the array by 1.
*/

/*
APPROACH-1:
Sorting and finding the mean of the array.
Converting all the elements of the array to the median and finding the corresponding moves.

T.C = O(N*Log(N)) + O(N);
S.C = O(1);
*/

class Solution1 {
public:
    int minMoves2(vector<int>& nums){

        //Obtaining the size of the array:
        int n = nums.size();

        //Sorting the array:
        sort(nums.begin(),nums.end());

        //Creating a variable to keep the track of number of moves:
        int moves = 0;

        //Creating a variable to keep the track of target_number:
        int target_num = INT_MIN;

        //If the number of elements are odd:
        if(n%2 != 0){

            //Obtaining the middle index:
            int i = n/2;

            //Updating the target number:
            target_num = nums[i];
        }

        //If the number of elements are even:
        else{

            //Obtaining two middle index:
            int i1 = n/2;
            int i2 = (n/2)-1;

            //Updating the target number:
            target_num = (nums[i1]+nums[i2])/2;
        }

        //Traversing over the array to find the number of moves:
        for(int i = 0 ; i < n ; i++){

            //Updating the moves:
            moves += abs(nums[i]-target_num);
        }

        //Returning the minimum moves:
        return moves;
    }
};

/*
APPROACH-2: 
Sorting and finding the mean of the array.
Converting all the elements of the array to the median and finding the corresponding moves by considering only half the array.

T.C = O(N*Log(N)) + O(N/2);
S.C = O(1);
*/

class Solution2 {
public:
    int minMoves2(vector<int>& nums){

        //Obtaining the size of the array:
        int n = nums.size();

        //Sorting the array:
        sort(nums.begin(),nums.end());

        //Creating a variable to keep the track of number of moves:
        int moves = 0;

        //Creating a variable to keep the track of target_number:
        int target_num = INT_MIN;

        //If the number of elements are odd:
        if(n%2 != 0){

            //Obtaining the middle index:
            int i = n/2;

            //Updating the target number:
            target_num = nums[i];
        }

        //If the number of elements are even:
        else{

            //Obtaining two middle index:
            int i1 = n/2;
            int i2 = (n/2)-1;

            //Updating the target number:
            target_num = (nums[i1]+nums[i2])/2;
        }

        //Traversing over the array to find the number of moves:
        for(int i = 0 ; i < n/2 ; i++){

            //Updating the moves:
            moves += (abs(nums[i]-target_num)+abs(target_num-nums[n-1-i]));
        }

        //Returning the minimum moves:
        return moves;
    }
};

/*
APPROACH-3: Using the stl function: 'nth_element()':
T.C = O(n) + O(n/2);
S.C = (1);

ABOUT THE FUNCTION: 'nth_element':
The std::nth_element() function in C++ STL is used to partially sort a range of elements,
such that the element at the nth position is the one that would be in that position in a fully sorted sequence.
All elements before the nth position are less than or equal to the element at n,
and all elements after the nth position are greater than or equal to the element at n.
However, the order of elements before and after the nth position is undefined.

SYNTAX: 
nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last);
nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp);
where,
-> first: Iterator to the beginning of the range.
-> nth: Iterator pointing to the nth element in the range.
-> last: Iterator to the end of the range.
-> comp: A comparison function or lambda for custom sorting (optional).

TIME COMPLEXITY:
Average Case: O(n), where n = (last−first), Achieved using a variant of the Quickselect algorithm (based on partitioning).
Worst Case: O(n^2)

SPACE COMPLEXITY:
O(1), as it operates in-place.
*/

class Solution3 {
public:
    int minMoves2(vector<int>& nums){

        //Obtaining the size of the array:
        int n = nums.size();

        //Creating a variable to keep the track of number of moves:
        int moves = 0;

        //Arranging the elements such that [n/2]th element is placed where it should be.
        nth_element(nums.begin(),nums.begin()+(n/2),nums.end());

        //Obtaining the median:
        int median = nums[n/2];

        //Traversing over the array to find the number of moves:
        for(int i = 0 ; i < n/2 ; i++){

            //Updating the moves:
            moves += (abs(nums[i]-median)+abs(median-nums[n-1-i]));
        }

        //Returning the minimum moves:
        return moves;
    }
};




int main(){

return 0;
}