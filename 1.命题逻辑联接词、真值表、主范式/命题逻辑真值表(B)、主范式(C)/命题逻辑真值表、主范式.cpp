// 2053385 高逸轩 //
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

#include <iostream>
#include <iomanip>

using namespace std;

// 快速幂求a的b次方%c
int QuickPow(int a, int b, int c)
{
	int ret = 1;
	int num = a % c;
	while (b)
	{
		if (b & 1)               // b为奇数
			ret = ret * num % c;
		b = b >> 1;              // b/=2
		num = num * num % c;
	}
	return ret;
}

// 命题变量单元
struct variable
{
	char name;  // 变量名称 
    bool value; // 变量值
};

// 真值表类
class TruthTable
{
public:
	// 构造函数，根据输入的表达式s构建
	TruthTable(const string s = "");

	// 析构函数，释放内存，避免内存丢失
	~TruthTable() { delete[]variables, delete[]principalConjunctiveNormalForm, delete[]principalDisjunctiveNormalForm; }

	// 输出真值表
	void PrintTruthTable();

	// 输出主范式
	void PrintPrincipalNormForms();

private:

	int* principalDisjunctiveNormalForm;// 主析取范式
	int* principalConjunctiveNormalForm;// 主合取范式
	int variableNumber = 0;             // 变量总数
	variable* variables;                // 存储变量的名称和其对应赋值
	string expression;                  // 表达式

	// 将十进制数字num转换为二进制数字，同时将二进制数字按位赋值给variable变量
	void SetVariablesValue(int num = 0);

	// 计算当前状态下表达式的值
	bool CalculateExpressionValue();

	// 输出全部变量与表达式名称
	void PrintVariablesName()const;

	// 输出全部变量与表达式的值
	void PrintVariablesValue();

	// 将表达式中的变量名转换为数字
	string AlphaToNum();

};

// 构造函数，根据输入的表达式s为私有成员赋初值
TruthTable::TruthTable(const string s)
{
	variable temp[33];                                 // 暂时存储变量
	int cnt = 0;                                       // 变量总数
	FOR(i, 0, s.length())
	{
	judge:if (isalpha(s[i]))                           // 若表达式中某位为字母，则将该字母计入变量
	{
		FOR(j, 0, cnt)
			if (s[i] == temp[j].name)                  // 重复出现的变量名不计数
			{
				i++;
				goto judge;
			}

		temp[cnt].name = s[i], temp[cnt].value = false;// 新出现的变量放入数组中记录，同时初始值赋0
		cnt++;
	}
	}
	printf("\n该式子中的变量个数为:%d\n", cnt);        // 输出变量个数

	// 设置TruthTable类的私有成员
	variableNumber = cnt;
	expression = s;
	variables = new variable[cnt];
	principalConjunctiveNormalForm = new int[QuickPow(2, cnt, INT_MAX)];// 主合取范式中最多有2的n次方个极大项
	principalDisjunctiveNormalForm = new int[QuickPow(2, cnt, INT_MAX)];// 主析取范式中最多有2的n次方个极小项
	FOR(i, 0, cnt)
		variables[i] = temp[i];
}

// 输出真值表
void TruthTable::PrintTruthTable()
{
	// 输出各变量名称作为表头
	PrintVariablesName();

	// 真值表共2的n次方行，用lines变量储存
	int n = variableNumber;
	int lines = QuickPow(2, n, INT_MAX);
	FOR(i, 0, lines)
	{
		SetVariablesValue(i);  // 设置数字i的二进制数码为当前各变量的值
		PrintVariablesValue(); // 输出各变量赋值、当前赋值状态下表达式的值
	}
}

// 输出主范式
void TruthTable::PrintPrincipalNormForms()
{
	// 根据不同赋值，极小项与极大项的和有2的n次方个
	int n = variableNumber;
	int lines = QuickPow(2, n, INT_MAX);
	
	// 分别记录主合取范式中极大项的数目、主析取范式中极小项的数目
	int principalConjunctiveNormalFormNumber = 0, principalDisjunctiveNormalFormNumber = 0;

	// 对2的n次方中情况进行遍历
	FOR(i, 0, lines)
	{
		SetVariablesValue(i);                                                                                       // 设置数字i的二进制数码为当前各变量的值
		if (CalculateExpressionValue()) principalDisjunctiveNormalForm[principalDisjunctiveNormalFormNumber++] = i; // 若当前赋值使得公式的真值为1，则为极小项，计入主析取范式
		else principalConjunctiveNormalForm[principalConjunctiveNormalFormNumber++] = i;                            // 若当前赋值使得公式的真值为0，则为极大项，计入主合取范式
	}

	// 输出主合取范式
	if (principalConjunctiveNormalFormNumber)
	{
		printf("\n该命题公式的主合取范式:\n\t");
		FOR(i, 0, principalConjunctiveNormalFormNumber - 1)
			cout << "M(" << principalConjunctiveNormalForm[i] << ")\\/";
		cout << "M(" << principalConjunctiveNormalForm[principalConjunctiveNormalFormNumber - 1] << ')' << endl;
	}
	else printf("\n该命题公式不存在主合取范式.\n");

	// 输出主析取范式
	if (principalDisjunctiveNormalFormNumber)
	{
		printf("\n该命题公式的主析取范式:\n\t");
		FOR(i, 0, principalDisjunctiveNormalFormNumber - 1)
			cout << "M(" << principalDisjunctiveNormalForm[i] << ")/\\";
		cout << "M(" << principalDisjunctiveNormalForm[principalDisjunctiveNormalFormNumber - 1] << ')' << endl;
	}
	else printf("\n该命题公式不存在主析取范式.\n");
}

// 将十进制数字num转换为二进制数字，同时将二进制数字按位赋值给variable变量
void TruthTable::SetVariablesValue(int num)
{
	int cnt = variableNumber;
	// 共为cnt个变量赋值，进行cnt次
	while (cnt)
	{
		variables[cnt - 1].value = num % 2; // 将转化后的二进制数字按位把变量表 从后向前 赋值
		num /= 2;
		cnt--;
	}
}

// 输出全部变量和表达式名称
void TruthTable::PrintVariablesName()const
{
	FOR(i, 0, variableNumber)
		cout << setiosflags(ios::right) << setw(3) << variables[i].name;  // 输出变量名称
	cout << "  " << expression << endl << endl;                           // 输出表达式名称
}

// 输出全部变量和表达式的值
void TruthTable::PrintVariablesValue()
{
	FOR(i, 0, variableNumber)
		cout << setiosflags(ios::right) << setw(3) << variables[i].value;  // 输出变量的值
	cout << "  " << CalculateExpressionValue() << endl << endl;            // 输出表达式的值
}

// 将公式expression中的命题变量转换为其对应赋值（把字母换成数字）的中缀表达式
// 例：!a & b (a=0,b=1) 转换为 !0 & 1
string TruthTable::AlphaToNum()
{
	string ret = expression;
	FOR(i, 0, expression.length())
	{
		// 若当前字符为字母，则其为变量，将其转换为数字字符
		if (isalpha(expression[i]))
		{
			FOR(j, 0, variableNumber)
			{
				// 在cnt个字符中找到对应变量的赋值
				if (variables[j].name == expression[i])
				{
					ret[i] = variables[j].value + '0';
					break;
				}
			}
		}
	}
	return ret;
}

// 比较运算符优先级，顺序为 ( ) ! & | ^ ~ ，括号 否定 合取 析取 蕴涵 等值
// 返回值-1为 a < b
// 返回值 1为 a >= b
// 返回值 0为特殊操作：连续两次否定视为撤销这两次否定操作
int CompareOperator(const char a, const char b)
{
	if (a == '!')
	{
		if (b == '(') return -1;
		else if (b == '!') return 0;
		else return 1;
	}
	else if (a == '&')
	{
		if ((b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '|')
	{
		if ((b == '&' || b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '^')
	{
		if ((b == '&' || b == '(' || b == '|' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '~')
	{
		if ((b == '~' || b == ')')) return 1;
		else return -1;
	}
	else if (a == '(')  return -1;
}

//  &    |     ^    ~
// 合取 析取 蕴涵 等值 四种运算
bool CalcuateValue(const bool a, const char c, const bool  b) 
{
	if (c == '&') return a & b;    // 合取 
	if (c == '|') return a | b;    // 析取
	if (c == '^') return (!a) | b; // 蕴涵
	if (c == '~') return a == b;   // 等值
}

// 计算当前各命题变量赋值情况下的表达式的值
bool TruthTable::CalculateExpressionValue()
{
	bool stack1[33];        // 存放数字的栈
	char stack2[33];        // 存放运算符的栈 
	int top1 = 0, top2 = 0; // 栈顶
	string s = AlphaToNum();// 将字母变量转换为数字后的公式

	// 模拟将表达式整体加括号，以判断结束标志
	s += ')';
	stack2[top2++] = '(';
	FOR(i, 0, s.length())
	{
		// 表达式该位置为0/1，直接入栈
		if (isdigit(s[i])) stack1[top1++] = s[i] - '0';

		// 表达式该位置为运算符
		else
		{
			// 遇到左括号直接入栈
			if (s[i] == '(') stack2[top2++] = s[i];

			// 遇到右括号则弹出栈中运算符并进行运算，直到遇到左括号为止
			else if (s[i] == ')')
			{
				// 栈为空，则直接进入下一次循环，不必进行左括号匹配
				if (!top2) continue;

				// 弹出栈内运算符直到匹配到左括号
				while (stack2[top2 - 1] != '(')
				{
					// !是单元运算符，需要特判
					if (stack2[top2 - 1] == '!')
					{
						// 取数栈顶元素进行取反，并放回数栈
						bool a = stack1[--top1];
						if (a == 1) stack1[top1++] = 0;
						else stack1[top1++] = 1;

						// 符号栈顶的!弹出
						top2--, i--;
					}

					// 其余二元运算符运算
					else
					{
						// 取b为栈顶，a为栈次顶元素，进行二元运算
						bool b = stack1[--top1];
						bool a = stack1[--top1];
						stack1[top1++] = CalcuateValue(a, stack2[--top2], b);
					}
				}
				top2--; // 左括号出栈
			}

			else if (CompareOperator(stack2[top2 - 1], s[i]) == -1) stack2[top2++] = s[i];// 栈顶元素优先级小于当前元素，当前元素入栈
			else if (CompareOperator(stack2[top2 - 1], s[i]) == 0) top2--;                // 特殊情况，连续两个！出现，直接出栈
			else if (CompareOperator(stack2[top2 - 1], s[i]) == 1)                        // 栈顶元素优先级大于当前元素，出栈
			{
				// 非运算特殊处理
				if (stack2[top2 - 1] == '!')
				{
					bool a = stack1[--top1];
					if (a == 1) stack1[top1++] = 0;
					else stack1[top1++] = 1;
					top2--, i--;
				}
				// 其他二元运算符运算
				else
				{
					bool b = stack1[--top1];
					bool a = stack1[--top1];
					stack1[top1++] = CalcuateValue(a, stack2[--top2], b);
					stack2[top2++] = s[i];
				}
			}
		}
	}
	// 最终数栈中仅留下一个数字，即最终运算结果
	return stack1[top1 - 1];
}

// 计算器Title展示
void PrintMenu ()
{
	printf("***************************************\n");
	printf("**                                   **\n");
	printf("**         欢迎进入逻辑运算软件      **\n");
	printf("**   (可运算真值表,主范式,支持括号)  **\n");
	printf("**                                   **\n");
	printf("**              用!表示非            **\n");
	printf("**              用&表示与            **\n");
	printf("**              用|表示或            **\n");
	printf("**             用^表示蕴含           **\n");
	printf("**             用~表示等值           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("请输入一个合法的命题公式（命题变元名称大小写敏感，请使用英文括号）:\n");

}

int main()
{
	// 计算器title展示
	PrintMenu();

	// 输入命题公式
	string expression;
	cin >> expression;

	// 构造真值表变量
	TruthTable truthTable(expression);

	// 输出真值表
	printf("\n输出真值表如下:\n \n");
	truthTable.PrintTruthTable();

	// 输出主范式
	truthTable.PrintPrincipalNormForms();

	return 0;
}