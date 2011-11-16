#include <iostream>
#include "boost/math/distributions/normal.hpp"
using boost::math::normal; 
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace ::std;

//test unnormalized uniform pdf 
float float_uniform_pdf(float d)
{
	return 1;
}

//test normal pdf with m=5, s=1
float float_normal_pdf(float d)
{
	normal dnormal(5,1);
	return 30*pdf(dnormal, d);  
}

class metropolis_hastings
{
	private:
		boost::mt19937 rng;
		boost::normal_distribution<float> proposal; 
		boost::uniform_real<float> uniform;  //BUG: uniform_real is problematic as it requires a range
		
		boost::variate_generator< boost::mt19937 , boost::normal_distribution <float> > *q;
		boost::variate_generator< boost::mt19937 , boost::uniform_real <float> > *r;
				
	
	public:
		metropolis_hastings()
		{
			rng.seed(time(0));
			q = new boost::variate_generator< boost::mt19937 , boost::normal_distribution <float> > (rng, proposal);
			r = new boost::variate_generator< boost::mt19937 , boost::uniform_real <float> > (rng, uniform); 
		}
		
		float getsample (float (*P) (float), int burnin)
		{
			//init
			float x = (*r)(); //BUG starting point should be random, not random in range (0..1] 
			float p_x = P(x);

			for (int count = 0; count < burnin; count++)
			{
				//grab a sample from the proposal distribution Q(x)
				float x_cand = x + (*q)();
				float p_x_cand = P(x_cand);

				if ( (p_x_cand / p_x) > (*r)())
				{
					//cout << "Accepted!" << x << "\t" << x_cand << endl;
					x = x_cand;
					p_x = p_x_cand;
				}
				//else
					//cout << "Rejected!" << endl;
			}

			return x;
	}
	
	float getsample (float (*P) (float))
	{
		return getsample(P, 50);
	}
};

int main(int argc, char* argv[])
{
	int count = 0;
	float sum = 0;
	
	metropolis_hastings mh;
	
	
	for (int x=0; x < 1000; x++)
	{
		float sample = mh.getsample(&float_normal_pdf);
		sum+=sample;
		//cout << sample << endl;
		if (sample > 4.0f && sample < 6.0f)
			count++;
	}
	cout << count << "\t" << (sum/1000) << endl;
	
}
