typedef struct
{
	char* brand;
	int size;
	char* type;
	int frequency;
	float voltage;
} ram;

enum
{
	
};

void init(ram** rams, int* N);

int inputSize(int* N);

void print(ram* rams, int* N);

void add(ram** rams, int* N);

void delete(ram** rams, int* N);

void sort(ram* rams, int N);
