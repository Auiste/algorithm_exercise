//尺取法，滑动窗口法，双指针法，一般用于求解一定限制的区间个数或最短区间

/*eg. Leetcode LCR.008 长度最小的子数组
 * */
#include<iostream>
#include <climits>
#include <vector>
using namespace std;
int minSubArrayLen(int target, vector<int> &nums){
    int res = INT_MAX;
    int n = nums.size();    //数组长度0 ~ n - 1
    int l = 0, r = 0;
    int sum = 0;
    while(r < n){
        sum += nums[r];
        while(l <= r && sum - nums[l] >= target){
            sum -= nums[l];
            l++;
        }
        if(sum >= target){
            res = min(res, r - l + 1);
        }
        r++;
    }
    if(res == INT_MAX){
        res = 0;
    }
    return res;
}



