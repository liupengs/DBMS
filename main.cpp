#include"main.h"
#include"working.h"
#include<iostream>
void trans(string *s)
{   
	if(s[0]=="select")    
		wselect(s);
	else if(s[0]=="insert") 
		winsert(s);
    else if(s[0]=="update") 
		wupdate(s);
	else if(s[0]=="delete")
		wdelete(s);
	else if(s[0]=="create")
		wcreate(s);
	else if(s[0]=="drop")
		wdrop(s);
	else
		cout<<"Error"<<endl;

}
int main()
{
	    string s[60];
		int i,t,j;
		while(1)
		{
		     i=0;
	         while(cin>>s[i])
			 {
		    	t=s[i].size()-1;
	        	if(s[i][t]==59) break;
				if(s[i]=="exit_sql") {t=-1;break;}
				if(s[i]=="look_sql") { look();t=-2;break;}
				i++;
			 }
			 if(t==-1) break;


/***************************************************************
	    ifstream fp;                                                  //
    	int number,lenth,i=0;
    	char a;
	    string ta_name;
    	fp.open("E:\\MyProjects\\DBMS\\date\\date.mysql",ios::binary); //	
    	//fp.seekg(ex,ios::beg);
		string z[10];
    	fp>>a;
        fp>>ta_name;                                                   //
    	fp>>lenth;
    	fp>>number;
		while(i<2){ fp.read((char *)(z+i),sizeof(string));   i++;}           //
        fp.close();
		for( j=0;j<number*lenth;j++)                                //
		{
			cout<<z[j]<<" ";
		}


/***************************************************************/

			 if(t!=-2)  trans(s);
			 t=i;
			 for(j=0;j<t;j++) 
			 {
				 for(i=0;s[j][i]!=NULL;i++) s[j][i]=NULL;
			 }
		}

	return 0;
}
