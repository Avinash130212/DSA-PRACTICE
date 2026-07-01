/*
 * LeetCode 875: Koko Eating Bananas
 * https://leetcode.com/problems/koko-eating-bananas/
 *
 *  SEARCH SPACE:
 * speed of eating banans in a hour so at least case we can think of is eating 1 banans and best case is given pile of banans in a hour which is possible when k is considered as max(arr) this takes at 1 hour for every pile which is minimum in our best case
 * so now we have defined our search space and secondly we are not actaully finding for a target as of in a classic binary search comparing arr[mid] and moving accordingly here we are 
 * computing time taken for each in the bound and moving it accordingly while eleminating one half as if we take a k that is taking more time than required so the values of k behing=d it are all eliminated as the values lesser than that will take evenn more time and no use as there is a monotonic trend

 *  CORE PATTERN:
 * the question koko eating banans comes in the category of binary search on answers as firstly the search space is not the only array as of for classic binary search where we keep
 * low = 0 and high = n-1 where n is the size of the array here search space might be chaning all the time depending on the fundamental constarinst
 * since here when we keep each value of k it is in the form not working working and so no it is a sign of binary search space where the low is intailly in the not working place and high 
 * is in working region after applying binary search in the end whta we observe is that they change their polairty which is low points to teh minimum working position which is our answer and high goes to not working so that is why we are retuning low here


 *  CHECKER FUNCTION:
 *  so this computes the number of hours taken by each k value and if it is in the bound in the sense it takes time less than or equal to actual required hours so we try to move left to search for a better answers
 *  storing the present and if the computed time is more than actual required time we move towards right by increasing low, since we need a bigger k
 * 
 * BINARY SEARCH TEMPLATE:
 *
 * while(low < high){
 *      if(K works){
 *          high = mid;      // keep mid because it may be the answer
 *      }
 *      else{
 *          low = mid + 1;   // discard mid because it is invalid
 *      }
 * }
 *
 * Time Complexity: O(n log(maxPile))
 *      Binary search performs log(maxPile) iterations.
 *      Each iteration scans all piles once for calculating the total number of hours for that k
 *
 * Space Complexity: O(1)
 */

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {

        int low = 1;
        int high = *max_element(piles.begin(), piles.end());

        while(low < high){

            int mid = low + (high - low) / 2;

            int totalHours = 0;

            for(int bananas : piles){
                totalHours += ceil((double)bananas / mid);
                // using double is important as we are trying to hold the float value of it and then we are ceiling it 
            }

            if(totalHours <= h){
                // mid works.
                // Try finding an even smaller valid K.
                high = mid;
            }
            else{
                // mid doesn't work.
                // Every value <= mid is also invalid.
                low = mid + 1;
            }
        }

        return low;
    }
};

/*
 * DRY RUN
 *
 * piles = [3,6,7,11]
 * h = 8
 *
 * low = 1
 * high = 11
 *
 * mid = 6
 * totalHours = 6
 * -> valid
 * high = 6
 *
 * low = 1
 * high = 6
 *
 * mid = 3
 * totalHours = 10
 * -> invalid
 * low = 4
 *
 * low = 4
 * high = 6
 *
 * mid = 5
 * totalHours = 8
 * -> valid
 * high = 5
 *
 * low = 4
 * high = 5
 *
 * mid = 4
 * totalHours = 8
 * -> valid
 * high = 4
 *
 * low = high = 4
 *
 * Answer = 4
 */