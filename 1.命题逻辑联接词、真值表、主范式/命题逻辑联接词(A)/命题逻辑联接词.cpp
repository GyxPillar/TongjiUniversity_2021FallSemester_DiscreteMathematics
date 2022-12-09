// 2053385 高逸轩 //
#include <iostream>
#include "input_tools.h"
using namespace std;
int main()
{
	// 二元变量p q
	int p, q;

	while (1)
	{
		// Title展示
		printf("***************************************\n");
		printf("**                                   **\n");
		printf("**        欢迎进入逻辑运算程序       **\n");
		printf("**                                   **\n");
		printf("***************************************\n");


		// 获取p的值，通过getint函数处理了输入错误，保证了健壮性
		printf("\n  请输入P的值（0或1）,以回车结束:");
		p = getint(0, 1, "  P的值输入有误,请重新输入!\n  请输入P的值（0或1）,以回车结束:");
		cout << endl;

		// 获取q的值，通过getint函数处理了输入错误，保证了健壮性
		printf("\n  请输入Q的值（0或1）,以回车结束:");
		q = getint(0, 1, "  Q的值输入有误,请重新输入!\n  请输入Q的值（0或1）,以回车结束:");



		// 对p q进行二元运算，并输出结果
		printf("\n\n");
		printf("  合取:\n       P/\\Q = %d\n", p & q);                     // 合取式p∧q，在变量运算中为 p & q
		printf("  析取:\n       P\\/Q = %d\n", p | q);                     // 析取式p∨q，在变量运算中为 p | q
		printf("  条件:\n       P→Q = %d\n", (!p) | q);                   // 条件运算式p→q，即(!p)∨q，在变量运算中为(!p)|q
		printf("  双条件:\n       P<->Q = %d\n", ((!p) | q) & ((!q) | p)); // 双向条件运算p↔q，即(p→q)∧(q→p)，在变量运算中表示为((!p) | q) & ((!q) | p)


		// 判断是否进入下一次运算
		char c = '\0';
	judge:printf("\n是否继续运算?（y/n）");
		cin >> c;
		cin.clear();
		cin.ignore(1024, '\n');               // 清除缓存区，避免缓存区中的剩余字符对后续运行产生影响
		if (c == 'y')   system("cls");        // 选择了y，则继续运行，清屏
		else if (c == 'n')
		{
			printf("欢迎下次再次使用!\n");    // 选择了n，则退出，跳出循环
			break;
		}
		else
		{
			printf("输入错误,请重新输入!\n"); // 选择了其他选项，则重新输入用户选择
			goto judge;
		}
	}

	return 0;
}