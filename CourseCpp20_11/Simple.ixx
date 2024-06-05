export module Simple;

export int square(int x);

export template<typename T> inline T Max(T x, T y) {
	return x < y ? y : x;
}

//template int Max<int>(int a, int b);