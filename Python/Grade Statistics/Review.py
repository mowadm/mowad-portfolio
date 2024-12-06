# From two files, calculate the number of scores and the average, then combine
# both files into one list and calculate the number, average, max, and min.
# All with corresponding letter grade
# Michael Mowad
# August 1, 2022

# Create function for calculating the letter grade
def letterGrade(score):
    # Define letter grade values
    A = 89.5
    B = 79.5
    C = 69.5
    D = 59.5
    F = 0

    # Use elif loop to return appropriate letter grade
    if score > 100:
        grade = 'invalid score'
    elif score >= A:
        grade = 'A'
    elif score >= B:
        grade = 'B'
    elif score >= C:
        grade = 'C'
    elif score >= D:
        grade = 'D'
    elif score >= F:
        grade = 'F'
    else:
        grade = 'invalid score'

    return grade

# Establish try/except error handling
try:
    # Define main function
    def main():
        # Open file and intialize reading, list, and accumulators
        section1File = open('Section1.txt', 'r')
        section1InFile = section1File.readline()
        section1List = []
        total1 = 0
        count1 = 0

        # Strip \n from each item and convert to float, append to list, and add
        # accumulators
        while section1InFile != '':
            section1InFile = float(section1InFile.rstrip('\n'))
            section1List.append(section1InFile)
            count1 += 1
            total1 += section1InFile
            section1InFile = section1File.readline()

        # Calculate average and letter grade
        average1 = total1 / count1
        grade1 = letterGrade(average1)

        # Print Output
        print(f'Number of scores in Section 1: {count1}')
        print(f'Average: {average1:.2f} Letter Grade: {grade1}')

        # Open second file and initialize reading, list, and accumulators
        section2File = open('Section2.txt', 'r')
        section2InFile = section2File.readline()
        section2List = []
        total2 = 0
        count2 = 0

        # Strip \n from each item and convert to float, append to list, and add
        # accumulators
        while section2InFile != '':
            section2InFile = float(section2InFile.rstrip('\n'))
            section2List.append(section2InFile)
            count2 += 1
            total2 += section2InFile
            section2InFile = section2File.readline()

        # Calculate average and letter grade
        average2 = total2 / count2
        grade2 = letterGrade(average2)

        # Print Output
        print(f'\nNumber of scores in Section 2: {count2}')
        print(f'Average: {average2:.2f} Letter Grade: {grade2}')

        # Combine both lists and calculate number, average, min, and max + letters
        combinedList = section1List + section2List
        count3 = len(combinedList)
        average3 = (total1 + total2) / count3
        grade3 = letterGrade(average3)
        minscore = min(combinedList)
        mingrade = letterGrade(minscore)
        maxscore = max(combinedList)
        maxgrade = letterGrade(maxscore)

        # Output results
        print(f'\nNumber of scores in both sections combined: {count3}')
        print(f'Average: {average3:.2f} Letter grade: {grade3}')
        print(f'Lowest score: {minscore:.2f} Letter grade: {mingrade}')
        print(f'Highest Score: {maxscore:.2f} Letter grade: {maxgrade}')

    main()

# except statements for common and general errors
except IOError:
    print('There was an error loading the file')
except ValueError:
    print('File contains non-numerical or invalid data')
except Exception as err:
    print(err)

    
    



