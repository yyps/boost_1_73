// boost_date_time.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//
//#include <iostream>
//#include <string>
//#include <boost/date_time/posix_time/posix_time.hpp>
//using namespace std;
//using namespace boost::posix_time;
//
//int main()
//{
//    /* 获取系统当前时间 */
//    ptime time = second_clock::local_time();
//    cout << to_iso_string(time) << endl;
//    cout << to_simple_string(time) << endl;
//    cout << to_iso_extended_string(time) << endl;
//    tm tm_ = to_tm(time); /* to tm */ 
//    cout << "year: " << tm_.tm_year + 1900 << endl;
//    cout << "Mon: " << tm_.tm_mon + 1 << endl;
//    cout << "day: " << tm_.tm_mday << endl;
//    cout << "hour: " << tm_.tm_hour << endl;
//    cout << "min: " << tm_.tm_min << endl;
//    cout << "sec: " << tm_.tm_sec << endl;
//}
// 

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <windows.h>
using namespace std;
class TEST
{
public:
	TEST()
	{
		cout << "Create Test" << endl;
	}
	~TEST()
	{
		cout << "Destroy Test" << endl;
	}
	shared_ptr<TEST> ptr2;
	int n1;
	int n2;
};

typedef  shared_ptr<TEST> TPtr;
//map<int, TPtr> g_maps;
unordered_map<int, TPtr> g_maps;

void push()
{
	TPtr ptr1(new TEST());
	g_maps.insert(pair<int, TPtr>(1, ptr1));
	TPtr ptr2(new TEST());
	g_maps.insert(pair<int, TPtr>(2, ptr2));
	TPtr ptr3(new TEST());
	g_maps.insert(pair<int, TPtr>(3, ptr3));
	TPtr ptr4(new TEST());
	g_maps.insert(pair<int, TPtr>(4, ptr4));

}

struct Heap_deleter
{
	void operator()(LPVOID p)
	{
		HeapFree(GetProcessHeap(), 0, p);
	}
}

int main()
{
	
	//push();
	//cout << "creat ok" << endl;
	////g_maps.erase(3);
	//g_maps.clear();
	//cout << "over" << endl;
	{
		shared_ptr<TEST> ptr;

	//	TEST* a = new TEST;
	//	a->n1 = 4;
		ptr = make_shared<TEST>();
		if (!ptr)
		{
			cout << "aaa" << endl;
		}
		ptr->ptr2 = ptr;
		cout << ptr->n1 << endl;
		cout << ptr->n2 << endl;

	//	ptr.reset();

		cout << "l1" << endl;
	}

	cout << "bbb" << endl;
	//TEST* t = (TEST*)::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TEST));
	
//	t = NULL;
//	HeapFree(GetProcessHeap(), 0, t);

//	shared_ptr<TEST> ptr(t, HeapFree);


	return 0;
}