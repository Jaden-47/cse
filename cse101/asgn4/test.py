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


def validate_solution(actor_and_movie):

        if(len(actor_and_movie) == 1):
            with open("cleaned_movielist.txt", 'r') as movie_list:
                for line, cast in enumerate(movie_list.readlines()):
                    if(cast.find(actor_and_movie[0])):
                        return True
                return False

        for i in range(0, len(actor_and_movie)-2, 2):
            #print(i)
            flag = True
            with open("cleaned_movielist.txt", 'r') as movie_list:
                for line, cast in enumerate(movie_list.readlines()):
                    movie_name = cast.split()[0]
                    # print(actor_and_movie[i+1][2:-2])
                    if(movie_name == actor_and_movie[i+1][2:-2]):
                        '''
                        print(
                            'movie: '+movie_name+' '+actor_and_movie[i]+' '+actor_and_movie[i+2])
                        print('cast: '+cast)
                        print(str(cast.find(actor_and_movie[i]))+" "+ str(cast.find(actor_and_movie[i])>=0))
                        print(str(cast.find(actor_and_movie[i+2]))+" "+ str(cast.find(actor_and_movie[i+2])>=0))
                        '''
                        if((cast.find(actor_and_movie[i])>=0) and (cast.find(actor_and_movie[i+2])>=0)):
                            flag=False
                            break
                if flag==True:
                    return False

        return True


# Open the output file to be validated as output
with open(filename, 'r') as output:

    # Go over every line of the output file to valid that instance
    for line, solution in enumerate(output.readlines()):

        # If there was no solution to the chess board we take them on their word
        if solution == 'Not present\n':
            print("No solution for this case. Skipping...")

        # Otherwise try to validate the solution that they provided
        else:

            # Split the line on spaces and so we can convert the locations to tuples of ints later
            actor_and_movie = solution.split()
            if len(actor_and_movie) % 2:

                # Break the locations up into a list of tuples of ints so we can validate teh answer properly

                # If the answer is valid then let the user know, otherwise valid_solution will tell them what happened
                if validate_solution(actor_and_movie):
                    print(
                        f'Solution on line number {line+1} is a valid configuration! :)')
                else:
                    print(
                        f'Solution on line number {line+1} is not valid! :(')

            # Given a non even list length then the output is wonky so dont try to parse it
            else:
                print(
                    'Malformed solution, there should be a odd number of movies and actors')
