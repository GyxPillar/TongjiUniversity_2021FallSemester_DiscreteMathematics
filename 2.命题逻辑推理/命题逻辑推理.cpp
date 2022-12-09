// 2053385 高逸轩 //

#include <iostream>
using namespace std;

int main()
{
	cout << "命题如下：" << endl;
	cout << "（1）营业员A或B偷了手表" << endl;
	cout << "（2）若A作案，则作案不在营业时间" << endl;
	cout << "（3）若B提供的证据正确，则货柜未上锁" << endl;
	cout << "（4）若B提供的证据不正确，则作案发生在营业时间" << endl;
	cout << "（5）货柜上了锁" << endl;

	cout << endl << "用命题变元表示如下：" << endl;
	cout << "a : 营业员A偷了手表" << endl;
	cout << "b : 营业员B偷了手表" << endl;
	cout << "c : 作案不在营业时间" << endl;
	cout << "d : B提供的证据正确" << endl;
	cout << "e : 货柜未上锁" << endl;

	cout << endl << "命题与命题变元的对应表示为：" << endl;
	cout << "（1）营业员A或B偷了手表                         ->   a  | b " << endl;
	cout << "（2）若A作案，则作案不在营业时间                ->   a -> c" << endl;
	cout << "（3）若B提供的证据正确，则货柜未上锁            ->   d -> e" << endl;
	cout << "（4）若B提供的证据不正确，则作案发生在营业时间  ->   !d->!c" << endl;
	cout << "（5）货柜上了锁                                 ->   !e" << endl;

	for (int a = 0; a<=1; a++)
		for (int b= 0; b<=1 ;b++)
			for (int c = 0; c<=1 ; c++)
				for (int d = 0; d<=1 ; d++)
					for (int e = 0; e<=1 ; e++)
						if ((a | b) & (!a | c) & (!d | e) & (d | !c) & (!e))  // 在计算时，a->b转换为!a|b
						{
							cout << endl << "a=" << a << "，b=" << b << "时，满足以上全部条件" << endl;
							cout << "根据以上推理：";
							a ? cout << "A偷了手表" : cout << "A没有偷手表";  // 若a！=0,则A偷了手表，否则A没有偷
							cout << "    ";
							b ? cout << "B偷了手表" : cout << "B没有偷手表";  // 若b！=0,则B偷了手表，否则B没有偷
							cout << endl;
						}

	return 0;

}