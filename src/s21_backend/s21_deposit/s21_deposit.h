#ifndef S21_C_DEPOSIT_H
#define S21_C_DEPOSIT_H

#include "../s21_common/s21_common.h"

/**
 * @brief List defining constant statuses for functions used in the deposit calculator.
*/
enum deposit_functions_status {
//  Deposit capitalization disabled/enabled.
    NOT_CAPITAL = 0, CAPITAL = 1,
//  Type of operation with deposit sum.
    REFILL = 0, WITHDRAWALS = 1,
};

/**
 * @brief Struct representing the monthly and total return of the deposit
*/
typedef struct investment {
    long double profit;                 /** Deposit return for the current period                                           */
    long double balance_changing;       /** Change in the amount held on deposit in the current period.                     */
    long double receiving;              /** Profit received that does not go to the deposit balance.                        */
    long double balance;                /** Amount deposited in the current period.                                         */
    long double **result;               /** An array of all the above main fields of the structure for storing the results. */
    long double *total;                 /** An array where all period results are added up.                                 */
} investment;

/**
 * @brief Struct representing initial information about the deposit.
*/
typedef struct deposit_init {
    long double amount;                 /** Amount deposited.                                           */
    long double rate;                   /** Deposit interest rate.                                      */
    time_data date;                     /** Date of deposit placement                                   */
    int term;                           /** Deposit term.                                               */
    int term_type;                      /** Type of calculation of the period (days/months, etc.)       */
    int capital_time;                   /** Frequency of capitalization                                 */
    int capital;                        /** Interest capitalization status.                             */
    int current;                        /** A counter that tracks the actual number of payment periods. */
} deposit_init;

/**
 * @brief Struct representing initial information about deposit replenishments and partial withdrawals.
*/
typedef struct operations {
    time_data *date;            /** An array containing all operations dates.                        */
    long double *sum;           /** An array containing all operations amounts.                      */
    int *type;                  /** An array containing all types of operations.                     */
    long double min_balance;    /** The amount below which cannot remain after partial withdrawals.  */
    int count;                  /** Number of operations.                                            */
    int current;                /** A counter that tracks the actual number of operations made.      */
} operations;

// Main functions

void calculate_deposit(deposit_init *data, investment *pay, operations *oper);
int calc_period(deposit_init *data, investment *pay, time_data end_period, long double percent);
void write_results(deposit_init data, investment *pay);
long double calc_period_percent(deposit_init *data, time_data *begin, time_data *oper, time_data *end);

#endif