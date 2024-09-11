from cs50 import SQL
import csv

with open("students.csv", "r") as file:
    csv_reader = csv.DictReader(file)
    data = [row for row in csv_reader]

db = SQL("sqlite:///roster.db")

students_list = []
house_list = []
house_alignments = []

for row in data:
    student_name = row.get('student_name')
    house_name = row.get('house')
    house_head = row.get('head')

    if student_name and student_name not in students_list:
        students_list.append(student_name)
    if house_name and house_head:
        house_list.append((house_name, house_head))
    if student_name and house_name:
        house_alignments.append((student_name, house_name))

for student_name in students_list:
    db.execute('''
               INSERT INTO students (student_name)
               VALUES (?)
               ''', student_name)

for house_name, house_head in house_list:
    db.execute('''
               INSERT INTO houses (houses_name, head)
               VALUES (?, ?)
               ''', house_name, house_head)

for student_name, house_name in house_alignments:
    student_id = db.execute('SELECT id FROM students WHERE student_name = ?', student_name)[0]['id']
    house_id = db.execute('SELECT id FROM houses WHERE houses_name = ?', house_name)[0]['id']
    db.execute('''
               INSERT INTO houses_alignments (students_id, houses_id)
               VALUES (?, ?)
               ''', student_id, house_id)
