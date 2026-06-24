/*
 * LeetCode 162: Find Peak Element
 * https://leetcode.com/problems/find-peak-element/
 *
 * CORE PATTERN: "Find the Boundary" Binary Search
 * this is a classic form where we are combining the binary search with graphs not completely just the idea 
 * we are trying to visualize where we where the peak is with the help of mid and trying to move that side accordingly
 * so that is done with the help of comparsion where if the current mid is less than mid+1 which means it is increasing curve and the peak might be towards right
 * so we move towards right by eleminating the left half and if the mid is greater than mid+1 which means we are on a decreasing curve and the peak might be towards left so we move towards left by eliminating the right half.
 * this is a very common pattern in many problems like:
 * - find peak in a mountain array
 * - find valley/peak in bitonic array
 * - local maxima problems
 *
 * GENERIC SHAPE OF "FOLLOW THE SLOPE" BINARY SEARCH:
 * while (left < right) {
 *     if (going uphill at mid, i.e. nums[mid] < nums[mid+1]) {
 *         a peak must exist to the right -> move left bound right.
 *     } else {
 *         going downhill (or at a peak) at mid -> a peak must exist
 *         at mid or to the left -> move right bound to mid.
 *     }
 * }
 *
 * Time Complexity: O(log n)
 * standard binary search halving, but the decision is based on comparing
 * nums[mid] with its right neighbour instead of comparing to a target.
 * Space Complexity: O(1)
 * only a few integer pointers used, no extra space proportional to n.
 */

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1]) {
                // we're on an upward slope, so a peak must lie to the right of mid
                left = mid + 1;
            } else {
                // we're on a downward slope (or mid itself is a peak),
                // so a peak must lie at mid or to its left
                right = mid;
            }
        }
        return left; // left == right, pointing at a peak
    }
};

 /*
 *
 * DRY RUN EXAMPLE:
 * nums = [1,2,1,3,5,6,4], target: find any peak
 * left=0,right=6,mid=3 -> nums[3]=3 < nums[4]=5 -> uphill -> left=4
 * left=4,right=6,mid=5 -> nums[5]=6 > nums[6]=4 -> downhill -> right=5
 * left=4,right=5,mid=4 -> nums[4]=5 < nums[5]=6 -> uphill -> left=5
 * left=5,right=5 -> loop ends -> return 5 (nums[5]=6 is a peak) ✓
 */