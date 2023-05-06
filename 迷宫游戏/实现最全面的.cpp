#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define maxn 1000
using namespace std;
int n,m;//n*m迷宫 
int flag=0; //若有能到终点的路，则flag变为1
int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}}; //方向数组 ,分别为上，下，右，左 ，输出分别设为0,1,2,3
int vis[maxn][maxn];//DFS标记数组 
int mp[maxn][maxn];  //输入的迷宫 
char mp2[maxn][maxn]; //待输出的迷宫 
typedef struct Point
{
    int x,y;
}SElemType;
SElemType pre[maxn][maxn];//记录每个位置的前驱
SElemType solution[maxn*maxn];//方案记录数组
 
//链栈定义及操作 
typedef struct Snode
{
    SElemType data;
    struct Snode *next;
}Snode,*Linkstack;
 
void Init_S(Linkstack &S)//初始化
{
    S=(Linkstack)malloc(sizeof(Snode));
    S->next=NULL;
}
 
int IsEmpty(Linkstack S) //判断链栈是否为空
{
    if(S->next==NULL) return 1; //1表示为空 
	else return 0;
}
 
void Push(Linkstack &S,SElemType e) //压栈 
{
    Linkstack p=(Linkstack)malloc(sizeof(Snode));
    p->data=e;
	p->next=S->next;
    S->next=p;
}
 
void Pop(Linkstack &S,SElemType &e) //出栈 
{
    
    if(S->next==NULL) return ;
    Linkstack p=S->next;
    e=p->data;
    S->next=p->next;
    free(p);
}
 
int Check(SElemType u)  //检查点是否有障碍和是否已经遍历过 
{
	if(mp[u.x][u.y]==0&&vis[u.x][u.y]==0)
		return 1;
	else return 0;
}
 
void Input() //输入迷宫 
{
	memset(mp,1,sizeof(mp));//把输入的地图全部设置1，表示是障碍 
	cout<<"输入迷宫"<<endl; 
	for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>mp[i][j];//n行m列全部自己输入，右侧和下侧不用管，因为上边mp开了100*100的，全部设置成1了 
}
 
void Output() //输出迷宫 
{
	printf("迷宫为：\n\n");
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) 
			cout<<mp[i][j];
        cout<<endl;//一行一换行 
    }
    cout<<endl;	
}
 
int Direction(SElemType a,SElemType b)  //节点a->b的方向（方向数组做了解释） 
{
	for(int i=0;i<4;++i)
		if(b.x==a.x+dir[i][0]&&b.y==a.y+dir[i][1])
			return i;
}
 
void Output1(int inx,int iny,int outx,int outy) //以三元组形式输出一条通路
{
	
    int len=0;
    SElemType p={outx,outy};
    while(!(p.x==inx&&p.y==iny))
    {
        solution[++len]={p.x,p.y};
        p=pre[p.x][p.y];
    }
    solution[++len]={inx,iny};
    for(int i=len;i>=2;--i)
    {
        printf("(%d,%d,%d)\n",solution[i].x,solution[i].y,Direction(solution[i],solution[i-1]));
    }
    printf("(%d,%d,OK)\n\n",n,m);//到达终点 
}
 
void Solve1(int a,int b,int c,int d)
{
	cout<<"项目1：非递归输出："<<endl;
	memset(vis,0,sizeof(vis));//所有地点都标记为未走过 
	Linkstack S;
	Init_S(S);
	Push(S,{a,b});
	vis[a][b]=1;
	if(IsEmpty(S)==1){
		cout<<"无通路,请重新输入"<<endl;
	}
	while(!IsEmpty(S))
	{
		SElemType u,v;
		Pop(S,u); //取栈顶
		if(u.x==c&&u.y==d){//到达终点 
			Output1(a,b,c,d); //到达终点输出一组解 
//			return ;   //并终止函数 (按题意)
		} 
		for(int i=0;i<4;i++){
			v.x=u.x+dir[i][0];
			v.y=u.y+dir[i][1];
			if(!Check(v)) continue;
			vis[v.x][v.y]=1;
			pre[v.x][v.y]=u;
			Push(S,v);
		}
	}
//	cout<<"无通路,请重新输入"<<endl;
}
 
void Output2(int len) 
{
	for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            mp2[i][j]=mp[i][j]+48;//48代表字符0 
    for(int i=1;i<len;++i)
    {
        int x=solution[i].x,y=solution[i].y,d=Direction(solution[i],solution[i+1]);
        if(d==0) mp2[x][y]='U';
        if(d==1) mp2[x][y]='D';
        if(d==2) mp2[x][y]='R';
        if(d==3) mp2[x][y]='L';    //DOWN,UP,RIGHT,LEFT
    }
    flag=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
            printf("%c ",mp2[i][j]);//上边变成字符型了 
        printf("\n");
    }
    printf("\n");
}
 
void DFS(int k,int inx,int iny,int outx,int outy) 
{
	/*k表示当前走到第几步，x，y表示当前的位置*/
    solution[k]={inx,iny};
    vis[inx][iny]=1;
    if(inx==outx&&iny==outy) Output2(k);//如果到了终点就输出此方案
    else
    for(int i=0;i<4;++i)//四个方向遍历
    {
        int u=inx+dir[i][0],v=iny+dir[i][1];
        if(!Check({u,v})) continue;
        DFS(k+1,u,v,outx,outy);
    }
    vis[inx][iny]=0;//回溯，vis信息清零
}
 
void Solve2(int a,int b,int c,int d)
{
	cout<<"项目2：递归输出："<<endl;
	flag=0;
	memset(vis,0,sizeof(vis));
	DFS(1,a,b,c,d);
	if(!flag) cout<<"无通路,请重新输入"<<endl;//flag是0，表示没有路 
}
 
int main(){
	
//	freopen("text1.txt","r",stdin); 
//	while(cin>>n>>m)
//	{  

		
		cout<<"输入迷宫的行数：";
		cin>>n;
		cout<<"输入迷宫的列数：";
		cin>>m; 
		int a,b,c,d;
		cout<<"输入起点、终点:"<<endl; //(a,b)起点，（b,c）终点
		cin>>a>>b>>c>>d; 
		Input();
		Output();
		Solve1(a,b,c,d);
		Solve2(a,b,c,d);
		cout<<"xxxxxxxxxxxxxxxxxxxxxx"<<endl;
//	} 
	
	return 0;
} 
