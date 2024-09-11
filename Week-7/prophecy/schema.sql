CREATE TABLE students (
    id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);
CREATE TABLE houses (
    id INTEGER,
    houses_name TEXT NOT NULL,
    head TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE houses_alignments (
    id INTEGER,
    students_id INTEGER,
    houses_id INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(students_id) REFERENCES students(id),
    FOREIGN KEY(houses_id) REFERENCES houses(id)
);
