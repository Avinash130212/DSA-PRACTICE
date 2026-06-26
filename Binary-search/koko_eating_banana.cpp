/*
 * LeetCode 875: Koko Eating Bananas
 * https://leetcode.com/problems/koko-eating-bananas/
 *
 * CORE PATTERN: Binary Search on Answer
 *
 * This problem is presented in the form of  story which is eventually been decoded came to the idea of binary search by recoginsing the pattern
 * that search space includes invalid and valid answers .
 * instead of searching for the array index(classic binary search) we have been searching of the minimum value of k for which koko can eat
 * banans and eliminating the search space by calculating the time taken by each value of k and move accordingly 
 * 
 * Observation:
 * - Smaller K -> More hours required.
 * - Larger K -> Fewer hours required.
 *
 * This creates a monotonic search space:
 *
 *      Invalid        Valid
 *  ❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
 *              ^
 *      First valid answer
 *Since all invalid answers appear before all valid answers,
 *we can use binary search to locate the first valid K.
 * Our goal is to find the first valid K.
 *
 * SEARCH SPACE:
 * low  = 1
 * high = maximum pile size
 * why ?
 * 
 *The minimum possible eating speed is 1 banana/hour.

 * The maximum useful eating speed is the size of the largest pile.
 *   Any speed greater than the largest pile gives the same result because
 * Koko can finish every pile in one hour.
 but since we are searching for min k we are taking the maximum pile size as high 
 * CHECKER FUNCTION:
 * For every candidate K,
 *      totalHours += ceil(pile / K)
 *
 * If totalHours <= h,
 *      K is valid.
 * and we are trying to search for a better k by moving towards left and min is asked
 * Otherwise,
 *      K is invalid.
 * we have to eat in the valid time only so we should try to increase k value so that it can cover all the bananas in less time
 *  and hence we move right 
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