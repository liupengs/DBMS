#include<string>
#include<fstream>
#include <iomanip>
#include"zhiduan.h"
#include<iostream>
using namespace std;
void select(string *s);
int  analysis_se(string *s,string *str,string *ta_name,string *condition);
int find(string *s,zhiduan *z,int *len_zhidaun,int *ex,int num_ta);
void select_ta(int *ex,string *str,int num_ta,int *data_num_per_ta);
void show(string *st,zhiduan *z,string *zhiduan_name,int *len_zhiduan,int ex);
