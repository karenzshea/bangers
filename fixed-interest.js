#!/usr/bin/env node

function calc_loan_value(loan_amt, interest_rate, years, current) {
    if (current == years) return loan_amt;

    const new_loan_amt = loan_amt - (loan_amt * interest_rate);

    return calc_loan_value(new_loan_amt, interest_rate, years, ++current);
}

function main() {
    if (process.argv.length <= 2) {
        console.log('node interest.js [starting loan amount] [interest %] [no. years]');
        process.exit(0);
    }
    const loan_amount = Number(process.argv[2]);
    const interest_rate = Number(process.argv[3]) / 100;
    const years = Number(process.argv[4]);

    const new_loan_amt = calc_loan_value(loan_amount, interest_rate, years, 0);
    const interest_amt = new_loan_amt * interest_rate;

    const log_output = [
        "Starting loan value is", loan_amount, "€ with an interest rate of", interest_rate, "\n",
        "After", years, "years, the new loan value will be:", Math.round(new_loan_amt), "€\n",
        "The interest amount for the following year will be", Math.round(interest_amt), '€'];
    console.log(log_output.join(" "));
}

if (require.main === module) {
    return main();
}
