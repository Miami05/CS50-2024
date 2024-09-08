import csv
import requests


# COVID-19 Seven-Day Average Calculation
# This program is designed to calculate the seven-day rolling average of COVID-19 case numbers.
# It processes cumulative case data
# from a CSV file and computes the average number of new cases over the last seven days.

def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


#  Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in new_cases:
            previous_cases[state] = cases
            new_cases[state] = []
        new_cases_today = cases - previous_cases[state]
        previous_cases[state] = cases
        if len(new_cases[state]) >= 14:
            new_cases[state].pop(0)
        new_cases[state].append(new_cases_today)
    return (new_cases)

#  Calculate and print out seven day average for given state


def comparative_averages(new_cases, states):
    for state in states:
        prev_week = new_cases[state][-7:]
        current_week = new_cases[state][:7]
        avg_prev_week = round(sum(prev_week) / 7)
        avg_curr_week = round(sum(current_week) / 7)
        diff = avg_curr_week - avg_prev_week
        if diff > 0:
            msg = "an increase"
        else:
            msg = "a decrease"
        try:
            percent_change = round((diff / avg_prev_week) * 100)
        except ZeroDivisionError:
            print("Can't divide with 0")
        print(f"{state} had a 7-day average of {avg_curr_week} and {msg} of {percent_change}%")


main()
