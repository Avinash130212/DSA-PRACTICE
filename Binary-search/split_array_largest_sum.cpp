/*
    Problem:  LEETCODE 410 - Split array largest sum
    Link: https://leetcode.com/problems/split-array-largest-sum/
      

    CORE PATTERN:
   -firstly we shouldnt be driven by the question wording that we shoudl split the given array in k parts and at each split we calculate 
   maximum and out of all maximum we should return the least as generating all the subarray is a slow porcess and hence not feasible one.
   instead of this we should think in other way and convert this question in the form of "Can we given X which is the subarray sum is it possible to split thta into k parts"
   this makes the question in the category of binary search on answers where we should be deciding the search space based on the constraints and we just keep
   a checker function we will be just moving the mid which is sum according to the return value of the checker function
   the idea behind converting the given question into this wording is based on the phrases used in the question min(max) and the required element is a number only so we can define a search 
   space for that and also after applying few test cases it comes like not wori=king and working category

    SEARCH SPACE REASONING:
    - here since the search space is all the subarrays sum so the least case will be the max element in the array as if we take an elemnet 
    lesser than that as the low then we cant even include few elements as subarrays which is blocking our formation and high 
    should be taken as the sum as the worst case that can happen is k =1 so it conatins only one subarrays so the 
    he is forced to take all the elements from the arrays which becoms the  high = sum(array)
    
    CHECKER FUNCTION :
    it calculates the number of subarrays it can form with the given maximum subarray sum it can handle
    by keeping a prefix sum and count_subarrays once the sum crosses the limit of maximum sum we increase the subarray count and make the 
    prefix sum as the present element itself

   DRY RUN:
    nums = [7, 2, 5, 10, 8], k = 2

    l=10, h=32
    mid=21 -> cnt_subarray=2 -> 2<=2 -> h=20
    l=10, h=20
    mid=15 -> cnt_subarray=3 -> 3>2 -> l=16
    l=16, h=20
    mid=18 -> cnt_subarray=2 -> 2<=2 -> h=17
    l=16, h=17
    mid=16 -> cnt_subarray=3 -> 3>2 -> l=17
    l=17, h=17
    mid=17 -> cnt_subarray=3 -> 3>2 -> l=18
    l=18, h=17 -> loop ends (l > h)

    return low = 18

    TIME COMPLEXITY: O(n * log(sum(nums) - max(nums)))
    at each iteration we will be traversing through entire loop and will be calculating the 
    number of subarrays  that will be formed with present maximum sum for a subarray .
    SPACE COMPLEXITY: O(1)
*/

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int maxi = INT_MIN;
        int total = 0;
        for(int i =0;i<n;i++){
            if(nums[i]>maxi){
                maxi = nums[i];
            }
            total+=nums[i];
        }
        int low = maxi ;
        int high = total;
        while(low<=high){
            int mid = low + (high-low)/2;
            int prefx_sum =0;
            int subb_count = 1;
            for(int i =0;i<n;i++){
                if(prefx_sum+nums[i]<=mid){
                    prefx_sum+=nums[i];
                }
                else{
                    subb_count+=1;
                    prefx_sum = nums[i];
                }
            }
            if(subb_count<=k){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return low;
        
    }
};