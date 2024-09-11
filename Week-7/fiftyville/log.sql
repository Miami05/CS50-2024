-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2023 AND hour = 10;
SELECT * FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE name = 'Bruce';
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.year = 2023
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';
SELECT *
FROM passengers
JOIN flights f1 ON passengers.flight_id = f1.id
JOIN airports a ON f1.origin_airport_id = a.id
JOIN airports a2 ON f1.destination_airport_id = a2.id
JOIN people p ON passengers.passport_number = p.passport_number
WHERE f1.month = 7
  AND f1.year = 2023
  AND f1.day = 29
  AND f1.hour = 8;

