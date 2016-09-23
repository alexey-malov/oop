
typedef double Matrix2x2[2][2];

void Fn(Matrix2x2 mat)
{
	mat[0][0] = 3.0;
}

struct WrappedMatrix2x2
{
	Matrix2x2 items;
};

void Fn2(WrappedMatrix2x2 mat)
{
	mat.items[0][0] = 3.0;
}

void main()
{
	Matrix2x2 mat = {
		{1.0, 2.5},
		{4.5, 3.2}
	};
	assert(mat[0][0] == 1.0);
	assert(mat[0][1] == 2.5);
	assert(mat[1][0] == 4.5);
	assert(mat[1][1] == 3.2);

	Fn(mat);
	assert(mat[0][0] == 3.0);

	WrappedMatrix2x2 wrappedMat = {
		{
			{ 1.0, 2.5 },
			{ 4.5, 3.2 }
		} 
	};
	Fn2(wrappedMat);
	assert(wrappedMat.items[0][0] == 1.0);
}
