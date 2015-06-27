#include <ctype.h>
#include <iostream.h>
#include <iomanip.h>
#include <math.h>
#include <string.h> 
#include <time.h>

void s();
void t();
double simpson (double, double, int);
double trapeze (double, double, int);
void   get_conditionsS(double &, double &, int &);
void   get_conditionsT(double &, double &, int &);
double user_function (double);

//====================================================================== 
// Main program
//====================================================================== 

void simpntrapMain()
{
	char ch;
	cout << "Enter s for simpson's rule or t for trapezoidal: ";
	cin.get(ch);
	ch = tolower(ch);
	
	switch(ch)
	{
	case 's':
		s();
		break;
	case 't':
		t();
		break;
	default:
		cout << "S or T!";
		break;
	}
	
	return 0;
}

void s()
{
		clock_t start, finish;
	double  xmin, xmax, value, time_taken;
	int     intervals;
	get_conditionsS(xmin, xmax, intervals);
  
  start = clock();
  
  // Do the calculation 50000 times so that the time taken is a few
  // seconds, rather than a few milliseconds.
  for (unsigned long i = 0 ; i < 50000; i++) 
  {
    value = simpson (xmin, xmax, intervals);
  }
  
  finish = clock();
  time_taken = (finish - start) / double(CLOCKS_PER_SEC);
  
  cout << setprecision(6) 
       << "Successful integration, value = " << value << endl
       << "Time for 500 Simpson's rule calculations (" << intervals
       << " intervals) was " << time_taken << " seconds" << endl;
}

void t()
{
		clock_t start, finish;

	double  xmin, xmax, value, time_taken;
	int     intervals;

	  get_conditionsT(xmin, xmax, intervals);
 
  start = clock();      
  
  // Do the calculation 50000 times so that the time taken is a few
  // seconds, rather than a few milliseconds.
  for (unsigned long i = 0 ; i < 50000; i++) 
  {
    value = trapeze (xmin, xmax, intervals);
  }
  
  finish = clock();
  time_taken = (finish - start) / double(CLOCKS_PER_SEC);

  cout << setprecision(6) 
       << "Successful integration, value = " << value << endl
       << "Time for 500 trapezoidal calculations (" << intervals
       << " intervals) was " << time_taken << " seconds" << endl;
}
//====================================================================== 

void get_conditionsS(double & xmin, double & xmax, int & intervals)
{              
  double temp;
  
  cout << "Simpson's rule integration" << endl
       << "Input the values of x between which the "
          "function is to be integrated:" << endl
       << "X1 = ";
  cin  >> xmin;
  cout << "X2 = ";
  cin  >> xmax;
  
  if (xmax < xmin)
  { 
    // swap the values of xmin and xmax
    temp = xmax;
    xmax = xmin;
    xmin = temp;
  }
  
  do
  {
    cout << "Number of intervals (1 or more) : ";
    cin  >> intervals;
  }
  while (intervals <= 0);
}
void   get_conditionsT(double & xmin, double & xmax, int & intervals)
{              
  double temp;
  
  cout << "Trapezoid rule integration" << endl
       << "Input the values of x between which the "
          "function is to be integrated:" << endl
       << "X1 = ";
  cin  >> xmin;
  cout << "X2 = ";
  cin  >> xmax;
  
  if (xmax < xmin)
  { 
    // swap the values of xmin and xmax
    temp = xmax;
    xmax = xmin;
    xmin = temp;
  }
  
  do
  {
    cout << "Number of intervals (1 or more) : ";
    cin  >> intervals;
  }
  while (intervals <= 0);
}
 
//====================================================================== 
//  Procedure to use Simpson's rule to integrate the function defined
//  in function user_fun.  Returns the value of the integral 
//
//  lowerx, upperx = range of function
//  intervals      = number of intervals to use (N.b, since Simpson's
//                   rule only works for an odd number of intervals,
//                   this value is doubled and one is added for use 
//                   in the calculation). 
//====================================================================== 

double simpson (double lowerx, double upperx, int intervals)
{
  double result, gap, x;
    
  gap    = (upperx - lowerx) / (2.0 * intervals);
  result = user_function(lowerx) + user_function(upperx);
  x      = lowerx + gap;
  
  for (int i = 1; i < intervals; i++)
  {
    result += (4.0 * user_function(x));
    x      += gap;
    result += (2.0 * user_function(x));
    x      += gap;
  }
  
  result += (4.0 * user_function(x));
  
  result *= (gap / 3.0);
  return result;
}
    
//====================================================================== 

double user_function (double x)
{
  return x*x*x - 3.0*x*x - x + 9.0;
}


double trapeze (double lowerx, double upperx, int intervals)
{
  double result, gap, x;
    
  gap    = (upperx - lowerx) / intervals;
  result = user_function(lowerx) + user_function(upperx);
  x      = lowerx + gap;
  
  for (int i = 1; i < intervals; i++)
  {
    result += (2.0 * user_function(x));
    x      += gap;
  }
  
  result *= (gap / 2.0);
  return result;
}