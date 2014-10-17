#include"select.h"
#include"compar.h"
char p[3][10]={">","<","="};
struct con
{
	string taname;
	string name;
	string judge;
	string term;
};
int  comp(string *st ,con g,int mark,int i,int len_zhiduan,int data_num_per_ta,string *str,int len);
int  the_main(string s,string *str,string *condtion,string *ta_name,int *len_zhiduan,int num_ta,zhiduan *z,string *zhiduan_name,int *data_num_per_ta);
void select(string *s)
{
	string zhiduan_name[20];
	string str[60];
	string ta_name[10];
	string condition[10];
	zhiduan z[20];
 	int ex[10],len_zhiduan[10],num_ta,mark=0,i,data_num_per_ta[10];
	/************测试************************
	int i;                                   /*
	*****************************************/
	 num_ta=analysis_se(s,zhiduan_name,ta_name,condition);//判断输入语句是否正确，和解析SQl语句
	 if(num_ta==0)
	 {
		 cout<<"ERROR：格式错误……"<<endl;
	 }
	 else
	 {
          find(ta_name,z,len_zhiduan,ex,num_ta);//判断数据库中是否有元素
	      for(i=0;i<num_ta;i++)
		  {
	         if(ex[i]==-1)
			 {
		         mark=-1;
			 }
		  }
	      if(mark==-1)
		  {
	        	cout<<"ERROR:没有数据……"<<endl;
		  }
   	      else 
		  {
	     	select_ta(ex,str,num_ta,data_num_per_ta);
	    	if(!the_main(s[1],str,condition,ta_name,len_zhiduan,num_ta,z,zhiduan_name,data_num_per_ta))
			{
				cout<<"ERROR:输入错误……"<<endl;
			}
		  }
	 }
    
	/*******测试*********************************

	for(i=0;zhiduan_name[i]!="";i++)           //
	{
		cout<<zhiduan_name[i]<<" ";            //

	}                                          //
	cout<<endl;
   	for(i=0;ta_name[i]!="";i++)                //
	{
		cout<<ta_name[i]<<" ";
                                               //
	}
	cout<<endl;
	for(i=0;condition[i]!="";i++)              //
	{
		cout<<condition[i]<<" ";               //
                                               //
	}
	cout<<endl;                                //
    /*******************************************/
    
}
/***********************分析输入的语句**********************************************/
int  analysis_se(string *s,string *st,string *ta_name,string *condition)
{
	int i,j,r,c,num_ta,mark=0; //mark为标记
	i=1;
	r=0;
	while(s[i]!="from" && s[i]!="FROM")
	{
		if(s[i]=="" || s[i]==";") mark=1;
		if(mark==1) break;
		if(s[i]==",") {i++;continue;}
		st[r]="";
		for(j=0,c=0;s[i][j]!=NULL;j++)
		{
			if(s[i][j]==59) {mark=1; break;}
	    	else if(s[i][j]!=',') 
			{st[r]+=s[i][j];c++;}
			else
			{st[r]+='\0';r++;c=0;continue;}
		}

		st[r]+='\0';
		i++;
		r++;
	}
	i++;
	r=0;
	if(mark==1) return 0;

	while(s[i]!="where" && s[i]!="WHERE")
	{
        if(s[i]=="" || s[i]==";") mark=1;
		if(mark==1) break;
		ta_name[r]="";
		if(s[i]==",") {i++;continue;}
		for(j=0;s[i][j]!=NULL;j++)
		{
			if(s[i][j]==59){ mark=1;break;}
			if(s[i][j]!=',')  ta_name[r]+=s[i][j];
			else {r++;continue;}
		}
		i++;
		r++;
	}

	if(mark==1) return 0;

	num_ta=r;
	i++;
	r=0;
	while(s[i]!=";")
	{
		if(s[i]=="") mark=1;
		if(mark==1) break;
		condition[r]="";
		for(j=0;s[i][j]!=NULL;j++)
		{

			if(59<s[i][j] && s[i][j]<63) 
			{
				if(condition[r][0]>63 || condition[r][0]<59) 
				{
					r++;
					condition[r]="";
					 condition[r]+=s[i][j];
				}
                else 
				{
				  condition[r]+=s[i][j];
				}
			}
			else 
			{
				if(59<condition[r][0]  && condition[r][0]<63) 
				{ 
					r++;
					condition[r]="";
					if(s[i][j]!=39) condition[r]+=s[i][j];;
				}
                else
				{
					 if(s[i][j]!=39) condition[r]+=s[i][j];
				}
			}
			if(s[i][j]==59){ mark=1;break;}

			
		}
		i++;
		r++;
	}
	if(mark==1) return 0;
	return num_ta;

}
/******************************判断数据库中是否有此数据**********************************/
int find(string *s,zhiduan *z,int *len_zhidaun,int *ex,int num_ta)
{
    char a;
	string ta_name;
	int lenth;
	int i=0,t,y=0,j;
	ifstream fp;
	int number;
	int mark;

	ifstream zd;
	zd.open(ZHIDUAN_PATH,ios::binary);
	if(zd.fail()) cout<<"Error"<<endl;
	while(i<num_ta)
	{
    	t=-1;
		zd.seekg(0,ios::beg);
	  while(1)
	  {
		if(zd.fail()) break;
    	zd>>a;
    	zd>>ta_name;
    	zd>>lenth;
		j=0;
		if(ta_name==s[i])
		{
	        
	      	while(j<lenth)
			{
				zd.read((char *)(z+y),sizeof(zhiduan));
				j++;
				y++;
			}
			t=lenth;
			break;
		}
		else
		{
			zd.seekg(sizeof(zhiduan)*lenth,ios::cur);
		}
	  }


/****************************测试******************

	cout<<a<<" "<<ta_name<<" "<<lenth<<endl;       //
    for(int j=0;j<2;j++)                           //
    cout<<z[j].name<<" ";
	cout<<z[j].size<<" "<<z[j].type<<endl;         //

/***************************************************/
	    
	    len_zhidaun[i]=t;
		i++;
	}
	
	zd.close();
/************************************************************************************



*************************************************************************************/
	fp.open(DATE_PATH,ios::binary);
	i=0;
	while(i<num_ta)
	{
		mark=1;
		fp.seekg(0,ios::beg);
    	while(1)
		{
	        fp>>a;
        	fp>>ta_name;
	    	if(fp.fail()) break;
	      	if(ta_name==s[i])
			{
                mark=0;
		        ex[i]=fp.tellg();
		    	break;
			}
	    	else 
			{
		    	fp>>lenth;
		    	fp>>number;
				fp.seekg(1,ios::cur);
		    	fp.seekg(sizeof(char)*10*lenth*number+1,ios::cur);
			}
		}
		if(mark==1) ex[i]=-1;
		i++;
	}
	fp.close();
    return 0;
	
}
/*****************************************检索内容*********************************/

void select_ta(int *ex,string *str,int num_ta, int *data_num_per_ta)
{
    ifstream fp;
	int number,lenth,i,j,c=0;
	char z[60][10];
	c=0;
	string ta_name;
	fp.open(DATE_PATH,ios::binary);	
	for(i=0;i<num_ta;i++)
	{
    	fp.seekg(ex[i],ios::beg);
    	fp>>lenth;
    	fp>>number;
		fp.seekg(1,ios::cur);
        data_num_per_ta[i]=number;
		j=0;
		while(j<lenth*number)
		{
	     	fp.read((char *)(z+c),sizeof(char)*10);
			c++;
			j++;
		}
/**************************测试******************
        int y;
		for(j=0;j<data_num_per_ta[i];j++)        //
		{
			for(y=0;y<lenth;y++)
			{                                    //
			 cout<<z[x]<<" ";
			 x++;
			}     
			cout<<endl;                          //

		}
		                                         //

/************************************************/
	}
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
/**************************************************************************************/




/*****************根据所给条件，显示数据*********************************/




void show(string *st,zhiduan *z,string *zhiduan_name,int *len_zhiduan,int ex)
{

	int x=0,i,j,a[10],t;

    int y;
	for(i=0;zhiduan_name[i]!="";i++) cout<<"-----------------";
		cout<<endl;
    for(i=0;zhiduan_name[i]!="";i++)
	{

		std::cout <<"|    "<<std::left << std::setw(10) << zhiduan_name[i]<<"  ";
	}
	std::cout<<"|"<<endl;
	for(i=0;zhiduan_name[i]!="";i++) cout<<"-----------------";
		std::cout<<endl;
	for(i=0;zhiduan_name[i]!="";i++)
	{
		for(j=0;j<len_zhiduan[0];j++)
		{
			if(compchar1(zhiduan_name[i],z[j].name)){a[i]=j;break;}
		}
	}
	t=i;
    for(j=0;st[j]!="";j+=len_zhiduan[0])        
		{
		 	for(y=0;y<t;y++)
			{    
				std::cout<<"|   "  << std::left << std::setw(10) << st[j+a[y]]<<"   ";
			}     
		cout<<"|"<<endl; 

		
	for(i=0;zhiduan_name[i]!="";i++) cout<<"-----------------";
		cout<<endl;
	}
    

}

/****************************************************************************************/

int  the_main(string s,string *str,string *condtion,string *ta_name,int *len_zhiduan,int num_ta,zhiduan *z,string *zhiduan_name,int *data_num_per_ta)
{
	 string st[60];
	con g[4];
	int i,j,y=0,w=0,mark=0,or_and=0,size=0,ta=0,m=0,x;
    /******************************************/
	/*             判断输入格式               *//**********************/
	/******************************************/
	for(i=0;condtion[i]!="";i++)
	{
		if(condtion[1]=="" && compar1(condtion[0],"1")) { or_and=-1;mark=1;continue;}
		if(condtion[i]=="and"){ size++;y++;or_and=2;continue;}
	    if(condtion[i]=="or") {size++; y++;or_and=1;continue;}
	   if(condtion[i][0]>59 && condtion[i][0]<63) 
	   {
		  w++;//判断是否是表的字段
		  g[y].judge=condtion[i];
		  continue;
	   }
	  ta=0;
	  if(w==0)
	  {
		for(j=0;condtion[i][j]!=NULL;j++)
		{
			if(condtion[i][j]==46) {ta=1;break;}
		}
		if(ta==1)
		{
			ta=j;
			g[y].taname="";
			for(j=0;j<ta;j++)
			{
				g[y].taname+=condtion[i][j];
			}
			g[y].taname+='\0';
            ta++;
            for(j=0;ta_name[j]!="";j++)
			{
				if(ta_name[j]==g[y].taname) 
				{
					m=1;
					break;
				}
			}
			if(m==0) break;
			m=j;
			g[y].name="";
			for(j=ta;condtion[i][j]!=NULL;j++) g[y].name+=condtion[i][j];
			g[y].name+='\0';

            ta=0;
		    for(j=0;j<m;j++) ta+=len_zhiduan[j];
		    for(j=0;j<len_zhiduan[m];j++)
			{
			   if(compar1(condtion[i],z[ta+j].name)){mark=1;break;}
			
			}
		}
		else
		{
			for(x=0;x<num_ta;x++)
			{
		     	for(j=0;j<len_zhiduan[x];j++)
				{
			        if(compar1(condtion[i],z[ta+j].name)){mark=1;break;}
			
				}
				if(mark==1) break;
			}
			if(mark==1)
			{
				g[y].taname=ta_name[x];
				g[y].name=condtion[i];
			}

		}
		
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
	 m=0;
	}
	if(mark==0) return 0;
	if(i!=(size*4+3) && or_and!=-1) return 0;


/******************************************************************/
	  /*                      比较                       */
/******************************************************************/
   if(or_and==0)
   {
	   for(i=0;i<len_zhiduan[0];i++)
	   {
	      if(compchar1(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar1(g[0].judge,p[i])) break;
	   }
	   if(i==3) return 0;
	   or_and=len_zhiduan[0]*data_num_per_ta[0];
       mark=comp(str ,g[0],mark,i,len_zhiduan[0],data_num_per_ta[0],st,or_and);
	   if(mark==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }   
	   /**************************************************/
     	for(j=0;j<mark;j++) cout<<st[j]<<" ";            //
	     cout<<endl;                                      //
	   /**************************************************/
	  	   
   }
   if(or_and==2)
   {
	   string v[60];
	   for(i=0;i<len_zhiduan[0];i++)
	   {
	      if(compchar1(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar1(g[0].judge,p[i])) break;
	   }
       if(i==3) return 0;
	   or_and=len_zhiduan[0]*data_num_per_ta[0];
	   int t=comp(str ,g[0],mark,i,len_zhiduan[0],data_num_per_ta[0],v,or_and);
	   for(i=0;i<len_zhiduan[0];i++)
	   {
	      if(compchar1(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar1(g[1].judge,p[i])) break;
	   }
	   if(i==3) return 0;
	   t=comp(v ,g[1],mark,i,len_zhiduan[0],data_num_per_ta[0],st,t);
	   if(t==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }   
	   for(i=0;i<t;i++) cout<<st[i]<<" ";
	   cout<<endl;
   }
   if(or_and==1)
   {


	   string v[60];
	   for(i=0;i<len_zhiduan[0];i++)
	   {
	      if(compchar1(g[0].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar1(g[0].judge,p[i])) break;
	   }
	   if(i==3) return 0;
       or_and=len_zhiduan[0]*data_num_per_ta[0];
	   int  c1=comp(str ,g[0],mark,i,len_zhiduan[0],data_num_per_ta[0],st,or_and);
	/**************************************************
     	for(j=0;j<c1;j++) cout<<st[j]<<" ";          //
	     cout<<endl;                                  //
	/**************************************************/
	  for(i=0;i<len_zhiduan[0];i++)
	   {
	      if(compchar1(g[1].name,z[i].name)) break;
	   }
	   mark=i;
	   for(i=0;i<3;i++)
	   {
		   if(compchar1(g[1].judge,p[i])) break;
	   }
	   	   if(i==3) return 0;

	  int   c2=comp(str ,g[1],mark,i,len_zhiduan[0],data_num_per_ta[0],v,or_and);
	/**************************************************
     	for(j=0;j<c2;j++) cout<<v[j]<<" ";            //
	     cout<<endl;                                  //
	/**************************************************/
	  int t,n;
	  size=0;
	  for(i=0;i<c2;i+=len_zhiduan[0])
	  {
		  mark=0;
		  for(j=0;j<c1;j+=len_zhiduan[0])
		  {
		     for(t=0;t<len_zhiduan[0];t++)
			 {
			  if(!compar1(st[j+t],v[i+t])) break;
			  else continue;
			 }
			 if(t==len_zhiduan[0]){ mark=1;break;}
			 else continue; 
			 
		  }

		  if(mark==0)
		  {
		     for(n=0;n<len_zhiduan[0];n++)
			 {
					 st[c1+size]=v[i+n];
					 size++;
			 }
		  }
	  }

	/**************************************************
     	for(j=0;st[j]!="";j++) cout<<st[j]<<" ";    //
	     cout<<endl;                                  //
	/**************************************************/

	  if(c1+size==0)
	   {
		   cout<<"没有数据……"<<endl;
		   return 2;
	   }   

   }   
   if(or_and==-1) 
   {
	   for(i=0;str[i]!="";i++) st[i]=str[i];
   }
   //void show(string *st,zhiduan *z,string *zhiduan_name,int *len_zhiduan)
   if(s=="*")
   {


	   /**************************************************************************************/

	   	for(i=0;i<len_zhiduan[0];i++) cout<<"-----------------";
		cout<<endl;
       for(i=0;i<len_zhiduan[0];i++)
	   {	
		   std::cout <<"|    "<<std::left << std::setw(10) << z[i].name<<"  ";
	   }
       std::cout<<"|"<<endl;
	   for(i=0;i<len_zhiduan[0];i++) cout<<"-----------------";
		cout<<endl;

       for(j=0;st[j]!="";j+=len_zhiduan[0])        
		{
		 	for(y=0;y<len_zhiduan[0];y++)
			{    
				std::cout<<"|  " << std::left << std::setw(10) << st[j+y]<<"    ";
			}     
			cout<<"|"<<endl; 
			for(i=0;i<len_zhiduan[0];i++) cout<<"-----------------";
		cout<<endl;

		}
    /*************************************************************************************************/


   }
   else 
     show(st,z,zhiduan_name,len_zhiduan,1);

	return 1;
}
/**************************************************************/

int  comp(string *st ,con g,int mark,int i,int len_zhiduan,int data_num_per_ta,string *str,int len)
{
	int j,n,x=0;
    	if(i==0)
		{
	    	for(j=0;j<len;j+=len_zhiduan)
			{
            
		    	if(! compar_a1(g.term,st[j+mark]))
				{

				   for(n=0;n<len_zhiduan;n++) {str[x]=st[j+n];x++;}
				}

			}
		}
	    if(i==1)
		{
	    	for(j=0;j<len;j+=len_zhiduan)
			{            
		    	if(!compar_a1(st[j+mark],g.term))
				{
			    	for(n=0;n<len_zhiduan;n++) {str[x]=st[j+n];x++;}
				}

			}
		
		}
    	if(i==2)
		{
	    	for(j=0;j<len;j+=len_zhiduan)
			{
			//compar(st[j+mark],g.term);
            
		    	if(compar1(st[j+mark],g.term))
				{

			    	for(n=0;n<len_zhiduan;n++) {str[x]=st[j+n];x++;}
				}

			}
		}
  return x;


}


