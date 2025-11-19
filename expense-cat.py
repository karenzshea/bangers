import argparse
import csv
import re
import shutil
from difflib import SequenceMatcher
from enum import auto, Enum
from os import path
from tempfile import NamedTemporaryFile


"""
To-do
- allow user to edit vendor name when saving
- gracefully handle exiting early

"""

class Provider(Enum):
    ing = auto()


def parse_vendors_file(file_path):
        return VendorManager(categories_dict)


class VendorManager:
    def __init__(self, _cache_file):
        self.cache_file = _cache_file
        self.categories = []
        self.vendors = {}
        self.load_from_cache()

    def load_from_cache(self):
        with open(self.cache_file, 'r') as file:
            reader = csv.DictReader(file, delimiter=';')
            categories_dict = {}
            for line in reader:
                cat_index = len(self.categories)
                self.categories.append(line['category'])
                if vendors := line['vendors']:
                    for vendor in vendors.strip(',').split(','):
                        self.vendors[vendor] = cat_index

    def write_to_cache(self):
        success = False
        with NamedTemporaryFile('w', delete=False, dir=path.dirname(self.cache_file)) as tmpfile:
            tmpfile.write(';'.join(['category','vendors']) + '\n')

            for key, values in self.dict_repr().items():
                line = ';'.join([str(key), ','.join(values)])
                tmpfile.write(line + '\n')

            shutil.move(tmpfile.name, self.cache_file)

    def dict_repr(self):
        data = {category: [] for category in self.categories}
        for vendor, cat_index in self.vendors.items():
            data[self.categories[cat_index]].append(vendor)
        return data

    def __repr__(self):
        return str(self.dict_repr())

    def add_vendor(self, vendor, category, save_to_cache=True):
        self.vendors[vendor.lower()] = self.categories.index(category)
        if save_to_cache:
            self.write_to_cache();


    def category_for_vendor(self, rhs):
        """
        Returns the category of a given vendor, if found
        """
        for lhs, index in self.vendors.items():
            # simple equality check
            if lhs.lower() == rhs.lower():
                return self.categories[index]
            else:
                s = SequenceMatcher(None, lhs.lower(), rhs.lower())
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
    parser.add_argument('provider', choices=['ing'])
    parser.add_argument('-v', '--vendors_file', required=False)

    args = parser.parse_args()

    vendor_manager = VendorManager(args.vendors_file)

    generate_report(args.input_file_path, Provider[args.provider], vendor_manager)


def generate_report(file_path, provider, vendor_manager):
    if provider == Provider.ing:
        generate_ing_report(file_path, vendor_manager)

def normalize_currency_value(string):
    total = 0.0
    match = re.search(r'((\d+[\.]?){1,}),(?P<cent>\d{2})', string)
    if match:
        normal = match.group(1).replace('.', '') + '.' + match.group('cent')
        total += float(normal)
    return total

def generate_ing_report(file_path, vendor_manager):
    VENDOR = 'Auftraggeber/Empfänger'

    total = 0
    with open(file_path, 'r', encoding='ISO-8859-1') as file:
        for i in range(0, 13):
            line = file.readline()
            match = re.search(r'^Saldo;(\d+\.*\d+,*\d+);', line)
            if match:
                total = match.group(1)

        header = file.readline().strip('\n').split(';')

        print(f'Total expenses: {total}')

        report = {category: 0 for category in vendor_manager.categories}
        filereader = csv.DictReader(file, delimiter=';', fieldnames=header)
        for row in filereader:
            vendor_value = row[VENDOR]
            # vendor category was cached
            if category_key := vendor_manager.category_for_vendor(vendor_value):
                # add expense to corresponding category
                report[category_key] += float(normalize_currency_value(row['Betrag']))
            # vendor unknown, ask user for category
            else:
                print(f'[{row["Buchung"]}] {row[VENDOR]}: {row["Betrag"]}')
                for category, index in enumerate(vendor_manager.categories):
                    print('{}: {}'.format(category, index))
                cat_index = int(input("Enter category number: "))
                category_key = vendor_manager.categories[cat_index]
                report[category_key] += float(normalize_currency_value(row['Betrag']))

                save_vendor = None
                while save_vendor != 'y' and save_vendor != 'n':
                    save_vendor = input("Save vendor to category? (y/n) ")

                save_vendor = True if save_vendor == 'y' else False

                if save_vendor:
                    cache_vendor = None
                    while cache_vendor != 'y' and cache_vendor != 'n':
                        cache_vendor = input("Cache vendor to file? (y/n) ")
                    cache_vendor = True if cache_vendor == 'y' else False
                    # TODO allow user to edit name saved

                    vendor_manager.add_vendor(
                            vendor_value,
                            vendor_manager.categories[cat_index],
                            cache_vendor
                    )

        print(report)





if __name__ == '__main__':
    main()
