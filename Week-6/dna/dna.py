import csv
import sys

# DNA Matching Project
# This program is designed to match a given DNA sequence against a database of DNA profiles
# to identify possible matches.
# It reads a CSV file containing DNA profiles with counts of specific Short Tandem Repeats (STRs)
# and a separate file with a DNA sequence.

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid usage")
        sys.exit(1)
    dna_file = sys.argv[2]
    # Read database file into a variable
    rows = []
    with open(sys.argv[1], "r") as file1:
        csv_data = csv.DictReader(file1)
        for row in csv_data:
            rows.append(row)
    # Read DNA sequence file into a variable
    with open(dna_file, mode="r") as file2:
        dna_sequence = file2.read().strip()
    # Find longest match of each STR in DNA sequence
    strs = list(rows[0].keys())[1:]

    result = {}
    for str_sequence in strs:
        result[str_sequence] = longest_match(dna_sequence, str_sequence)
    # Check database for matching profiles
    for people in rows:
        match = True
        for str_sequence in result:
            if int(people[str_sequence]) != result[str_sequence]:
                match = False
                break
        if match:
            print(people["name"])
            return
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
