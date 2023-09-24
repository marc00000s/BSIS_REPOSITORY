import sys
import os
import csv
import re
os.system('cls')

student_fields = ['roll', 'name', 'age', 'email', 'phone']
student_database = 'students.csv'
student_grade = ['grade']
student_subject = ['subject']


class STUDENT_MANAGEMENT_SYSTEM:

    @staticmethod
    def display_menu():
        print("---------------------------------------")
        print(" Welcome to Student Management System")
        print("---------------------------------------")
        options = ["Add New Student", "Add Subject", "Add Grade", "View/Display All Student Record",
                   "Search Student Record", "Update Student Record", "Delete Student Record",
                   "Read Student Record", "Save Student Record", "Sort Student Record"]
        for i in range(len(options)):
            print("{:<3} {:<24}".format(str(i+1) + ".", options[i]))
        print("{:<3} {:<24}".format("0.", "Quit"))

    @staticmethod
    def add_student():
        print("-------------------------")
        print("Add Student Information")
        print("-------------------------")
        global student_fields
        global student_database

        student_data = []
        for field in student_fields:
            if field is 'email':
                regex = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'
                while True:
                    value = input("Enter " + field + ": ")
                    if (re.fullmatch(regex, value)):
                        break
                    else:
                        print("\nEmail invalid!")
            else:
                value = input("Enter " + field + ": ")
            student_data.append(value)

        with open(student_database, "a", encoding="utf-8") as f:
            writer = csv.writer(f)
            writer.writerows([student_data])

        print("Data saved successfully")
        input("Press any key to continue")
        return

    @staticmethod
    def add_subject():
        print("-------------------------")
        print("Add Subject")
        print("-------------------------")
        global student_fields
        global student_database
        global student_grade

        student_data = []
        for field in student_subject:
            value = input("Enter " + field + ": ")
            student_data.append(value)

        with open(student_database, "a", encoding="utf-8") as f:
            writer = csv.writer(f)
            writer.writerows([student_data])

        print("Data saved successfully")
        input("Press any key to continue")
        return

    @staticmethod
    def add_grade():
        print("-------------------------")
        print("Add Student Information")
        print("-------------------------")
        global student_fields
        global student_database
        global student_grade

        student_data = []
        for field in student_grade:
            value = input("Enter " + field + ": ")
            student_data.append(value)

        with open(student_database, "a", encoding="utf-8") as f:
            writer = csv.writer(f)
            writer.writerows([student_data])

        print("Data saved successfully")
        input("Press any key to continue")
        return

    @staticmethod
    def view_students():
        global student_fields
        global student_database
        global student_grade

        print("--- Student Records ---")

        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            for x in student_fields:
                print(x, end='\t |')
            print("\n------------------------------------------")

            for y in student_subject:
                print(y, end='\t |')
            print("\n")

            for z in student_grade:
                print(z, end='\t |')
            print("\n")

            for row in reader:
                for item in row:
                    print(item, end="\t|")
                print("\n")

        input("Press any key to continue")

    @staticmethod
    def search_student():
        global student_fields
        global student_database
        global student_grade
        global student_subject

        print("--- Search Student ---")
        roll = input("Enter roll no. to search: ")
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            for row in reader:
                if len(row) > 0:
                    if roll == row[0]:
                        print("----- Student Found -----")
                        print("Roll: ", row[0])
                        print("Name: ", row[1])
                        print("Age: ", row[2])
                        print("Email: ", row[3])
                        print("Phone: ", row[4])
                        print("Subject: ", row[0])
                        print("Grade: ", row[0])
                        break
            else:
                print("Roll No. not found in our database")
        input("Press any key to continue")

    @staticmethod
    def update_student():
        global student_fields
        global student_database
        global student_grade
        global student_subject

        print("--- Update Student ---")
        roll = input("Enter roll no. to update: ")
        index_student = None
        updated_data = []
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            counter = 0
            for row in reader:
                if len(row) > 0:
                    if roll == row[0]:
                        index_student = counter
                        print("Student Found: at index ", index_student)
                        student_data = []
                        for field in student_fields:
                            value = input("Enter " + field + ": ")
                            student_data.append(value)
                        updated_data.append(student_data)
                    else:
                        updated_data.append(row)
                    counter += 1

        if index_student is not None:
            with open(student_database, "w", encoding="utf-8") as f:
                writer = csv.writer(f)
                writer.writerows(updated_data)
        else:
            print("Roll No. not found in our database")

        input("Press any key to continue")

    @staticmethod
    def delete_student():
        global student_fields
        global student_database
        global student_grade
        global student_subject

        print("--- Delete Student ---")
        roll = input("Enter roll no. to delete: ")
        student_found = False
        updated_data = []
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            counter = 0
            for row in reader:
                if len(row) > 0:
                    if roll != row[0]:
                        updated_data.append(row)
                        counter += 1
                    else:
                        student_found = True

        subject = input("Enter grade to delete: ")
        student_found = False
        updated_data = []
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            counter = 0
            for row in reader:
                if len(row) > 0:
                    if subject != row[0]:
                        updated_data.append(row)
                        counter += 1
                    else:
                        student_found = True

        if student_found is True:
            with open(student_database, "w", encoding="utf-8") as f:
                writer = csv.writer(f)
                writer.writerows(updated_data)
            print("The subject", subject, "deleted successfully")
        else:
            print("The subject was not found in our database")

        grade = input("Enter grade to delete: ")
        student_found = False
        updated_data = []
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            counter = 0
            for row in reader:
                if len(row) > 0:
                    if grade != row[0]:
                        updated_data.append(row)
                        counter += 1
                    else:
                        student_found = True

        if student_found is True:
            with open(student_database, "w", encoding="utf-8") as f:
                writer = csv.writer(f)
                writer.writerows(updated_data)
            print("The Grade", grade, "deleted successfully")
        else:
            print("The grade was not found in our database")

        if student_found is True:
            with open(student_database, "w", encoding="utf-8") as f:
                writer = csv.writer(f)
                writer.writerows(updated_data)
            print("The Grade:", grade, "deleted successfully")
        else:
            print("The grade was not found in our database")

        input("Press any key to continue")

    @staticmethod
    def save_student():
        print("Data is saved automatically and successfully")
        input("Press any key to continue")
        return
    @staticmethod
    def read_student():   
        global student_fields
        global student_database
        global student_grade
    
        print("--- CSV Student Records ---")
    
        with open(student_database, "r", encoding="utf-8") as f:
            reader = csv.reader(f)
            for x in student_fields:
                print(x, end='\t |')
            print("\n------------------------------------------")
            

            for y in student_subject:
                print(y, end='\t |')
            print("\n")

            for z in student_grade:
                print(z, end='\t |')
            print("\n")

            for row in reader:
                for item in row:
                    print(item, end="\t|")
                print("\n")
                
    
        input("Press any key to continue")

    @staticmethod
    def sort_students(sort_by, data):
        data.sort(key=lambda x: x[sort_by-1])

        with open(student_database, 'w') as f:
            csv_writer = csv.writer(f)
            for row in data:
                csv_writer.writerow(row)

    while True:
        os.system('clear')
        display_menu()

        choice = input("Enter your choice: ")
        if choice == '1':
            os.system('clear')
            add_student()
        elif choice == '2':
            os.system('clear')
            add_subject()
        elif choice == '3':
            os.system('clear')
            add_grade()
        elif choice == '4':
            os.system('clear')
            view_students()
        elif choice == '5':
            search_student()
            os.system('clear')
        elif choice == '6':
            os.system('clear')
            update_student()
        elif choice == '7':
            os.system('clear')
            delete_student()
        elif choice == '8':
            os.system('clear')
            save_student()         
        elif choice == '9':
            os.system('clear')
            read_student()  
        elif choice == '10':
            while True:
                os.system("clear")
                print("{:<4} {:<24} {:<3} {:<24} {:<11}".format(
                    "Roll", "Name", "Age", "Email", "Phone"))
                with open(student_database) as f:
                    data = list(csv.reader(f))
                for row in data:
                    print("{:<4} {:<24} {:<3} {:<24} {:<11}".format(
                        row[0], row[1], row[2], row[3], row[4]))
                sort_by = int(input(
                    '\nEnter 1 to sort by ID, 2 to sort by name, or 3 to sort by email, 0 to exit: '))
                if sort_by is 0:
                    break
                else:
                    sort_students(sort_by, data)
        else:
            break

    print("-------------------------------")
    print(" Thanks you!!!")
    print("-------------------------------")
