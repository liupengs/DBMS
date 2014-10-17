#include"insert.h"
#include"zhiduan.h"
int find_ta(string *s,zhiduan *z);
int find_ta_d(string s,string *str);
int judge(zhiduan *z,string *s,int lenth);
int compear(char *z,char *s);
void insert(string *s)
{
	int lenth;
	char ch[30][10];
	int ex,i,j,mark;
	zhiduan z[10];
	string str[30];
	lenth=find_ta(s,z);
	if(lenth==0) cout<<"表不存在！"<<endl;
    else if(!judge(z,s,lenth))
	{
		cout<<"格式错误……"<<endl;
	}
   
	else
	{
	    analysis_in(s,lenth,str);
		//cout<<z[0].size<<endl;
		for(i=0;i<lenth;i++) 
		{
			mark=0;
			if(compear(z[i].type,"char"))
			{
				for(j=0;str[i][j]!=NULL;j++){}
				if(j>z[i].size) {mark=1;break;}
			}
			else 
			{
				for(j=0;str[i][j]!=NULL;j++)
				{
					if(str[i][0]!=45 && (str[i][0]<48 && str[i][0]>57)) {mark=2;break;}
					if(str[i][j]<44 || str[i][j]>57)  {mark=2;break;}
				}
			}
		}
		if(mark!=0) 
		{
			if(mark==1) cout<<"ERROR："<<z[i].name<<"超过长度……"<<endl;
			if(mark==2) cout<<"ERROR："<<z[i].name<<"输入错误……"<<endl;
		}
		else
		{
	     	for(i=0;i<lenth;i++)
			{
			   j=0;
			  while(str[i][j]!=NULL)
			  {
				 ch[i][j]=str[i][j];
				 j++;

			  }
		    	ch[i][j]='\0';
			}
/***********************测试*****************
		for(int f=0;f<lenth;f++)
			cout<<ch[f]<<" ";                //
		cout<<endl;
/*********************************************/

	    	 ex=find_ta_d(s[2],str);
	    	 if(ex!=-2) 
	         savadata(ch[0],lenth,s,ex);
		}
	}
}
/******************找到要插入的表，并判断是否存在*******************/
int find_ta(string *s,zhiduan *z)
{
    int count=1;
	string ta_name;    
	int lenth;
	char a;
    
	ifstream fp;
	fp.open(ZHIDUAN_PATH,ios::binary);
	if(fp.fail()) cout<<"表不存在！"<<endl;
	while(1)
	{   
    	fp>>a;
    	fp>>ta_name;
    	fp>>lenth;
		if(fp.fail()) break;
    	int n=0;
		if(ta_name==s[2])
		{
              while(n<lenth)
			  {
	    	     fp.read((char *)(z+n),sizeof(zhiduan));
    		     n++;
			  }
			    fp.close();  
		    	return lenth;
		}
		
		 fp.seekg(sizeof(zhiduan)*lenth,ios::cur);	
	}
	fp.close();  
	return 0;

}
/*****************解析SQL语句，交插入数据**********************/
void analysis_in (string *s,int lenth,string *str)
{
	int i,j,n,c,mark=0,t,v;
	for(i=0;s[i]!=");";i++)
	{
		for(j=0;s[i][j]!=NULL;j++)
		{
			if(s[i][j]==59) {mark=-1;break;}
			if(s[i][j]==40) mark++;
			if(mark==2) break;
		}
		if(mark==2) break;
		if(mark==-1) break;

	}
	t=j+1;
	if(s[i][t]==NULL)
	{
		i++;
        j=0;
	
        while(s[i]!=");")
		{
	       if(s[i]==",") { i++;continue;}
		   
	        n=0;
			if(s[i][n]==41) break;
		    if(s[i][n]==59) break;
	        if(s[i][n]==39)
			{
		    	str[j]="";
			     for(n=1;s[i][n]!=39;n++)
				 {
				   if(s[i][n]==44 && s[i][n+1]!=NULL)
				   {
					   str[j]+='\0';
					   j++;
					   str[j]="";
				   }
				   str[j]+=s[i][n];
				 }
			      str[j]+='\0';
			}
	       else 
		   {
			  
			  for(n=0;s[i][n]!=NULL;n++) 
			  {
				 if(s[i][n]==41) break;
		    	 if(s[i][n]==59) break;
				  str[j]+=s[i][n];
			  }
			  str[j]+='\0';
		  }
	       j++;
	    	i++;
		}
	}
	else 
	{

       c=v=0;
	   int f=0,x=0;
	   str[c]="";
	   while(s[i]!=");")
	   { 
	    	for(j=0;s[i][j]!=NULL;j++)
			{

                if(v==0) j=t;
		    	if(s[i][j]==41){ mark=0;break;}
	            if(s[i][j]==44)
				{
			     	str[c]+='\0';
			    	c++;
			    	continue;
				}
				if(s[i][j]==39)
				{
					f++;
					j++;
				}
				if(f%2==1 || f==0)
				{
		
		         	str[c]+=s[i][j];
				}
				if(f%2==0 && f!=0)
				{
					f=0;
			    	continue;

				}
				v++;
			 
	 
			}
		    if(mark==0) break;
	    	i++;
			v++;
	   }
	   str[c]+='\0';
	}
 //  for(i=0;i<=c;i++) cout<<str[i]<<endl;
}
/*****************************存储数据********************************/
void savadata(char *str,int lenth,string *s,int ex)
{
  //  for(int i=0;str[i]!="";i++) cout<<str[i]<<" ";
//	cout<<endl;
	if(ex<=0)
	{
	
		int n=1;
		if(ex!=0)//第一次插入，但非第一个数据
		{
		   	 fstream zd;
		   	 zd.open(DATE_PATH,ios::in | ios::out  |ios::binary);
	         if(zd.fail()) cout<<"打开失败………"<<endl;
	    	 zd.seekp(-ex,ios::beg);
	         zd<<" "<<"~"<<" ";
	         zd<<s[2]<<" ";
	         zd<<lenth<<" ";
        	 zd<<n<<" ";
             zd.write((char *)(str),sizeof(char)*lenth*10);
			 cout<<"插入成功……"<<endl;
		}
		else //第一个数据，第一次插入
		{
			ofstream zd;
			zd.open(DATE_PATH,ios::binary | ios::app );
			if(zd.fail()) cout<<"打开失败………"<<endl;
	        zd<<" "<<"~"<<" ";
	        zd<<s[2]<<" ";
	        zd<<lenth<<" ";
        	zd<<n<<" ";
            zd.write((char *)(str),sizeof(char)*lenth*10);
			zd.close();
			cout<<"插入成功……"<<endl;

		}
    	
	/******************测试*******************************************
		ifstream fp;                                                  //
    	int number,lenth,i=0;
    	char a;
	    string ta_name;
    	fp.open(DATE_PATH,ios::binary); //	
    	//fp.seekg(ex,ios::beg);
		char z[10][10];
    	fp>>a;
        fp>>ta_name;                                                   //
    	fp>>lenth;
    	fp>>number;
    	fp.read((char *)(z),sizeof(char)*10*lenth*number);             //
        fp.close();
		for(int j=0;j<number*lenth;j++)                                //
		{
			cout<<z[j]<<" ";
		}
   /********************************************************************/
	}
	else 
	{
		ifstream fp;
		fstream zd;
     	int number,t;
		fp.open(DATE_PATH,ios::binary | ios::beg);
		fp.seekg(ex,ios::beg);
		fp>>number;
		fp.close();


        t=number+1;
		zd.open(DATE_PATH,ios::in | ios::out  |ios::binary);
	    if(zd.fail()) cout<<"打开失败………"<<endl;
        zd.seekp(ex+1,ios::beg);
		zd<<t<<" ";
		zd.seekp((sizeof(char)*10*number*lenth),ios::cur);
		int u=zd.tellg();
		if(zd.eof()==0)
		{
			char change[100000];
			char c[100000];
			ex=zd.tellg();
			zd.close();
			ifstream in;
			ofstream ou;
			in.open(DATE_PATH,ios::binary | ios::beg);
			in.read((char *)(change),ex);
			ou.open(DATE1_PATH,ios::binary | ios::app);
			ou.write((char *)(change),ex);
			ou.write((char *)(str),sizeof(char)*10*lenth);
			int i=0;
			while(1)
			{
                in.read((char *)(c+i),sizeof(char));
				i++;
				if(in.eof()!=0)break;
				
			}
			ou.write((char *)(c),(i-1)*sizeof(char));
			ou.close();
			in.close();

			remove( DATE_PATH);
            rename( DATE1_PATH,DATE_PATH);
			cout<<"插入成功……"<<endl;



            
		}
		else
		{
	    	zd.write((char *)(str),sizeof(char)*10*lenth);
			zd.close();
			cout<<"插入成功……"<<endl;

		}
	
    /******************** 测试**********************************************
    	int lenth,i=0;
    	char a;                                                             //
	    string ta_name;
    	fp.open("E:\\MyProjects\\DBMS\\date\\date.mysql",ios::binary);	    //
    	//fp.seekg(ex,ios::beg);
		char z[10][10];                                                     //
    	fp>>a;
        fp>>ta_name;
    	fp>>lenth;                                                          //
    	fp>>number;
    	fp.read((char *)(z),sizeof(char)*10*lenth*number);                   //
        fp.close();
		for(int j=0;j<number*lenth;j++)                                      //
		{
			cout<<z[j]<<" ";
		}
		                                                                     //
	/*************************************************************************/


	}


}
/*****************************查看数据库中此表是否已经有数据***********************/
int find_ta_d(string s,string*str)
{
	ifstream fp;
	char a,c[30][10];
	string ta_name,st[30];
	int lenth,number,u,j,h=0;
	fp.open("E:\\date.mysql",ios::binary);
	while(1)
	{
        u=fp.tellg();
	    fp>>a;
    	fp>>ta_name;
    	fp>>lenth;
		if(fp.fail()) break;
		if(s==ta_name)
		{
		    int x=fp.tellg();
			fp>>number;
			fp.seekg(1,ios::cur);
 			j=0;
			while(j<lenth*number)
			{
	     	    fp.read((char *)(c+j),sizeof(char)*10);
	 	    	j++;
			}
       /****************判断数据是否已经存在************************************/
			for(int i=0;i<lenth*number;i++)
			{
				st[i]="";
				for( j=0;c[i][j]!='\0';j++) st[i]+=c[i][j];
				st[i]+='\0';
			}
			for(i=0;i<lenth*number;i++)
			{
                
				for(j=0;j<lenth;j++) 
				{
					if(str[j]!=st[i*lenth+j]) break;
				}
				if(j==lenth)
				{
					cout<<"数据已经存在"<<endl;
				    return -2;
				}


			}

       /**************************************************************************/
			fp.close();

			return x;
		}
		else 
		{   fp>>number;
	    	fp.seekg(1,ios::cur);
			fp.seekg(sizeof(char)*10*lenth*number,ios::cur);
			h=fp.tellg();

		}
	}
	fp.close();
	return -h;
}


/*****************************判断插入的格式*******************************************/


int  judge(zhiduan *z,string *s,int lenth)
{
	int i=2,mark=1,c=0,j,x=0,w,v;
	char str[10][10];
	if(s[1]!="into" && s[i]!="INTO") return 0;
	while(s[i]!=")")
	{
		w=0;
		for(j=0;s[i][j]!=NULL;j++)
		{
			if(s[i][j]==41)
			{
				str[c][x]='\0';mark=0;break;
			}
			if(s[i][j]==40) 
			{
				str[c][x]='\0';c++;  x=0;continue;
			} 
	        if(s[i][j]==',')
			{
				str[c][x]='\0';
				c++;
				x=0;
				continue;
			}
			str[c][x]=s[i][j];
			x++;
			 
	
		}
		if(mark==0) break;
		i++;
	}
	if(mark!=0) str[c][x]=s[i][j];


	/*****************测试******************************
	for(i=0;i<lenth;i++)                               //
		cout<<z[i].name<<endl;                         //
	for(i=0;i<=c;i++) 
		cout<<str[i]<<endl;                            //
	/***************************************************/

    if(c>lenth) return 0;
	if(c<lenth) return 0;
	v=1;
	for(i=0;i<lenth;i++)
	{
		for(j=0;str[i+1][j]!='\0';j++)                  
		{
			if(str[i+1][j]!=z[i].name[j]) {v=0;break;}  
		
		}
		    if(v==0)   break;
			if(z[i].name[j]!='\0') break;
	}
	if(i<lenth) return 0;
	else return 1;

}
int compear(char *z,char *s)
{
	for(int i=0;z[i]!=NULL;i++)
	{
		if(z[i]!=s[i]) break;
	}
	if(z[i]!=NULL) return 0;
	if(s[i]!=NULL) return 0;
	return 1;
}