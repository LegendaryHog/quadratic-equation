
//Program that solve quadratic equation
//User enter the coefficients of equation and program return
//what equation it is (quadratic or not) and how many roots it has
//and this roots/root



#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR 6



// Function that introduce the program.
void Introduction (void);

// Function that ask user to start or not.
int Start_or_not (void);

// Function that return coefficients of equation in main function.
void Scan_coefficients (double* coef_a, double* coef_b, double* coef_c);

// Function that check input (and repeat him if necessary) and return right coefficients in function "Scan_coefficients".
double Scan_one_coefficient (char coef_name [8]);

// Function that solve equation by "Solve_quadratic" and "Solve_linear" and return case of solution and roots in main.
void Solve_equation (double coef_a, double coef_b, double coef_c, double *root_1,
                      double *root_2, int* case_of_solution);

// Function that output solution of equation.
void Output_solution (double root_1, double root_2, int case_of_solution);

//Function that ask user to continue work or stop.
int Continue_or_not (void);

// Function that check input.
int Get_user_choice (void);

// Function that divide all coefficients on max coefficient
void Make_new_coefficients (double* coef_a, double* coef_b, double* coef_c);

// Function that solve linear case of equation.
void Solve_linear (double coef_b, double coef_c, double* root_1, int* case_of_solution);

// Function that solve quadratic case of equation.
void Solve_quadratic (double coef_a, double coef_b, double coef_c, double discriminant,
                       double* root_1, double* root_2, int* case_of_solution);

// Function that finds discriminant if equation is quadratic.
void Find_the_discriminant (double coef_a, double coef_b, double coef_c, double* discriminant);

// Function that convert numbers close to zero to zero.
int Zero_check (double var);

// Function that clear input buffer.
void Clear_buffer (void);

// Unit test.
void Unit_test (double test_coef_a, double test_coef_b, double test_coef_c, double test_root_1, double test_root_2, int test_case,
                double root_1, double root_2, int case_of_solution, int* test_counter);

// Function that return 1 if two double nuvbers is equal and 0, if it's not.
int Double_epsilon_check (double var_1, double var_2);

// Function that run unit test.
void Run_unit_test (double* root_1, double* root_2, int* case_of_solution);





int main ()
{
    double coef_a = 0, coef_b = 0, coef_c = 0, root_1 = 0, root_2 = 0;
    int case_of_solution = ERROR, start = 0, continue_ = 0;

    Run_unit_test (&root_1, &root_2, &case_of_solution);

    Introduction ();

        if (Start_or_not () == 0)    //
        {                         // end main if user don't want
            return 0;             // solve equation
        }                         //
        else
        {
            do {
            Scan_coefficients (&coef_a, &coef_b, &coef_c);                                 //
            Solve_equation (coef_a, coef_b, coef_c, &root_1, &root_2, &case_of_solution);  // core of programm
            Output_solution (root_1, root_2, case_of_solution);                            //

            } while (Continue_or_not () != 0);
        }                                                                                  // continue solve if user want it
        return 0;
}


void Introduction (void)
{
    printf ("Hello user, I am program that can solve every quadratic equation.\n");
    printf ("Quadratic equation look like: A*x^2 + B*x + C = 0.\n");
    printf (" A call senior coefficient,\n B call average coefficient,\n C call junior coefficient.\n");
    printf ("Do you want solve equation?\n If Yes, print: 1\n  If No, print: 0\n ");
}

int Start_or_not (void)
{
    int user_choice_1;

    user_choice_1 = Get_user_choice ();

    switch (user_choice_1) {                                                            //
                                                                                        //
        case 0:                                                                         //
            printf ("Ok((( Bye(( No, I don't cry((( I am just stupid machine((((");     //
            return 0;                                                                   //
            break;                                                                      // cycle that return user choice in main
        case 1:                                                                         // in main function
            return 1;                                                                   // or repeat input if user print
            break;
        case 2:
            return 2;
            break;                                                                      // number but not 0 or 1
        default:                                                                        //
            printf (" Please, print 0 or 1, don't hurt me(((\n");                       //
            user_choice_1 = Get_user_choice ();                                         //
            break;                                                                      //
    }

}

void Scan_coefficients (double* coef_a, double* coef_b, double* coef_c)
{
    printf ("Enter the coefficients of quadratic equation.\n");
    *coef_a = Scan_one_coefficient ("senior");
    *coef_b = Scan_one_coefficient ("average");
    *coef_c = Scan_one_coefficient ("junior");
}


double Scan_one_coefficient (char coef_name [8])
{
    double coef = 0;
    bool input_check = true;

    while (input_check)                                          //
    {                                                            //
        printf ("Enter the %s coefficient: ", coef_name);        //
        if (scanf ("%lf", &coef) != 1)                           //
        {                                                        //
            printf (" Incorrect input, try again.\n");           //
            Clear_buffer ();                                     //
        }                                                        //
        else                                                     // block that check input coefficients
        {                                                        // and ask to repeat it if input is incorrect
            if (getchar () != '\n')                              // (not number and "enter" after)
            {                                                    //
                printf (" Incorrect input, try again.\n");       //
                Clear_buffer ();                                 //
            }                                                    //
            else                                                 //
            {                                                    //
                input_check = false;                             //
            }                                                    //
        }
    }


    return coef;
}

void Solve_equation (double coef_a, double coef_b, double coef_c, double* root_1, double* root_2, int* case_of_solution)
{

        double discriminant = 0;
        Make_new_coefficients (&coef_a, &coef_b, &coef_c);
        if (isnanf (coef_a))
        {
            coef_a = 0;
            coef_b = 0;
            coef_c = 0;
        }
        if (Zero_check (coef_a) == 0)                                                                    //
        {                                                                                                // if senior coefficient equal to 0
            Solve_linear (coef_b, coef_c, root_1, case_of_solution);                                     // (equation is linear) then start
        }                                                                                                // function "Solve_linear"

        else                                                                                             //
        {                                                                                                // if senior coefficient don't equal to 0
            Solve_quadratic (coef_a, coef_b, coef_c, discriminant, root_1, root_2, case_of_solution);    // (equation is quadratic) then start
        }                                                                                                // function "Solve_quadrtic"
}

void Output_solution (double root_1, double root_2, int case_of_solution)
{
    switch (case_of_solution) {                                                                               //
        case 0:                                                                                               //
            printf ("The equation isn\'t quadratic and has infinitely many roots\n");                         //
            break;                                                                                            //
        case 1:                                                                                               //
            printf ("The equation isn\'t quadratic and has no roots\n");                                      //
            break;                                                                                            //
        case 2:                                                                                               // cycle that print text and roots in depend
            printf ("The equation isn\'t quadratic and has only one root that is equal to %f\n", root_1);     // of value of case_of_solution
            break;                                                                                            //
        case 3:                                                                                               //
            printf ("The equation has no roots\n");                                                           //
            break;                                                                                            //
        case 4:                                                                                               //
            printf ("The equation has only one root that is equal to %f\n", root_1);                          //
            break;                                                                                            //
        case 5:                                                                                               //
            printf ("The equation has only two roots that are equal to %f and %f\n", root_1, root_2);         //
            break;                                                                                            //
        default:                                                                                              //
            printf ("WTF what did you input, fucking idiot??????");                                           //
            break;                                                                                            //
    }
}

int Continue_or_not (void)
{
    int user_choice_2;

    printf ("\n\nDo you want solve one more equation with me?\n If Yes, print: 1\n If No, print: 0\n ");

    user_choice_2 = Get_user_choice ();

    switch (user_choice_2) {                                          //
                                                                      //
        case 0:                                                       //
            printf ("Ok, bye <3");                                    //
            return 0;                                                 // cycle that return user choice in main
            break;                                                    // in main function
        case 1:                                                       // or repeat input if user print
            return 1;                                                 // number but not 0 or 1
            break;                                                    //
        default:                                                      //
            printf ("Please, print 0 or 1, don't hurt me(((\n");      //
            user_choice_2 = Get_user_choice ();                       //
            break;                                                    //
    }
}

int Get_user_choice (void)
{
    bool input_error = true;
    int num;

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
                input_error = false;
            }
        }
    }
    return num;
}

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

}

void Solve_quadratic (double coef_a, double coef_b, double coef_c, double discriminant, double* root_1, double* root_2, int* case_of_solution)
{
    double sqrt_discriminant = 0;
    Find_the_discriminant (coef_a, coef_b, coef_c, &discriminant);
    sqrt_discriminant = sqrt(discriminant);

    if (discriminant < 0)
    {
        *case_of_solution = 3;
    }
    else
        {
        *root_1 = ( - coef_b + sqrt_discriminant )/( 2 * coef_a );
        *root_2 = ( - coef_b - sqrt_discriminant )/( 2 * coef_a );
        {
            if (Zero_check (*root_1) == 0)
            {
                *root_1 = 0;
            }
            if (Zero_check (*root_2) == 0)
            {
                *root_2 = 0;
            }
        }
            if (Zero_check (discriminant) == 0)
                *case_of_solution = 4;
            else
                *case_of_solution = 5;

        }
}

void Find_the_discriminant (double coef_a, double coef_b, double coef_c, double* discriminant)
{
    *discriminant = coef_b * coef_b - 4 * coef_a * coef_c;
}

void Solve_linear (double coef_b, double coef_c, double* root_1, int* case_of_solution)
{
    if (Zero_check (coef_b) == 0 && Zero_check (coef_c) == 0)
    {
        *case_of_solution = 0;
    }
    if (Zero_check (coef_b) == 0 && Zero_check (coef_c) != 0)
    {
        *case_of_solution = 1;
    }
    if (Zero_check (coef_b) != 0)
    {
        *root_1 = - coef_c / coef_b;
            if (Zero_check (*root_1) == 0)
            {
                *root_1 = 0;
            }
            *case_of_solution = 2;
    }
}

int Zero_check (double var)
{
    const double epsilon = 1e-6;

    if (fabs (var) < epsilon)        //
    {                                // return information about absolute value of variable less then 10^-6 or not
        return 0;                    // (0 if number close to 0 and 1 if no)
    }                                //
    else                             //
    {
        return 1;
    }
}

void Clear_buffer (void)
{
    while (getchar () != '\n') {;}
}

void Unit_test (double test_coef_a, double test_coef_b, double test_coef_c, double test_root_1, double test_root_2,
                 int test_case, double root_1, double root_2, int case_of_solution, int* test_counter)
{
    Solve_equation (test_coef_a, test_coef_b, test_coef_c, &root_1, &root_2, &case_of_solution);

    int roots_equality_1 = Double_epsilon_check (test_root_1, root_1);
    int roots_equality_2 = Double_epsilon_check (test_root_2, root_2);

    if (case_of_solution == test_case)
    {
        switch (case_of_solution) {

        case 0:
            (*test_counter)++;
            break;
        case 1:
            (*test_counter)++;
            break;
        case 2:
            if (roots_equality_1 == 1)
                (*test_counter)++;
            break;
        case 3:
            (*test_counter)++;
            break;
        case 4:
            if (roots_equality_1 == 1)
                (*test_counter)++;
            break;
        case 5:
            if ((roots_equality_1 == 1) && (roots_equality_2 == 1))
                (*test_counter)++;
            break;
        default:
            printf ("HAHA WTF FUCK YOU");
            break;
        }
    }
}

int Double_epsilon_check (double var_1, double var_2)
{
    const double epsilon1 = 1e-6;

    if (fabs(var_1-var_2) < epsilon1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Run_unit_test (double* root_1, double* root_2, int* case_of_solution)
{
    double test_coef_a, test_coef_b, test_coef_c, test_root_1, test_root_2;
    int test_case;
    int test_counter = 0;

    Unit_test (1, 2, 1, -1, 0, 4, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (0.00000001, 57, -114, 2, 0, 2, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (0.000000001, 0.000000003, 0.000000002, -1, -2, 5, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (1, 5, 6, -2, -3, 5, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (0, 60, 45, -0.75, 0, 2, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (0, 0, 0, 0, 0, 0, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (0, 0, 300, 0, 0, 1, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (1, -4, 4, 2, 0, 4, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (1, 0,  -4, -2, 2, 5, *root_1, *root_2, *case_of_solution, &test_counter);
    Unit_test (1, 2, 2, 0, 0, 3, *root_1, *root_2, *case_of_solution, &test_counter);

    printf ("\nTest results: %d successful tests of 10\n\n\n", test_counter);
}











