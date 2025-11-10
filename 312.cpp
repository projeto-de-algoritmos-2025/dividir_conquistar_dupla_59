#include <bits/stdc++.h>
using namespace std;

static vector<int> parseLineToInts(const string &line) {
    vector<int> out;
    string s = line;
    // remove colchetes e espaços
    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c){
        return c=='[' || c==']';
    }), s.end());

    // Troca vírgulas por espaços
    for (char &c : s) if (c == ',') c = ' ';

    // Tokeniza por espaço
    stringstream ss(s);
    int x;
    while (ss >> x) out.push_back(x);
    return out;
}

int maxCoins(vector<int>& nums) {
    int n = (int)nums.size();

    // arr com sentinelas
    vector<int> arr(n + 2, 1);
    for (int i = 0; i < n; i++) arr[i + 1] = nums[i];
    n += 2; // agora n é o tamanho de arr

    // dp[l][r] = melhor resultado no intervalo aberto (l, r)
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // len = distância entre left e right
    for (int len = 2; len < n; len++) {
        for (int left = 0; left + len < n; left++) {
            int right = left + len;
            // escolher k como último balão estourado no intervalo (left, right)
            int best = 0;
            for (int k = left + 1; k < right; k++) {
                best = max(best, dp[left][k] + dp[k][right] + arr[left] * arr[k] * arr[right]);
            }
            dp[left][right] = best;
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Entrada flexível:
    // Caso A:
    //   linha1: n
    //   linha2: n números
    // Caso B:
    //   linha única: vetor como "[3,1,5,8]" ou "3,1,5,8"
    string line1;
    if (!getline(cin, line1)) {
        cerr << "Entrada vazia.\n";
        return 1;
    }

    vector<int> nums;
    // Tenta detectar se line1 é apenas um inteiro n
    {
        stringstream ss(line1);
        long long n;
        if ((ss >> n) && ss.eof()) {
            // Parece um n
            string line2;
            if (!getline(cin, line2)) {
                cerr << "Esperava a linha com os " << n << " numeros.\n";
                return 1;
            }
            nums = parseLineToInts(line2);
            if ((long long)nums.size() != n) {
                cerr << "Fornecidos " << nums.size() << " numeros, mas n = " << n << ".\n";
                return 1;
            }
        } else {
            // Trata line1 como o vetor todo
            nums = parseLineToInts(line1);
        }
    }

    int ans = maxCoins(nums);
    cout << ans << "\n";
    return 0;
}
