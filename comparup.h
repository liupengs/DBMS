#include<string>
using namespace std;
int compar2(string s,string c)
{
	int i,mark=0;
	for(i=0;s[i]!=NULL;i++)
	{
		if(s[i]!=c[i])
		{
			mark=1;
			break;
		}
	}
	if(mark==1) return 0;
	if(c[i]!=NULL) return 0;
    return 1;
}

int compchar2(string s,char *c)
{
	int i,mark=0;
	for(i=0;s[i]!=NULL;i++)
	{
		if(s[i]!=c[i])
		{
			mark=1;
			break;
		}
	}
	if(mark==1) return 0;
	if(c[i]!='\0') return 0;
    return 1;
}
int compar_a2(string a, string b)
{
	for(int i=0;a[i]!=NULL;i++)
	{
		if(b[i]==NULL) break;
		if(a[i]<b[i])break;
	}
	if(b[i]!=NULL || b[i]!=NULL) return 0;
	return 1;
}
