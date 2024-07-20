class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        long long ans = nums[0];
        long long p1 = 1;
        for(auto v:nums){
            p1 *= v;
            ans = max(ans, p1);
            if (p1 == 0)
                p1 = 1;
        }
        long long p2 = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            p2 *= nums[i];
            ans = max(ans, p2);
            if(p2 == 0)
                p2 = 1;
        }
        return ans;
    }
  
};
