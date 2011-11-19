#include <iostream>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace ::std;
using namespace ::boost;

template<class SampleType = float>
class metropolis_hastings
{
	private:
		boost::mt19937 rng;
		boost::normal_distribution<float> proposal;
		boost::uniform_real<float> uniform;  //BUG: uniform_real is problematic as it requires a range

		boost::variate_generator< boost::mt19937 , boost::normal_distribution <float> > *q;
		boost::variate_generator< boost::mt19937 , boost::uniform_real <float> > *r;

	public:
		metropolis_hastings() :
								q(new variate_generator< mt19937 , normal_distribution <float> > (rng, proposal)),
								r(new variate_generator< mt19937 , uniform_real <float> > (rng, uniform))
		{
		rng.seed(time(0));
		}

		float getsample (float (*P) (SampleType))
		{
			return getsample(P, 550);
		}

		float getsample (float (*P) (SampleType), int burnin)
			{
				//init
				float x = (*r)(); //BUG starting point should be random, not random in range (0..1]
				float p_x = P(x);
					for (int count = 0; count < burnin; count++)
				{
					//grab a sample from the proposal distribution Q(x)
					//do {
						float x_cand = x + (*q)();
						float p_x_cand = P(x_cand);
					//} while (p_x_cand

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

};

