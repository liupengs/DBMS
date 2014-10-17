#include"update.h"
#include<fstream>
#include"zhiduan.h"
#include"comparup.h"
char Q[3][10]={">","<","="};
struct up
{
	string name;
	string judge;
	string term;
};

int  analyse_up(string *s,string * condition ,set &se);
int find_up(string s,zhiduan *z,int *ex);
int comp_up(string *st ,up g,int mark,int i,int *ex,int *a);
int  the_main(set se,string *str,string *condtion,zhiduan *z,int *ex);

/************************************入口函数*****************************************/

void updata(string *s)
{
	int ex[4];
	string str[60],condition[60];
	set se;
	zhiduan z[10];
	if(!find_up(s[1],z,ex)) cout<<"ERROR:没有数据……"<<endl;
	get_date(str,ex);
	analyse_up(s,condition,se);
	if(!the_main(se,str,condition,z,ex)) cout<<"ERROR:输入错误……"<<endl;

}
/**************************判断是否有数据*********************************/

int find_up(string s,zhiduan *z,int *ex)
{
    char a;
	string ta_name;
	int lenth;
	int i=0,y=0,j;
	ifstream fp;
	int number;
	int mark=0;

	/*******************************************************************
                               表文件
    ********************************************************************/
	ifstream zd;
	zd.open(ZHIDUAN_PATH,ios::binary);
	if(zd.fail()) cout<<"Error"<<endl;
	zd.seekg(0,ios::beg);
	  while(1)
	  {
		if(zd.fail()) break;
    	zd>>a;
    	zd>>ta_name;
    	zd>>lenth;
		j=0;
		if(ta_name==s)
		{
			mark=1;
			zd.read((char *)(z),sizeof(zhiduan)*lenth);	
			break;
		}
		else
		{
			zd.seekg(sizeof(zhiduan)*lenth,ios::cur);
		}

	  }
    if(mark==0) return 0;
    ex[1]=lenth;
	zd.close();
    /*******************************************************************
                               数据文件
    ********************************************************************/
	fp.open(DATE_PATH,ios::binary);
	i=0;
	mark=0;
	fp.seekg(0,ios::beg);
    while(1)
	{
	    fp>>a;
        fp>>ta_name;
		fp>>lenth;
		fp>>number;
		fp.seekg(1,ios::cur);
	    if(fp.fail()) break;
	    if(ta_name==s)
		{
             mark=1;
		     ex[0]=fp.tellg();
			 ex[1]=lenth;
			 ex[2]=number;
			 fp.seekg(sizeof(char)*10*lenth*number,ios::cur);
			 ex[3]=fp.tellg();


		     break;
		}
	    else 
		{
			fp.seekg(1,ios::cur);
		   	fp.seekg(sizeof(char)*10*lenth*number,ios::cur);
		}
	}
	fp.close();
	if(mark==0) return 0;
    return 1;
}


/*****************************************************************************************************/


int  analyse_up(string *s,string *condition,set &se)
{
     int i=4,r=0,j,mark=0,t,w;
   	 if(s[2]!="SET" && s[2]!="set") return 0;
	 for(i=3;s[i]!="";i++)
	 {
		 if(s[i]=="where" || s[i]=="WHERE" ){mark=1;t=i;break;}
	 }
	 if(mark==0) return 0;
 /**************************解析更改的值*******************************/
     mark=0;
	 w=0;
	 i=3;
	 se.end="";
	 se.first="";
	 while(i<t)
	 {
		if(s[i]==";" ||  s[i]=="") {mark=1;break;}
		for(j=0;s[i][j]!=NULL;j++)
		{
            if(s[i][j]==59){mark=1; break;}
			if(59<s[i][j] && s[i][j]<63) 
			{
				 w++;
				 continue;
			}
			else 
			{
				if(w==1)
				{ 
			    	if(s[i][j]==39) continue;
			    	se.end+=s[i][j];
				}
                else 
				{
					se.first+=s[i][j];
				}
			}
			
		}
		i++;
	}
	 if(mark==1) return 0;
/**********************解析限制条件*********************************/
     t++;
	 r=0;
	 i=t;
     while(s[i]!=";" && s[i]!="")
	 {
		if(s[i]==";") break;
		condition[r]="";
		for(j=0;s[i][j]!=NULL;j++)
		{
            if(s[i][j]==59) break;
			if(59<s[i][j] && s[i][j]<63) 
			{
				if(condition[r][0]>63 || condition[r][0]<59) { r++;condition[r]="";condition[r]+=s[i][j];}
                else condition[r]+=s[i][j];
			}
			else 
			{
				if(59<condition[r][0]  && condition[r][0]<63)
				{ 
					if(s[i][j]==39) continue;
			    	r++; 
			    	condition[r]="";
			    	condition[r]+=s[i][j];
				}
                else 
				{
				   if(s[i][j]!=39)
					condition[r]+=s[i][j];
				}
			}
			
		}
		i++;
		r++;
	}
	 /*for(i=0;condition[i]!="";i++)
		 condition[i]+='\0';
/*******************测试************
	for(i=0;condition[i]!="";i++)  //
		cout<<condition[i]<<" ";   //
	cout<<endl;                    //
/***********************************/
	 if(r==0) return 0;
	return 1;
}

/************************************************************************/
void get_date(string *str ,int *ex)
{

	ifstream fp;
	int i,j,c=0;
	char z[60][10];
	j=c=0;
	fp.open(DATE_PATH,ios::binary);	
    fp.seekg(ex[0],ios::beg);
	while(j<ex[1]*ex[2])
	{
	     	fp.read((char *)(z+c),sizeof(char)*10);
			c++;
			j++;
	}
/**************************测试******************
        int y;
		for(j=0;j<ex[2];j++)        //
		{
			for(y=0;y<ex[0];y++)
			{                                    //
			 cout<<z[x]<<" ";
			 x++;
			}     
			cout<<endl;                          //

		}
		                                         //

/************************************************/
	for(i=0;i<c;i++)
	{
		str[i]="";
		for(j=0;z[i][j]!=NULL;j++)
		{
		    str[i]+=z[i][j];
		}
		str[i]+='\0';
	}
    fp.close();
    
}




void change_date(int *a,string *str,int *ex,set se,int numof)
{
	int lenth=0,i,j,mark=0,m;
	int all,number;
	char c[60][10];
	char e;
	string ta_name;
	all=ex[2]*ex[1];
	for(i=0;i<all;i+=ex[1])
	{
		for(j=0;j<ex[1];j++)
		{
		   if(j==numof && a[i]==1)
		   {
		     change_s_c(se.end,c[i+numof]);
		   }
	       else change_s_c(str[i+j],c[i+j]);
		}
	}
	
   /*******************测试************************
	for(int j=0;j<i;j++) cout<<str[j]<<endl;          //
	/**********************************************/


        ifstream fp;
		ofstream zd;
		char frist[100000];
		char end[100000];
		fp.open(DATE_PATH,ios::binary | ios::beg);
		fp.seekg(0,ios::beg);
    	fp.read((char *)(frist),ex[0]);
		fp.seekg(ex[3],ios::beg);
		for(i=0;i<7;i++)
		{
			if(fp.eof()) break;
			fp.seekg(1,ios::cur);
		}
		if(i==7) mark=1;
		if(mark==1)
		{
		   m=1;
	       fp.seekg(ex[3],ios::beg);
		   fp>>e;
		   fp>>ta_name;
		   if(fp.fail()) m=0;
		   fp>>lenth;
		   fp>>number;
		   fp.seekg(1,ios::cur);
		}
		if(m==1 && mark==1)
		{
           i=0;
	       while(1)
			{
                fp.read((char *)(end+i),sizeof(char));
				i++;
				if(fp.eof()!=0)break;
				
			}
		   i--;
		}
	    fp.close();

		zd.open(DATE1_PATH,ios::binary | ios::app);
	    if(zd.fail()) cout<<"打开失败………"<<endl;
	    zd.write((char *)(frist),ex[0]);
		zd.write((char *)(c),sizeof(char)*10*all);
	    if(mark==1 && m==1)
		{
			zd<<" "<<e<<" ";
			zd<<ta_name<<" ";
			zd<<lenth<<" ";
			zd<<number<<" ";
			zd.write((char *)(end),i*sizeof(char));
		}
		zd.close();
	    if(!remove( DATE_PATH )) cout<<"修改成功……"<<endl;
	    else {  cout<<"修改失败……"<<endl;}
	    rename( DATE1_PATH,DATE_PATH );
}



void change_s_c(string s,char *c)
{
	for(int i=0;s[i]!=NULL;i++)
		c[i]=s[i];
	c[i]='\0';
}

/*******************************************************************************/
int  the_main(set se,string *str,string *condtion,zhiduan *z,int *ex)
{
	up g[4];
	int i,y=0,w=0,mark=0,or_and=0,size=0,ta=0,m=0;
    /******************************************/
	/*             判断输入格式               *//**********************/
	/******************************************/
	for(i=0;condtion[i]!="";i++)
	{
	   if(condtion[1]=="" && compar2(condtion[0],"1")) { or_and=-1;continue;}
	   if(condtion[i]=="and"){ size++;y++;or_and=2;continue;}
	   if(condtion[i]=="or") {size++; y++;or_and=1;continue;}
	   if(condtion[i][0]>59 && condtion[i][0]<63) 
	   {
		  w++;
		  g[y].judge=condtion[i];
		  continue;
	   }
	  ta=0;
	  if(w==0)	 g[y].name=condtion[i];
	  if(w==1)
	  {
		  g[y].term=condtion[i];
		  w=0;
	  }
	}
	if(i!=(size*4+3) && or_and!=-1) return 0;
   

/******************************************************************/
	  /*                      比较                       */
/******************************************************************/
   int a[50],b[5];
   for(i=0;i<50;i++){ a[i]=0;b[i]=0;}
   if(or_and==0)
   {
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar2(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar2(g[0].judge,Q[i])) break;
	   }
	   if(i==3) return 0;
	   or_and=ex[0]*ex[1];
       mark=comp_up(str ,g[0],mark,i,ex,a);
	   if(mark==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }   
	  	   
   }
   /*****************and*******************/
   if(or_and==2)
   {
	   string v[60];
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar2(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar2(g[0].judge,Q[i])) break;
	   }
	   or_and=ex[0]*ex[1];
	   int t=comp_up(str ,g[0],mark,i,ex,a);
	   for(i=0;i<ex[0];i++)
	   {
	      if(compchar2(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar2(g[1].judge,Q[i])) break;
	   }
	   int m=comp_up(v ,g[1],mark,i,ex,b);
	   if(t==0 && m==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }  
	   for(i=0;i<or_and;i++)
	   {
		   if(b[i]==1) a[i]=1;
	   }
   }

   /*********or****************/
   if(or_and==1)
   {


	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar2(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar2(g[0].judge,Q[i])) break;
	   }
       or_and=ex[0]*ex[1];
	   int  c1=comp_up(str ,g[0],mark,i,ex,a);
	  for(i=0;i<ex[1];i++)
	   {
	      if(compchar2(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar2(g[1].judge,Q[i])) break;
	   }
	  int   c2=comp_up(str ,g[1],mark,i,ex,a);
	  if(c1==0  && c2==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }   

   }   
   if(or_and==-1) 
   {
	   for(i=0;str[i]!="";i++) a[i]=1;
   }
   for(i=0;i<ex[0];i++)
   {
	   if(compchar2(se.first,z[i].name)) break;
   }
   if(i==ex[0]) return 0;
   change_date(a,str,ex,se,i);

	return 1;
}
/**************************************************************/
int  comp_up(string *st ,up g,int mark,int i,int *ex ,int *a)
{
	int j,n,x=0,t=0;
	int len=ex[1]*ex[2];
    	if(i==0)
		{
	    	for(j=0;j<len;j+=ex[1])
			{
            
		    	if(compar_a2(st[j+mark],g.term))
				{

				   for(n=0;n<ex[1];n++)
				   {
					   a[j+n]=1;
					   
				   }
				   t=1;
				}

			}
		}
	    if(i==1)
		{
	    	for(j=0;j<len;j+=ex[1])
			{            
		    	if(compar_a2(g.term,st[j+mark]))
				{
			    	for(n=0;n<ex[1];n++)
					{
						a[j+n]=1;
					}
					 t=1;
				}

			}
		
		}
    	if(i==2)
		{
	    	for(j=0;j<len;j+=ex[1])
			{
            
		    	if(compar2(st[j+mark],g.term))
				{

			    	for(n=0;n<ex[1];n++)
					{
						a[j+n]=1;
					}
					 t=1;
				}

			}
		}
		return t;
}

