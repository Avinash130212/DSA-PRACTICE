/*
 * LeetCode 1011: Capacity To Ship Packages Within D Days
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 *
 * CORE PATTERN: Binary Search on Answer
 *
 * This problem is similar to Koko Eating Bananas and Smallest Divisor:
 * defining our search space is the first step we should be doing in these type of pattern problems
 * here the search space is slightly different from the koko eating bananas as we have a constranint that we should nt we splitiing the packages
 * so here the min cant be low as we cant transfer other packages so we have to keep a safe min that transfers all the weights irrespective of number of days taken 
 * so safer low is max(weights array) and high is sum(weights array) as that is the best case where we can transfer all the weights in a day 
 * obviously it might be more than that but since we are chceking for least best case so high should be sum(weights array)
 * So For every candidate capacity, we check the corresponding days needed
 * and move left or right accordingly.
 *
 * Observation:
 * - Smaller capacity -> more days needed (less fits per day).
 * - Larger capacity  -> fewer days needed (more fits per day).
 *
 * This creates a monotonic search space:
 *
 *      Invalid        Valid
 *  ❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
 *              ^
 *      First valid answer
 *
 * Since all invalid capacities appear before all valid capacities,
 * we can binary search to locate the first valid capacity.
 * Our goal is to find the first valid capacity.
 *
 * SEARCH SPACE:
 * low  = maximum element in weights
 * high = sum of all elements in weights

 * CHECKER FUNCTION:
 * For every candidate capacity,
 *      walk through weights in order, keeping a running_sum.
 *      If running_sum > capacity, that package starts a NEW day —
 *      carry its own weight forward as running_sum (don't drop it).
 *      act_days starts at 1 (day 1 begins the moment the first
 *      package is loaded).
 *
 * If act_days <= days,
 *      capacity is valid, and it may still be the answer (don't discard it).
 *      We try to search for a better (smaller) capacity by moving
 *      high down to mid, since the minimum is asked.
 * Otherwise,
 *      capacity is invalid. Too many days were needed, so we should
 *      increase the capacity to reduce days further -> move low past mid.
 *
 * BINARY SEARCH TEMPLATE (preferred style: while(low < high), high = mid):
 *
 * while(low < high){
 *      if(capacity works){
 *          high = mid;        // keep mid, it may still be the answer
 *      }
 *      else{
 *          low = mid + 1;     // discard mid, it is invalid
 *      }
 * }
 * return low;
 *
 * Time Complexity: O(n log(sum(weights) - max(weights)))
 *      Binary search performs log(high - low) iterations.
 *      Each iteration scans all elements once for calculating the
 *      days needed for that capacity.
 *
 * Space Complexity: O(1)
 * no extra space is been used that is chainging based on our array input
 */

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {

        int low = *max_element(weights.begin(), weights.end());
        int high = accumulate(weights.begin(), weights.end(), 0);

        while (low < high) {

            int mid = low + (high - low) / 2;

            int running_sum = 0;
            int act_days = 1;
            // act_days starts at 1, not 0: day 1 begins the moment
            // the first package is loaded.

            for (int w : weights) {
                running_sum += w;
                if (running_sum > mid) {
                    running_sum = w;
                    // carry THIS package's weight into the new day,
                    // don't reset to 0 or its weight vanishes
                    act_days += 1;
                }
            }

            if (act_days <= days) {
                // mid works.
                // Keep mid in the search space, try finding an even
                // smaller valid capacity.
                high = mid;
            } else {
                // mid doesn't work.
                // Every value <= mid is also invalid, safe to discard mid.
                low = mid + 1;
            }
        }

        return low;
    }
};

/*
 * DRY RUN
 *
 * weights = [1,2,3,4,5,6,7,8,9,10]
 * days = 5
 *
 * low = max = 10, high = sum = 55
 *
 * mid = 32
 * running through weights, capacity 32 easily fits everything in
 * very few days -> act_days small -> valid -> high = 32
 * (binary search keeps narrowing...)
 *
 * Eventually candidate mid = 15:
 * running_sum: 1,3,6,10,15(ok),21(>15! new day=6),13,21(>15! new day=8),
 *              17(>15! new day=9),19(>15! new day=10)
 * act_days = 5 -> valid (5 <= 5) -> high = 15
 *
 * Eventually low = high = 15
 * loop ends -> Answer = 15
 */

/*
 * NOTES — same pattern family as Smallest Divisor (LC 1283):
 * 1. low is NOT the minimum element here (unlike a naive first guess) —
 *    it's max(weights), because a single package can never be split.
 *    Compare to Smallest Divisor, where low = 1 is always valid (just
 *    slow); here, capacity below max(weights) is impossible outright.
 * 2. running_sum must carry the overflowing package's weight forward
 *    (running_sum = w), not reset to 0 — otherwise that package's
 *    weight silently disappears from the simulation.
 * 3. high = mid (not mid - 1) for the same reason as Smallest Divisor:
 *    mid might be the final answer, so it can't be discarded while
 *    still valid. while(low < high) handles convergence without
 *    needing any +-1 on the valid branch.
 */