/*
 * LeetCode 1283: Find the Smallest Divisor Given a Threshold
 * https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
 *
 * CORE PATTERN: Binary Search on Answer
 *
 * This problem is similar to koko eating bananas like from the basic intution we have been checking the numbers from 1 to max in the vector and 
 * as we can see the pattern of not working and working , and also we see the word smallest these are the pivots for recoginsing the pattern to be binary search
 * here for every divisor we should be checking the corresponding total_sum and moving to left and right accordingly 
 * 
 * Observation:
 * - Smaller divisor -> larger sum (division gives bigger numbers).
 * - Larger divisor -> smaller sum (division gives smaller numbers).
 *
 * This creates a monotonic search space:
 *
 *      Invalid        Valid
 *  ❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
 *              ^
 *      First valid answer
 *
 * Since all invalid divisors appear before all valid divisors,
 * we can binary search to locate the first valid divisor.
 * Our goal is to find the first valid divisor.
 *
 * SEARCH SPACE:
 * low  = 1
 * high = maximum element in nums
 *
 * why?
 * The smallest possible divisor is 1.
 * The largest useful divisor is the largest element in nums.
 *   Any divisor greater than the largest element gives the same result
 *   because every nums[i]/divisor rounds up to 1 anyway.
 * since we are searching for the min divisor we are taking the
 * maximum element as high.
 *
 * CHECKER FUNCTION:
 * For every candidate divisor,
 *      totalSum += ceil(nums[i] / divisor)
 *
 * If totalSum <= threshold,
 *      divisor is valid.
 * and we are trying to search for a better (smaller) divisor by moving
 * towards left since min is asked. if we did not find we will return the previous value only 
 * Otherwise,
 *      divisor is invalid.
 * the sum exceeded the threshold so we should try to increase the
 * divisor so that it shrinks the sum further, hence we move right.
 *
 * BINARY SEARCH TEMPLATE:
 *
 * while(low <= high){
 *      if(divisor works){
 *          high = mid-1;      // keep mid because it may be the answer
 *      }
 *      else{
 *          low = mid + 1;   // discard mid because it is invalid
 *      }
 * }
 *
 * Time Complexity: O(n log(maxElement))
 *      Binary search performs log(maxElement) iterations.
 *      Each iteration scans all elements once for calculating the
 *      total sum for that divisor.
 *
 * Space Complexity: O(1)
 */

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {

        int low = 1;
        int high = *max_element(nums.begin(), nums.end());

        while(low < =high){

            int mid = low + (high - low) / 2;

            int totalSum = 0;

            for(int num : nums){
                totalSum += ceil((double)num / mid);
                // using double is important as we are trying to hold the float value of it and then we are ceiling it
            }

            if(totalSum <= threshold){
                // mid works.
                // Try finding an even smaller valid divisor.
                high = mid-1;
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
 * nums = [1, 2, 5, 9]
 * threshold = 6
 *
 * low = 1
 * high = 9
 *
 * mid = 5
 * totalSum = ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5
 * -> valid
 * high = 5
 *
 * low = 1
 * high = 5
 *
 * mid = 3
 * totalSum = ceil(1/3)+ceil(2/3)+ceil(5/3)+ceil(9/3) = 1+1+2+3 = 7
 * -> invalid
 * low = 4
 *
 * low = 4
 * high = 5
 *
 * mid = 4
 * totalSum = ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7
 * -> invalid
 * low = 5
 *
 * low = high = 5
 *
 * Answer = 5
 */