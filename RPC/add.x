const MAX_N = 256;
typedef int Number;


struct addargs{
	Number i;
	Number j;
};

program ADDPROGRAM{
	version VERSION{
		Number ADD(addargs) = 1;
	}  = 1;
} = 8888;
