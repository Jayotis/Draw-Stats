// Picks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Picks.h"
#include <tchar.h>
#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// The one and only application object
CWinApp theApp;
using namespace std;

typedef char card[6];
typedef int Tcard[7];
const int Set=3;
char prime[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
class Picks
{
public:
	void Init();
	void HitMan();
	void HitStat(Tcard);
	void SortSkips();
	void CalcA(int y);
	void Combinations();
	void FindGR();
	bool Cull();
	void Feeder();
	void HitSS(Tcard);
	void PreHit();
	void HitSSB(Tcard);
	bool IsPrime(card);
	bool Valid(card);
	bool Ranged(card);
	void CalcSkip(int skp);
	bool Skiper(int pick);
	void Prob_Sort(int s);
	void Score_Sort(int w);
	void Diff_Sort(int y);
	void Print();
	void LoadCombos();
	void Picker();
	void DelGR(int x);
	void FindSig(int z);
	void Score(int q);
	void HitScore(int t);
	void HitSig(int r);
	void SigSort();
	void HitAvg(int u);
	void Calc_Stats();
	void HitDiff(int o);
	void SortAvg();
	bool ReCull();
	void RM_Sort();
	void HitSSA(Tcard);
	bool ReRanged(card);
	bool Trim(card);
	char picks[49];
	void StatStat(Tcard);


struct list_p
{
	double prob;
	list_p *nxt;
};
struct num_stats
{
	list_p *start;
	list_p *last;
	int drawn;
	bool picked;
	bool GR;
	bool H;
	bool L;
	int picks;
	int Last_D;
	int skp;
	int Ap;
	int rm;
	double high;
	double low;
	double HighMark;
	double MidMark;
	double LowMark;
	double prob;
	double AvgP;
	double AvgT;
	double diff;
	double Sigma;
	double X[Set];

};
typedef struct SkipStats
{
	int skip;
	double Prob;
	int skips;
	SkipStats *nxt;
};
typedef    struct Combos
{
    card aset;
    struct Combos * nxt;
};
struct p_draws
{
	card draw;
	p_draws *nxt;
};
struct draw_list
{
	Tcard a_draw;
	draw_list *nxt;
};

    Combos* astart;
	SkipStats* Start;
	p_draws* pStart;
	draw_list* dStart;
	
    char LastDraw[7];
	int total_draws;
	int total_picks;
	int tpick;
	int total_skips;
	int total_combos;
	char filename[20];
	char datfile[20];
	int SkipSet[100];
	int prob_list[49];
	int rm_list[49];
	int score_list[49];
	int avg_list[49];
	int diff_list[49];
	bool analysis;
	int results[49];
	int siglist[49];
	int Sresults[49];
	int Aresults[49];
	int Dresults[49];
	int Astat[49];
	int Sstat[49];
	int Dstat[49];
	int Rstat[49];
	int step[4][10];
	int DrawCount;
	int sig_count;
	int diff_count;
	int avg_count;
	int score_count;

	bool random;
	bool show_set;
	bool root;
	num_stats Stats[49];
	card last_draw;
	char debug;
};

void Picks::Calc_Stats()
{
	double prob=0.0;
	bool found=false;
	bool all=false;
	int num=0;
	int list_pos=0;
	double l_prob=990.0;
	double tp=0.0;

	//Average
	while(!found)
	{
		for(int j=0;j<49;j++)
		{
			tp=(double)Aresults[j]/DrawCount;
			if(tp>prob&&tp<l_prob)
			{
				prob=tp;
				num=j;
				found=true;
			}
		}
		if(found)
		{
			found=false;
			Astat[list_pos]=num;
			l_prob=(double)Aresults[num]/DrawCount;
			list_pos++;
			prob=0.0;
		}
		else break;
	}
	prob=0.0;
	num=0;
	found=false;
	l_prob=990.0;
	list_pos=0;

	// Sig
	while(!found)
	{
		for(int j=0;j<49;j++)
		{
			tp=(double)Sresults[j]/DrawCount;
			if(tp>prob&&tp<l_prob)
			{
				prob=tp;
				num=j;
				found=true;
			}
		}
		if(found)
		{
			found=false;
			Sstat[list_pos]=num;
			l_prob=(double)Sresults[num]/DrawCount;
			list_pos++;
			prob=0.0;
		}
		else break;
	}
	prob=0.0;
	num=0;
	found=false;
	l_prob=990.0;
	list_pos=0;

	//Diff
	while(!found)
	{
		for(int j=0;j<49;j++)
		{
			tp=(double)Dresults[j]/DrawCount;
			if(tp>prob&&tp<l_prob)
			{
				prob=tp;
				num=j;
				found=true;
			}
		}
		if(found)
		{
			found=false;
			Dstat[list_pos]=num;
			l_prob=(double)Dresults[num]/DrawCount;
			list_pos++;
			prob=0.0;
		}
		else break;
	}
	prob=0.0;
	num=0;
	found=false;
	l_prob=990.0;
	list_pos=0;

	//Score
	while(!found)
	{
		for(int j=0;j<49;j++)
		{
			tp=(double)results[j]/DrawCount;
			if(tp>prob&&tp<l_prob)
			{
				prob=tp;
				num=j;
				found=true;
			}
		}
		if(found)
		{
			found=false;
			Rstat[list_pos]=num;
			l_prob=(double)results[num]/DrawCount;
			list_pos++;
			prob=0.0;
		}
		else break;
	}
	prob=0.0;
	num=0;
	//0 score
	for(int j=0;j<12;j++)
		step[0][j]=Rstat[j];
	//1 sig
	for(int j=0;j<12;j++)
		step[1][j]=Sstat[j];
	//2 Diff
	for(int j=0;j<12;j++)
		step[2][j]=Dstat[j];
	//3 avg
	for(int j=0;j<12;j++)
		step[3][j]=Astat[j];

}
void Picks::HitSS(Tcard tmp)
{
	int t=0;
	t=0;
	while(t<49)
	{
		Stats[t].prob=(double)Stats[t].drawn/(double)Stats[t].picks;
		Stats[t].AvgT=Stats[t].AvgT+Stats[t].prob;
		Stats[t].Ap++;
		if(Stats[t].prob>Stats[t].high)
			Stats[t].high=Stats[t].prob;
		if(Stats[t].prob<Stats[t].low)
			Stats[t].low=Stats[t].prob;
		t++;
	}
	for(int i=0;i<7;i++)
	{
		if(tmp[i]!=99)
			CalcA(tmp[i]-1);
	}
}
void Picks::HitSSA(Tcard tmp)
{
	for(int j=0;j<49;j++)
	{
		Stats[j].AvgP=Stats[j].AvgT/(double)Stats[j].Ap;
		Stats[j].diff=Stats[j].AvgP-Stats[j].prob;
		FindSig(j);
		Score(j);
	}

	Score_Sort(1);
	SigSort();
	SortAvg();
	Diff_Sort(1);
}
void Picks::HitSSB(Tcard tmp)
{
	int t=0;
	if(tmp[0]==99)
		t++;
	while(t<7)
	{
		HitSig(tmp[t]-1);
		HitScore(tmp[t]-1);
		HitAvg(tmp[t]-1);
		HitDiff(tmp[t]-1);
		//CalcA(tmp[t]-1);
		t++;
	}
}
void Picks::HitStat(Tcard tmp)
{
	int t=0;
	for(int i=0;i<7;i++)
		last_draw[i]=tmp[i];
	if(tmp[0]==99)
		t++;
	while(t<7)
	{
		tpick++;
		//cout<<tmp[t]-1<<' ';
		Stats[(tmp[t]-1)].drawn++;
		Stats[(tmp[t]-1)].picked=true;
		Stats[(tmp[t]-1)].picks++;
		if(Stats[(tmp[t]-1)].Last_D!=0)
		{
			Stats[(tmp[t]-1)].skp=tpick-Stats[(tmp[t]-1)].Last_D;
			CalcSkip(Stats[(tmp[t]-1)].skp);
		}
		Stats[(tmp[t]-1)].Last_D=tpick; 
		for(int i=0;i<49;i++)
		{
			if(!Stats[i].picked)
				Stats[i].picks++;
		}
		t++;
	}

	for(int i=0;i<7;i++)
	{
		if(tmp[i]-1<50)//99 exception
		{
			Stats[(tmp[i]-1)].picked=false;
		}
	}
}
void Picks::HitSig(int r)
{
	for(int i=0;i<49;i++)
	{
		if(siglist[i]==r)
		{
			Sresults[i]++;
			return;
		}
	}
}
void Picks::HitAvg(int u)
{
	for(int i=0;i<49;i++)
	{
		if(avg_list[i]==u)
		{
			Aresults[i]++;
			return;
		}
	}
}
void Picks::HitDiff(int u)
{
	for(int i=0;i<49;i++)
	{
		if(diff_list[i]==u)
		{
			Dresults[i]++;
			return;
		}
	}
}
void Picks::HitScore(int t)
{
	for(int i=0;i<49;i++)
	{
		if(score_list[i]==t)
		{
			results[i]++;
			return;
		}
	}
}
void Picks::Feeder()
{
	draw_list* pTemp;
	pTemp=dStart;
	Tcard tmp={0,0,0,0,0,0,0};
	ifstream draw(filename);
	for(int i=0;i<7;i++)
		draw>>pTemp->a_draw[i];
	total_draws++;
	while(true)
	{
		for(int i=0;i<7;i++)
		{
			if(!(draw>>tmp[i]))
			{
				pTemp->nxt=NULL;
				return;
			}
		}
		total_draws++;
		pTemp->nxt=new draw_list;
		for(int i=0;i<7;i++)
			pTemp->nxt->a_draw[i]=tmp[i];
		pTemp=pTemp->nxt;
	}
}

void Picks::PreHit()
{
	bool ready=false;
	draw_list* temp;
	SkipStats *Stemp;
	Tcard tmp={0,0,0,0,0,0,0};
	DrawCount=0;
	Feeder();
	temp=dStart;
	while(temp!=NULL)
	{
		DrawCount++;
		HitStat(temp->a_draw);
		if(DrawCount>500)
		{
			HitSS(temp->a_draw);
			if(DrawCount>1000)
			{
				HitSSA(temp->a_draw);
				if(DrawCount>1500&&temp->nxt!=NULL)
				{
					HitSSB(temp->nxt->a_draw);
				}
			}
		}
		temp=temp->nxt;
	}
	Calc_Stats();
	Stemp=Start;
	while(Stemp!=NULL)
	{
		Stemp->Prob=(double)Stemp->skips/(double)total_skips;
		Stemp=Stemp->nxt;
	}
}
	
void Picks::FindSig(int z)
{
	list_p *temp;
	double sum=0.0;
	temp=Stats[z].start;
	while(temp!=NULL)
	{
		sum=sum+pow(temp->prob-Stats[z].AvgP,2);
		temp=temp->nxt;
	}
	Stats[z].Sigma=sqrt(sum/Stats[z].Ap);
	//DelGR(z);
}
void Picks::Score(int q)
{
	double Ex=(double)(Stats[q].drawn+1)/(Stats[q].picks+1);
	double A=Ex-Stats[q].AvgP;
	double B=2*(Stats[q].Sigma*Stats[q].Sigma);
	double D=((A*A)/B)*(-1);
	double C=sqrt(2*M_PI);
	Stats[q].X[0]=(1/(Stats[q].Sigma*C))*exp(D);
}
void Picks::RM_Sort()
{
	int trm=0;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].rm>trm&&!Stats[j].picked)
				{
					trm=Stats[j].rm;
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		rm_list[i]=num;
		trm=0;
		num=0;
	}
}
void Picks::Prob_Sort(int s)
{
	double prob=0.0;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].prob>prob&&!Stats[j].picked)
				{
					prob=Stats[j].prob;
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		prob_list[i]=num;
		prob=0.0;
		num=0;
	}
}
void Picks::Score_Sort(int w)
{
	double prob=0.0;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].X[0]>prob&&!Stats[j].picked)
				{
					prob=Stats[j].X[0];
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		score_list[i]=num;
		prob=0.0;
		num=0;
	}
}
void Picks::Diff_Sort(int o)
{
	double prob=-9999.9999;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].diff>prob&&!Stats[j].picked)
				{
					prob=Stats[j].diff;
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		diff_list[i]=num;
		prob=-9999.9999;
		num=0;
	}
}
void Picks::SortAvg()
{
	double prob=0.0;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].AvgP>prob&&!Stats[j].picked)
				{
					prob=Stats[j].AvgP;
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		avg_list[i]=num;
		prob=0.0;
		num=0;
	}
}
void Picks::SigSort()
{
	double prob=0.0;
	bool found=false;
	bool all=false;
	int num=0;
	for(int i=0;i<49;i++)
		Stats[i].picked=false;
	for(int i=0;i<49;i++)
	{
		while(!found)
		{
			for(int j=0;j<49;j++)
			{
				if(Stats[j].Sigma>prob&&!Stats[j].picked)
				{
					prob=Stats[j].Sigma;
					num=j;
					found=true;
					break;
				}
			}
			if(found)
				found=false;
			else 
			{
				Stats[num].picked=true;
				break;
			}
		}
		siglist[i]=num;
		prob=0.0;
		num=0;
	}
}
void Picks::DelGR(int x)
{
	list_p* past,*curr;
	curr=Stats[x].start;
	while(curr!=NULL)
	{
		past=curr;
		curr=curr->nxt;
		delete past;
	}
	Stats[x].start=NULL;
}
bool Picks::Ranged(card tmp)
{
	p_draws* Ptmp=pStart;
	int match=0;
	int comp=6;
	int set[6]={0,0,0,0,0,0};
	int list_count=0;
	int Tlist_count=0;
	bool top=false;
	bool bottom=false;
	int count=0;
	int gr=0;
	int hh=0;
	int ll=0;
	bool repeat=false;
	/*for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==prob_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==prob_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;

	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==prob_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==prob_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
*/
	count=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(tmp[i]==siglist[step[1][j]])
				count++;
		}
	}
	if(count>sig_count)
		sig_count=count;
	if(count<2)
		return false;

	count=0;


	for(int i=0;i<6;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(tmp[i]==avg_list[step[3][j]])
				count++;
		}
	}
	if(count>avg_count)
		avg_count=count;
	if(count<2)
		return false;

	count=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(tmp[i]==diff_list[step[2][j]])
				count++;
		}
	}
	if(count>diff_count)
		diff_count=count;
	if(count<2)
		return false;

	count=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(tmp[i]==score_list[step[0][j]])
				count++;
		}
	}
	if(count>score_count)
		score_count=count;
	if(count<2)
		return false;
	count=0;
	/*for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==score_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==score_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==score_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==score_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
		*/


	/*for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==siglist[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	/*for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==siglist[i])
				count++;
		}
	}
	if(count==6||count==0)
		list_count++;
	count=0;
	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==siglist[i])
				count++;
		}
	}
	if(count==6||count==0)
		list_count++;
	count=0;
	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==siglist[i])
			count++;
		}
	}
	if(count==6||count==0)
		list_count++;
		*/

	/*for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==avg_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==avg_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==avg_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==avg_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;*/

	/*for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==diff_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==diff_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==diff_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]-1==diff_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	if(list_count>0)
		Tlist_count++;
	list_count=0;
	*/
	count=0;
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tmp[j]==last_draw[i])
				count++;
		}
	}
	if(count==0||count>3)
		return false;
	/*if(!random)
	{
		comp=0;
		for(int i=0;i<6;i++)
		{
			if(Stats[tmp[i]-1].GR)
				gr++;
			else if(Stats[tmp[i]-1].H)
				hh++;
			else if(Stats[tmp[i]-1].L)
				ll++;
		}
		if(!(gr==2&&hh==2&&ll==2))
			return false;
	}*/
	int skp1=0;
	comp=0;
	for(int i=0;i<6;i++)
	{
		skp1=tpick-Stats[(tmp[i]-1)].Last_D;
		skp1++;
		if(Skiper(skp1))
			comp++;
	}
	if(comp!=6)
		return false;
	comp=0;
	count=0;
	/*temp=nstart;
	for(int i=0;i<6;i++)
	{
		while(count<((i+1)*7))
		{
			for(int j=0;j<6;j++)
			{
				if(temp->num==tmp[j])
				{
					set[i]++;
					break;
				}
			}
			temp=temp->nxt;
			count++;
		}
	}
	for(int i=0;i<6;i++)
	{
		if(set[i]!=1)
			return false;
	}*/
	for(int i=0;i<4;i++)
	{
		if((tmp[i]+1)==tmp[i+1])
		{
			if((tmp[i+1]+1)==tmp[i+2])
				return false;
		}
	}
	while(Ptmp!=NULL)
	{
		match=0;
		for(int i=0;i<7;i++)
		{
			for(int j=0;j<6;j++)
			{
				if(tmp[j]==Ptmp->draw[i])
					match++;
			}
		}
		if(match==6)
			return false;
		Ptmp=Ptmp->nxt;
	}
	return true;
	/*if(Tlist_count>0)
		return false;
	else return true;*/
}
void Picks::FindGR()
{
	double spread=0.0;
	int mark=0;
	/*for(int i=0;i<49;i++)
	{
		temp=Stats[i].start;
		while(mark<3500)
		{
			temp=temp->nxt;
			mark++;
		}
		while(temp!=NULL)
		{
			if(temp->prob>Stats[i].high)
				Stats[i].high=temp->prob;
			if(temp->prob<Stats[i].low)
				Stats[i].low=temp->prob;
			temp=temp->nxt;
		}
		DelGR(i);
	}*/
	for(int i=0;i<49;i++)
	{
		spread=Stats[i].high-Stats[i].low;
		Stats[i].HighMark=Stats[i].high-(spread*0.382);
		Stats[i].LowMark=Stats[i].high-(spread*0.618);
		Stats[i].MidMark=(spread*.5)+Stats[i].low;
		if(Stats[i].prob>Stats[i].LowMark&&Stats[i].prob<Stats[i].HighMark)
			Stats[i].GR=true;
		else if(Stats[i].prob>Stats[i].HighMark)
			Stats[i].H=true;
		else Stats[i].L=true;
	}
}
void Picks::Init()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<12;j++)
			step[i][j]=0;
	}
	for(int i=0;i<49;i++)
	{
		picks[i]=99;
	}
	pStart=new p_draws;
	for(int i=0;i<6;i++)
	{
		pStart->draw[i]=0;
		last_draw[i]=0;
	}
	if(root)
	{
                strcpy_s(datfile,"C:\\BaseFile.dat");
                strcpy_s(filename,"C:\\PastDraws.csv");
	}
	else
	{
                strcpy_s(datfile,"E:\\BaseFile.dat");
                strcpy_s(filename,"E:\\PastDraws.csv");
	}
	sig_count=0;
	diff_count=0;
	score_count=0;
	avg_count=0;

	analysis=false;
	pStart->nxt=NULL;
	Start=new SkipStats;
	Start->Prob=0.0;
	Start->skip=0;
	Start->skips=0;
	Start->nxt=NULL;
	total_draws=0;
	total_picks=0;
	total_skips=0;
	random=false;
	tpick=0;
	astart=new Combos;
	dStart=new draw_list;
	dStart->nxt=NULL;
	astart->nxt=NULL;
	total_combos=1;
	int i=1;
	for(int a=0;a<100;a++)
		SkipSet[a]=0;
	for(int i=0;i<49;i++)
	{
		prob_list[i]=0;
		Stats[i].drawn=0;
		Stats[i].start=NULL;
		Stats[i].picked=false;
		Stats[i].GR=false;
		Stats[i].H=false;
		Stats[i].L=false;
		Stats[i].picks=0;
		Stats[i].high=0.0;
		Stats[i].low=1.0;
		Stats[i].HighMark=0.0;
		Stats[i].MidMark=0.0;
		Stats[i].LowMark=0.0;
		Stats[i].diff=0.0;
		Stats[i].prob=0.0;
		Stats[i].Last_D=0;
		Stats[i].AvgP=0.0;
		Stats[i].AvgT=0.0;
		Stats[i].Sigma=0.0;
		Stats[i].Ap=0;
		Stats[i].rm=0;
		for(int j=0;j<Set;j++)
			Stats[i].X[j]=0.0;
		results[i]=0;
		Sresults[i]=0;
		siglist[i]=0;
		Aresults[i]=0;
		Dresults[i]=0;
	}
	for(int i=0;i<49;i++)
	{
		prob_list[i]=0;
		score_list[i]=0;
		avg_list[i]=0;
		diff_list[i]=0;
		rm_list[i]=0;
		Astat[i]=0;
		Sstat[i]=0;
		Dstat[i]=0;
	}

}
void Picks::HitMan()
{
	bool ready=false;
	p_draws* pTemp;
	SkipStats *Stemp;
	int temp=0;
	int i=0;
	ifstream draw(filename);
	while(draw>>temp)
	{
		if(temp==99)
		{
			last_draw[i]=temp;
			i++;
			draw>>temp;
		}
		tpick++;
		for(int j=0;j<49;j++)
		{
			if(!Stats[j].picked)
			{
				if(temp==(j+1))
				{
					Stats[j].drawn++;
					Stats[j].picked=true;
					if(Stats[j].Last_D!=0)
					{
						Stats[j].skp=tpick-Stats[j].Last_D;
						CalcSkip(Stats[j].skp);
					}
					Stats[j].Last_D=tpick; 
					last_draw[i]=temp;
				}
				Stats[j].picks++;
				if(tpick>3500)
				{
					if(Stats[j].picked)
					{
						if(ready)
						{
							HitSig(j);
							HitScore(j);
							HitAvg(j);
						}
						CalcA(j);
					}
					Stats[j].prob=(double)Stats[j].drawn/(double)Stats[j].picks;
					Stats[j].AvgT=Stats[j].AvgT+Stats[j].prob;
					Stats[j].Ap++;
					if(Stats[j].prob>Stats[j].high)
						Stats[j].high=Stats[j].prob;
					if(Stats[j].prob<Stats[j].low)
						Stats[j].low=Stats[j].prob;

				}
			}
		}
		i++;

		if(i==7)
		{
			pTemp=pStart;
			if(pStart->draw[0]!=0)
			{
				while(pTemp->nxt!=NULL)
				{
					pTemp=pTemp->nxt;
				}
				pTemp->nxt=new p_draws;
				pTemp=pTemp->nxt;
			}
			strcpy(pTemp->draw,last_draw);
			pTemp->nxt=NULL;
			if(tpick>11102&&analysis)
			{
				for(int j=0;j<49;j++)
				{
					Stats[j].AvgP=Stats[j].AvgT/(double)Stats[j].Ap;
					FindSig(j);
					Score(j);
				}
				Score_Sort(1);
				SigSort();
				SortAvg();
				ready=true;
			}
			for(int k=0;k<49;k++)
			{
				if(Stats[k].picked)
					Stats[k].picked=false;
			}
			i=0;
		}
	}
	for(int i=0;i<49;i++)
	{
		Stats[i].AvgP=Stats[i].AvgT/(double)Stats[i].Ap;
		Stats[i].diff=Stats[i].AvgP-Stats[i].prob;
		FindSig(i);
		Score(i);
	}
	Score_Sort(1);
	SigSort();
	SortAvg();
	Diff_Sort(1);
	Stemp=Start;
	while(Stemp!=NULL)
	{
		Stemp->Prob=(double)Stemp->skips/(double)total_skips;
		Stemp=Stemp->nxt;
	}

	draw.close();
}
void Picks::SortSkips()
{
	SkipStats *prev,*curr,*temp;
	bool allsort=false;
	while(!allsort)
	{
		allsort=true;
		if(Start->Prob<Start->nxt->Prob)
		{
			curr=Start->nxt;
			Start->nxt=curr->nxt;
			curr->nxt=Start;
			Start=curr;
			allsort=false;
		}
		else
		{
			prev=Start;
			curr=Start->nxt;
			while(curr->nxt!=NULL)
			{
				if(curr->Prob<curr->nxt->Prob)
				{
					temp=curr->nxt;
					curr->nxt=temp->nxt;
					temp->nxt=curr;
					prev->nxt=temp;
					prev=prev->nxt;
					allsort=false;
				}
				else
				{
					prev=curr;
					curr=curr->nxt;
				}
			}
		}
	}
	int count=0;
	curr=Start;
	//cout<<'\n'<<"Skip List\n";
	while(count!=100)
	{
		SkipSet[count]=curr->skip;
		//cout<<curr->skip<<' '<<curr->Prob<<'\n';
		curr=curr->nxt;
		count++;
	}
}
void Picks::CalcSkip(int skp)
{
	total_skips++;
	SkipStats* temp;
	bool found=false;
	temp=Start;
	if(temp->skip==0)
	{
		temp->skip=skp;
		temp->skips++;
		return;
	}
	while(temp!=NULL)
	{
		if(temp->skip==skp)
		{
			temp->skips++;
			return;
		}
		else temp=temp->nxt;
	}
	temp=Start;
	while(temp->nxt!=NULL)
		temp=temp->nxt;
	temp->nxt=new SkipStats;
	temp->nxt->skip=skp;
	temp->nxt->skips=1;
	temp->nxt->Prob=0.0;
	temp->nxt->nxt=NULL;
}
bool Picks::IsPrime(card num)
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<15; j++)
        {
            if(num[i]==prime[j])
                return true;
        }
    }
    return false;
}
void Picks::CalcA(int y)
{
	list_p *tempt;
	if(Stats[y].start==NULL)
	{
		Stats[y].start=new list_p;
		Stats[y].start->prob=(double)Stats[y].drawn/(double)Stats[y].picks;
		Stats[y].start->nxt=NULL;
		Stats[y].last=Stats[y].start;
	}
	else
	{
		tempt=Stats[y].last;
		tempt->nxt=new list_p;
		tempt->nxt->prob=(double)Stats[y].drawn/(double)Stats[y].picks;
		Stats[y].prob=tempt->nxt->prob;
		Stats[y].last=tempt->nxt;
		tempt->nxt->nxt=NULL;		
	}
}
bool Picks::Valid(card nums)
{
    int even=0;
	int sum=0;
	int ones=0;
    int tens=0;
    int twenties=0;
    int thrities=0;
    int forties=0;
    int low=0;

	if(!IsPrime(nums))
		return false;
    for(int i=0; i<6; i++)
    {
        if((int)nums[i]%2==0)
            even++;
		sum=sum+(int)nums[i];
		if(nums[i]<10)
            ones++;
        else if(nums[i]<20)
            tens++;
        else if(nums[i]<30)
            twenties++;
        else if(nums[i]<40)
            thrities++;
        else if(nums[i]<50)
            forties++;
        if(nums[i]<25)
            low++;
    }
    if(even<2||even>4)
        return false;
    if(sum<121||sum>200)
        return false;
    if(low<2||low>4)
        return false;
    if(ones>3||tens>3||twenties>3||thrities>3||forties>3)
        return false;
	if(ones&&tens&&twenties&&thrities&&forties)
		return false;
	return true;
}	
bool Picks::Skiper(int pick)
{
	for(int a=0;a<100;a++)
	{
		if(SkipSet[a]==pick)
			return true;
	}
	return false;
}	
void Picks::Combinations()
{
	FILE *pfile=fopen(datfile,"wb");
	int found=0;
	card set;
	for(int t=0;t<6;t++)
		set[t]=0;
    for (int Pos1 = 1; Pos1 < 45; Pos1++)
    {
		for(int t=0;t<6;t++)
			cout<<(int)set[t]<<' ';
		cout<<'\n';
        for (int Pos2 = Pos1 + 1; Pos2 < 46; Pos2++)
        {
            for (int Pos3 = Pos2 + 1; Pos3 < 47; Pos3++)
            {
                for (int Pos4 = Pos3 + 1; Pos4 < 48; Pos4++)
                {
                    for (int Pos5 = Pos4 + 1; Pos5 < 49; Pos5++)
                    {
                        for (int Pos6 = Pos5 + 1; Pos6 < 50; Pos6++)
                        {
                            set[0]=(char)Pos1;
                            set[1]=(char)Pos2;
                            set[2]=(char)Pos3;
                            set[3]=(char)Pos4;
                            set[4]=(char)Pos5;
                            set[5]=(char)Pos6;
							
                            if(Valid(set))
                            {
								total_combos++;
								//cout<<"found"<<' '<<total_combos<<'\n';
								fwrite(set,1,sizeof(set),pfile);
								//cout<<'\n';
                            }
                        }
                    }
                }
            }
        }
    }
	fclose(pfile);
}
bool Picks::Cull()
{
	Combos *temp,*curr,*prev;
	card tmp;
	bool gstart=false;
	int pos=1;
	sig_count=0;
	while(!gstart)
	{
		gstart=true;
		for(int i=0;i<6;i++)
			tmp[i]=astart->aset[i];
		if(!Ranged(tmp))
		{
			if(astart->nxt==NULL)
			{
				random=true;
				return false;
			}
			temp=astart;
			astart=astart->nxt;
			delete temp;
			gstart=false;
			total_combos--;
		}
	}
	prev=astart;
	curr=astart->nxt;
	pos++;
	cout<<"working!"<<'\n';
	while(curr!=NULL)
	{
		for(int i=0;i<6;i++)
			tmp[i]=curr->aset[i];
		if(!Ranged(tmp))
		{
			temp=curr;
			prev->nxt=curr->nxt;
			curr=curr->nxt;
			delete temp;
			total_combos--;
		}
		else
		{
			prev=curr;
			curr=curr->nxt;
			pos++;
			//cout<<"moved into Pos#"<<pos<<"total combos="<<total_combos<<'\n';
			//for(int  p=0; p<6;p++)
			//	cout<<(int)tmp[p]<<' ';
			//cout<<'\n';
		}
	}
	cout<<"done."<<'\n';
	return true;
}	
void Picks::Print()
{
	
	for(int i=0;i<49;i++)
	{
		cout<<prob_list[i]+1;
		if(prob_list[i]+1<10)
			cout<<' ';
		cout<<"--> "<<Stats[prob_list[i]].prob<<' ';
		if(Stats[prob_list[i]].GR)
			cout<<"**"<<' ';
		else if(Stats[prob_list[i]].H)
			cout<<"HH"<<' ';
		else if(Stats[prob_list[i]].L)
			cout<<"LL"<<' ';
		else cout<<"??"<<' ';
		cout<<"High="<<Stats[prob_list[i]].HighMark<<" Low="<<Stats[prob_list[i]].LowMark<<" Sig="<<fixed<<setprecision(10)<<Stats[prob_list[i]].Sigma<<" AvgP="<<Stats[prob_list[i]].AvgP<<'\n';
	}
	cout<<'\n'<<"Score List"<<'\n';
	for(int i=0;i<49;i++)
	{
		cout<<score_list[i]+1;
		if(score_list[i]+1<10)
			cout<<' ';
		cout<<"--> "<<Stats[score_list[i]].prob<<' ';
		if(Stats[score_list[i]].GR)
			cout<<"**"<<' ';
		else if(Stats[score_list[i]].H)
			cout<<"HH"<<' ';
		else if(Stats[score_list[i]].L)
			cout<<"LL"<<' ';
		else cout<<"??"<<' ';
		cout<<" Sig="<<fixed<<setprecision(10)<<Stats[score_list[i]].Sigma<<" AvgP="<<Stats[score_list[i]].AvgP<<" P(x)= "<<Stats[score_list[i]].X[0]<<'\n';
	}
	cout<<'\n';
	if(true)
	{
		for(int g=0;g<49;g++)
			cout<<"Pos->"<<g<<"  Hits->"<<results[g]<<'\n';
		cout<<"Sigma List \n";
		for(int g=0;g<49;g++)
			cout<<"Pos->"<<g<<"  Hits->"<<Sresults[g]<<'\n';
		cout<<"Avg List \n";
		for(int g=0;g<49;g++)
			cout<<"Pos->"<<g<<"  Hits->"<<Aresults[g]<<'\n';
	}


}
void Picks::LoadCombos()
{
	
	Combos* tc;
	total_combos=0;
	char temp=0;
	int pos=0;
	bool data=true;
	tc=astart;
	FILE *pfile=fopen(datfile,"rb");
	fread(astart->aset,sizeof(astart->aset),1,pfile);
	
	while(!feof(pfile))
	{
		total_combos++;
		tc->nxt=new Combos;
		tc=tc->nxt;
		fread(tc->aset,sizeof(astart->aset),1,pfile);
	}
	tc->nxt=NULL;
	fclose(pfile);
}
bool Picks::ReCull()
{
	RM_Sort();
	Combos *temp,*curr,*prev;
	card tmp;
	bool gstart=false;
	int pos=1;
	while(!gstart)
	{
		gstart=true;
		for(int i=0;i<6;i++)
			tmp[i]=astart->aset[i];
		if(!ReRanged(tmp))
		{
			if(astart->nxt==NULL)
			{
				random=true;
				return false;
			}
			temp=astart;
			astart=astart->nxt;
			delete temp;
			gstart=false;
			total_combos--;
		}
	}
	prev=astart;
	curr=astart->nxt;
	pos++;
	cout<<"working!"<<'\n';
	while(curr!=NULL)
	{
		for(int i=0;i<6;i++)
			tmp[i]=curr->aset[i];
		if(!ReRanged(tmp))
		{
			temp=curr;
			prev->nxt=curr->nxt;
			curr=curr->nxt;
			delete temp;
			total_combos--;
		}
		else
		{
			prev=curr;
			curr=curr->nxt;
			pos++;
			//cout<<"moved into Pos#"<<pos<<"total combos="<<total_combos<<'\n';
			//for(int  p=0; p<6;p++)
			//	cout<<(int)tmp[p]<<' ';
			//cout<<'\n';
		}
	}
	cout<<"done... again"<<'\n';
	return true;
}
bool Picks::ReRanged(card Rtmp)
{
	int count=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(Rtmp[j]-1==rm_list[i])
				count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;
	for(int i=10;i<24;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(Rtmp[j]-1==rm_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;

	for(int i=24;i<38;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(Rtmp[j]-1==rm_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	count=0;

	for(int i=38;i<49;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(Rtmp[j]-1==rm_list[i])
			count++;
		}
	}
	if(count==6||count==0)
		return false;
	else return true;
}
bool Picks::Trim(card str)
{
	Combos *temp,*curr,*prev;
	bool gstart=false;
	bool found=false;
	int pos=1;
	int match=1;
	int count;
	char blah;
	int y=0;
	while(!found)
	{
		temp=astart;
		while(temp!=NULL)
		{
			count=0;
			for(int a=0;a<6;a++)
			{
				y=0;
				while(picks[y]!=99)
				{
					if(picks[y]==temp->aset[a])
						count++;
					y++;
				}
			}
			if(count<match)
			{
				found=true;
				break;
			}
			count=0;
			temp=temp->nxt;
		}
		if(!found)
		{
			cout<<"All combinations eliminated.  Exit?\n";
			cin>>blah;
			return false;
		}
	}
	while(!gstart)
	{
		gstart=true;
		count=0;
		for(int i=0;i<6;i++)
		{
			y=0;
			while(picks[y]!=99)
			{
				if(picks[y]==astart->aset[i])
					count++;
				y++;
			}
		}
		if(count>=match)
		{
			temp=astart;
			astart=astart->nxt;
			delete temp;
			gstart=false;
			total_combos--;
		}
	}
	prev=astart;
	curr=astart->nxt;
	pos++;
	while(curr!=NULL)
	{
		count=0;
		for(int i=0;i<6;i++)
		{
			y=0;
			while(picks[y]!=99)
			{
				if(picks[y]==curr->aset[i])
					count++;
				y++;
			}
		}
		if(count>=match)
		{
			temp=curr;
			prev->nxt=curr->nxt;
			curr=curr->nxt;
			delete temp;
			total_combos--;
		}
		else
		{
			prev=curr;
			curr=curr->nxt;
			pos++;
			//cout<<"moved into Pos#"<<pos<<"total combos="<<total_combos<<'\n';
			//for(int  p=0; p<6;p++)
			//	cout<<(int)tmp[p]<<' ';
			//cout<<'\n';
		}
	}
	return true;
}
void Picks::Picker()
{
	cout<<"score count="<<score_count<<'\n';
	cout<<"diff count="<<diff_count<<'\n';
	cout<<"sig_count="<<sig_count<<'\n';
	cout<<"avg count="<<avg_count<<'\n';
	int pos=0;
	int i=1;
	int y=0;
	card tmp;
	Combos *tc;
	char ans='y';
	char pans='n';
	char show='n';
	bool valid=false;
	int set[49];
	for(int j=0;j<49;j++)
		set[j]=0;
	cout<<"first total combos="<<total_combos+1<<'\n';
	if(debug=='y')
	{
		cout<<"show set?\n";
		cin>>show;
	}
	tc=astart;
	while(tc!=NULL)
	{
		for(int k=0;k<6;k++)
			Stats[((int)tc->aset[k])-1].rm++;
		tc=tc->nxt;
	}
	//ReCull();
	if(show=='y')
	{
		tc=astart;
		while(tc!=NULL)
		{
			for(int k=0;k<6;k++)
				set[((int)tc->aset[k])-1]++;
			tc=tc->nxt;
		}
		for(int q=0;q<49;q++)
		{
			if(set[q]!=0)
				cout<<q+1<<" hit "<<set[q]<<'\n';
		}
	}
	while(!valid)
	{
		cout<<"total combos="<<total_combos+1<<'\n';
		cout<<"enter the position\n";
		cin>>pos;
		pos--;
		if((pos>=0&&pos<=total_combos))
			valid=true;
		else cout<<"\nInvalid responce, enter the position\n";
	}
	valid=false;
	while(true)
	{
		tc=astart;
		while(i<pos)
		{
			tc=tc->nxt;
			i++;
		}
		cout<<"Random pick = ";
		y=0;
		while(picks[y]!=99)
		{
			if(debug=='y')
				cout<<(int)picks[y]<<" ";
			y++;
		}
		cout<<"\n--> ";
		for(int j=0;j<6;j++)
		{
			cout<<(int)tc->aset[j]<<' ';
			tmp[j]=tc->aset[j];
			picks[y]=tc->aset[j];
			y++;
		}
		cout<<'\n';
		//cout<<"another?"<<'\n';
		i=1;
		/*cin>>ans;
		if(ans!='y')
			break;*/
		if(Trim(tmp))
		{
			valid=false;
			while(!valid)
			{
				cout<<"total combos="<<total_combos+1<<'\n';
				cout<<"enter the position\n";
				cin>>pos;
				pos--;
				if((pos>=0&&pos<=total_combos))
					valid=true;
				else cout<<"\nInvalid responce, enter the position\n";
			}
		}
		else return;
	}
}	
int _tmain(int argc, _TCHAR* argv[])
{
	Picks Pick;
	char ans=0;
	Pick.Init();
	cout<<"debug?";
	cin>>Pick.debug;
	if(Pick.debug=='y')
	{
		cout<<"Perform statistical analysis? \n";
		cin>>ans;
		if(ans=='y')
			Pick.analysis=true;
		cout<<"C: data? \n";
		cin>>ans;
		Pick.root=false;
		if(ans=='y')
			Pick.root=true;
		cout<<"Make combo file? \n";
		cin>>ans;
		Pick.Init();
		if(ans=='y')
			Pick.Combinations();
	}
	else 
	{
		Pick.root=false;
		Pick.Init();
	}
	Pick.LoadCombos();
	Pick.PreHit();
	Pick.FindGR();
	Pick.Prob_Sort(1);
	Pick.Score_Sort(1);
	Pick.SortAvg();
	Pick.SortSkips();
	Pick.Print();
	Pick.Cull();
	Pick.Picker();
	return 0;
}

