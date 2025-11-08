import argparse
import csv
from difflib import SequenceMatcher
from enum import auto, Enum
import re


class Provider(Enum):
    ing = auto()


class Categories:
    def __init__(self, data):
        self.categories = []
        self.vendors = {}

        for category, _vendors in data.items():
            index = len(self.categories)
            self.categories.append(category)
            for vendor in _vendors:
                self.vendors[vendor] = index

    def __repr__(self):
        data = {category: [] for category in self.categories}
        for vendor, cat_index in self.vendors.items():
            data[self.categories[cat_index]].append(vendor)
        return str(data)

    def add_vendor(self, vendor, category):
        self.vendors[vendor] = self.categories.index(category)


    def category_for_vendor(self, rhs):
        """
        Returns the category of a given vendor, if found
        """
        for lhs, index in self.vendors.items():
            # simple equality check
            if lhs == rhs:
                return self.categories[index]
            else:
                s = SequenceMatcher(None, lhs, rhs)
                i, j, k = s.find_longest_match(0, len(lhs), 0, len(rhs))
                # check if either overlaps completely with the other
                if k - i == len(lhs) or k - j == len(rhs):
                    return self.categories[index]
        return None


def main():
    parser = argparse.ArgumentParser(
                        prog='Expense-cat',
                        description='Generates a categorized summary of expense CSVs',
                        epilog=':)')
    parser.add_argument('input_file_path', help='File path to the CSV to parse')
    parser.add_argument('provider', choices='ing')
    parser.add_argument('-c', '--categories_file', required=False)

    args = parser.parse_args()

    categories = Categories({})
    if args.categories_file:
        categories = parse_categories_file(args.categories_file)

    generate_report(args.input_file_path, Provider[args.provider], categories)


def parse_categories_file(file_path):
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file, delimiter=';')
        categories = {}
        for line in reader:
            categories[line['category']] = line['vendors'].split(',') if line['vendors'] else []
        return Categories(categories)


def generate_report(file_path, provider, categories):
    if provider == Provider.ing:
        generate_ing_report(file_path, categories)


def generate_ing_report(file_path, categories):
    VENDOR = 'Auftraggeber/Empfänger'

    total = 0
    with open(file_path, 'r', encoding='ISO-8859-1') as file:
        for i in range(0, 13):
            line = file.readline()
            match = re.search(r'^Saldo;(\d+\.*\d+,*\d+);', line)
            if SequenceMatcher:
                total = match.group(1)

        header = file.readline().strip('\n').split(';')

        print(f'Total expenses: {total}')

        report = {category: 0 for category in categories.categories}
        filereader = csv.DictReader(file, delimiter=';', fieldnames=header)
        for row in filereader:
            vendor = row[VENDOR].lower()
            if category := categories.category_for_vendor(vendor):
                report[category] += float(row['Betrag'].replace(',', '.'))
            else:
                print(f'[{row["Buchung"]}] {row[VENDOR]}: {row["Betrag"]}')
                for category, index in enumerate(categories.categories):
                    print('{} {}'.format(category, index))
                cat_index = int(input("Enter category: "))
                report[categories.categories[cat_index]] += float(row['Betrag'].replace(',', '.'))
                save = None
                while save != 'y' and save != 'n':
                    save = input("Save vendor to category? ")
                if save:




        print(report)





if __name__ == '__main__':
    main()
