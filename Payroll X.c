#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LEN 50
#define FILE_NAME "employee_records.txt"

typedef struct {
    char id[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char address[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    char contact[MAX_NAME_LEN];
    char account_number[MAX_NAME_LEN];
    char cnic[MAX_NAME_LEN];
    char doj[MAX_NAME_LEN];
    char designation[MAX_NAME_LEN];
    double salary;
    
    double work_hours;
    double overtime_hours;
    int unpaid_leaves;
    int attendance_days;
} Employee;

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

char company_name[MAX_NAME_LEN] = "Default Company Name";
int is_company_name_set = 0;

void print_line() {
    printf("========================================================\n");
}

void save_employees_to_file() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Failed to open file for saving.\n");
        return;
    }

    fprintf(file, "%s\n", company_name);
    fprintf(file, "%d\n", employee_count);
    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%.2f\n%.2f\n%d\n%d\n",
                e->id, e->name, e->address, e->email, e->contact, e->account_number,
                e->cnic, e->doj, e->designation, e->salary, e->work_hours,
                e->overtime_hours, e->unpaid_leaves, e->attendance_days);
    }
    fclose(file);
}

void load_employees_from_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        fprintf(stderr, "Warning: File does not exist. Creating a new file.\n");
        save_employees_to_file(); // Create a new file
        return;
    }

    fgets(company_name, MAX_NAME_LEN, file);
    company_name[strcspn(company_name, "\n")] = '\0'; // Remove newline
    fscanf(file, "%d", &employee_count);
    fgetc(file); // Consume newline
    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        fgets(e->id, MAX_NAME_LEN, file); e->id[strcspn(e->id, "\n")] = '\0';
        fgets(e->name, MAX_NAME_LEN, file); e->name[strcspn(e->name, "\n")] = '\0';
        fgets(e->address, MAX_NAME_LEN, file); e->address[strcspn(e->address, "\n")] = '\0';
        fgets(e->email, MAX_NAME_LEN, file); e->email[strcspn(e->email, "\n")] = '\0';
        fgets(e->contact, MAX_NAME_LEN, file); e->contact[strcspn(e->contact, "\n")] = '\0';
        fgets(e->account_number, MAX_NAME_LEN, file); e->account_number[strcspn(e->account_number, "\n")] = '\0';
        fgets(e->cnic, MAX_NAME_LEN, file); e->cnic[strcspn(e->cnic, "\n")] = '\0';
        fgets(e->doj, MAX_NAME_LEN, file); e->doj[strcspn(e->doj, "\n")] = '\0';
        fgets(e->designation, MAX_NAME_LEN, file); e->designation[strcspn(e->designation, "\n")] = '\0';
        fscanf(file, "%lf\n%lf\n%lf\n%d\n%d\n",
               &e->salary, &e->work_hours, &e->overtime_hours,
               &e->unpaid_leaves, &e->attendance_days);
    }
    fclose(file);
}

void set_company_name() {
    print_line();
    printf("                  Set Company Name                     \n");
    print_line();
    printf("Enter company name: ");
    scanf(" %49[^\n]", company_name); // Limit input size
    is_company_name_set = 1;
    printf("Company name updated to: %s\n", company_name);
    print_line();
    save_employees_to_file();
}

void edit_company_name() {
    if (!is_company_name_set) {
        printf("Company name has not been set yet.\n");
        return;
    }
    
    print_line();
    printf("                  Edit Company Name                    \n");
    print_line();
    printf("Current company name: %s\n", company_name);
    printf("Enter new company name: ");
    scanf(" %49[^\n]", company_name); // Limit input size
    printf("Company name updated to: %s\n", company_name);
    print_line();
    save_employees_to_file();
}

int is_valid_name(const char *name) {
    int i;
    for (i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int is_valid_email(const char *email) {
    const char *at = strchr(email, '@');
    if (at && strchr(at, '.')) {
        return 1;
    }
    return 0;
}

int is_valid_contact(const char *contact) {
    int i;
    for (i = 0; i < strlen(contact); i++) {
        if (!isdigit(contact[i])) {
            return 0;
        }
    }
    return 1;
}

int is_valid_cnic(const char *cnic) {
    int len = strlen(cnic);
    if (len == 13 || (len == 15 && cnic[5] == '-' && cnic[13] == '-')) {
        return 1;
    }
    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void input_name(char *name) {
    while (1) {
        printf("Enter name: ");
        fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove newline
        if (is_valid_name(name)) {
            break;
        } else {
            printf("Invalid name. Only alphabetic characters and spaces are allowed. Please try again.\n");
            clear_input_buffer(); // Clear input buffer
        }
    }
}

void input_email(char *email) {
    while (1) {
        printf("Enter email: ");
        fgets(email, MAX_NAME_LEN, stdin);
        email[strcspn(email, "\n")] = '\0'; // Remove newline
        if (is_valid_email(email)) {
            break;
        } else {
            printf("Invalid email format. Please try again.\n");
            clear_input_buffer(); // Clear input buffer
        }
    }
}

void input_contact(char *contact) {
    while (1) {
        printf("Enter contact: ");
        fgets(contact, MAX_NAME_LEN, stdin);
        contact[strcspn(contact, "\n")] = '\0'; // Remove newline
        if (is_valid_contact(contact)) {
            break;
        } else {
            printf("Invalid contact. Only numeric characters are allowed. Please try again.\n");
            clear_input_buffer(); // Clear input buffer
        }
    }
}

void input_cnic(char *cnic) {
    while (1) {
        printf("Enter CNIC: ");
        fgets(cnic, MAX_NAME_LEN, stdin);
        cnic[strcspn(cnic, "\n")] = '\0'; // Remove newline
        if (is_valid_cnic(cnic)) {
            break;
        } else {
            printf("Invalid CNIC format. Please enter 13 digits or in the format XXXXX-XXXXXXX-X. Please try again.\n");
            clear_input_buffer(); // Clear input buffer
        }
    }
}

void add_employee() {
    if (employee_count >= MAX_EMPLOYEES) {
        print_line();
        printf("                  Add Employee                         \n");
        print_line();
        printf("Employee limit reached.\n");
        return;
    }

    Employee *e = &employees[employee_count];

    print_line();
    printf("                  Add Employee                         \n");
    print_line();

    input_name(e->name);

    printf("Enter address: ");
    scanf(" %49[^\n]%*c", e->address); // Limit input size

    input_email(e->email);

    input_contact(e->contact);

    printf("Enter account number: ");
    scanf(" %49[^\n]%*c", e->account_number); // Limit input size

    input_cnic(e->cnic);

    // Extract last 8 digits from CNIC and store as ID
    if (strlen(e->cnic) == 13) {
        strncpy(e->id, e->cnic + 5, 8); // Extract 8 digits from the 6th position
    } else if (strlen(e->cnic) == 15) {
        strncpy(e->id, e->cnic + 6, 8); // Extract 8 digits from the 7th position
    }
    e->id[8] = '\0'; // Null-terminate the string

    printf("Enter date of joining (DD/MM/YYYY): ");
    scanf(" %49[^\n]%*c", e->doj); // Limit input size

    printf("Enter designation: ");
    scanf(" %49[^\n]%*c", e->designation); // Limit input size

    printf("Enter salary: ");
    scanf("%lf", &e->salary);

    employee_count++;
    printf("Employee added successfully.\n");

    print_line();
    save_employees_to_file();
}

void modify_employee() {
    print_line();
    printf("                  Modify Employee                      \n");
    print_line();
    printf("Enter employee ID to modify: ");
    char id[MAX_NAME_LEN];
    scanf(" %49[^\n]", id);
    clear_input_buffer(); // Clear input buffer

    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        if (strcmp(e->id, id) == 0) {
            printf("Editing employee: %s\n", e->name);

            printf("Enter new name (current: %s, press Enter to keep): ", e->name);
            char name[MAX_NAME_LEN];
            fgets(name, MAX_NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (strlen(name) > 0) {
                if (is_valid_name(name)) {
                    strcpy(e->name, name);
                } else {
                    printf("Invalid name. Keeping the current name.\n");
                }
            }

            printf("Enter new address (current: %s, press Enter to keep): ", e->address);
            char address[MAX_NAME_LEN];
            fgets(address, MAX_NAME_LEN, stdin);
            address[strcspn(address, "\n")] = '\0';
            if (strlen(address) > 0) {
                strcpy(e->address, address);
            }

            printf("Enter new email (current: %s, press Enter to keep): ", e->email);
            char email[MAX_NAME_LEN];
            fgets(email, MAX_NAME_LEN, stdin);
            email[strcspn(email, "\n")] = '\0';
            if (strlen(email) > 0) {
                if (is_valid_email(email)) {
                    strcpy(e->email, email);
                } else {
                    printf("Invalid email. Keeping the current email.\n");
                }
            }

            printf("Enter new contact (current: %s, press Enter to keep): ", e->contact);
            char contact[MAX_NAME_LEN];
            fgets(contact, MAX_NAME_LEN, stdin);
            contact[strcspn(contact, "\n")] = '\0';
            if (strlen(contact) > 0) {
                if (is_valid_contact(contact)) {
                    strcpy(e->contact, contact);
                } else {
                    printf("Invalid contact. Keeping the current contact.\n");
                }
            }

            printf("Enter new account number (current: %s, press Enter to keep): ", e->account_number);
            char account_number[MAX_NAME_LEN];
            fgets(account_number, MAX_NAME_LEN, stdin);
            account_number[strcspn(account_number, "\n")] = '\0';
            if (strlen(account_number) > 0) {
                strcpy(e->account_number, account_number);
            }

            printf("Enter new CNIC (current: %s, press Enter to keep): ", e->cnic);
            char cnic[MAX_NAME_LEN];
            fgets(cnic, MAX_NAME_LEN, stdin);
            cnic[strcspn(cnic, "\n")] = '\0';
            if (strlen(cnic) > 0) {
                if (is_valid_cnic(cnic)) {
                    strcpy(e->cnic, cnic);
                } else {
                    printf("Invalid CNIC. Keeping the current CNIC.\n");
                }
            }

            printf("Enter new date of joining (current: %s, press Enter to keep): ", e->doj);
            char doj[MAX_NAME_LEN];
            fgets(doj, MAX_NAME_LEN, stdin);
            doj[strcspn(doj, "\n")] = '\0';
            if (strlen(doj) > 0) {
                strcpy(e->doj, doj);
            }

            printf("Enter new designation (current: %s, press Enter to keep): ", e->designation);
            char designation[MAX_NAME_LEN];
            fgets(designation, MAX_NAME_LEN, stdin);
            designation[strcspn(designation, "\n")] = '\0';
            if (strlen(designation) > 0) {
                strcpy(e->designation, designation);
            }

            printf("Enter new salary (current: %.2f, press Enter to keep): ", e->salary);
            char salary_input[MAX_NAME_LEN];
            fgets(salary_input, MAX_NAME_LEN, stdin);
            salary_input[strcspn(salary_input, "\n")] = '\0';
            if (strlen(salary_input) > 0) {
                double salary;
                if (sscanf(salary_input, "%lf", &salary) == 1) {
                    e->salary = salary;
                } else {
                    printf("Invalid salary. Keeping the current salary.\n");
                }
            }

            printf("Enter new work hours (current: %.2f, press Enter to keep): ", e->work_hours);
            char work_hours_input[MAX_NAME_LEN];
            fgets(work_hours_input, MAX_NAME_LEN, stdin);
            work_hours_input[strcspn(work_hours_input, "\n")] = '\0';
            if (strlen(work_hours_input) > 0) {
                double work_hours;
                if (sscanf(work_hours_input, "%lf", &work_hours) == 1) {
                    e->work_hours = work_hours;
                } else {
                    printf("Invalid work hours. Keeping the current work hours.\n");
                }
            }

            printf("Employee modified successfully.\n");
            print_line();
            save_employees_to_file();
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
    print_line();
}

void delete_employee() {
    print_line();
    printf("                  Delete Employee                      \n");
    print_line();
    printf("Enter employee ID to delete: ");
    char id[MAX_NAME_LEN];
    scanf(" %49[^\n]", id);

    int i;
    for (i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            int j;
            for (j = i; j < employee_count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employee_count--;
            printf("Employee deleted successfully.\n");
            print_line();
            save_employees_to_file();
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
    print_line();
}

void search_employee() {
    char search_id[MAX_NAME_LEN];

    print_line();
    printf("                  Search Employee                      \n");
    print_line();
    printf("Enter Employee ID to search: ");
    scanf(" %49[^\n]", search_id);
    clear_input_buffer(); // Clear input buffer
    
    int found = 0;
    int i;
    for (i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, search_id) == 0) {
            printf("Employee found:\n");
            print_line();
            printf("ID: %s\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Address: %s\n", employees[i].address);
            printf("Email: %s\n", employees[i].email);
            printf("Contact: %s\n", employees[i].contact);
            printf("Account Number: %s\n", employees[i].account_number);
            printf("CNIC: %s\n", employees[i].cnic);
            printf("Date of Joining: %s\n", employees[i].doj);
            printf("Designation: %s\n", employees[i].designation);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Work Hours: %.2f\n", employees[i].work_hours);
            printf("Overtime Hours: %.2f\n", employees[i].overtime_hours);
            printf("Unpaid Leaves: %d\n", employees[i].unpaid_leaves);
            printf("Attendance Days: %d\n", employees[i].attendance_days);
            print_line();
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", search_id);
        print_line();
    }
}


void view_all_employees() {
    print_line();
    printf("                  All Employees                        \n");
    print_line();
    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        printf("ID: %s\n", e->id);
        printf("Name: %s\n", e->name);
        printf("Address: %s\n", e->address);
        printf("Email: %s\n", e->email);
        printf("Contact: %s\n", e->contact);
        printf("Account Number: %s\n", e->account_number);
        printf("CNIC: %s\n", e->cnic);
        printf("Date of Joining: %s\n", e->doj);
        printf("Designation: %s\n", e->designation);
        printf("Salary: %.2f\n", e->salary);
        printf("Work Hours: %.2f\n", e->work_hours);
        printf("Overtime Hours: %.2f\n", e->overtime_hours);
        printf("Unpaid Leaves: %d\n", e->unpaid_leaves);
        printf("Attendance Days: %d\n", e->attendance_days);
        print_line();
    }
}

void add_attendance() {
    print_line();
    printf("                  Add Attendance                       \n");
    print_line();
    printf("Enter employee ID to update attendance: ");
    char id[MAX_NAME_LEN];
    scanf(" %49[^\n]", id);
    clear_input_buffer(); // Clear input buffer

    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        if (strcmp(e->id, id) == 0) {
            printf("Updating attendance for employee: %s\n", e->name);

            printf("Current attendance days: %d\n", e->attendance_days);
            printf("Enter days to add to attendance: ");
            int days_to_add;
            scanf("%d", &days_to_add);
            clear_input_buffer(); // Clear input buffer
            e->attendance_days += days_to_add;

            printf("Current unpaid leaves: %d\n", e->unpaid_leaves);
            printf("Enter unpaid leaves to add: ");
            int leaves_to_add;
            scanf("%d", &leaves_to_add);
            clear_input_buffer(); // Clear input buffer
            e->unpaid_leaves += leaves_to_add;

            printf("Enter overtime hours: ");
            scanf("%lf", &e->overtime_hours);
            clear_input_buffer(); // Clear input buffer

            printf("Attendance updated successfully.\n");
            print_line();
            save_employees_to_file();
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
    print_line();
}


void edit_attendance() {
    print_line();
    printf("                  Edit Attendance                      \n");
    print_line();
    printf("Enter employee ID to edit attendance: ");
    char id[MAX_NAME_LEN];
    scanf(" %49[^\n]", id);
    clear_input_buffer(); // Clear input buffer

    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        if (strcmp(e->id, id) == 0) {
            printf("Editing attendance for employee: %s\n", e->name);

            printf("Current attendance days: %d\n", e->attendance_days);
            printf("Enter new attendance days (press Enter to keep current): ");
            char input[MAX_NAME_LEN];
            fgets(input, MAX_NAME_LEN, stdin);
            if (strlen(input) > 1) { // Check if the input is not just Enter (newline)
                int new_attendance_days;
                sscanf(input, "%d", &new_attendance_days);
                e->attendance_days = new_attendance_days;
            }

            printf("Current unpaid leaves: %d\n", e->unpaid_leaves);
            printf("Enter new unpaid leaves (press Enter to keep current): ");
            fgets(input, MAX_NAME_LEN, stdin);
            if (strlen(input) > 1) { // Check if the input is not just Enter (newline)
                int new_unpaid_leaves;
                sscanf(input, "%d", &new_unpaid_leaves);
                e->unpaid_leaves = new_unpaid_leaves;
            }
            printf("Enter new overtime hours (current: %.2f, press Enter to keep): ", e->overtime_hours);
    char overtime_input[MAX_NAME_LEN];
    fgets(overtime_input, MAX_NAME_LEN, stdin);
    overtime_input[strcspn(overtime_input, "\n")] = '\0';
    if (strlen(overtime_input) > 0) {
        double overtime_hours;
        if (sscanf(overtime_input, "%lf", &overtime_hours) == 1) {
            e->overtime_hours = overtime_hours;
        } else {
            printf("Invalid overtime hours. Keeping the current overtime hours.\n");
        }
    }

            printf("Attendance updated successfully.\n");
            print_line();
            save_employees_to_file();
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
    print_line();
}



void generate_payslip() {
    // Get current time
    time_t now;
    struct tm *local_time;
    time(&now);
    local_time = localtime(&now);

    int current_month = local_time->tm_mon + 1; // tm_mon is 0-based
    int current_year = local_time->tm_year + 1900; // tm_year is years since 1900

    print_line();
    printf("                  Generate Payslip                     \n");
    print_line();

    // Input employee ID to generate payslip
    printf("Enter employee ID to generate payslip: ");
    char id[MAX_NAME_LEN];
    scanf(" %49[^\n]", id);
    clear_input_buffer(); // Clear input buffer

    Employee *found_employee = NULL;

    // Find the employee by ID
    int i;
    for (i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        if (strcmp(e->id, id) == 0) {
            found_employee = e;
            break;
        }
    }

    if (found_employee == NULL) {
        printf("Employee with ID %s not found.\n", id);
        print_line();
        return;
    }

    printf("Generating payslip for employee: %s\n", found_employee->name);

    // Input working days for the current month
    int working_days;
    printf("Enter working days for current month: ");
    scanf("%d", &working_days);
    clear_input_buffer(); // Clear input buffer

    // Retrieve attendance days from the employee record
    int attendance_days = found_employee->attendance_days;

    // Calculate daily rate based on input working days
    double daily_rate = found_employee->salary / working_days;

    // Calculate gross salary based on retrieved attendance days
    double gross_salary = attendance_days * daily_rate;

    // Print payslip
    print_line();
    printf("                  Payslip for %s                   \n", found_employee->name);
    print_line();
    printf("Company Name: %s\n", company_name);
    print_line();
    printf("Employee ID: %s\n", found_employee->id);
    printf("Designation: %s\n", found_employee->designation);
    printf("Date of Joining: %s\n", found_employee->doj);
    printf("Salary: %.2f\n", found_employee->salary);
    printf("Work Hours: %.2f\n", found_employee->work_hours);
    printf("Overtime Hours: %.2f\n", found_employee->overtime_hours);
    printf("Unpaid Leaves: %d\n", found_employee->unpaid_leaves);
    printf("Attendance Days: %d\n", attendance_days);
    printf("Gross Salary: %.2f\n", gross_salary);
    printf("Current Period: %d-%d\n", current_month, current_year);
    print_line();
}

void menu() {
    int choice;
    do {
        print_line();
        printf("                  Employee Management System           \n");
        print_line();
        printf("1. Set Company Name\n");
        printf("2. Edit Company Name\n");
        printf("3. Add Employee\n");
        printf("4. Modify Employee\n");
        printf("5. Delete Employee\n");
        printf("6. View All Employees\n");
        printf("7. Search Employee\n");  // Added new option here
        printf("8. Add Attendance\n");
        printf("9. Edit Attendance\n");
        printf("10. Generate Payslip\n");
        printf("11. Exit\n");
        print_line();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer(); // Clear input buffer

        switch (choice) {
            case 1:
                set_company_name();
                break;
            case 2:
                edit_company_name();
                break;
            case 3:
                add_employee();
                break;
            case 4:
                modify_employee();
                break;
            case 5:
                delete_employee();
                break;
            case 6:
                view_all_employees();
                break;
            case 7:
                search_employee(); // Call the new function
                break;
            case 8:
                add_attendance();
                break;
            case 9:
                edit_attendance();
                break;
            case 10:
                generate_payslip();
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

int main() {
    load_employees_from_file();
    menu();
    return 0;
}
