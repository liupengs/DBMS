#include"drop.h"
#include"zhiduan.h"
void drop(string *s)
{
	int ex[4];
   if( find(s[2],ex)) 
   {
	   delete_ta(ex);
   }
   else cout<<"ERROR:没有此表……"<<endl;
}
int find(string s,int *ex)
{
	char a;
	string ta_name;
	int lenth,u;
	int i=0,y=0,j;
	ifstream fp;
	int number;
	int mark=0;

	/*******************************************************************
                               表文件
    ********************************************************************/
	ifstream zd;
	zd.open(ZHIDUAN_PATH,ios::binary);
	if(zd.fail()) return 0;
	zd.seekg(0,ios::beg);
	  while(1)
	  {
		if(zd.fail()) break;
		u=zd.tellg();
    	zd>>a;
    	zd>>ta_name;
    	zd>>lenth;
		j=0;
		if(ta_name==s)
		{
			ex[0]=u;
			zd.seekg(sizeof(zhiduan)*lenth,ios::cur);
			u=zd.tellg();
			ex[1]=u;
			mark=1;
			break;
		}
		else
		{
			zd.seekg(sizeof(zhiduan)*lenth,ios::cur);
		}

	  }
    if(mark==0) return 0;
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
		u=fp.tellg();
	    fp>>a;
        fp>>ta_name;
		fp>>lenth;
		fp>>number;
		fp.seekg(1,ios::cur);
	    if(fp.fail()) break;
	    if(ta_name==s)
		{
			 mark=0;
			 ex[2]=u;
			 fp.seekg(sizeof(char)*10*lenth*number,ios::cur);
			 u=fp.tellg();
			 ex[3]=u;
		     break;
		}
	    else 
		{
			fp.seekg(1,ios::cur);
		   	fp.seekg(sizeof(char)*10*lenth*number,ios::cur);
		}
	}
	fp.close();
	if(mark==1) { ex[2]=ex[3]=-1;}
    return 1;
}
 /************************删除表***********************************/
void  delete_ta(int *ex)
{
	int i,mark=0,lenth,number,m;
	string ta_name;
    ifstream fp;
    ofstream zd;
	char frist[100000],a;
	char end[100000];
	char one[100000],two[100000];
	if(ex[3]>0)
	{
	
     	fp.open(DATE_PATH,ios::binary | ios::beg);
	    fp.seekg(0,ios::beg);
   	    if(ex[2]>10)  fp.read((char *)(frist),ex[2]-1);
    	int u=fp.tellg();
    	fp.seekg(ex[3],ios::beg);
		for(i=1;i<7;i++)
		{

		//	cout<<fp.eof()<<endl;
			if(fp.eof()!=0) break;
	     	fp.seekg(1,ios::cur);


		}
		if(i==7) mark=1;
		if(mark==1)
		{
			m=1;
    	    fp.seekg(ex[3],ios::beg);
			fp>>a;
			fp>>ta_name;
			if(fp.fail()) m=0;
			fp>>lenth;
			fp>>number;
			fp.seekg(1,ios::cur);
		}
	    u=fp.tellg();
        if(mark==1 && m==1)
		{
          i=0;
          while(1)
		  { 
		     if(fp.eof()!=0)break; 
			 if(fp.fail()) break;
             fp.read((char *)(end+i),sizeof(char));
	  	 
		    i++;		
		  }
		}
    	fp.close();


        zd.open(DATE1_PATH,ios::binary | ios::app);
    	if(zd.fail()) cout<<"打开失败………"<<endl;
        if(ex[2]>10) zd.write((char *)(frist),ex[2]-1);
        if(mark==1 && m==1) 
		{
			zd<<" "<<a<<" ";
			zd<<ta_name<<" ";
			zd<<lenth<<" ";
			zd<<number<<" ";
			zd.write((char *)(end),(i-1)*sizeof(char));
		}
    	zd.close();
	    remove(DATE_PATH);
     	rename(DATE1_PATH,DATE_PATH );
	}


	    ifstream ep;
        ofstream xd;
        mark=0;
	    ep.open(ZHIDUAN_PATH,ios::binary | ios::beg);
	    ep.seekg(0,ios::beg);
   	    if(ex[0]>10)  ep.read((char *)(one),ex[0]-1);
    	int u=fp.tellg();
    	ep.seekg(ex[1],ios::beg);
	    u=ep.tellg();
		if(!ep.eof())
		{
			ep>>a;
			ep>>ta_name;
			if(!ep.fail()) mark=1;
			ep>>lenth;
		}
		u=ep.tellg();
		if(mark==1)
		{

           i=0;
           while(1)
		   {
              if(ep.eof()!=0)break; 
			  if(ep.fail()) break;
			  ep.read((char *)(two+i),sizeof(char));
	   	      i++;
		   }
		}
		u=ep.tellg();
    	ep.close();

        xd.open(ZHIDUAN1_PATH,ios::binary | ios::app);
    	if(xd.fail()) cout<<"打开失败………"<<endl;
        if(ex[0]>10) xd.write((char *)(one),ex[0]-1);
        if(mark==1) 
		{
			xd<<" "<<a<<" ";
			xd<<ta_name<<" ";
			xd<<lenth;
			xd.write((char *)(two),(i-1)*sizeof(char));
		}
    	xd.close();
	    if(!remove( ZHIDUAN_PATH)) cout<<"删除成功……"<<endl;
	    else {  cout<<"删除失败……"<<endl;}
     	rename( ZHIDUAN1_PATH,ZHIDUAN_PATH);


}
