//-----------------------------------------------------------------------//
//Program that solve quadratic equation                                  //
//User enter the coefficients of equation and program return             //
//what equation it is (quadratic or not) and how many roots it has       //
//and this roots/root                                                    //
//-----------------------------------------------------------------------//

/*!
\title
    \author Kuteinikov SirGay
    \version 3.6
    \date 07.10.2021
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*! ********************************************************************
\brief Structure of data for unit test
\details Is used in function "Unit_test ()"
************************************************************************/

struct test_data {
    double coef_a; ///< senior coefficient
    double coef_b; ///< middle coefficient
    double coef_c; ///< junior coefficient

    double root_1; ///< first root if it exist, else - 0
    double root_2; ///< second root if it exist, else - 0

    int case_of_solution;///< situation of solution
};

#define NO_QUADRO_INF_ROOTS 0
#define NO_QUADRO_NO_ROOTS 1
#define NO_QUADRO_ONE_ROOT 2
#define QUADRO_NO_ROOTS 3
#define QUADRO_ONE_ROOT 4
#define QUADRO_TWO_ROOTS 5
#define ERROR_NUMBER_OF_SOLUTIONS 6



struct test_data test[10] = {
    //coef_a      //coef_b    //coef_c        //root_1  //root_2    //case_of_solution
    {1,            2,           1,            -1,        0,         QUADRO_ONE_ROOT},
    {0.000000003,  57,         -114,           2,        0,         NO_QUADRO_ONE_ROOT},
    {0.000000001,  0.000000003, 0.000000002,  -1,       -2,         QUADRO_TWO_ROOTS},
    {1,            5,           6,            -2,       -3,         QUADRO_TWO_ROOTS},
    {0,            60,          45,           -0.75,     0,         NO_QUADRO_ONE_ROOT},
    {0,            0,           0,             0,        0,         NO_QUADRO_INF_ROOTS},
    {0,            0,           300,           0,        0,         NO_QUADRO_NO_ROOTS},
    {1,           -4,           4,             2,        0,         QUADRO_ONE_ROOT},
    {1,            0,          -4,            -2,        2,         QUADRO_TWO_ROOTS},
    {1,            2,           2,             0,        0,         QUADRO_NO_ROOTS},
};


/*!
Function that introduces the program
*/

void Introduction (void);


/*!
Function that asks user to start or not.
\return
1 - if user print "1" (agree to start solving)\n
0 - if user choose "0" (refused from solving)
*/

int Start_or_not (void);


/*!
Function that runs function "Scan_one_coefficient" three times to read three coefficient.
\param coef_a, coef_b, coef_c - addresses of coefficients of equation
*/

void Scan_coefficients (double* coef_a, double* coef_b, double* coef_c);


/*!
Function that checks input (and repeats him if necessary) and returns right coefficients in function "Scan_coefficients".
\param coef_name - name of coefficient
\return coef - value of input coefficient
*/

double Scan_one_coefficient (char coef_name [8]);


/*!
Function that solves equation by "Solve_quadratic ()" and "Solve_linear ()" and determines roots and case of solution.
\param coef_a, coef_b, coef_c - values of coefficients
\param root_1, root_2 - addresses od roots
\return value of case_of_solution (look at "Output_solution ()" documentation)
*/

int Solve_equation (double coef_a, double coef_b, double coef_c, double *root_1,
                      double *root_2);


/*!
Function that put solution oh screen of equation.
\param root_1, root_2 - roots of equation
\param case_of_solution - the parameter situation of solution:\n
NO_QUADRO_INF_ROOTS (0) - The equation isn't quadratic and has infinitely many roots;\n
NO_QUADRO_NO_ROOTS (1) - The equation isn't quadratic and has no roots;\n
NO_QUADRO_ONE_ROOT (2) - The equation isn't quadratic and has only one root;\n
QUADRO_NO_ROOTS (3) - The equation is quadratic and has no roots;\n
QUADRO_ONE_ROOT (4) - The equation is quadratic and has only one root;\n
QUADRO_TWO_ROOTS (5) - The equation is quadratic and has only two roots.
*/


void Output_solution (double root_1, double root_2, int case_of_solutionj);


/*!
Function that ask user to continue work or stop.
\return
1 - if user print "1" (agree to continue working)\n
0 - if user print "0" (refused from continue)
*/

int Continue_or_not (void);


/*!
Function that get only "1" or "0".
\return
1 - if user print "1"
0 - if user print "0"
*/
int Get_user_choice (void);


/*!
Function that find greatest of absolute value coefficient and divide all coefficients on that coefficient
\param coef_a, coef_b, coef_c - addresses of coefficients of equation
*/

void Make_new_coefficients (double* coef_a, double* coef_b, double* coef_c);


/*!
Function that solve equation, if it is linear.
\param coef_b, coef_c - value of coefficients
\param root_1 - address of first root
\return value of case_of_solution (look at "Output_solution ()" documentation)
*/

int Solve_linear (double coef_b, double coef_c, double* root_1);


/*!
Function that solve quadratic case of equation.
\param coef_a, coef-b, coef_c - value of coefficients
\param discriminant - value of discriminant
\param root_1, root_2 - address of roots
\return value of case_of_solution (look at "Output_solution ()" documentation)
*/

int Solve_quadratic (double coef_a, double coef_b, double coef_c,
                       double* root_1, double* root_2);


/*!
Function that finds discriminant if equation is quadratic.
\param coef_a, coef_b, coef_c - value of coefficients
\return value of discriminant
*/

double Find_the_discriminant (double coef_a, double coef_b, double coef_c);


/*!
Function that check is number close to zero.
\param var - variable
\return
1 - if input number close to zero\n
0 - if not
*/

int Zero_check (double var);


/*!
Function that clear input buffer.
*/

void Clear_buffer (void);


/*!
Unit test.for "Solve_equation ()"
\param test_data test struct with data to test
\return
1 - if test was succesful
0 - if test was not succesful
*/

int Unit_test (struct test_data test);


/*!
Function that check equality of two numbers of type double.
\param var1, var2 - variables
\return
0 - if numbers aren't equal\n
1 - if numbers are equal
*/

int Double_epsilon_check (double var_1, double var_2);


/*!
Function that runs unit test.
*/

void Run_unit_test (void);



//-------------------------------------------------------------------------------------
int main (void)
{
    double coef_a = 0, coef_b = 0, coef_c = 0, root_1 = 0, root_2 = 0;

    int case_of_solution = ERROR_NUMBER_OF_SOLUTIONS;

    Run_unit_test ();

    Introduction ();

    if (Start_or_not () == 0)
    {
        return 0;
    }
    else
    {
        do {
        Scan_coefficients (&coef_a, &coef_b, &coef_c);
        case_of_solution = Solve_equation (coef_a, coef_b, coef_c, &root_1, &root_2);
        Output_solution (root_1, root_2, case_of_solution);

        } while (Continue_or_not () != 0);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
void Introduction (void)
{
    printf ("Hello user, I am program that can solve every quadratic equation.\n");
    printf ("Quadratic equation look like: A*x^2 + B*x + C = 0.\n");
    printf (" A call senior coefficient,\n B call average coefficient,\n C call junior coefficient.\n");
    printf ("Do you want solve equation?\n If Yes, print: 1\n  If No, print: 0\n ");
}

//--------------------------------------------------------------------------------------------------------------
int Start_or_not (void)
{
    int user_choice_1 = 0;

    user_choice_1 = Get_user_choice ();
    switch (user_choice_1) {

        case 0:
            printf ("Ok((( Bye(( No, I don't cry((( I am just stupid machine((((");
            return 0;
            break;

        case 1:
            return 1;
            break;

       default:
            printf ("Fuck you");
            return 300;
            break;
            }
}

//----------------------------------------------------------------------------------------------------------
void Scan_coefficients (double* coef_a, double* coef_b, double* coef_c)
{
    printf ("Enter the coefficients of quadratic equation (according to your position in the company).\n");
    *coef_a = Scan_one_coefficient ("senior");
    *coef_b = Scan_one_coefficient ("middle");
    *coef_c = Scan_one_coefficient ("junior");
}

//-----------------------------------------------------------------------------------------------------------
double Scan_one_coefficient (char coef_name [8])
{
    double coef = 0;
    bool input_check = true;


    while (input_check)
    {
        printf ("Enter the %s coefficient: ", coef_name);
        if (scanf ("%lf", &coef) != 1)
        {
            printf (" Incorrect input, try again.\n");
            Clear_buffer ();
        }
        else
        {
            if (getchar () != '\n')
            {
                printf (" Incorrect input, try again.\n");
                Clear_buffer ();
            }
            else
            {
                input_check = false;
            }
        }
    }
    return coef;
}

//--------------------------------------------------------------------------------------------------------------------------------
int Solve_equation (double coef_a, double coef_b, double coef_c, double* root_1, double* root_2)
{
        Make_new_coefficients (&coef_a, &coef_b, &coef_c);

        if (Zero_check (coef_a) == 1)
        {
            return Solve_linear (coef_b, coef_c, root_1);
        }
        else
        {
            return Solve_quadratic (coef_a, coef_b, coef_c, root_1, root_2);
        }
}

//-----------------------------------------------------------------------------------------------------------------------------------
void Output_solution (double root_1, double root_2, int case_of_solution)
{
    switch (case_of_solution) {
        case NO_QUADRO_INF_ROOTS:
            printf ("The equation isn\'t quadratic and has infinitely many roots\n");
            break;
        case NO_QUADRO_NO_ROOTS:
            printf ("The equation isn\'t quadratic and has no roots\n");
            break;
        case NO_QUADRO_ONE_ROOT:
            printf ("The equation isn\'t quadratic and has only one root that is equal to %f\n", root_1);
            break;
        case QUADRO_NO_ROOTS:
            printf ("The equation has no roots\n");
            break;
        case QUADRO_ONE_ROOT:
            printf ("The equation has only one root that is equal to %f\n", root_1);
            break;
        case QUADRO_TWO_ROOTS:
            printf ("The equation has only two roots that are equal to %f and %f\n", root_1, root_2);
            break;
        default:
            printf ("WTF what did you input, you fucking idiot??????");
            break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
int Continue_or_not (void)
{
    int user_choice_2 = 0;

    printf ("\n\nDo you want solve one more equation with me?\n If Yes, print: 1\n  If No, print: 0\n ");
    user_choice_2 = Get_user_choice ();
    switch (user_choice_2) {

        case 0:
            printf ("Ok, bye <3");
            return 0;
            break;
        case 1:
            return 1;
            break;
       default:
            printf ("Fuck you");
            break;
            }
}

//--------------------------------------------------------------------------------------------------------------------------------
int Get_user_choice (void)
{
    bool input_error = true, one_or_zero = true;
    int num = 0;

    while (input_error)
    {
        printf ("  Your choice: ");
        if (scanf ("%d", &num) != 1)
        {
            printf ("Please, print 0 or 1, don't hurt me(((\n");
            Clear_buffer ();
        }
        else
        {
            if (getchar () != '\n')
            {
                printf ("Please, print 0 or 1, don't hurt me(((\n");
                Clear_buffer ();
            }
            else
            {
                one_or_zero = (num == 0) || (num & 1);

                if (one_or_zero == 0)
                {
                    printf ("Please, print 0 or 1, don't hurt me(((\n");
                }
                else
                {
                    input_error = false;
                }
            }
        }
    }

    return num;
}

//-------------------------------------------------------------------------------------------------------------
void Make_new_coefficients (double* coef_a, double* coef_b, double* coef_c)
{
    double max_coef = 0;

    if (fabs (*coef_a) < fabs (*coef_b))
    {
        max_coef = *coef_b;
    }
    else
    {
        if (fabs (*coef_a) < fabs (*coef_c))
        {
            max_coef = *coef_c;
        }
        else
        {
            max_coef = *coef_a;
        }
    }

    *coef_a = (*coef_a)/(max_coef);
    *coef_b = (*coef_b)/(max_coef);
    *coef_c = (*coef_c)/(max_coef);

    if (isfinite (*coef_a) == 0)
        {
            *coef_a = 0;
            *coef_b = 0;
            *coef_c = 0;
        }

    assert (coef_a != coef_b);
    assert (coef_b != coef_c);
    assert (coef_c != coef_a);
    assert (coef_a != 0);
    assert (coef_b != 0);
    assert (coef_c != 0);
}

//-------------------------------------------------------------------------------------------------------------------------------
int Solve_quadratic (double coef_a, double coef_b, double coef_c, double* root_1, double* root_2)
{
    double sqrt_discriminant = 0;
    double discriminant = Find_the_discriminant (coef_a, coef_b, coef_c);

    assert (isfinite (discriminant) != 0);

    if (discriminant < 0)
    {
        return QUADRO_NO_ROOTS;
    }
    else
    {
        sqrt_discriminant = sqrt(discriminant);
        *root_1 = ( - coef_b + sqrt_discriminant )/( 2 * coef_a );
        *root_2 = ( - coef_b - sqrt_discriminant )/( 2 * coef_a );

        assert (root_1 != root_2);
        assert (root_1 != 0);
        assert (isfinite (*root_1) != 0);
        assert (isfinite (*root_2) != 0);

        if (Zero_check (*root_1) == 1)
        {
            *root_1 = 0;
        }
        if (Zero_check (*root_2) == 1)
        {
            *root_2 = 0;
        }

        if (Zero_check (discriminant) == 1)
        {
            return QUADRO_ONE_ROOT;
        }
        else
        {
            return QUADRO_TWO_ROOTS;
        }
    }
}

//---------------------------------------------------------------------------------------------------
double Find_the_discriminant (double coef_a, double coef_b, double coef_c)
{
    return coef_b * coef_b - 4 * coef_a * coef_c;
}

//----------------------------------------------------------------------------------------------------
int Solve_linear (double coef_b, double coef_c, double* root_1)
{
    if (Zero_check (coef_b) == 1 && Zero_check (coef_c) == 1)
    {
        return NO_QUADRO_INF_ROOTS;
    }
    if (Zero_check (coef_b) == 1 && Zero_check (coef_c) != 1)
    {
        return NO_QUADRO_NO_ROOTS;
    }
    if (Zero_check (coef_b) != 1)
    {
        *root_1 = - coef_c / coef_b;
        assert (isfinite (*root_1) != 0);
        assert (root_1 != 0);
        if (Zero_check (*root_1) == 1)
        {
            *root_1 = 0;
        }
        return NO_QUADRO_ONE_ROOT;
    }
}

//-----------------------------------------------------------------------------------------------------------------
int Zero_check (double var)
{
    const double epsilon = 1e-6;

    return fabs (var) < epsilon;
}

//------------------------------------------------------------------------------------------------------------------
void Clear_buffer (void)
{
    while (getchar () != '\n') {;}
}

//-------------------------------------------------------------------------------------------------------------------
int Unit_test (struct test_data test)
{
    double root_1 = 0, root_2 = 0;
    int case_of_solution = 0;

    case_of_solution = Solve_equation (test.coef_a, test.coef_b, test.coef_c, &root_1, &root_2);

    int roots_equality_1 = Double_epsilon_check (test.root_1, root_1);
    int roots_equality_2 = Double_epsilon_check (test.root_2, root_2);

    if (case_of_solution == test.case_of_solution)
    {
        switch (case_of_solution) {

        case 0:
            return 1;
            break;

        case 1:
            return 1;
            break;

        case 2:
            if (roots_equality_1 == 1)
                return 1;
            break;

        case 3:
            return 1;
            break;

        case 4:
            if (roots_equality_1 == 1)
                return 1;
            break;

        case 5:
            if ((roots_equality_1 == 1) && (roots_equality_2 == 1))
                return 1;
            break;

        default:
            return 0;
            break;
        }
    }

    printf ("UNIT TEST ERROR\n\n");
    printf ("case_of_solution - the parameter situation of solution:\n");
    printf ("0 - The equation isn't quadratic and has infinitely many roots;\n");
    printf ("1 - The equation isn't quadratic and has no roots;\n");
    printf ("2 - The equation isn't quadratic and has only one root;\n");
    printf ("3 - The equation is quadratic and has no roots;\n");
    printf ("4 - The equation is quadratic and has only one root;\n");
    printf ("5 - The equation is quadratic and has only two roots.\n\n");
    printf ("Input test coefficients:\n");
    printf ("senior coefficient: %f\nmiddle coefficient: %f\njunior coefficient: %f\n\n", test.coef_a, test.coef_b, test.coef_c);
    switch (test.case_of_solution) {
        case NO_QUADRO_INF_ROOTS:
            printf ("Expected result:\n case_of_solution = %d (equation is not quadratic and has infinitely many roots)\n", test.case_of_solution);
            printf ("Real result:\n case_of_solution = %d\n\n", case_of_solution);
            break;
        case NO_QUADRO_NO_ROOTS:
            printf ("Expected result:\n case_of_solution = %d (equation is not quadratic and has not roots)\n", test.case_of_solution);
            printf ("Real result:\n case_of_solution = %d\n\n", case_of_solution);
            break;
        case NO_QUADRO_ONE_ROOT:
            printf ("Expected result:\n case_of_solution = %d (equation is not quadratic and has one root)\n", test.case_of_solution);
            printf ("root_1 = %f\n\n", test.root_1);
            printf ("Real result:\n case_of_solution = %d\n", case_of_solution);
            printf ("root_1 = %f\n\n", root_1);
            break;
        case QUADRO_NO_ROOTS:
            printf ("Expected result:\n case_of_solution = %d (equation is quadratic and has not roots)\n\n", test.case_of_solution);
            printf ("Real result:\n case_of_solution = %d\n\n", case_of_solution);
            break;
        case QUADRO_ONE_ROOT:
            printf ("Expected result:\n case_of_solution = %d (equation is quadratic and has one root)\n\n", test.case_of_solution);
            printf ("root_1 = %f\n\n", test.root_1);
            printf ("Real result:\n case_of_solution = %d\n\n", case_of_solution);
            printf ("root_1 = %f\n\n", root_1);
            break;
        case QUADRO_TWO_ROOTS:
            printf ("Expected result:\n case_of_solution = %d (equation is quadratic and has two roots)\n", test.case_of_solution);
            printf ("root_1 = %f\nroot_2 = %f\n\n", test.root_1, test.root_2);
            printf ("Real result:\n case_of_solution = %d\n", case_of_solution);
            printf ("root_1 = %f\nroot_2 = %f\n\n", root_1, root_2);
            break;
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------
int Double_epsilon_check (double var_1, double var_2)
{
    const double epsilon = 1e-6;

    return fabs(var_1-var_2) < epsilon;
}

//------------------------------------------------------------------------------------------------------------
void Run_unit_test (void)
{
    int num_of_test = 0, test_counter = 0;

    for (num_of_test = 0; num_of_test < 10; num_of_test++)
    {
        test_counter += Unit_test (test[num_of_test]);
    }

    printf ("\nTest results: %d successful tests of 10\n\n", test_counter);
}









