#include "mh.h"
#include "boost/math/distributions/normal.hpp"

#include "mh_tests.h"

using namespace std;
using namespace boost;

//test unnormalized uniform pdf
float float_uniform_pdf(float d)
{
	return 1;
}

//test zero pdf
float float_zero_pdf(float d)
{
	return 0;
}

//test normal pdf with m=5, s=1
float float_normal_pdf(double d)
{
	boost::math::normal dnormal(5,1);
	return 30*pdf(dnormal, d);
}

//test unnormalized uniform pdf
float double_uniform_pdf(double d)
{
	return 1;
}

//test zero pdf
float double_zero_pdf(double d)
{
	return 0;
}

//test normal pdf with m=5, s=1
float double_normal_pdf(double d)
{
	boost::math::normal dnormal(5,1);
	return 30*pdf(dnormal, d);
}

float int_uniform_pdf(int d)
{
	if (d > 5) 
		return 1;
	else if (d<0)
		return 0;
	else
		return 0.5;
}

int main(int argc, char* argv[])
{
	int count = 0;
	double sum = 0;
	int n_samples = 10000;

	metropolis_hastings<int> mh;

	for (int x=0; x < n_samples; x++)
	{
		int sample = mh.getsample(&int_uniform_pdf);
		sum+=sample;
		//cout << sample << endl;
		if (sample > 4.0f && sample < 6.0f)
			count++;
	}
	cout << count << "\t" << (sum/n_samples) << endl;
}
