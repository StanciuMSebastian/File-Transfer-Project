#include "Server.h"

int main()
{
	Server* s = s->getInstance();

	for (int i = 0; i < 100; i++)
	{
		s->ListenForNewConnection();
	}

	system("pause");

	return 0;
}