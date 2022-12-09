// 2053385 高逸轩 //
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

#include <iostream>
#include "input_tools.h"
using namespace std;

// 邻接链表 边
struct Edge
{
	int src = -1;          // 起始点编号  
	int dst = -1;          // 目标点序号
	int value = 0;         // 边长度权重
	bool operator<(const Edge& other) { return value < other.value; };// 重载小于比较运算符
	bool operator>(const Edge& other) { return value > other.value; };// 重载大于比较运算符
};

// 邻接链表 点
struct Vertex
{
	int ancestor;          // 记录在并查集中的祖先
};

// 邻接链表
struct GraphList
{
	// 构造函数
	GraphList(int n = 0, int m = 0);

	// 析构函数
	~GraphList();

	// 构建图
	void SetGraphList();
	 
	// 并查集寻父节点
	int FindAncestor(int i);

	// Kruskal算法求得最小生成树
	void Kruskal();

	int vertexNumber = 0, edgeNumber = 0; // 记录顶点数、边数
	Edge* edges = NULL;                   // 顶点数组
	Vertex* vertexs = NULL;               // 边数组
};

// 构造函数
GraphList::GraphList(int n, int m)
{
	// 为顶点数、边数赋值
	vertexNumber = n, edgeNumber = m;

	// 为顶点数组、边数组开辟空间
	vertexs = new Vertex[n + 1], edges = new Edge[m + 1];
}

// 析构函数
GraphList::~GraphList()
{
	// 分别释放边数组和顶点数组内存，避免内存泄露
	delete[]edges;
	delete[]vertexs;
}

// 构图函数，根据键盘输入设置顶点数组和边数组信息
void GraphList::SetGraphList()
{
	// 输入边集信息，通过getint函数处理了错误输入，保证了健壮性
	cout << "请依次输入" << edgeNumber << "条边的起点、终点（编号从1开始）、权重：" << endl;

	FOR(i, 1, edgeNumber + 1)
	{
		string errorTips = "第";
		errorTips += char(i + '0');
		errorTips += "条边起点输入错误，请从此处开始重新输入本行元素：";
		errorTips += '\n';                                         // 得到当前边 起点 输入错误对应提示
		edges[i].src = getint(1, vertexNumber, errorTips);

		errorTips = "";
		errorTips += "第";
		errorTips += char(i + '0');
		errorTips += "条边终点输入错误，请从此处开始重新输入本行元素：";
		errorTips += '\n';                                         
		errorTips += char(edges[i].src + '0');
		errorTips += ' ';                                          // 得到当前边 终点 输入错误对应提示
		edges[i].dst = getint(1, vertexNumber, errorTips);

		errorTips = "";
		errorTips += "第";
		errorTips += char(i + '0');
		errorTips += "条边权值输入错误，请从此处开始重新输入本行元素：";
		errorTips += '\n';
		errorTips += char(edges[i].src + '0');
		errorTips += ' ';                                          
		errorTips += char(edges[i].dst + '0');
		errorTips += ' ';                                          // 得到当前边 权值 输入错误对应提示
		edges[i].value = getint(1, INT_MAX, errorTips);

	}

	FOR(i, 1, vertexNumber + 1)
		vertexs[i].ancestor = i;   // 并查集初始化
}

// 并查集寻父节点，采用记忆化搜索
int GraphList::FindAncestor(int i)
{
	if (i == vertexs[i].ancestor) return i;
	return vertexs[i].ancestor = FindAncestor(vertexs[i].ancestor);
}

// 类模板实现优化后的快速排序，排序区间为[l,r]
template<typename T>void QuickSort(T a[],int l,int r)
{
	if (l > r)
		return;
	T mid = a[(l + r) / 2];      // 取中间元素
	int i = l, j = r;
	while (i < j)
	{
		while (a[i] < mid) i++;  // 查找左半部分比中间数大的数
		while (a[j] > mid) j--;  // 查找右半部分比中间数小的数
		if (i <= j)              // 如果有一组不满足排序条件（左小右大）的数
		{
			swap(a[i], a[j]);    // 交换
			i++;
			j--;
		}
	}
	if (l < j) QuickSort(a, l, j);// 递归排序左半部分
	if (i < r) QuickSort(a, i, r);// 递归排序右半部分
}

// 实现Kruskal贪心算法构建最小生成树
void GraphList::Kruskal()
{
	// 快速排序，区间[1,edgeNumber]
	QuickSort(edges, 1, edgeNumber);

	// ans记录最小生成树边权之和，cnt记录已选边数量
	int ans = 0, cnt = 0;
	FOR(i, 1, edgeNumber + 1)
	{
		int f1 = FindAncestor(edges[i].src); // f1为边起点的祖先
		int f2 = FindAncestor(edges[i].dst); // f2为边终点的祖先

		// 若两点祖先不同，则分属不同的连通分支，需要合并，将此边加入最小生成树
		if (f1 != f2)
		{
			cnt++;                                     // 已选边数+1
			ans += edges[i].value;     // 树的边权之和更新
			vertexs[f1].ancestor = f2; // f1的祖先设置为f2，两点属于同一个联通分支
			cout << "选择起点为" << edges[i].src << " 终点为" << edges[i].dst << " 权值为" << edges[i].value << " 的边" << endl;
		}
		if (cnt == vertexNumber - 1)                   // 当最小生成树终已选边数=顶点数-1时，最小生成树构造完成
		{
			cout << "最小生成树最小边权和为：" << ans << endl;
			return;
		}
	}
	// 若未能选满vertexNumber-1条边，则不能构成最小生成树
	cout << "以上的边不能构成最小生成树" << endl;
}

int main()
{
	// 输入顶点数量与边数量，通过getint函数保证健壮性
	int vertexNumber, edgeNumber;
	cout << "请输入顶点数量、边数量：";
	vertexNumber = getint(1, 5000, "顶点数量输入错误，请重新输入顶点数量和边数量：");
	edgeNumber = getint(0, 5000, "边数量输入错误，请重新输入边数量:");

	// 定义邻接表
	GraphList MinSpanningTree(vertexNumber, edgeNumber);

	// 根据输入的信息进行构图
	MinSpanningTree.SetGraphList();
	
	// 用Kruskal贪心算法构造最小生成树
	MinSpanningTree.Kruskal();

	return 0;
}

