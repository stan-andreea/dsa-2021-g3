from pathlib import Path
from shutil import copy

students = ["Toma Lungoci"
        , "Ovidiu Florin Voivod"
        , "Matei Radu"
        , "Katalin Simon"
        , "Anda Domsa Stina"
        , "Dan Dumitru Ciobanu"
        , "Mircea Talu"
        , "Teodora Tat"
        , "Andrei Ionut Lauran"
        , "Maria Gliga Hambet"
        , "Alexandru Lucian Olar"
        , "Horea Radu Marcu"
        , "Doru Gabriel Chete"
        , "Monica Iulia Utiu"
        , "Arpad Alex Lacatus"
        , "Bogdan Emilian Sandu"
        , "Alexandru Radu Todor"
        , "Andreea Alexandra Stan"
        , "Dan Cristian Deac"
        , "Ionut Pop"
        , "Agnes Bogdan"
        , "Noemi Veres"
        , "Mihai Alexandru Sandu"
        , "Paolo Adrian Pocol"
        , "Sarolta Jakab Gyik"
        , "Stefan Alexandru Cimpan"
        , "Alisa Dariana Roman"
        , "Catalin Goga"
        , "Lucian Avram"]

for student in students:
    for i in range(2, 15):
        path = ""
        if i < 10:
            path = student + "/Lab0" + str(i)
        else:
            path = student + "/Lab" + str(i)
        Path(path).mkdir(parents=True, exist_ok=True)
        
        src = "README.md"
        copy(src, path)

print(students);

input("Press Enter to continue...")
