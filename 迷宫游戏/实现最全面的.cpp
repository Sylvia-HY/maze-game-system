#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define maxn 1000
using namespace std;
int n,m;//n*m�Թ� 
int flag=0; //�����ܵ��յ��·����flag��Ϊ1
int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}}; //�������� ,�ֱ�Ϊ�ϣ��£��ң��� ������ֱ���Ϊ0,1,2,3
int vis[maxn][maxn];//DFS������� 
int mp[maxn][maxn];  //������Թ� 
char mp2[maxn][maxn]; //��������Թ� 
typedef struct Point
{
    int x,y;
}SElemType;
SElemType pre[maxn][maxn];//��¼ÿ��λ�õ�ǰ��
SElemType solution[maxn*maxn];//������¼����
 
//��ջ���弰���� 
typedef struct Snode
{
    SElemType data;
    struct Snode *next;
}Snode,*Linkstack;
 
void Init_S(Linkstack &S)//��ʼ��
{
    S=(Linkstack)malloc(sizeof(Snode));
    S->next=NULL;
}
 
int IsEmpty(Linkstack S) //�ж���ջ�Ƿ�Ϊ��
{
    if(S->next==NULL) return 1; //1��ʾΪ�� 
	else return 0;
}
 
void Push(Linkstack &S,SElemType e) //ѹջ 
{
    Linkstack p=(Linkstack)malloc(sizeof(Snode));
    p->data=e;
	p->next=S->next;
    S->next=p;
}
 
void Pop(Linkstack &S,SElemType &e) //��ջ 
{
    
    if(S->next==NULL) return ;
    Linkstack p=S->next;
    e=p->data;
    S->next=p->next;
    free(p);
}
 
int Check(SElemType u)  //�����Ƿ����ϰ����Ƿ��Ѿ������� 
{
	if(mp[u.x][u.y]==0&&vis[u.x][u.y]==0)
		return 1;
	else return 0;
}
 
void Input() //�����Թ� 
{
	memset(mp,1,sizeof(mp));//������ĵ�ͼȫ������1����ʾ���ϰ� 
	cout<<"�����Թ�"<<endl; 
	for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>mp[i][j];//n��m��ȫ���Լ����룬�Ҳ���²಻�ùܣ���Ϊ�ϱ�mp����100*100�ģ�ȫ�����ó�1�� 
}
 
void Output() //����Թ� 
{
	printf("�Թ�Ϊ��\n\n");
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) 
			cout<<mp[i][j];
        cout<<endl;//һ��һ���� 
    }
    cout<<endl;	
}
 
int Direction(SElemType a,SElemType b)  //�ڵ�a->b�ķ��򣨷����������˽��ͣ� 
{
	for(int i=0;i<4;++i)
		if(b.x==a.x+dir[i][0]&&b.y==a.y+dir[i][1])
			return i;
}
 
void Output1(int inx,int iny,int outx,int outy) //����Ԫ����ʽ���һ��ͨ·
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
    printf("(%d,%d,OK)\n\n",n,m);//�����յ� 
}
 
void Solve1(int a,int b,int c,int d)
{
	cout<<"��Ŀ1���ǵݹ������"<<endl;
	memset(vis,0,sizeof(vis));//���еص㶼���Ϊδ�߹� 
	Linkstack S;
	Init_S(S);
	Push(S,{a,b});
	vis[a][b]=1;
	if(IsEmpty(S)==1){
		cout<<"��ͨ·,����������"<<endl;
	}
	while(!IsEmpty(S))
	{
		SElemType u,v;
		Pop(S,u); //ȡջ��
		if(u.x==c&&u.y==d){//�����յ� 
			Output1(a,b,c,d); //�����յ����һ��� 
//			return ;   //����ֹ���� (������)
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
//	cout<<"��ͨ·,����������"<<endl;
}
 
void Output2(int len) 
{
	for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            mp2[i][j]=mp[i][j]+48;//48�����ַ�0 
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
            printf("%c ",mp2[i][j]);//�ϱ߱���ַ����� 
        printf("\n");
    }
    printf("\n");
}
 
void DFS(int k,int inx,int iny,int outx,int outy) 
{
	/*k��ʾ��ǰ�ߵ��ڼ�����x��y��ʾ��ǰ��λ��*/
    solution[k]={inx,iny};
    vis[inx][iny]=1;
    if(inx==outx&&iny==outy) Output2(k);//��������յ������˷���
    else
    for(int i=0;i<4;++i)//�ĸ��������
    {
        int u=inx+dir[i][0],v=iny+dir[i][1];
        if(!Check({u,v})) continue;
        DFS(k+1,u,v,outx,outy);
    }
    vis[inx][iny]=0;//���ݣ�vis��Ϣ����
}
 
void Solve2(int a,int b,int c,int d)
{
	cout<<"��Ŀ2���ݹ������"<<endl;
	flag=0;
	memset(vis,0,sizeof(vis));
	DFS(1,a,b,c,d);
	if(!flag) cout<<"��ͨ·,����������"<<endl;//flag��0����ʾû��· 
}
 
int main(){
	
//	freopen("text1.txt","r",stdin); 
//	while(cin>>n>>m)
//	{  

		
		cout<<"�����Թ���������";
		cin>>n;
		cout<<"�����Թ���������";
		cin>>m; 
		int a,b,c,d;
		cout<<"������㡢�յ�:"<<endl; //(a,b)��㣬��b,c���յ�
		cin>>a>>b>>c>>d; 
		Input();
		Output();
		Solve1(a,b,c,d);
		Solve2(a,b,c,d);
		cout<<"xxxxxxxxxxxxxxxxxxxxxx"<<endl;
//	} 
	
	return 0;
} 
