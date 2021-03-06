/*Begin: code taken and updated from DynamicStringStack.h */
#include <string>
using namespace std;

struct StackNode
{
	int row, col;
	StackNode *next;
};


class DynamicStack
{
	private:
		StackNode *top;
		StackNode* GetTopPointer(DynamicStack myStack);

	public:
		DynamicStack(void);
		void push(int, int);
		void pop(int &, int &);
		bool isEmpty(void);
};
/*End: code taken from DynamicStringStack.h */