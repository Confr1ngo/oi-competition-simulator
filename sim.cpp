#include <bits/stdc++.h>
#include <windows.h>
#include "simpreferences.h"
using namespace std;
double perc[ppl+1][probcnt+1];
int points[ppl+1][probcnt+1],namemaxlen;
int minrr=INT_MAX;
mt19937 eng;
inline double getamp(int minrating,int rating){
	if (!userating) return 1;
	return sqrt(double(rating)/minrating);
}
inline void setFontColor(int ForgC,int BackC){
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}
const string status[8]={"","Wrong Answer","Accepted","Time Limit Exceeded","Compile Error","Runtime Error","Memory Limit Exceeded","No source file found"};
const int color[8]={0,12,10,9,14,5,9,8};
const int STAT_WA  = 0x01;
const int STAT_AC  = 0x02;
const int STAT_TLE = 0x03;
const int STAT_CE  = 0x04;
const int STAT_RE  = 0x05;
const int STAT_MLE = 0x06;
const int STAT_NSF = 0x07;
inline void printTestStatus(int t){
	setFontColor(color[t],0);
	cout<<status[t];
	setFontColor(7,0);
}
inline double randBetween(double x,double y,mt19937 &engine){
	uniform_real_distribution<double>uid(x,y);
	return uid(engine);
}
inline int randintBetween(int x,int y,mt19937 &engine){
	uniform_int_distribution<int>uid(x,y);
	return uid(engine);
}
inline void printTime(int tm){
	int hr=tm/60,mn=tm%60;
	if (tm>len/6*5) setFontColor(12,0);
	else if (tm>len/6*4) setFontColor(4,0);
	else if (tm>len/6*3) setFontColor(6,0);
	else if (tm>len/6*2) setFontColor(14,0);
	else if (tm>len/6*1) setFontColor(10,0);
	else setFontColor(2,0);
	cout<<"["<<setfill('0')<<setw(2)<<hr<<":"<<setw(2)<<mn<<"] ";
	setFontColor(7,0);
}
inline void printer(int tm,int ppl,int tsk,string message){
	if (delayed) Sleep(infoDelay);
	printTime(tm);
	if (message.find(" 100 分的解法")!=string::npos){
		setFontColor(10,0);
	}
	if (message.find("对拍！当前稳度")!=string::npos){
		setFontColor(13,0);
	}
	if (message.find("诶呀诶呀！")!=string::npos){
		setFontColor(11,0);
	}
	cout<<setfill(' ')<<setw(namemaxlen)<<names[ppl];
	cout<<" 完成了 "<<char('A'+tsk-1)<<" 题"<<message<<".\n";
	setFontColor(7,0);
}
inline string genNewScore(int newscore,double &wd){
	if (wd>100) wd=100;
	wd=int(round(wd*100))/100.0;
	string wd2=to_string(wd);
	wd2.erase(wd2.size()-4,4);
	string scorestr=to_string(newscore);
	while (scorestr.size()!=3) scorestr=" "+scorestr;
	return " "+scorestr+" 分的解法！当前稳度 "+wd2+"%";
}
inline string genNewWD(double wd,bool succ){
	if (succ){
		wd=int(round(wd*100))/100.0;
		string wd2=to_string(wd);
		wd2.erase(wd2.size()-4,4);
		return "的对拍！当前稳度 "+wd2+"%";
	}
	wd=int(round(wd*100))/100.0;
	string wd2=to_string(wd);
	wd2.erase(wd2.size()-4,4);
	return "一次错误的对拍！诶呀诶呀！当前稳度 "+wd2+"%";
}
// 2 10 16 6 4 12
int main(){
	for (int i=1;i<=ppl;i++){
		namemaxlen=max(namemaxlen,(int)names[i].size());
		minrr=min(minrr,rating[i]);
	}
	// for (int i=1;i<=15;i++){
	// 	setFontColor(i,0);
	// 	cout<<i<<" ";
	// }
	// return 0;
	eng.seed(time(0));
	for (int i=1;i<=len;i++){
		for (int j=1;j<=ppl;j++){
			bool ok=0,ok2=0;
			for (int k=1;k<=probcnt;k++){
				if (ok) continue;
				if (randBetween(0,100,eng)<=0.15*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<100){
						points[j][k]=100;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=0.25*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<90){
						points[j][k]=90;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=0.50*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<80){
						points[j][k]=80;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=1.00*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<70){
						points[j][k]=70;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=2.00*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<50){
						points[j][k]=50;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=3.00*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<30){
						points[j][k]=30;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=4.00*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<15){
						points[j][k]=15;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=5.00*1000/diff[k]*probcnt/6*getamp(minrr,rating[j])){
					if (points[j][k]<5){
						points[j][k]=5;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
			}
			for (int k=1;k<=probcnt;k++){
				if (ok2 || !points[j][k] || perc[j][k]>99.9) continue;
				if (randBetween(0,100,eng)<=0.50){
					ok2=true;
					double delta=(randBetween(0.0,100.0,eng)<=10.0? -20:7.5);
					perc[j][k]+=delta;
					perc[j][k]=max(perc[j][k],0.0);
					perc[j][k]=min(perc[j][k],100.0);
					printer(i,j,k,genNewWD(perc[j][k],delta>0));
				}
				else if (randBetween(0,100,eng)<=0.25){
					ok2=true;
					double delta=(randBetween(0.0,100.0,eng)<=10.0? -20:10);
					perc[j][k]+=delta;
					perc[j][k]=max(perc[j][k],0.0);
					perc[j][k]=min(perc[j][k],100.0);
					printer(i,j,k,genNewWD(perc[j][k],delta>0));
				}
				else if (randBetween(0,100,eng)<=0.10){
					points[j][k]=100;ok2=true;
					double delta=(randBetween(0.0,100.0,eng)<=10.0? -20:15);
					perc[j][k]+=delta;
					perc[j][k]=max(perc[j][k],0.0);
					perc[j][k]=min(perc[j][k],100.0);
					printer(i,j,k,genNewWD(perc[j][k],delta>0));
				}
			}
		}
	}
	printTime(len);
	cout<<setfill(' ');
	cout<<"比赛已结束！现在开始最终测试。\n";
	for (int i=1;i<=ppl;i++){
		cout<<"开始测试选手 "<<setw(namemaxlen)<<names[i]<<" 的程序...\n";
		for (int j=1;j<=probcnt;j++){
			cout<<"开始测试 "<<char(j+'A'-1)<<" 题...(预测得分: "<<points[i][j]<<")\n";
			if (delayed) Sleep(testDelay*2);
			if (points[i][j]==0){
				int temp=randintBetween(0,1,eng);
				if (temp){
					printTestStatus(STAT_NSF);
					cout<<"\n";
				}
				else{
					for (int test=1;test<=20;test++){
						cout<<"Test #"<<test<<(test<10? " : ":": ");
						printTestStatus(STAT_WA);cout<<"\n";
						if (delayed) Sleep(testDelay/2);
					}
				}
				cout<<"得分: 0%.\n";
			}
			else{
				bool ji=(randBetween(0,100*getamp(minrr,rating[j]),eng)>=perc[i][j] && points[i][j]!=0);
				bool scgain=(!ji && randBetween(0,10,eng)<1 && points[i][j]!=100);
				int pointsloss=randintBetween(1,points[i][j]/5,eng)*5;
				int pointsgain=randintBetween(1,min(5,20-points[i][j]/5),eng)*5;
				points[i][j]-=ji*pointsloss;
				points[i][j]+=scgain*pointsgain;
				if (ji && 0==points[i][j]){
					int pk=randintBetween(1,100,eng);
					if (pk<=5){
						printTestStatus(STAT_CE);
						cout<<"\n";
					}
					else if (pk<=80){
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							printTestStatus(STAT_WA);cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else{
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							printTestStatus((randintBetween(0,1,eng)? STAT_WA:STAT_RE));cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
				}
				else if (points[i][j]==100){
					for (int test=1;test<=20;test++){
						cout<<"Test #"<<test<<(test<10? " : ":": ");
						printTestStatus(STAT_AC);cout<<"\n";
						if (delayed) Sleep(testDelay/2);
					}
				}
				else if (points[i][j]==95){
					for (int test=1;test<=20;test++){
						cout<<"Test #"<<test<<(test<10? " : ":": ");
						if (test<=19) printTestStatus(STAT_AC);
						else printTestStatus(!randintBetween(0,2,eng)? STAT_WA:(randintBetween(0,1,eng)? STAT_TLE:STAT_RE));
						cout<<"\n";
						if (delayed) Sleep(testDelay/2);
					}
				}
				else{
					int temp=randintBetween(1,100,eng);
					if (temp<=5){ //0-1-0
						int start=randintBetween(2,20-points[i][j]/5,eng);
						int end=start+points[i][j]/5-1;
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test>=start && test<=end) printTestStatus(STAT_AC);
							else printTestStatus(STAT_WA);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else if (temp<=50){ //1-0
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test<=points[i][j]/5) printTestStatus(STAT_AC);
							else printTestStatus(STAT_WA);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else if (temp<=70){ //1-2
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test<=points[i][j]/5) printTestStatus(STAT_AC);
							else printTestStatus(STAT_TLE);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else if (temp<=80){ //0-1-2
						int start=randintBetween(2,20-points[i][j]/5,eng);
						int end=start+points[i][j]/5-1;
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test>=start && test<=end) printTestStatus(STAT_AC);
							else if (test>end) printTestStatus(STAT_TLE);
							else if (test<start) printTestStatus(STAT_WA);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else if (temp<=90){ //1-4
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test<=points[i][j]/5) printTestStatus(STAT_AC);
							else printTestStatus(STAT_RE);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else if (temp<=95){ //1-5
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test<=points[i][j]/5) printTestStatus(STAT_AC);
							else printTestStatus(STAT_MLE);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
					else{ //1-0/4
						for (int test=1;test<=20;test++){
							cout<<"Test #"<<test<<(test<10? " : ":": ");
							if (test<=points[i][j]/5) printTestStatus(STAT_AC);
							else printTestStatus(randintBetween(0,1,eng)? STAT_WA:STAT_RE);
							cout<<"\n";
							if (delayed) Sleep(testDelay/2);
						}
					}
				}
				cout<<"得分: "<<points[i][j]+ji*pointsloss-scgain*pointsgain<<"%->"<<points[i][j]<<"%.\n";
			}
			if (delayed) Sleep(testDelay*5);
			points[i][0]+=points[i][j]*scoredist[j]/100;
		}
		cout<<"选手总分: "<<points[i][0]<<".\n\n";
	}
	struct SortUsage{
		int id;
		int score;
	}competitor[ppl+1];
	for (int i=1;i<=ppl;i++){
		competitor[i].id=i;
		competitor[i].score=points[i][0];
	}
	sort(competitor+1,competitor+ppl+1,[=](SortUsage a,SortUsage b){return a.score>b.score;});
	cout<<"\n"<<competitionname<<" 比赛结果:\n";
	int totalscore=0;
	for (int i=1;i<=probcnt;i++){
		totalscore+=scoredist[i];
	}
	for (int i=1;i<=ppl;i++){
		if (i==1) setFontColor(14,0);
		if (i==2) setFontColor(8,0);
		if (i==3) setFontColor(6,0);
		cout<<"Rank "<<setw(int(ceil(log10(ppl+1))))<<i<<": ";
		setFontColor(7,0);
		cout<<setw(namemaxlen)<<names[competitor[i].id]<<" ";
		for (int j=1;j<=probcnt;j++){
			cout<<setw(int(ceil(log10(scoredist[j]+1))))<<
			points[competitor[i].id][j]*scoredist[j]/100;
			cout<<(j==probcnt? " = ":" + ");
		}
		cout<<setw(int(ceil(log10(totalscore+1))))<<competitor[i].score<<" pts\n";
	}
	return 0;
}
/*
* how ability mechanic works
* amplifier = sqrt(ability/minability)
* probability *= amplifier
* -----------------------------------------------------
* every minute 0.15*1000/difficulty*probcnt/6%  100 pts
*              0.25*1000/difficulty*probcnt/6%  90  pts
*              0.50*1000/difficulty*probcnt/6%  80  pts
*              1.00*1000/difficulty*probcnt/6%  70  pts
*              2.00*1000/difficulty*probcnt/6%  50  pts
*              3.00*1000/difficulty*probcnt/6%  30  pts
*              4.00*1000/difficulty*probcnt/6%  15  pts
*              5.00*1000/difficulty*probcnt/6%  5   pts
* original AC Rate 90000/difficulty*probcnt/6%  
* check                        0.50%  + 7.50% AC Rate
* check                        0.25%  +10.00% AC Rate
* check                        0.10%  +15.00% AC Rate
* check failure    check_rate*10.00%  -20.00% AC Rate
*/
