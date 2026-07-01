/*
 * LeetCode 1539: Kth Missing Positive Number
 * https://leetcode.com/problems/kth-missing-positive-number/
 *
 * CORE PATTERN: Binary Search on Answer (Binary Search on Index)
 *
 * This problem is a bit different from Koko / Ship Capacity / Smallest
 * Divisor — there we searched over a RANGE OF VALUES (capacity, divisor,
 * eating speed). Here we search over the INDICES of the given array.
 * as the requried element is not in the array so we cannot directly take the array itself as our search space.
 * 
 * arr is strictly increasing and only has positive integers, so we can
 * binary search to find the boundary index where the kth missing number
 * "lives," instead of scanning the array linearly.
 *
 * Observation:
 * - If nothing were missing, arr[i] would always equal (i+1).
 * - Whatever GAP exists between arr[i] and (i+1) IS exactly the count
 *   of positive integers missing before arr[i].
 *      missing_before(i) = arr[i] - (i + 1)
 * - This "missing count" only grows or stays the same as i increases
 *   (array is strictly increasing) -> monotonic -> binary search works.
 *
 * This creates a monotonic search space over indices:
 *
 *      missing < k        missing >= k
 *  ❌ ❌ ❌ ❌ ❌        ✅ ✅ ✅ ✅
 *                    ^
 *          boundary we are searching for
 *
 * Our goal is to find the LAST index where missing < k (call it h).
 * Everything past that index has already "crossed" k missing numbers.
 *
 * SEARCH SPACE:
 * low  = 0
 * high = arr.size() - 1
 *
 * CHECKER (inline, no separate function needed):
 * For every candidate index m,
 *      missing = arr[m] - (m + 1)
 *
 * If missing < k,
 *      not enough numbers have gone missing yet by index m,
 *      so the answer lies further right -> low = m + 1
 * Otherwise (missing >= k),
 *      we've already crossed k missing numbers by index m,
 *      so the answer is at or before m -> high = m - 1
 *
 * BINARY SEARCH TEMPLATE (this one uses low <= high, since we're
 * narrowing toward a final POSITION rather than a final VALUE):
 *
 * while(low <= high){
 *      if(missing < k){
 *          low = mid + 1;      // push right, not enough missing yet
 *      }
 *      else{
 *          high = mid - 1;     // pull left, mid already crossed k
 *      }
 * }
 * return k + high + 1;
 *
 * WHY THE FINAL FORMULA WORKS: k + high + 1
 * - When the loop ends, high = last index where missing < k.
 * - That means among the natural numbers 1, 2, 3, ..., the first
 *   (high + 1) of arr's elements are "accounted for" (not missing).
 * - So the boundary point on the number line is (high + 1).
 * - From that boundary, we still need to walk forward exactly k more
 *   missing numbers to reach the kth one overall.
 * - answer = boundary + k = (high + 1) + k = k + high + 1
 *
 * Time Complexity: O(log n)
 *      Binary search over array indices only — no inner loop, unlike
 *      Ship Capacity / Koko which scan the array at every step depending on the checking condition in every question 
 *
 * Space Complexity: O(1)
 * only pointers used, no extra space scales with input
 */

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {

        int low = 0;
        int high = arr.size() - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            int missing = arr[mid] - (mid + 1);

            if (missing < k) {
                // not enough missing yet, push search right
                low = mid + 1;
            } else {
                // already crossed k missing, pull search left
                high = mid - 1;
            }
        }

        return k + high + 1;
    }
};

/*
 * DRY RUN
 *
 * arr = [2, 3, 4, 7, 11], k = 5
 *
 * low = 0, high = 4
 *
 * mid = 2 -> arr[2] = 4, missing = 4 - 3 = 1 -> 1 < 5 -> low = 3
 * low = 3, high = 4
 * mid = 3 -> arr[3] = 7, missing = 7 - 4 = 3 -> 3 < 5 -> low = 4
 * low = 4, high = 4
 * mid = 4 -> arr[4] = 11, missing = 11 - 5 = 6 -> 6 >= 5 -> high = 3
 * low = 4, high = 3 -> loop ends (low > high)
 *
 * Answer = k + high + 1 = 5 + 3 + 1 = 9
 * Manual check: missing numbers are 1,5,6,8,9,10,...
 * 5th missing number = 9 ✅
 */

/*
 * NOTES — how this differs from Ship Capacity / Smallest Divisor:
 * 1. Here we binary search over INDICES of arr, not over a range of
 *    candidate VALUES (capacity/divisor). The "value" we eventually
 *    return is computed using a formula AFTER the loop ends, not
 *    returned directly as low/high.
 * 2. Template uses while(low <= high) with high = mid - 1 / low = mid + 1,
 *    not while(low < high) with high = mid. That's because we are
 *    not converging on a valid index itself — we're converging on a
 *    boundary, then using high (which ends up one step OUTSIDE the
 *    loop's valid range) to compute the final answer.
 * 3. No inner loop / no checker function — the "cost" of checking a
 *    candidate is O(1) here (just one subtraction), unlike Ship
 *    Capacity where checking a candidate costs O(n).
 * 4. Edge case worth tracing by hand: when k is small enough that the
 *    answer lies BEFORE arr[0] even starts contributing missing
 *    numbers. Try arr = [5,6,7,8], k = 3 — high will end at -1, and
 *    the formula k + high + 1 = 3 + (-1) + 1 = 3 still holds, since
 *    1, 2, 3 are the first three missing positives.
 */