/*
 * LeetCode 540: Single Element in a Sorted Array
 * https://leetcode.com/problems/single-element-in-a-sorted-array/
 *
 * CORE PATTERN: Binary Search on "Pair Boundary" / Index Parity
 *THE IDEA :  it comes  comes from the test cases given in the question.
 *as we can clearly observe that all the pairs before the single element in the array start with odd index and  
 *after the single element the pairs continue by starting from even index
 *this can be used as the approach for finding the single element .
 *the base case in this question which is usually if nums[mid]==target returning the mid is not applicable here asn replaced by
 *checking the condition that if the corresponding value of mid index is similar with the neighbours or not if not then it is the single element we are searching for
 *and also here we have writing  the edge cases seperately as we are compaing our mid the neighbours so it might lead to segementation fault.
 *so here we have trimme down our search space access the elements with out any error.


 * Time Complexity: O(log n)
 * since it is a binary search based approach we are eliminating half of the search space in each iteration.
 * Space Complexity: O(1)
 */

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        // edge cases
        int n = nums.size();
        if (n == 1) return nums[0];
        if (nums[n-1] != nums[n-2]) return nums[n-1];
        if (nums[0] != nums[1]) return nums[0];
        // so we have trimmed our search space initially so that we
        // simplify our code and satisfy edge cases.

        int low = 1;
        int high = n - 2;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] != nums[mid+1] && nums[mid] != nums[mid-1]) {
                return nums[mid];
            }
            else if ((mid % 2 == 1 && nums[mid-1] == nums[mid]) ||
                     (mid % 2 == 0 && nums[mid] == nums[mid+1])) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

/*
 * DRY RUN EXAMPLE:
 * nums = [1,1,2,3,3,4,4,8,8]
 * n = 9, edge checks pass (no early return)
 * low=1, high=7
 *
 * mid=4 -> nums[4]=3, nums[3]=3, nums[5]=4
 *   nums[mid]==nums[mid-1] (3==3), mid%2==0 -> check (mid%2==0 && nums[mid]==nums[mid+1])
 *   nums[4]=3, nums[5]=4 -> not equal -> falls to else -> high=3
 *
 * low=1, high=3, mid=2 -> nums[2]=2, nums[1]=1, nums[3]=3
 *   nums[mid]!=nums[mid+1] && nums[mid]!=nums[mid-1] -> TRUE
 *   return nums[2] = 2
 *
 * Correct answer: 2
 */