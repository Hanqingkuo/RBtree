#include <iostream>
#include "readblackTree.h"
using namespace std;
int main()
{
	int x = 0;
	RBTree rb;
	rb.InitRoot();
	for(int i = 0; i < 5; ++i)
	{
		rb.Insert(i+2);
	}
	//rb.Insert(1);
	rb.Show();
	std::cout<<"please enter you need del number:";
	
	while(std::cin>>x,x != -1)
	{
		rb.Delete(x);
		rb.Show();
	}
}