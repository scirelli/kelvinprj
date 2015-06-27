#include <iostream.h>
#include <iomanip.h>
#include <math.h>
#include <string.h> 
#include <time.h> 

#define MIN_TOLERANCE 1.0e-10

int    newton_raphson (double, double, int, int &, double &, 
         double &, char []);
void   get_conditions(double &, double &, int &); 
double user_function(double);
double user_derivative(double);

void newtonMain()
{
  clock_t start, finish;
  double  root, value, estimate, tolerance, time_taken;
  int     iterations, max_iterations, error;
  char    err_string[80];
 
  get_conditions(estimate, tolerance, max_iterations);
  
  start = clock();
  
  // Do the calculation 50000 times so that the time taken is a few
  // seconds, rather than a few milliseconds.
  for (unsigned long i = 0 ; i < 50000; i++) 
  {
    error = newton_raphson(estimate, tolerance, max_iterations, 
      iterations, root, value, err_string);
  }
  
  finish = clock();
  time_taken = (finish - start) / double(CLOCKS_PER_SEC); 

// Print out the number of iterations, or an error message } 
  
  if (error)
  {
    cout << "ERROR : " << err_string << endl;
  }
  else
  {
    cout << "Successful calculation, " << iterations
         << " iterations." << endl
         << "The root is " << root << endl
         << "The value of the function at this point is "
         << setiosflags(ios::fixed) << setprecision(2) 
         << value << endl
         << "Time for 1000 Newton-Raphson calculations was " 
         << time_taken << " seconds." << endl;         
  }
  
  return 0;
}

//====================================================================== 

void get_conditions(double & estimate, double & tolerance, 
  int & max_iterations)
{
  cout << "Initial estimate of root : ";
  cin  >> estimate;   
  
  cout << "Calculation will terminate when f(x) is less than the"
       << endl << "tolerance level input by the user." << endl;
  
  do
  {
    cout << "Tolerance : ";
    cin  >> tolerance;
    if (tolerance <= MIN_TOLERANCE)
    {
      cout << "ERROR : tolerance must be greater than "
           << MIN_TOLERANCE << endl;
    }
  }
  while (tolerance <= MIN_TOLERANCE);

  do
  {
    cout << "Maximum number of iterations (1 or more) : ";
    cin  >> max_iterations;
  }
  while (max_iterations < 1);
}

//====================================================================== 
// Function to find a root of an equation by the Newton-Raphson method.
//   estimate       : User's initial estimate of the root.
//   tolerance      : Tolerance level of the answer.
//   max_iterations : Maximum number of iterations to be performed.     
//   root           : Final value of the root.
//   value          : Value of user_funct at the root.
//   iterations     : Number of iterations performed.
//   err_string     : Error message.
//
// Function returns 1 (true) if an error has been encountered. 
//====================================================================== 

int newton_raphson (double estimate, double tolerance, int max_iterations, 
                    int & iterations, double & root, double & value, 
                    char err_string[]) 
{ 
  double deriv;

  for (iterations = 1; iterations <= max_iterations; iterations++)
  {    
    value = user_function(estimate);
    deriv = user_derivative(estimate);
    
    if (fabs(deriv) < 1.0e-10)
    {
      strcpy(err_string, "Slope was zero at some point");
      return 1;
    }
   
    if (fabs(value) <= tolerance)
    { 
      // The root has been found
      root = estimate;
      return 0;
    }
    else
    {
      estimate -= value / deriv;
    }
  }
 
  strcpy(err_string, "Maximum number of iterations was exceeded");
  return 1;
}

//======================================================================
// Function to return the value of the equation [y = cos(x) - x] 

double user_function (double x)
{
  return cos(x) - x;
} 

//======================================================================
// Function to return the derivative of the equation [y = cos(x) - x] 

double user_derivative (double x)
{
  return -sin(x) - 1.0;
}

