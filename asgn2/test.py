import sys
import os

# Attempt to get the file we are checking the validity of and let the user know if they didnt specify one
try:
    filename = sys.argv[1]
except IndexError:
    print('Output file not provided, please specify an output file to check the validity of')
    exit(1)

# Make sure the path to the given file actually exists before going futher
if not os.path.exists(filename):
    print('Output filepath does not exist!')
    exit(1)


def validate_solution(queen_locations):

    # Create a chess board whose size is the number of queens in the solution and assume all spaces are free
    chess_board = [[False for j in range(len(queen_locations))] for i in range(len(queen_locations))]

    # Go over every queen in the solution and mark its protected locations as blocked from other queens
    for row, column in queen_locations:
        
        # Go over the entire board and check to see if this cell is a protected location of the current queen
        for row_index in range(len(queen_locations)):
            for col_index in range(len(queen_locations)):
                
                # If this is the location of the queen itself dont mark it, will make sense later
                if row == row_index and column == col_index:
                    continue
                
                # Otherwise check if it is in the same row, column, or diagonal of the current queen
                straight = row == row_index or column == col_index
                diagonal = abs(column - col_index) == abs(row - row_index)

                # If the space is one of those then mark the space as blocked by a given peice
                if straight or diagonal:
                    chess_board[row_index][col_index] = True
    
    # Then go over the given queens locations once more and check to make sure their placed location is free
    for row, column in queen_locations:

        # If the location they are supposed to be placed at is blocked by another piece then this isnt a valid solution
        if chess_board[row][column]:
            print(f'Solution on line number {line} is not a valid solution. Conflict at location {row}, {column} -- ' \
                   'space is protected by another queen on the board!')
            return False
    
    # If we made it here we have validated the solution so reutrn true
    return True


# Open the output file to be validated as output
with open(filename, 'r') as output:
    
    # Go over every line of the output file to valid that instance
    for line, solution in enumerate(output.readlines()):
        
        # If there was no solution to the chess board we take them on their word
        if solution == 'No solution\n':
            print("No solution for this board. Skipping...")

        # Otherwise try to validate the solution that they provided
        else:
            
            # Split the line on spaces and so we can convert the locations to tuples of ints later
            raw_locs = solution.split()

            # The length of this list should always ben even as a single location requires 2 ints
            if not len(raw_locs) % 2:
                
                # Break the locations up into a list of tuples of ints so we can validate teh answer properly
                queen_locs = [(int(raw_locs[i + 1]) - 1, int(raw_locs[i]) - 1) for i in range(0, len(raw_locs), 2)]

                # If the answer is valid then let the user know, otherwise valid_solution will tell them what happened
                if validate_solution(queen_locs):
                    print(f'Solution on line number {line} is a valid configuration! :)')

            # Given a non even list length then the output is wonky so dont try to parse it
            else:
                print('Malformed solution, there should be a row column pair for each queen!')
                