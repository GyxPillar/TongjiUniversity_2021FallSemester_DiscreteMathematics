// 2053385 高逸轩 //
#include <iostream>
#include <iomanip>
#include "input_tools.h"

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)
using namespace std;

// 哈夫曼树节点
struct HuffmanTreeNode 
{
	string coding = "";   // 哈夫曼编码
	int weight = 0;       // 点权值
	HuffmanTreeNode* leftChild = NULL, * rightChild = NULL, * parent = NULL;    // 左右子树、父节点初始设置为空
	bool operator<(const HuffmanTreeNode& x) { return weight < x.weight; }      // 重载小于号，用于排序
	bool operator>(const HuffmanTreeNode& x) { return weight > x.weight; }      // 重载大于号，用于排序

	// 重载加号
	HuffmanTreeNode operator+(const HuffmanTreeNode& x)
	{
		HuffmanTreeNode ret;
		ret.weight = weight + x.weight;
		return ret;
	}
};

class HuffmanTree
{
public:
	// 构造函数
	HuffmanTree(const int n = 0) :nodeNumber(n) { root = new HuffmanTreeNode; };

	// 析构函数，调用销毁函数，释放空间
	~HuffmanTree() { DeleteTree(root); }

	// 建立哈夫曼树
	void BuildHuffmanTree(const int w[]);	
	
	// 合并hft1 hft2两树，存储于新节点parent并以地址形式返回
	void MergeTree(HuffmanTreeNode& hft1, HuffmanTreeNode& hft2, HuffmanTreeNode*& parent);

	// 销毁以current为地址节点根的树
	void DeleteTree(HuffmanTreeNode* current);

	// 返回根节点地址
	HuffmanTreeNode* Root() { return root; }

	// 生成哈夫曼编码表
	void GenerateHuffmanTable(HuffmanTreeNode* current);

	// 输出哈夫曼编码表
	void PrintHuffmanTable(HuffmanTreeNode* current);

	// 快速排序函数
	friend void QuickSort(HuffmanTreeNode a[], int l, int r);

private:
	HuffmanTreeNode* root = NULL; // 根节点
	int nodeNumber = 0;           // 叶节点数目
};

// 优化版快速排序
void QuickSort(HuffmanTreeNode a[], int l, int r)
{
	if (l > r)
		return;
	HuffmanTreeNode mid = a[(l + r) / 2];    // 取中间元素
	int i = l, j = r;
	while (i < j)
	{
		while (a[i] < mid) i++;              // 查找左半部分比中间数大的数
		while (a[j] > mid) j--;              // 查找右半部分比中间数小的数
		if (i <= j)                          // 如果有一组不满足排序条件（左小右大）的数
		{
			swap(a[i], a[j]);                // 交换
			i++;
			j--;
		}
	}
	if (l < j) QuickSort(a, l, j);          // 递归排序左半部分
	if (i < r) QuickSort(a, i, r);          // 递归排序右半部分
}

// 构造哈夫曼树
void HuffmanTree::BuildHuffmanTree(const int w[])
{
	// 哈夫曼树共 2 * n - 1 个节点，用数组模拟队列
	HuffmanTreeNode* array = new HuffmanTreeNode[2 * nodeNumber];

	// 将初始的叶子节点放入数组
	FOR(i, 0, nodeNumber)
		array[i].weight = w[i];

	HuffmanTreeNode* ancestor = new HuffmanTreeNode;
	// 将n个节点最终合并为1个根节点，需要n-1次合并
	FOR(i, 0, nodeNumber - 1)
	{
		HuffmanTreeNode* current1 = new HuffmanTreeNode, * current2 = new HuffmanTreeNode, * parent;

		// 对队列指定区间进行排序，保证每次取出的点是权值较小的点
		QuickSort(array, 2 * i, nodeNumber + i - 1);

		// 取出队列中最小元素和次小元素
		*current1 = array[2 * i], * current2 = array[2 * i + 1];

		// 将最小元素和次小元素合并至parent
		MergeTree(*current1, *current2, parent);

		// 父节点入队列
		array[nodeNumber + i] = *parent;

		// 将根节点位置更新
		root = parent;
	}

	// 释放用来模拟队列临时数组的空间
	delete[]array;
}

// 合并hf1 hft2两节点至parent节点，并以地址形式返回
void HuffmanTree::MergeTree(HuffmanTreeNode& hft1, HuffmanTreeNode& hft2, HuffmanTreeNode*& parent)
{
	// 申请空间
	parent = new HuffmanTreeNode;
	
	// 左右子树位置设置
	parent->leftChild = &hft1, parent->rightChild = &hft2;

	// 权重设置
	parent->weight = hft1.weight + hft2.weight;
	
	// 左右子树父节点位置设置
	hft1.parent = parent, hft2.parent = parent;

}

// 销毁以current地址为根的树的空间
void HuffmanTree::DeleteTree(HuffmanTreeNode* current)
{
	// 遇空位置返回
	if (current == NULL) return;
	
	// 递归向下释放空间
	DeleteTree(current->leftChild), DeleteTree(current->rightChild);
	
	// 释放当前节点的空间
	delete current;
}

// 生成哈夫曼编码表
void HuffmanTree::GenerateHuffmanTable(HuffmanTreeNode* current)
{
	// 已经遍历至叶节点之下，则返回
	if (current == NULL) return;

	// 若当前节点不是叶节点，更新其左右子树的哈夫曼编码
	if (current->leftChild != NULL)
		(current->leftChild)->coding = current->coding + '0';  // 左子树编码在父节点基础上后缀+0
	if (current->rightChild != NULL)
		(current->rightChild)->coding = current->coding + '1'; // 右子树编码在父节点基础上后缀+1

	// 向下遍历
	GenerateHuffmanTable(current->leftChild);
	GenerateHuffmanTable(current->rightChild);
}

// 输出哈夫曼编码表
void HuffmanTree::PrintHuffmanTable(HuffmanTreeNode* current)
{
	// 已经遍历至叶节点之下，则返回
	if (current == NULL) return;

	// 若当前节点是叶节点，输出其权重和哈夫曼编码
	if (current->leftChild == NULL && current->rightChild == NULL)
		cout << setiosflags(ios::left) << setw(6) << current->weight << "：  " << current->coding << endl;

	// 向下遍历
	PrintHuffmanTable(current->leftChild);
	PrintHuffmanTable(current->rightChild);
}
string to_string(int num)
{
	if (num == 0)
		return " 0 ";

	string str = "";
	int num_ = num > 0 ? num : -1 * num;

	while (num_)
	{
		str = (char)(num_ % 10 + 48) + str;
		num_ /= 10;
	}

	if (num < 0)
		str = " - " + str;

	return str;
}
int main()
{
	// 输入节点个数，通过getint保证健壮性
	int nodeNumber = 0;
	cout << "请输入叶节点个数：";
	nodeNumber = getint(1, 100000, "节点个数输入错误，请重新输入：");

	// 输入各个节点的权值，通过geint保证健壮性
	int* f = new int[nodeNumber];
	cout << "请依次输入叶节点权值：" << endl;
	FOR(i, 0, nodeNumber)
	{
		string errorTips = "第";
		errorTips += char(i + '0');
		errorTips += "个节点权值输入错误，请从此重新输入：";
		errorTips += '\n';
		FOR(j, 0, i)
		{
			errorTips += to_string(f[j]);
			errorTips += " ";
		}
		f[i] = getint(1, INT_MAX, errorTips);
	}


	// 建立哈夫曼树
	HuffmanTree huffmanTree(nodeNumber);
	huffmanTree.BuildHuffmanTree(f);

	// 生成哈夫曼编码表
	huffmanTree.GenerateHuffmanTable(huffmanTree.Root());

	// 输出哈夫曼编码表
	cout << "生成的叶子节点哈夫曼编码如下：" << endl;
	huffmanTree.PrintHuffmanTable(huffmanTree.Root());

	return 0;
}