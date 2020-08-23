#include "GridFill.h"
#include <queue>
#include <stack>
#include <string>
#include <iomanip>

using std::ostream;
using std::istream;
using std::stack;
using std::queue;

Fill::Fill()
{
	row = 0;
	col = 0;
	grid = nullptr;

	#ifndef TESTING
		BLACK = 1;
	#endif
}

Fill::Fill(int r, int c)
{
	row = r;
	col = c;
	grid = new int*[r];
	for (int i = 0; i < r; i++) {
		grid[i] = new int[c];
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			grid[i][j] = 0;

	#ifndef TESTING
		BLACK = 1;
	#endif
}

void Fill::fillStack(int i, int j)
{
	stack<Point> st;
	st.push({ i, j });
	//if the selected pixel is black, we dont paint anything
	if (grid[i][j] != 0) st.pop();

	//go to the right then top then left then bottom
	//while there are unpainted elements
	do
	{
		//paint black	

		#ifndef TESTING
		if (grid[st.top().i][st.top().j] == 0)
		{
			grid[st.top().i][st.top().j] = BLACK++;
		}
		#else
			grid[st.top().i][st.top().j] = BLACK;
		#endif
			//right
		if (st.top().j < col - 1 && grid[st.top().i][st.top().j + 1] == 0)
		{
			st.push({ st.top().i, st.top().j + 1});
		}
		else 
			//top
			if (st.top().i > 0 && grid[st.top().i - 1][st.top().j] == 0)
			{
				st.push({ st.top().i - 1, st.top().j });
			}
			else
				//left
				if (st.top().j > 0 && grid[st.top().i][st.top().j - 1] == 0)
				{
					st.push({ st.top().i, st.top().j - 1 });
				}
				else
					//bottom
					if (st.top().i < row - 1 && grid[st.top().i + 1][st.top().j] == 0)
					{
						st.push({ st.top().i + 1, st.top().j });
					}
					else
						//if all the "pixels" arount current is black, backtrack
						{
							st.pop();
						}

	} while (!st.empty());

}

void Fill::fillQueue(int i, int j)
{
	queue<Point> que;
	que.push({i, j});
	//if the selected pixel is black, we dont paint anything
	if (grid[i][j] != 0) que.pop();

	while (!que.empty())
	{
		#ifndef TESTING
		if (grid[que.front().i][que.front().j] == 0)
		{
			grid[que.front().i][que.front().j] = BLACK++;
		}
		#else
			grid[que.front().i][que.front().j] = BLACK;
		#endif
		//right
		if (que.front().j < col - 1 && grid[que.front().i][que.front().j + 1] == 0)
		{
			que.push({ que.front().i, que.front().j + 1 });
		}
		
		//top
		if (que.front().i > 0 && grid[que.front().i - 1][que.front().j] == 0)
		{
			que.push({ que.front().i - 1, que.front().j });
		}
			
		//left
		if (que.front().j > 0 && grid[que.front().i][que.front().j - 1] == 0)
		{
			que.push({ que.front().i, que.front().j - 1 });
		}
				
		//bottom
		if (que.front().i < row - 1 && grid[que.front().i + 1][que.front().j] == 0)
		{
			que.push({ que.front().i + 1, que.front().j });
		}

		//move to the next element
		que.pop();
	}
}

void Fill::fillRecursive(int i, int j)
{
	//if the selected pixel is black, we dont paint anything
	if (grid[i][j] != 0) return;
	#ifndef TESTING
		grid[i][j] = BLACK++;
	#else
		grid[i][j] = BLACK;
	#endif
	//right
	if (j < row - 1 && grid[i][j + 1] == 0)
	{
		fillRecursive(i, j + 1);
	}
	//top
	if (i > 0 && grid[i - 1][j] == 0)
	{
		fillRecursive(i - 1, j);
	}
	//left
	if (j > 0 && grid[i][j - 1] == 0)
	{
		fillRecursive(i, j - 1);
	}
	//bottom
	if (i < col - 1 && grid[i + 1][j] == 0)
	{
		fillRecursive(i + 1, j);
	}
}

void Fill::fillStackInefficient(int i, int j)
{
	/*
	stack<Point> st;
	st.push({ i, j });

	while (!st.empty())
	{

		#ifndef TESTING
			if (grid[st.top().i][st.top().j] == 0)
			{
				grid[st.top().i][st.top().j] = BLACK++;
			}
		#else
			grid[st.top().i][st.top().j] = BLACK;
		#endif
			
		st.pop();
		//right
		if (st.top().j < col - 1 && grid[st.top().i][st.top().j + 1] == 0)
		{
			st.push({ st.top().i, st.top().j + 1 });
		}
		 
		//top
		if (st.top().i > 0 && grid[st.top().i - 1][st.top().j] == 0)
		{
			st.push({ st.top().i - 1, st.top().j });
		}
			 
		//left
		if (st.top().j > 0 && grid[st.top().i][st.top().j - 1] == 0)
		{
			st.push({ st.top().i, st.top().j - 1 });
		}
				 
		//bottom
		if (st.top().i < row - 1 && grid[st.top().i + 1][st.top().j] == 0)
		{
			st.push({ st.top().i + 1, st.top().j });
		}
					
		
	}
	*/
}

Fill::Fill(Fill & toCopy)
{
	row = toCopy.row;
	col = toCopy.col;
	grid = new int*[row];
	for (int i = 0; i < row; i++) {
		grid[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			grid[i][j] = toCopy.grid[i][j];

	#ifndef TESTING
		BLACK = 1;
	#endif
}

Fill& Fill::operator=(Fill & toCopy)
{
	row = toCopy.row; 
	col = toCopy.col;
	int** newGrid = new int*[row];
	for (int i = 0; i < row; i++)
	{
		newGrid[i] = new int[col];
	}
	grid = newGrid;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			grid[i][j] = toCopy.grid[i][j];

	return *this;
}

Fill::~Fill()
{
	for (int i = 0; i < row; i++) 
	{
		delete[] grid[i];
	}
}

void Fill::printCanvas()
{
	std::string str = "";

	for (int i = 0; i < col * 3 + 2; i++)
	{
		str += std::string("_");
	} 
	std::cout << str << "\n";
	for (int i = 0; i < row; i++)
	{
		std::cout << "|";
		for (int j = 0; j < col; j++)
		{
			#ifndef TESTING
				std::cout << std::setw(3) << grid[i][j];
			#else
				std::cout << grid[i][j] << " ";
			#endif
		}
		std::cout << "|" << "\n";
	}
	std::cout << str << "\n";
}

std::ostream & operator<<(std::ostream & out, Fill f)
{
	for (int i = 0; i < f.row; i++)
	{
		for (int j = 0; j < f.col; j++)
		{
			#ifndef TESTING
				out << std::setw(3) << f.grid[i][j];
			#else
				out << f.grid[i][j] << ' ';
			#endif
		}
		out << '\n';
	}

	return out;
}

std::istream & operator>>(std::istream & fin, Fill& f)
{
	int row, col;	

	fin >> row;
	fin >> col;

	Fill fTemp(row, col);
	f = fTemp;

	for (int i = 0; i < f.row; i++)
	{
		for (int j = 0; j < f.col; j++)
		{
			fin >> f.grid[i][j];
		}
	}

	return fin;
}
