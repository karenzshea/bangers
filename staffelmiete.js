#!/usr/bin/env node

function calc_interest(rent, year_increase_pct, years, current) {
    if (current == years) return rent;

    const new_rent = rent + (rent * year_increase_pct);

    return calc_interest(new_rent, year_increase_pct, years, ++current);
}

function main() {
    if (process.argv.length <= 2) {
        console.log('node interest.js [base rent] [pct increase] [no. years]');
        process.exit(0);
    }
    const base_rent = Number(process.argv[2]);
    const increase_pct = Number(process.argv[3]);
    const years = Number(process.argv[4]);

    const end_rent = calc_interest(base_rent, increase_pct / 100, years, 0);

    const log_output = ["Starting rent is", base_rent + ".", "\n", "After", years, "year(s) of a yearly increasing rent of", increase_pct, "the total rent will be:", end_rent];
    console.log(log_output.join(" "));
}

if (require.main === module) {
    return main();
}
