#include<iostream>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int l, r;
		cin >> l >> r;
		cout << r / 2 - (l - 1) / 2 << endl;	
	}
	
}
