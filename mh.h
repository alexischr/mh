#ifndef MH_METROPOLIS_HASTINGS
#define MH_METROPOLIS_HASTINGS

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
		boost::normal_distribution<double> proposal;
		//boost::uniform_real<float> uniform;  //BUG: uniform_real is problematic as it requires a range

		boost::variate_generator< boost::mt19937 , boost::normal_distribution <double> > *q;
		//boost::variate_generator< boost::mt19937 , boost::uniform_real <float> > *r;

	public:
		metropolis_hastings()
		{
			rng.seed(time(0));
			//can't put anything in the initializer because the rng needs to be seeded first of all			
			q = new variate_generator< mt19937 , normal_distribution <double> > (rng, proposal);
		}
		
		~metropolis_hastings()
		{
				delete q;
		}
		
		SampleType getproposedsample (SampleType x)
		{
			SampleType pr = x + static_cast<SampleType>((*q)());
			return pr;
		}
		
		SampleType getproposedsample (int x, vector<SampleType> *v)
		{
			SampleType pr;
			
			do
			{
				pr = x + static_cast<SampleType>((*q)());
			} while (pr < 0 || pr > v->size());
			
			return pr;		
		}
		
		void getinitial(double *x)
		{
			*x = 0.0;
		}
		
		void getinitial(float *x)
		{
			*x = 0.0f;
		}
		
		void getinitial(int *x)
		{
			*x = 0;
		}
		
		SampleType getsample (float (*P) (SampleType))
		{
			return getsample(P, 500);
		}
		
		float chance()
		{
			//return (*r)();
			return (float)rand()/RAND_MAX;
		}

		SampleType getsample (float (*P) (SampleType), int burnin, vector<SampleType> *v)
		{
				//init
				SampleType x;
				getinitial(&x);

				float p_x = P((*v)[x]);
								
				for (int count = 0; count < burnin; count++)
				{
					//grab a sample from the proposal distribution Q(x)
					SampleType x_cand = getproposedsample(x,v);
					float p_x_cand = P((*v)[x_cand]);
					
					if ( (p_x_cand / p_x) > chance())
					{
						//cout << "Accepted!" << x << "\t" << x_cand << endl;
						x = x_cand;
						p_x = p_x_cand;
					}
					/*else
						cout << "Rejected!" << endl; */
				}
				return x;
		}
			
		SampleType getsample (float (*P) (SampleType), int burnin)
			{
				//init
				SampleType x;
				getinitial(&x);

				float p_x = P(x);
								
				for (int count = 0; count < burnin; count++)
				{
					//grab a sample from the proposal distribution Q(x)
					SampleType x_cand = getproposedsample(x);
					float p_x_cand = P(x_cand);
					
					if ( (p_x_cand / p_x) > chance())
					{
						//cout << "Accepted!" << x << "\t" << x_cand << endl;
						x = x_cand;
						p_x = p_x_cand;
					}
					/*else
						cout << "Rejected!" << endl; */
				}
				return x;
		}

};

#endif

