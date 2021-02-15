#include<bits/stdc++.h>
using namespace std;

struct fpnode
{
	string item;
	int cnt=0;
	map <string,fpnode*> child;
};

unordered_map <string,int> item_cnt;
vector <vector<string>> trans;

fpnode* create_root()
{
	fpnode *t=new fpnode;
	t->item="NULL";
	t->cnt=0;
	return t;
}

fpnode* add(fpnode *t, vector <string> &v, int i)
{
	t->item=v[i];
	t->cnt++;
	int j=i+1;
	if(j>=v.size())
		return t;
	if(!t->child.count(v[j]))
		t->child[v[j]]=new fpnode;
	t->child[v[j]]=add(t->child[v[j]],v,j);
	return t;
}

int compare_trans(string &a, string &b)
{
	return item_cnt[a]!=item_cnt[b]?item_cnt[a]>item_cnt[b]:a<b;
}

void print_fptree1(fpnode *t, int x)
{
	fstream fout;
	fout.open("output.txt",ios::app);
	if(!t)
		return;
	for(int i=0;i<x;i++)
	{
		cout<<"\t";
		fout<<"\t";
	}
	cout<<"-"<<t->item<<":"<<t->cnt<<endl;
	fout<<"-"<<t->item<<":"<<t->cnt<<endl;
	for(auto &i:t->child)
		print_fptree1(i.second,x+1);
}

void initialize()
{
	ifstream fin("input.txt");
	fstream fout;
	fout.open("output.txt",ios::out);
	string s;
	while(getline(fin,s))
	{
		int i=0;
		for(;i<s.length();i++)
		{
			if(s[i]==' ')
				break;
		}
		unordered_set <string> temp;
		vector <string> trans_temp;
		string t,a;
		i++;
		for(;i<s.length();i++)
		{
			if(s[i]==' ' && temp.count(t))
				t.clear();
			else if(s[i]==' ')
			{
				temp.insert(t);
				item_cnt[t]++;
				trans_temp.push_back(t);
				t.clear();
			}
			else
				t+=s[i];
		}
		if(!temp.count(t))
		{
			temp.insert(t);
			item_cnt[t]++;
			trans_temp.push_back(t);
		}
		trans.push_back(trans_temp);
	}
	fpnode *t=create_root();
	for(auto &i:trans)
	{
		sort(i.begin(),i.end(),compare_trans);
		if(!t->child.count(i[0]))
			t->child[i[0]]=new fpnode;
		add(t->child[i[0]],i,0);
	}
	cout<<"DFS output of the fp tree constructed"<<endl;
	fout<<"DFS output of the fp tree constructed"<<endl;
	print_fptree1(t,0);
}

int main()
{
	initialize();
	return 0;
}
