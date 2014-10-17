#include"create.h"
#include"zhiduan.h"
int  analysis_ta(string *s,zhiduan *z);
void create_db(string *s)
{
	cout<<"ERROR：此功能暂未开放……"<<endl;
}
void create_ta(string *s)
{
	int t,size=0;
	if(s[1]!="table") 
	{
		cout<<"ERROR:输入错误……"<<endl;
	}
	else if( find_cr(s[2]))
	{
		cout<<"表已经存在！"<<endl;
	}
  else
  {
	    zhiduan z[10];
    	t=analysis_ta(s,z);
/****************测试*****************************
	for(int i=0;i<t;i++)
	
	{
		cout<<z[i].name<<endl;
		cout<<z[i].size<<endl;
		cout<<z[i].type<<endl;
	}
***************************************************/
	ofstream zd;
	zd.open(ZHIDUAN_PATH,ios::binary|ios::app);
	if(zd.fail()) cout<<"打开失败………"<<endl;
	zd<<" "<<"~"<<" ";
	zd<<s[2]<<" ";
	zd<<t;
    zd.write((char *)(z),sizeof(zhiduan)*t);
	zd.close();
	cout<<"建表成功……"<<endl;
  }
}
int  analysis_ta(string *s,zhiduan *z)
{
	
	int i=4,j=0,n,h,mark=0;
	if(s[3]!="(" ) return 0;
   while(s[i]!=");" && s[i]!="")
   {
	   z[j].size=0;
	   n=0;
       for(int c=0;c<=s[i].size();c++)
	   {
		   if(s[i][c]==59) {mark=1;break;}
	      z[j].name[c]=s[i][c];

	   }
	   if(mark==1) break;
	   i++;
	   while(1)
	   {
		   if(s[i][n]==59) {mark=1;break;}
		   if(s[i][n]=='(' || s[i][n]==NULL) break;
		   z[j].type[n]=s[i][n];
		   n++;


	   }
	   
	   z[j].type[n]='\0';
	   if(mark==1) break;
	   if(s[i][n]!=NULL && s[i][n]!=59)
	   {
		        for(h=n+1;s[i][h]!=')';h++)
				{
					if(s[i][h]==59) {mark=1;break;}
		             z[j].size=z[j].size*10+s[i][h]-48;
				}
	   }
	   else z[j].size=1;

	   if(mark==1) break;
	   j++;
	   i++;

   }
   return j;
}
int look_ta()
{
    int count=0;
	string ta_name;    
	int lenth;
	char a;
    
	ifstream fp;
	fp.open(ZHIDUAN_PATH,ios::binary);
	if(fp.fail()) {cout<<"Error"<<endl; return 0;}
	cout<<"---------------------------表--------------------------"<<endl;
	while(1)
	{
		int u=fp.tellg();
    	fp>>a;
    	fp>>ta_name;
    	fp>>lenth;
		u=fp.tellg();
		fp.seekg(sizeof(zhiduan)*lenth,ios::cur);
		u=fp.tellg();
		if(fp.fail()) break;
    	/****************************测试*******************************
			cout<<a<<" "<<ta_name<<" "<<lenth<<endl;
    	for(int i=0;i<2;i++)
	   	cout<<d[i].name<<" "<<d[i].size<<" "<<d[i].type<<endl;
	   *******************************************************************/
	     count++;
		 cout.setf(ios::left);
			cout<<"             表"<<count<<"           |        "<<ta_name<<endl;;		
	}
	cout<<"-------------------------------------------------------"<<endl;
	fp.close();
	return 0;
}
bool find_cr(string s)
{
    int count=1;
	string ta_name;    
	int lenth;
	char a;
	ifstream fp;
	fp.open(ZHIDUAN_PATH,ios::binary);
	while(1)
	{   
    	fp>>a;
    	fp>>ta_name;
    	fp>>lenth;
		if(fp.fail()) break;
    	int n=0;
		if(ta_name==s)
		{
			   fp.close();
			   return 1;
	
		}
		else 
		{
			 fp.seekg(sizeof(zhiduan)*lenth,ios::cur);

		}
	}
	fp.close();
	return 0;
}