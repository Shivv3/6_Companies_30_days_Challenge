#include<iostream>
#include<vector>
using namespace std;

/*
APPROACH-1:
Creting a new matrix and storing the avg value corresponding to all cells in the image matrix.
T.C = O(m*n);
S.C = O(m*n);
*/
class Solution1 {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img){

        //Obtaining the size of the image:
        int m = img.size();
        int n = img[0].size();

        //Creating a matrix to store the smooth values:
        vector<vector<int>> smooth_img(m,vector<int>(n,0));

        //Creating the vectors to help us gets values of neighbouring rows and columns
        vector<int> del_row = {-1,-1,-1,+1,+1,+1,0,0};
        vector<int> del_col = {-1,0,+1,-1,0,+1,+1,-1};

        //Traversing over each value:
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n; j++){

                //Creating a variable to calculate the average:
                int avg = 0;

                //Creating a variable to keep the track of cell being considered:
                int cell_count = 0;

                //Updating the sum of current cell in the avg:
                avg += img[i][j];

                //Updating the cell_count:
                cell_count++;

                //Updating the sum of 8 neihgbouring cells in the avg:
                for(int k = 0 ; k < 8 ; k++){

                    //If the cell is valid:
                    if(i+del_row[k] >= 0 && i+del_row[k] < m && j+del_col[k] >= 0 && j+del_col[k] < n){

                        //Updating the sum in the average:
                        avg += img[i+del_row[k]][j+del_col[k]];

                        //Updating the cell_count:
                        cell_count++;
                    }
                }

                //Calculating the avg:
                avg = avg/cell_count;

                //Updating the smooth value into the new matrix:
                smooth_img[i][j] = avg;
            }
        }

        //Returning the smooth image:
        return smooth_img;
    }
};

/*
Approach-2: Constant Space approach:
1. For every cell, assume it stores Y (and not r).
2. Extract r, the original value of img[i][j], from Y using Y%256.
3. Compute smoothened value using neighbors of img[i][j]. For computing a smoothened value, we need the original value of neighbors as well, which will be extracted using the same logic.
4. The smoothened value will be stored in p.
5. Encode the smoothened value in img[i][j] as img[i][j] += (sum/count)*256. where p = (sum/count).
6. Once every Y of the matrix is encoded with smoothened value, from it extract smoothened value p by doing Y/256.
7. 256 is choosen as a value, Because all the cell values in the matrix is in range [0,255].

T.C = O(m*n)
S.C = O(1)
*/

class Solution2 {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img){

        //Obtaining the size of the image:
        int m = img.size();
        int n = img[0].size();

        //Creating the vectors to help us gets values of neighbouring rows and columns
        vector<int> del_row = {-1,-1,-1,+1,+1,+1,0,0};
        vector<int> del_col = {-1,0,+1,-1,0,+1,+1,-1};

        //Traversing over all the cells in the matrix:
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++){

                //Creating a variable to keep the track of average sum:
                int avg = 0;

                //Creating a variable to keep the track of number of cells being considered in avg:
                int cell_count = 1;

                //Updating the average sum with the original value:
                avg += img[i][j]%256;

                //Obtaining the neighbours of the cell:
                for(int k = 0 ; k < 8 ; k++){

                    //If the cell is valid:
                    if(i+del_row[k] >= 0 && i+del_row[k] < m && j+del_col[k] >= 0 && j+del_col[k] < n){

                        //Obtaining the new indexes:
                        int new_x = i+del_row[k];
                        int new_y = j+del_col[k];

                        //Obtaining the original value of the cell:
                        int original_value = img[new_x][new_y]%256;

                        //Updating the original value into the avg sum:
                        avg += original_value;

                        //Increasing the cell_count:
                        cell_count++;
                    }
                }

                //Calculating the average:
                avg = avg/cell_count;

                //Encoding the new value into the cell:
                img[i][j] = img[i][j] + avg*256;        //Adding a the avg as a multiple of 256.
            }
        }

        /*
        If we divide the  img[i][j] with 256, we can obtain the value = avg;
        If we modulus the img[i][j] with 256, we can obtain the value = original value.
        */

        //Traversing over all the cells in the matrix:
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++){

                //Obtaining the smoothed value from the coded value:
                int smoothed_value = img[i][j]/256;

                //Updating the cell to the smoothed value now:
                img[i][j] = smoothed_value;
            }
        }

        //Returning the updated matrix:
        return img;
    }
};

/*
APPROACH-3: Using bit-Manipulation:
1. An integer, in most of the programming languages, is represented using 32 bits. The 255 is 11111111 in binary. All numbers from 0 to 255 require at most 8 bits to represent them.
2. We, to avoid any inconsistency, won't alter the most significant bit, as it is often used to represent the sign of the integer. Hence, the 23 bits are free to use.
3. Now the smoothed value is an average of nine values ranging from 0 to 255. Hence, the average will also lie between 0 to 255. Thus, the smoothed value will also require at most 8 bits to represent it.
4. Initially, the smoothened corresponding value was a separate integer.
5. We can left shift that integer 8 times.
6. Now there is a property of bitwise OR (|) operator. x | 0 = x. doing bitwise OR of both these separate integers.
7. The most significant 16 bits will remain 0 because both integers have 0 in those bits. The least significant 8 bits will store the values of img[i][j]. The remaining 8 bits left to the 'img[i][j]' will store the values of the smoothened corresponding value.
8. The bitwise AND (&) operator has property of x & 0 = 0 and The bitwise AND (&) operator has property of x & 1 = x.
9. We extract the original value of img[i][j] from this mixed integer by setting all except the least significant 8 bits to 0.
10. Thus, the integer with which we can do bitwise AND (&) to extract the original value of img[i][j] is 00000000000000000000000011111111, which is 255 in decimal, and 11111111 in binary.
11. Right shifting the mixed integer 8 times can get us the smoothed value.

T.C = O(n*m)
S.C = O(1);
*/

class Solution3 {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img){

        //Obtaining the size of the image:
        int m = img.size();
        int n = img[0].size();

        //Creating the vectors to help us gets values of neighbouring rows and columns
        vector<int> del_row = {-1,-1,-1,+1,+1,+1,0,0};
        vector<int> del_col = {-1,0,+1,-1,0,+1,+1,-1};

        //Traversing over all the cells in the matrix:
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++){

                //Creating a variable to keep the track of average sum:
                int avg = 0;

                //Creating a variable to keep the track of number of cells being considered in avg:
                int cell_count = 1;

                //Updating the average sum value with the original value:
                avg += img[i][j] & 255;

                //Obtaining the neighbours of the cell:
                for(int k = 0 ; k < 8 ; k++){

                    //If the cell is valid:
                    if(i+del_row[k] >= 0 && i+del_row[k] < m && j+del_col[k] >= 0 && j+del_col[k] < n){

                        //Obtaining the new indexes:
                        int new_x = i+del_row[k];
                        int new_y = j+del_col[k];

                        //Obtaining the original value of the cell:
                        int original_value = img[new_x][new_y] & 255;

                        //Updating the original value into the avg sum:
                        avg += original_value;

                        //Increasing the cell_count:
                        cell_count++;
                    }
                }

                //Calculating the average:
                avg = avg/cell_count;

                //Creating an index to keep the track of bits:
                int b = 0;

                //Left shifting the average by 8 bits:
                avg = avg << 8;
                
                //Encoding the shifted avg value into the cell:
                img[i][j] = img[i][j] | avg;
            }
        }

        //Traversing over all the cells in the matrix:
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++){

                //Right shifting the values in each cell 8 times to get the smoothed value stored in each cell of matrix:
                img[i][j] = img[i][j] >> 8;
            }
        }

        //Returning the updated matrix:
        return img;
    }
};






int main(){

return 0;
}