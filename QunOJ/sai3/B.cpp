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

// 高精度。
// 输入：scan，=。
// 输出：print，getNum。
// 运算：+，＊，-，/，取负号，%，> 。
// 注意：负数的话是num的每一位都是负的，不过输出时只输出一个负号。

class BigNum
{
	private:

	const static int MaxL=1000;
	const static int Mod=10000;				// 数组每个元素保存 0-(Mod-1) 的值。
	const static int Dlen=4;

	int num[MaxL/Dlen+1],len;				// num的0处是最低位。

	void changeStoNum(const char *);

	public:

	BigNum() { len=1; memset(num,0,sizeof(num)); }
	BigNum(int);
	BigNum(const char *x) { changeStoNum(x); }
	
	BigNum operator + (const BigNum &) const;
	BigNum operator - (const BigNum &) const;
	BigNum operator * (const BigNum &) const;
	BigNum operator / (const int) const;
	BigNum operator - () const;
	bool operator > (const BigNum &a) const;
	int operator % (const int m) const;
	BigNum & operator = (const BigNum &);

	void scan();
	void print();
	void getNum(char *);
};

BigNum::BigNum(int x)
{
	memset(num,0,sizeof(num));
	len=0;

	do
	{
		num[len++]=x%Mod;
		x/=Mod;
	}while(x);
}

void BigNum::changeStoNum(const char *x)		// x的0处是最高位。
{
	int L=strlen(x),p=0;
	int temp,tp;
	int flag=1;

	if(x[0]=='-')
	{
		flag=-1;
		++x;
		L--;
	}

	memset(num,0,sizeof(num));
	len=L/Dlen;
	if(L%Dlen)	++len;

	for(int i=L-1;i>=0;i-=Dlen)
	{
		temp=0;
		tp=i-Dlen+1;
		if(tp<0) tp=0;

		for(int j=tp;j<=i;++j)
			temp=temp*10+x[j]-'0';
		num[p++]=flag*temp;
	}
}

void BigNum::scan()
{
	char x[MaxL];

	scanf("%s",x);
	changeStoNum(x);
}

void BigNum::print()
{
	printf("%d",num[len-1]);

	for(int i=len-2;i>=0;--i)
		printf("%04d",abs(num[i]));
}

void BigNum::getNum(char *s)
{
	int l=0;
	
	sprintf(s,"%d",num[len-1]);
	l=strlen(s);
	
	for(int i=len-2;i>=0;--i)
	{
		sprintf(s+l,"%04d",num[i]);
		l+=4;
	}
	s[l]=0;
}

BigNum & BigNum::operator = (const BigNum &a)
{
	memset(num,0,sizeof(num));

	len=a.len;
	for(int i=0;i<len;++i)
		num[i]=a.num[i];

	return *this;
}

BigNum BigNum::operator + (const BigNum &a) const
{
	BigNum ret;
	
	ret.len=max(len,a.len);

	for(int i=0;i<ret.len;++i)
	{
		ret.num[i]+=((i<len ? num[i] : 0)+(i<a.len ? a.num[i] : 0));
		ret.num[i+1]+=ret.num[i]/Mod;
		ret.num[i]%=Mod;
	}
	if(ret.num[ret.len]>0)	++ret.len;

	return ret;
}

BigNum BigNum::operator * (const BigNum &a) const
{
	BigNum ret;

	ret.len=len+a.len;

	for(int i=0;i<len;++i)
		for(int j=0;j<a.len;++j)
		{
			ret.num[i+j]+=num[i]*a.num[j];
			ret.num[i+j+1]+=ret.num[i+j]/Mod;
			ret.num[i+j]%=Mod;
		}

	while(ret.num[ret.len-1]==0 && ret.len>1)	--ret.len;

	return ret;
}

BigNum BigNum::operator - (const BigNum &a) const
{
	return *this+(-a);
}

BigNum BigNum::operator - () const
{
	BigNum ret;

	ret.len=len;

	for(int i=0;i<len;++i)
		ret.num[i]=-num[i];

	return ret;
}

BigNum BigNum::operator / (const int a) const
{
	BigNum ret;
	int down=0;

	ret.len=len;

	for(int i=len-1;i>=0;--i)
	{
		ret.num[i]=(num[i]+down*Mod)/a;
		down=num[i]+down*Mod-ret.num[i]*a;
	}
	while(ret.num[ret.len-1]==0 && ret.len>1)	--ret.len;

	return ret;
}

int BigNum::operator % (const int a) const
{
	int ret=0;

	for(int i=len-1;i>=0;--i)
		ret=((ret*Mod)%a+num[i])%a;

	return ret;
}

bool BigNum::operator > (const BigNum &a) const
{
	if(len!=a.len)
		return len>a.len;

	for(int i=len-1;i>=0;--i)
		if(num[i]!=a.num[i])
			return num[i]>a.num[i];

	return 0;
}

BigNum tans,ans,temp;
BigNum dp[50][10];
char s[100];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	char tc;
	
	int T,N;

	while(~scanf("%d %d",&T,&N))
	{
		temp=0;
		scanf("%s",s);
		int len=strlen(s);

		for(int i=0;i<len;++i)
		{
			tc=s[i+1];
			s[i+1]=0;

			temp=BigNum(s);
			dp[i][0]=temp;
			s[i+1]=tc;
		}

		for(int i=1;i<=N;++i)
			for(int j=i;j<len;++j)
			{
				tc=s[j+1];
				s[j+1]=0;
	
				ans=0;

				
				for(int k=j;k>=i-1 && k>=1;--k)
					if(dp[k-1][i-1]*BigNum(&s[k])>ans)
						ans=dp[k-1][i-1]*BigNum(&s[k]);

				dp[j][i]=ans;

				s[j+1]=tc;
			}

		dp[T-1][N].print();
		printf("\n");
	}
	
	return 0;
}
