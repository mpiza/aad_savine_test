// aad_full_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "aad.h"
#include "black_scholes.h"
#include "black_scholes_mc.h"


 // A simple Multiplier class
template < class T>
struct Multiplier
{
	const T multiplyBy;
	Multiplier(const double m) : multiplyBy(m) {}
	T operator () (const T y) const
{
		return multiplyBy * y;
	}
};

template <class T>
T f(T x[5])
{
	T y1 = x[2] * (5.0 * x[0] + x[1]);
	T y2 = log(y1);
	T y = (y1 + x[3] * y2) * (y1 + y2);
	return y;
};

template <class T>
T f2(T x[3])
{
	T y = (x[1]*x[2] * (5.0 * x[0] + x[1]) + 3.5*x[0])*(x[0]*x[2])*x[0]*x[2]*(x[2] + x[0]);

	return y;
};

template <class T>
T f3(T x[2])
{
	T y = (5.0 * x[1] * 7.0 * x[2]);

	return y;
};

int test1()
{
	// Instrumented code
	// Initialize tape first
	Number::tape->rewind();

	// Initialize inputs, including data members
	// Note that puts inputs on tape, as leave nodes
	Multiplier<Number> doubler(2.0);
	Number y(5.0);
	// The calculation itself, in this case, a simple product
	Number z = doubler(y);
	// Adjoint propagation
	z.propagateToStart();
	// Display results
	cout << z.value() << endl; // 10.0
	cout << y.adjoint() << endl; // 2.0
	cout << doubler.multiplyBy.adjoint() << endl; // 5.0

	return 0;
}

int test2()
{
	Number::tape->rewind();
	Number x[3] = { Number(2.0), Number(3.0), Number(4.0) };
	Number yy = f2(x);

	yy.propagateToStart();



	for (size_t i = 0; i < 3; ++i)
	{
		cout << "a" << i << " = " << x[i].adjoint() << endl;
	}

	return 0;


}

int test4()
{
	Number::tape->rewind();
	Number x[2] = {  Number(3.0), Number(4.0) };
	Number yy = f3(x);

	yy.propagateToStart();



	for (size_t i = 0; i < 2; ++i)
	{
		cout << "a" << i << " = " << x[i].adjoint() << endl;
	}

	return 0;


}

int test_bs_analytic()
{

	Number::tape->rewind();

	Number spot(1.0);
	Number rate(0.0);
	Number yield(0.0);
	Number vol(0.2);
	Number strike(1.0);
	Number mat(1.0);
	Number price;
	price = blackScholes(spot, rate, yield, vol, strike, mat);

	price.propagateToStart();

	cout << " Black Scholes Analytic " << endl; 

	cout << "price " << price.value() << endl;
	cout << "spot " << spot.value() << " spot_der " << spot.adjoint() << endl;
	cout << "rate " << rate.value() << " rate_der " << rate.adjoint() << endl;
	cout << "yield " << yield.value() << " yield_der " << yield.adjoint() << endl;
	cout << "vol " << vol.value() << " vol_der " << vol.adjoint() << endl;
	cout << "strike " << strike.value() << " strike_der " << strike.adjoint() << endl;
	cout << "mat " << mat.value() << " mat_der " << mat.adjoint() << endl;

	return 0;

}


int test_bs_mc()
{

	Number::tape->rewind();

	Number spot(1.0);
	Number rate(0.0);
	Number vol(0.2);
	Number strike(1.0);
	Number mat(1.0);
	Number price;
	int num_sims = 1000000;

	
	price = monte_carlo_call_price(num_sims, spot, strike, rate, vol, mat);

	price.propagateToStart();

	cout << " Black Scholes Monte Carlo " << endl;

	cout << "price " << price.value() << endl;
	cout << "spot " << spot.value() << " spot_der " << spot.adjoint() << endl;
	cout << "rate " << rate.value() << " rate_der " << rate.adjoint() << endl;
	cout << "vol " << vol.value() << " vol_der " << vol.adjoint() << endl;
	cout << "strike " << strike.value() << " strike_der " << strike.adjoint() << endl;
	cout << "mat " << mat.value() << " mat_der " << mat.adjoint() << endl;

	return 0;

}

int test_bs_all()
{

	Number::tape->rewind();

	Number spot(1.0);
	Number rate(0.0);
	Number yield(0.0);
	Number vol(0.2);
	Number strike(1.0);
	Number mat(1.0);
	Number price;
	price = blackScholes(spot, rate, yield, vol, strike, mat);

	price.propagateToStart();

	cout << " Black Scholes Analytic " << endl;

	cout << "price " << price.value() << endl;
	cout << "spot " << spot.value() << " spot_der " << spot.adjoint() << endl;
	cout << "rate " << rate.value() << " rate_der " << rate.adjoint() << endl;
	cout << "yield " << yield.value() << " yield_der " << yield.adjoint() << endl;
	cout << "vol " << vol.value() << " vol_der " << vol.adjoint() << endl;
	cout << "strike " << strike.value() << " strike_der " << strike.adjoint() << endl;
	cout << "mat " << mat.value() << " mat_der " << mat.adjoint() << endl;

	Number::tape->rewind();
	int num_sims = 100000;

	Number spot2(1.0);
	Number rate2(0.0);
	Number yield(0.0);
	Number vol(0.2);
	Number strike(1.0);
	Number mat(1.0);
	Number price;

	price = monte_carlo_call_price(num_sims, spot, strike, rate, vol, mat);

	price.propagateToStart();

	cout << " Black Scholes Monte Carlo " << endl;

	cout << "price " << price.value() << endl;
	cout << "spot " << spot.value() << " spot_der " << spot.adjoint() << endl;
	cout << "rate " << rate.value() << " rate_der " << rate.adjoint() << endl;
	cout << "vol " << vol.value() << " vol_der " << vol.adjoint() << endl;
	cout << "strike " << strike.value() << " strike_der " << strike.adjoint() << endl;
	cout << "mat " << mat.value() << " mat_der " << mat.adjoint() << endl;

	return 0;

}

int main()
{
	
	//test_bs_analytic();
	//test_bs_mc();
	test_bs_all();

	return 0;
}

