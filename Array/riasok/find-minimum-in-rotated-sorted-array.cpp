class Solution {
public:
    int findMin(vector<int>& nums) {
        int curr = nums[0];
        for(auto n : nums){
            if (curr > n){
                return n;
            }
            curr = n;
        }
        return nums[0];
    }
};

int main(){
    return 0;
}