#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        double max_prod = INT_MIN;
        double prod = 1;

        for (int i = 0; i < nums.size(); ++i) {
            prod *= nums[i];
            max_prod = max(prod, max_prod);
            if (prod == 0)
                prod = 1;
        }
        prod = 1;
        for (int i = nums.size() - 1; i > -1; --i) {
            prod *= nums[i];
            max_prod = max(prod, max_prod);
            if (prod == 0)
                prod = 1;
        }

        return max_prod;
    }
};

// [-2,3,-4]
// [-2. 3, 0, 4, -4]
// [-2. 3, -4, 4]
// [-2. 3, 4]
// [2, -3, 0]
// 일단 앞에서부터 쭉 곱한거랑
// 현재의 max랑 비교
// 만약에 0이 나오지 않는 이상 계속 곱하다 보면 음수인건 음수대로 없어지고
// 음수*음수가 되면 새로운 max가 됨
