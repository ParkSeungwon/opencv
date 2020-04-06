#include<iostream>
#include"combi.h"
using namespace std;

int main()
{
	nCr ncr{7, 2};
	while(ncr.next()) {
		for(int i=0; i<ncr.size(); i++) cout << ncr[i] << ' ';
		cout << endl;
	}
}

