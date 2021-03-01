#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int modpow(int64_t base, int exp, int64_t mod)
{
	int64_t result = 1;
	base = (base < mod ? base : base%mod);
	for (;;)
	{
		if (exp & 1)
		{
			result *= base;
			result = (result < mod ? result : result%mod);
		}
		exp >>= 1;
		if (!exp)
			break;

		base *= base;
		base = (base < mod ? base : base%mod);
	}

	return result;
}

char line[1024];
int main() {

	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "Can't open input file\n");
		return 1;
	}


	int start;
	fgets(line, sizeof(line), fin);//ignore first line


	fgets(line, sizeof(line), fin);

	fclose(fin);

	regex sep(",|\\s");

	regex_token_iterator<string::iterator> rend;

	vector<int> mods;
	vector<int> values;

	string s(line);

	int v, a;
	int i = 0;
	char *endptr;
	for (regex_token_iterator<string::iterator> d(s.begin(), s.end(), sep, -1); d != rend; d++) {
		if (d->str()[0] != 'x') {
			v = strtol(d->str().c_str(), &endptr, 10);
			values.push_back(v);
			a = i;
			while (a < 0)
				a += v;
			mods.push_back(a);
		}
		i--;
	}

	int64_t n = 1;
	for (int p : values)
		n *= p;

	vector<int64_t> yvec;
	vector<int> zvec;

	for (int p : values) {
		int64_t y = n / p;
		yvec.push_back(y);
		int z = modpow(y, p - 2, p); //Fermat
		zvec.push_back(z);
	}

	int64_t x = 0;
	for (i = 1; i < mods.size(); i++) {
		x = (x + yvec[i] * mods[i] * zvec[i]) % n;
	}

	printf("%" PRId64 "\n", x);

	return 0;
}