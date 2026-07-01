/*
    Problem: Kth Missing Positive Number
    Link: https://leetcode.com/problems/kth-missing-positive-number/

      CORE PATTERN:

    - Since  Array is sorted + strictly increasing -> binary search is a strong signal.
      but we cannot directly apply the classic binary search since the number we are searching for 
      is not in the array itself and also we cannot binary search on answers pattern as well 
      beacuse the question is not asking for finding the min/max answer and the region is not in the form of not working and working form
      instaed of directly searching for the missing number we use binary search by keeping track of missing number at that particualr index
    - At any index i, the number of positive integers missing BEFORE arr[i]
      is: arr[i] - (i + 1)
        -> because if nothing were missing, arr[i] should be  equal to (i+1).
        -> the gap between arr[i] and (i+1) IS the count of missing numbers.

    SEARCH SPACE REASONING:
    - l = 0, h = n-1 over the INDICES of arr.
    - At mid m: missing = arr[m] - (m+1)
        - if missing < k  -> not enough numbers missing yet, the kth missing
                             number lies to the RIGHT of m -> l = m+1
        - if missing >= k -> we've crossed or reached k missing numbers,
                             so the answer is at or before m -> h = m-1
    - Loop ends when l > h. At this point, h is the last index where
      missing < k and it might not be in the bound so we cannot access the element using it
      (i.e., the last "safe" index before crossing k).

    WHY THE FINAL FORMULA WORKS: k + h + 1
    
    - After the loop, h = number of elements in arr that are "before" the
      answer's region (elements contributing fewer than k missing numbers).
    - So among the first (h+1) numbers of the natural number line, only
      h elements of arr are present. The rest are missing.
    - We want the kth missing number overall, so we count k positions past
      that boundary point: answer = h + 1 (boundary) + k (the kth missing)
      Hence: k + h + 1

    DRY RUN:    
    arr = [2, 3, 4, 7, 11], k = 5

    l=0, h=4
    m=2 -> arr[2]=4, missing = 4-3 = 1 -> 1<5 -> l=3
    l=3, h=4
    m=3 -> arr[3]=7, missing = 7-4 = 3 -> 3<5 -> l=4
    l=4, h=4
    m=4 -> arr[4]=11, missing = 11-5 = 6 -> 6>=5 -> h=3
    l=4, h=3 -> loop ends (l > h)

    answer = k + h + 1 = 5 + 3 + 1 = 9
    Check manually: missing numbers are 1,5,6,8,9,10,... 
    5th missing = 9 

    TIME COMPLEXITY:  O(log n)   -> binary search over array indices
    SPACE COMPLEXITY: O(1)       -> only pointers used
*/

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int l = 0;
        int h = arr.size() - 1;

        while (l <= h) {
            int m = (l + h) / 2;
            int missing = arr[m] - (m + 1);

            if (missing < k) {
                l = m + 1;
            } else {
                h = m - 1;
            }
        }

        return k + h + 1;
    }
};