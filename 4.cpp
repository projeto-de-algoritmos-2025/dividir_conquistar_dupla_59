#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        if (A.size() > B.size()) return findMedianSortedArrays(B, A);

        int n = A.size();
        int m = B.size();

        int totalLeft = (n + m + 1) / 2;
        int left = 0, right = n;

        while (left <= right) {
            int cutA = (left + right) / 2;
            int cutB = totalLeft - cutA;

            int L1 = (cutA == 0 ? INT_MIN : A[cutA - 1]);
            int R1 = (cutA == n ? INT_MAX : A[cutA]);

            int L2 = (cutB == 0 ? INT_MIN : B[cutB - 1]);
            int R2 = (cutB == m ? INT_MAX : B[cutB]);

            if (L1 <= R2 && L2 <= R1) {
                if ((n + m) % 2 == 0) {
                    return (max(L1, L2) + min(R1, R2)) / 2.0;
                } else {
                    return max(L1, L2);
                }
            }
            else if (L1 > R2) {
                right = cutA - 1;
            }
            else {
                left = cutA + 1;
            }
        }

        return 0.0; 
    }
};

int main() {
    Solution sol;

    // Exemplos para testar
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};

    double ans = sol.findMedianSortedArrays(nums1, nums2);
    cout << "Mediana = " << ans << endl;

    // Outro teste
    vector<int> a = {1, 2};
    vector<int> b = {3, 4};
    cout << "Mediana = " << sol.findMedianSortedArrays(a, b) << endl;

    return 0;
}
