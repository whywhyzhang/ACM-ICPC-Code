#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
	
using namespace std;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	int T,N;

	scanf("%d",&T);

	while(T--)
	{
		scanf("%d",&N);

		if(N%7==0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	
	return 0;
}
