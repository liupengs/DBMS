#include "working.h"
// function.cpp: implementation of the function class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void wdelete(string *s)
{
	delete_sql(s);

}
void winsert(string *s)
{
	insert(s);
  
}
void wupdate(string *s)
{
   updata(s);
}
void wselect(string *s)
{
	select(s);

}
void wcreate(string *s)
{

	if(s[1]=="table") create_ta(s);
	else create_db(s);

}
void wdrop(string *s)
{
	if(s[1]!="table" && s[1]!="TABLE") cout<<"ERROR:ÊäÈë´íÎó¡­¡­"<<endl;
	else 
	{
		drop(s);
	}
}
void look()
{

	look_ta();
}
