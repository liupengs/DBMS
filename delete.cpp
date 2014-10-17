#include"delete.h"
#include"copar.h"
#include<fstream>
#include"zhiduan.h"
void get_zhiduan(zhiduan *z,string s);
int the_main(string s,string *condtion,int *ex);
char q[3][10]={">","<","="};
struct jug
{
	string name;
	string judge;
	string term;
};
int  comp(string *st ,jug g,int mark,int i,int *ex,string *str,int len);

void delete_sql( string *s)
{
	 int ex[4];
	 string condtion[10];
     if(!analysis_se(s,condtion)) {cout<<"格式错误……"<<endl;}
	 else if(!find_ta(s[2],ex)){ cout<<"此表没有数据……"<<endl;}
	 else
	 {
		if(! the_main(s[2],condtion,ex))  cout<<"输入格式错误……"<<endl;

	 }


}

/************************SQL语句分析********************************/

int   analysis_se(string *s,string *condition)
{
	  int i=4,r=0,j;
	  char a[10]="from";
	  char b[10]="where";
	 

     if(!compar(s[1],a)) return 0;
	 if(!compar(s[3],b)) return 0;
     while(1)
	 {
		if(s[i]==";") break;
		if(s[i]=="") break;
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
	return 1;
}

/*************************************判断数据库中是否有此表数据******************************/


int find_ta(string ch,int *ex)
{


    ifstream fp;
	string ta_name,st[30];
	int lenth,number,u,h=0;
	char a;
	fp.open(DATE_PATH,ios::binary);
	while(1)
	{
		int x=fp.tellg();
	    fp>>a;
    	fp>>ta_name;
    	fp>>lenth;
		if(fp.fail()) break;
		if(ch==ta_name)
		{
			u=fp.tellg();
			fp>>number;
			ex[0]=u;
			ex[1]=lenth;
			ex[2]=number;
			ex[3]=x;
			fp.close();
			return 1;
		}
	  	else 
		{   fp>>number;
		    fp.seekg(1,ios::cur);
			fp.seekg(sizeof(char)*10*lenth*number+1,ios::cur);
			h=fp.tellg();

		}
	}
	fp.close();
	return 0;
}




/**************************获取字段*****************************/

void get_zhiduan(zhiduan *z,string ta_name)
{
	ifstream zd;
	char a;
	string tname;
	int lenth,y;
	zd.open(ZHIDUAN_PATH,ios::binary);
	if(zd.fail()) cout<<"Error"<<endl;
	 while(1)
	  {
		if(zd.fail()) break;
    	zd>>a;
    	zd>>tname;
    	zd>>lenth;
		if(ta_name==tname)
		{
			y=0;
	      	while(y<lenth)
			{
				zd.read((char *)(z+y),sizeof(zhiduan));
				y++;
			}
		}
		else
		{
			zd.seekg(sizeof(zhiduan)*lenth,ios::cur);
		}
	  }
	 zd.close();
}


/*****************************删除***and***判断***********************/

int  the_main(string s,string *condtion,int *ex)
{
	zhiduan z[10];
	jug g[4];
	int i,j,y=0,w=0,mark=0,or_and=0,size=0;
	get_zhiduan(z,s);
    /******************************************/
	/*             判断输入格式               *//**********************/
	/******************************************/
	for(i=0;condtion[i]!="";i++)
	{
		if(condtion[i]=="and"){ size++;y++;or_and=2;continue;}
	    if(condtion[i]=="or") {size++; y++;or_and=1;continue;}
	  if(condtion[i][0]>59 && condtion[i][0]<63) 
	  {
		  w++;
		  g[y].judge=condtion[i];
		  continue;
	  }
	  if(w==0)
	  {
		for(j=0;j<ex[1];j++)
		{
			if(compar(condtion[i],z[j].name)){mark=1;}
			
		}
		g[y].name=condtion[i];
	  }
	  if(mark==0) 
	  {
		  break;
	  }
	  if(w==1)
	  {
		  g[y].term=condtion[i];
		  w=0;
	  }
	}
	if(mark==0) return 0;
	if(i!=(size*4+3)) return 0;


	 /******************************************/
	/*             获取数据                   *//**********************/
	/******************************************/


    ifstream fp;
	char c[60][10];
	int number;
	string st[60];
	string str[60];
	fp.open(DATE_PATH,ios::binary);	
	fp.seekg(ex[0],ios::beg);
	fp>>number;
	fp.seekg(1,ios::cur);
	j=0;
	mark=ex[1]*ex[2];
	while(j<mark)
	{
	     	fp.read((char *)(c+j),sizeof(char)*10);
			j++;
	}
	for(i=0;i<mark;i++)
	{
		st[i]="";
	    for( j=0;c[i][j]!='\0';j++) st[i]+=c[i][j];
			st[i]+='\0';
	}
	fp.close();
/**************************测试******************
	y=0;
		for(j=0;j<ex[2];j++)                    //
		{
			for(i=0;i<ex[1];i++)
			{                                    //
			 cout<<c[y]<<" ";
			 y++;
			}     
			cout<<endl;                          //

		}
		                                         //

/************************************************/


/******************************************************************/
	  /*                      比较                       */
/******************************************************************/
   if(or_and==0)
   {
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar(g[0].judge,q[i])) break;
	   }
	   if(i==6) return 0;
       mark=comp(st ,g[0],mark,i,ex,str,ex[1]*ex[2]);
	   /**************************************************
     	for(j=0;j<mark;j++) cout<<str[j]<<" ";            //
	     cout<<endl;                                      //
	   /**************************************************/
	   if(mark==ex[1]*ex[2])
	   {
		   cout<<"删除无效……"<<endl;
		   return 2;
		   

	   }
	  // if(2.p[0].3) cout<<"22",,endl;
	   
   }
   if(or_and==1)
   {
	   string v[60];
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar(g[0].judge,q[i])) break;
	   }
	   int t=comp(st ,g[0],mark,i,ex,v,ex[1]*ex[2]);
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar(g[1].judge,q[i])) break;
	   }
	   t=comp(v ,g[1],mark,i,ex,str,t);
	   if(t==ex[i]*ex[2])
	   {
		   cout<<"删除无效……"<<endl;
		   return 2;
	   }   
	   /**************测试******************
	   for(i=0;i<t;i++) cout<<str[i]<<" "; //
	   cout<<endl;                         //
	   /***********************************/
   }
   if(or_and==2)
   {


	   string v[60];
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar(g[0].judge,q[i])) break;
	   }
	   int  c1=comp(st ,g[0],mark,i,ex,str,ex[1]*ex[2]);
	/**************************************************
     	for(j=0;j<c1;j++) cout<<str[j]<<" ";          //
	     cout<<endl;                                  //
	/**************************************************/
	   for(i=0;i<ex[1];i++)
	   {
	      if(compchar(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar(g[1].judge,q[i])) break;
	   }
	  int   c2=comp(st ,g[1],mark,i,ex,v,ex[1]*ex[2]);
	/**************************************************
     	for(j=0;j<c2;j++) cout<<v[j]<<" ";            //
	     cout<<endl;                                  //
	/**************************************************/
	  int t,n;
	  size=0;
	  for(i=0;i<c2;i+=ex[1])
	  {
		  mark=0;
		  for(j=0;j<c1;j+=ex[1])
		  {
		     for(t=0;t<ex[1];t++)
			 {
			  if(!compar(str[j+t],v[i+t])) break;
			 }
			 if(t<ex[1]) continue;
			 else { mark=1;break;}
			 
		  }
		  if(mark==0)
		  {
		       for(n=0;n<ex[1];n++)
				 {
					 str[c1+size]=v[j+n];
					 size++;
				 }
				 
		  }
	  }

	/**************************************************
     	for(j=0;str[j]!="";j++) cout<<str[j]<<" ";    //
	     cout<<endl;                                  //
	/**************************************************/

	  if(c1+size==ex[1]*ex[2])
	   {
		   cout<<"删除无效……"<<endl;
		   return 2;
	   }   

   }
   move(ex,str);
   

	return 1;
}


/*****************************string->char********************/
	
void change(string s,char *c)
{
		for(int i=0;s[i]!=NULL;i++)
		c[i]=s[i];
		c[i]='\0';
}


/**************************************************************/
int  comp(string *st ,jug g,int mark,int i,int *ex,string *str,int len)
{
	int j,n,x=0;
	if(i==0)
	{
		for(j=0;j<len;j+=ex[1])
		{
            
			if(compar_a(g.term,st[j+mark]) || compar(st[j+mark],g.term))
			{

				for(n=0;n<ex[1];n++) {str[x]=st[j+n];x++;}
			}

		}
	}
	if(i==1)
	{
		for(j=0;j<len;j+=ex[1])
		{
			int xx=compar_a(st[j+mark],g.term);
            
			if(compar_a(st[j+mark],g.term) || (compar(st[j+mark],g.term)))
			{
				for(n=0;n<ex[1];n++) {str[x]=st[j+n];x++;}
			}

		}
		
	}
	if(i==2)
	{
		for(j=0;j<len;j+=ex[1])
		{
			//compar(st[j+mark],g.term);
            
			if(!compar(st[j+mark],g.term))
			{

				for(n=0;n<ex[1];n++) {str[x]=st[j+n];x++;}
			}

		}
	}
	return x;


}


   /**********************************************//*          */
   /*               文件操作                     *//**************/
   /**********************************************//*          */  

void move(int *ex,string *str)
{
	int lenth=0,i;
	char c[60][10];
	for(i=0;str[i]!="";i++)
	{
		change(str[i],c[i]);
		lenth++;
	}
	
   /*******************测试************************
	for(int j=0;j<i;j++) cout<<str[j]<<endl;          //
	/**********************************************/


        ifstream fp;
		ofstream zd;
		char frist[100000];
		char end[100000],a;
		string ta_name;
		int number,u,length,mun,mark=0,t=0;
		fp.open(DATE_PATH,ios::binary | ios::beg);
		fp.seekg(0,ios::beg);
		if(ex[3]<10) t=1;//删除的是第一个表
		if(lenth==0)
		{

		   fp.read((char *)(frist),ex[3]);
		   fp>>a;
		   fp>>ta_name;
		   fp>>length;
		}
		else 
		{
			 fp.read((char *)(frist),ex[0]);
		}
		fp>>number;
		fp.seekg(1,ios::cur);
        u=fp.tellg();
		fp.seekg((sizeof(char)*10*ex[1]*ex[2]),ios::cur);
        u=fp.tellg();
		i=0;

		fp>>a;
		fp>>ta_name;
		fp>>length;
	    fp>>mun;
		fp.seekg(1,ios::cur);
		if(fp.fail())   mark=1;//表示删除的是最后的表
	    while(1)
			{
                fp.read((char *)(end+i),sizeof(char));
				i++;
				if(fp.eof()!=0)break;
				
			}
	    fp.close();


		zd.open(DATE1_PATH,ios::binary | ios::app);
	    if(zd.fail()) cout<<"打开失败………"<<endl;
		if(lenth>0)//没有完全删除
		{
		     zd.write((char *)(frist),ex[0]);
			 zd<<" "<<(lenth/ex[1])<<" ";
			 zd.write((char *)(c),sizeof(char)*10*lenth);
			 if(mark==0 )
			 {
		        zd<<" "<<a<<" ";
	        	zd<<ta_name<<" ";
	        	zd<<length<<" ";
	        	zd<<mun<<" ";
	        	number=zd.tellp();
			    zd.close();
	            fstream	cd;
				cd.open(DATE1_PATH,ios::in | ios::out  |ios::binary );
                cd.seekg(number,ios::beg);
	            cd.write((char *)(end),(i-1)*sizeof(char));
		        cd.close();
			 }
			 else 
			 {
				 zd.close();
			 }
		}
		else
		{
		    if(t==0) zd.write((char *)(frist),ex[3]-1);
			if(mark==0)
			{
				zd<<" "<<a<<" ";
	        	zd<<ta_name<<" ";
	        	zd<<length<<" ";
	        	zd<<mun<<" ";
	        	number=zd.tellp();
				 zd.close();
			
	            fstream	cd;
	            cd.open(DATE1_PATH,ios::in | ios::out  |ios::binary);
                cd.seekg(number,ios::beg);
	            cd.write((char *)(end),(i-1)*sizeof(char));
		        cd.close();

			}
			else zd.close();
		}

	    if(!remove( DATE_PATH )) cout<<"删除成功……"<<endl;
	    else {  cout<<"删除失败……"<<endl;}
	     rename(DATE1_PATH,DATE_PATH );
}

