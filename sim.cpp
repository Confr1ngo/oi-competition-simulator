#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int probcnt=10; // 题总数
const int ppl=2; // 总人数
const int len=300; // 比赛长（单位：分）
const int diff[probcnt+1]={0,800,1000,1300,1700,2200,2500,2800,3000,3400,3500}; // 难度分
const int scoredist[probcnt+1]={0,4000,4500,5000,5500,6000,6500,7000,8000,9000,10000}; // Score Distribution
int points[ppl+1][probcnt+1],namemaxlen;
const int infoDelay=100; // 比赛信息输出间隔
const int testDelay=200; // Final Test 信息输出间隔
double perc[ppl+1][probcnt+1];
const bool delayed=true; // 输出延迟启用情况
const string competitionname="20230904"; // 比赛名称
string names[ppl+1]={"","GHJ","BP"};
// string names[ppl+1]={"","GHJ","SR","HYF","YYZ","ZJY","SK","YJ","NZ","LHX","FJZ","LZY","HSJ","CHK","WZF","ZJC","SKC","LKY","CZY","QQH","YLH","ZY"};
mt19937 eng;
/*
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
void setFontColor(int ForgC,int BackC){
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}
double randBetween(double x,double y,mt19937 &engine){
	uniform_real_distribution<double>uid(x,y);
	return uid(engine);
}
void printTime(int tm){
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
void printer(int tm,int ppl,int tsk,string message){
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
string genNewScore(int newscore,double &wd){
	if (wd>100) wd=100;
	wd=int(round(wd*100))/100.0;
	string wd2=to_string(wd);
	wd2.erase(wd2.size()-4,4);
	string scorestr=to_string(newscore);
	while (scorestr.size()!=3) scorestr=" "+scorestr;
	return " "+scorestr+" 分的解法！当前稳度 "+wd2+"%";
}
string genNewWD(double wd,bool succ){
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
	}
	// for (int i=1;i<=15;i++){
	// 	setFontColor(i,0);
	// 	cout<<i<<" ";
	// }
	eng.seed(time(0));
	for (int i=1;i<=len;i++){
		for (int j=1;j<=ppl;j++){
			bool ok=0,ok2=0;
			for (int k=1;k<=probcnt;k++){
				if (ok) continue;
				if (randBetween(0,100,eng)<=0.15*1000/diff[k]*probcnt/6){
					if (points[j][k]<100){
						points[j][k]=100;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=0.25*1000/diff[k]*probcnt/6){
					if (points[j][k]<90){
						points[j][k]=90;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=0.50*1000/diff[k]*probcnt/6){
					if (points[j][k]<80){
						points[j][k]=80;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=1.00*1000/diff[k]*probcnt/6){
					if (points[j][k]<70){
						points[j][k]=70;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=2.00*1000/diff[k]*probcnt/6){
					if (points[j][k]<50){
						points[j][k]=50;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=3.00*1000/diff[k]*probcnt/6){
					if (points[j][k]<30){
						points[j][k]=30;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=4.00*1000/diff[k]*probcnt/6){
					if (points[j][k]<15){
						points[j][k]=15;ok=true;
						perc[j][k]=90000.0/diff[k];
						printer(i,j,k,genNewScore(points[j][k],perc[j][k]));
					}
				}
				else if (randBetween(0,100,eng)<=5.00*1000/diff[k]*probcnt/6){
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
			cout<<"开始测试 "<<char(j+'A'-1)<<" 题...";
			if (delayed) Sleep(testDelay);
			bool ji=randBetween(0,100,eng)>=perc[i][j];
			if (ji && points[i][j]!=0){
				double temp=randBetween(0,100,eng);
				int pointsloss=0;
				if (temp>=60) pointsloss=points[i][j];
				else if (temp>=20) pointsloss=(points[i][j]/2-1)/5*5+5;
				else pointsloss=(points[i][j]*2/3-1)/5*5+5;
				cout<<"诶呀诶呀！挂了"<<pointsloss<<"分！";
				points[i][j]-=pointsloss;
				cout<<"最终成绩: "<<points[i][j]*scoredist[j]/100<<"("<<points[i][j]<<"%).\n";
				points[i][0]+=points[i][j]*scoredist[j]/100;
			}
			else{
				cout<<"该题最终成绩: "<<points[i][j]*scoredist[j]/100<<"("<<points[i][j]<<"%).\n";
				points[i][0]+=points[i][j]*scoredist[j]/100;
			}
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
