#include<iostream>
#include<math.h>
using namespace std;

/*
PROBLEM STATEMENT:
You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2),
where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.
Return true if the circle and rectangle are overlapped otherwise return false.
In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.
*/

/*
APPROACH: 
The approach is based on finding the nearest point on the rectangle to the circle's center.
If the distance between this nearest point and the circle’s center is less than or equal to the circle's radius, the circle and rectangle overlap.


Key Steps:
1. Find the Nearest Point on the Rectangle:
-> The nearest point on a rectangle to a given point (circle center) can be found using a technique called clamping.
-> This method ensures the point on the rectangle's perimeter or within its bounds that is closest to the circle's center is computed efficiently.

-> For any coordinate of the circle's center, the nearest point on the rectangle is the value that lies within the range of the rectangle's corresponding side.
-> If the coordinate is inside the rectangle's bounds, it remains unchanged.
-> If the coordinate is outside the rectangle's bounds, it is clamped to the nearest boundary value.

-> Clamp to Rectangle Bounds:
        If xc < x1 then the nearest x-coordinate is x1 (left edge).
        If xc > x2 then the nearest x-coordinate is x2 (right edge).
        The same logic applies to the y-coordinate for clamping to y1 and y2.abort

2. Calculate Distance:
Use the get_dist function to compute the distance between the circle’s center and the nearest point.

3. Check Overlap:
If the distance is greater than the radius, return false (no overlap).
Otherwise, return true (overlap exists).
*/

/*
T.C = O(1)
S.C = O(1)
*/

class Solution {
public:
    //A function to find the distance between two points:
    double get_dist(pair<int,int> p1, pair<int,int> p2){

        //Obtaining the coordinates:
        int x1 = p1.first;
        int x2 = p2.first;
        int y1 = p1.second;
        int y2 = p2.second;

        // Correct formula to calculate the distance
        double dist = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));

        //Returning the distance:
        return dist;
    }

    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {

        //Obtaining the coordinates of the nearest point on the rectangle to the circle:
        int xn = max(x1,min(xCenter,x2));   //Where x1 -> left_edge and x2 -> right_edge.
        int yn = max(y1,min(yCenter,y2));   //Where y1 -> down_edge and y2 -> up edge.

        //The distance between the centre of circle and the nearest point to the circle on the rectangle:
        int dist = get_dist({xn,yn},{xCenter,yCenter});

        //If the distanct is greater than the radius:
        if(dist > radius){

            //No overlap:
            return false;
        }

        //Overlap:
        return true;
    }
};
int main(){

return 0;
}