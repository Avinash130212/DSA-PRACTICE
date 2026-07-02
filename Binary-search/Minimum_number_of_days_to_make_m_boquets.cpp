/*
    Problem: Minimum number of days to make m boquets
    Link:  https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
      

    CORE PATTERN:
    -firstly we will be checking the number of boquets that can be formed with a given bloomday and if the 
    bouqets we actually got are less than required which means that we should be increasing the bloomdays and wait for longer time
    and also we should also keep track of k adjacent flowers that can be picked but given that they all have been bloomed
    so the core idea is depending on the number of boquets formed with the given bloomday we will be moving the days 
    left or right accordingly keeping in mind about the adjecent flowers as well

    SEARCH SPACE REASONING:
    - here since it is all about the days so the least case is that we can be choosing the minimum bloom days 
       in the array or we can take 1 as well but coming to highest we can take it as max(bloom days) array as 
       it is the least best case where all the flowers will bloom
       So,
       low = min(bloomdays)
       high = max(bloomdays)
    
    CHECKER FUNCTION :
    the function will be calculating the number of bouqets that can be formed with the present bloomday
    using nested if and else conditonal statements and also keep the track of k adjacents

    DRY RUN:
    bloomDay = [1, 10, 3, 10, 2], m = 3, k = 1

    l=1, h=10
    mid=5 -> bouquets=3 -> 3>=3 -> h=4,ans=5
    l=1, h=4
    mid=2 -> bouquets=2 -> 2<3 -> l=3
    l=3, h=4
    mid=3 -> bouquets=3 -> 3>=3 -> h=2,ans=3
    l=3, h=2 -> loop ends (l > h)

    answer = ans = 3

    TIME COMPLEXITY: O(n * log(max(bloomDay) - min(bloomDay)))
    at each iteration we will be traversing through entire loop and will be calculating the 
    number of bouqets that will be formed with present bloomday and since the search space is from max(bloomdays) to 
    min(bloomdays) .
    SPACE COMPLEXITY: O(1)
*/

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if((long long)m*k>n) return -1;
        int low = 0;
        int maxi = INT_MIN;
        for(int i =0;i<n;i++){
            if(bloomDay[i]>maxi){
                maxi = bloomDay[i];
            }
        }
        int high = maxi;
        int ans =-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            int streak  = 0;
            int boq = 0;
            for(int i =0;i<n;i++){
                if(bloomDay[i]<=mid){
                    streak+=1;
                
                if(streak==k){
                    boq+=1;
                    streak = 0;
                }
                }
                else{
                    streak =0;
                }
            }
            if(boq<m){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return ans;
    }
};