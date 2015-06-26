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

const int MaxN=1010;
const int MaxM=1010;

int next1[MaxM];

void KMP_pre(int m,char s[])
{
	int i=0,j=-1;

	next1[0]=-1;

	while(i<m)
	{
		while(j!=-1 && s[i]!=s[j])
			j=next1[j];

		++i;
		++j;

		next1[i]=j;
	}
}

int KMP(int n,char s1[],int m,char s2[])
{
	int i=0,j=0;
	int ret=0;

	KMP_pre(m,s2);

	while(i<n)
	{
		while(j!=-1 && s1[i]!=s2[j])
			j=next1[j];

		++i;
		++j;

		if(j>=m)
		{
			++ret;
			j=0;
		}
	}

	return ret;
}

char s1[MaxN],s2[MaxM];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	while(~scanf("%s",s1))
	{
		if(s1[0]=='#' && s1[1]==0)
			break;

		scanf("%s",s2);

		printf("%d\n",KMP(strlen(s1),s1,strlen(s2),s2));
	}
	
	return 0;
}
