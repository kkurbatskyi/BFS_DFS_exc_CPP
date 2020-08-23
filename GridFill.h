#ifndef GRIDFILL_H
#define GRIDFILL_H

#include <iostream>
#include <queue>
#include <stack>

#define TESTING

using std::ostream;
using std::istream;
using std::stack;
using std::queue;

class Fill {
private:
	int** grid;
	int row;
	int col;

#ifdef TESTING
	const int BLACK = 1;
#else
	int BLACK;
#endif
public:

	struct Point {
		int i;
		int j;
	};

	Fill();
	Fill(int r, int c);

	void fillStack(int i, int j);

	void fillQueue(int i, int j);

	void fillRecursive(int i, int j);

	void fillStackInefficient(int i, int j);

	void printCanvas();

	friend std::ostream& operator<<(std::ostream& out, Fill f);
	friend std::istream& operator>>(std::istream& in, Fill& f);

	Fill(Fill& toCopy);
	Fill& operator=(Fill& toCopy);
	~Fill();
};



#endif // !GRIDFILL_H
