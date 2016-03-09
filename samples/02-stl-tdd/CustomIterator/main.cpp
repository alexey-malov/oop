#include "GetlineIterator.h"
#include <iostream>
#include <algorithm>

using namespace std;


void main()
{
	copy(CGetlineIterator(cin), (CGetlineIterator()), ostream_iterator<string>(cout, "\n"));
}