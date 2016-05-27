#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int M=1048576;
const int max_=1<<29;

typedef struct
{
	int min,max;
}node;
node tree[M*2];
int n,k;

int query_max(int s,int t)
{
	int ans=-max_;
	for (s+=M-1,t+=M+1; s^t^1; s>>=1,t>>=1)
	{
		if (~s&1) ans=max(ans,tree[s^1].max);
		if (t&1) ans=max(ans,tree[t^1].max);
	}
	return ans;
}
	
int query_min(int s,int t)
{
	int ans=max_;
	for (s+=M-1,t+=M+1; s^t^1; s>>=1,t>>=1)	
	{
		if (~s&1) ans=min(ans,tree[s^1].min);
		if (t&1) ans=min(ans,tree[t^1].min);
	}
	return ans;
}

void init()
{
    freopen("F:\\Workplace\\POJ\\input.txt", "r", stdin);
	scanf("%d %d",&n,&k);
	for (int i=1; i<=n; ++i)
	{
		scanf("%d",&tree[M+i].max);
		tree[M+i].min=tree[M+i].max;
	}
	for (int i=M-1; i>=1; --i)
	{
		tree[i].min=min(tree[i*2].min,tree[i*2+1].min);
		tree[i].max=max(tree[i*2].max,tree[i*2+1].max);
	}
	for (int i=1; i<=n-k+1; ++i)
		printf("%d ",query_min(i,i+k-1));
	printf("\n");
	for (int i=1; i<=n-k+1; ++i)
		printf("%d ",query_max(i,i+k-1));
	printf("\n");
}
	
int main()
{
	init();
	return 0;
}
			
