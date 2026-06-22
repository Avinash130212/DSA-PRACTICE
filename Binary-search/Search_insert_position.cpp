/*
 * LeetCode 35: Search Insert Position
 * https://leetcode.com/problems/search-insert-position/
 *
 * CORE PATTERN: "Lower Bound" Binary Search
 * This is a TEMPLATE for a huge class of binary search problems folloing the pattern of eliminating the corresponding half of the search space based on a condition.   
 * - first/last occurance of a element
 * - frequency of the element in an array
 * - floor/ceiling value of a number in a sorted array
 *
 * GENERIC SHAPE OF LOWER BOUND BINARY SEARCH:
 * while (left <= right) {
 *     if (condition true at mid) {
 *         save the current candidate value
 *         shrink by moving towards left and searching for a better candidate.
 *     } else {
 *         shrink search to the righter half .
 *     }
 * }
 *
 * Time Complexity: O(log n)
 * similar to classic binary search but the difference is in the updating our mid according to the condition.
 * Space Complexity: O(1)
 * we have used only constant space that will not be changed based on the input size of the array.
 */

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int ans = n;  // default: target is larger than everything -> as the array is sorted and we have traversed it completely since we found that it is larger than maximum element in the array so it must be inserted after the maximum which is size of the array itself.
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                ans = mid;       // mid is a possible answer
                right = mid - 1; // but look further left for a smaller valid index there might be a chance of lower value satsifying the condition so we are shrinking towards left by moving right bound towards left.
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

/*
 * COMMON MISTAKES:
 * 1. Using `left < right` instead of `left <= right` — misses the case
 *    where left == right, which can give a wrong final answer.
 *   we are ending the loop without completely checking.
 * 2. Forgetting to default `ans = n` — if target is bigger than all
 *    elements, the correct insert position is at the very end.
 *
 * DRY RUN EXAMPLE:
 * nums = [1,3,5,6], target = 2
 * left=0,right=3,mid=1 -> nums[1]=3>=2 -> ans=1, right=0
 * left=0,right=0,mid=0 -> nums[0]=1<2  -> left=1
 * left = 1 , right =0 , left>right.
 * loop ends -> return ans = 1
 */