class Solution {
public:
	vector<int> multiply(const vector<int>& A) {
		vector<int> B(A.size(), 1);
		int tmp = 1;
		for (int i = 1; i<A.size(); ++i)
		{
			tmp *= A[i - 1];
			B[i] *= tmp;
		}

		tmp = 1;
		for (int i = A.size() - 2; i >= 0; --i)
		{
			tmp *= A[i + 1];
			B[i] *= tmp;
		}
		return B;
	}
};