// Filename: PrintSolutionHelper.java
//
// Contains console printer for Nqueens.
// 
// Compile 
//          javac PrintSolutionHelper.java
// Run
//          java PrintSolutionHelper <FILE>
//
// Each line of <FILE> is expected to be a sequence of integers showing the positions of queens, or some string such as "No solution", etc.
//
// This program prints out each solution with queens as a chessboard, onto the console. The program implicitly assumes the board size is the maximum row/column number seen on each line.
//
// C. Seshadhri, Dec 2016. Sept 2017, Jan 2020.
//
import java.io.*;
import java.util.ArrayList;

class PrintSolutionHelper {

    private static int board_size;  // board size provided by the user
    private static ArrayList<Integer> row; // rows read from solution file
    private static ArrayList<Integer> column; // columns read from solution file

    // Convenient method to print error message and exit
    // Input: String message to be printed
    // Output: void, simply exits program

    private static void errExit(String message) {

        System.err.println(message);
        System.exit(1);
    }

    // A cool method that actually prints a chessboard with queens onto the console. Uses some UNICODE awesomeness
    // Input: 2D boolean array isFilled, where isFilled[i][j] is true iff there is a queen at col i, row j.
    // Assumes that isFilled is board_size X board_size.
    // Output: void, basically prints the chessboard with the queens onto console

    private static void printSolution(boolean[][] isFilled)
    {
        String line = "  "; // starting strings to be printed. line is the dividing horizontal strip along the board
        String col_nums = "  ", col_str = ""; // these strings are for printing the column numbers below

        for (int i=1; i < board_size+1; i++) // loop over all the columns to create the line and col_nums strings
        {
            line = line + "+--"; // each iteratin add "+--" to line
            if (i < 10) // have to break into cases, since i < 10 is one symbol, but i >= 10 is two
                col_str = " " + Integer.toString(i) + " ";  // add string i to col_str with spacing
            else
                col_str = " " + Integer.toString(i);  // add string i to col_str with less spacing, since i >= 10
            col_nums = col_nums + col_str ; // append col_str to col_nums
        }
        line = line + "+";  // complete line string

        for (int i=board_size; i > 0; i--) // loop over all the rows in decreasing order. each iteration will print a row
        {
            System.out.println(line); // start by printing a line
            String pieces, background; // pieces string will actually put the queen symbols into string
            if (i < 10)   // pieces begins with row number, again break into cases if i has 1 vs 2 symbols
                pieces = " "+Integer.toString(i);
            else
                pieces = Integer.toString(i);

            for (int j=1; j < board_size+1; j++) // now loop over columns to create individual squares
            {
                if ((i+j)%2 == 1) // place alternating black or red background for squares
                    background = "\u001B[40m";  // ANSI escape code for black
                else
                    background = "\u001B[41m";  // ANSI escape code for red
                if (isFilled[i][j]) // if (i,j) has a queen
                    pieces = pieces + "|"+background+"\u2655 "+"\u001B[0m"; // put UNICODE symbol for queen with a line. also set background, and then apply ANSI reset code
                else
                    pieces = pieces + "|"+background+"  "+"\u001B[0m";  // put a space and set background, reset as before
            }
            System.out.println(pieces+"|");
        }

        System.out.println(line); // print out the final line
        System.out.println(col_nums); // print out the columns below
    }

    // Method to read the solution from solution.txt generated by your program
    // Input: Filename passed via command line agrument
    // Output: true, if line represented sequence of queens, and false if anything else detected

    private static boolean readFromSolutionFile(String line) {

        String[] args = line.split(" ");

        // ready the arguments before reading
        row = new ArrayList<Integer>();
        column = new ArrayList<Integer>();
        board_size = 0;

        if (args.length%2 == 1) // odd number of elements, so cannot be sequence of queen positions
            return false;

        int pos = 0; // to store position

        for (int i=0; i<args.length; i++)  //loop over args
        {
            try {
                pos = Integer.parseInt(args[i]); // parse string as an input
            }
            catch (NumberFormatException e) { // args[i] is not int
                return false; // failed to parse line as sequence of queen positions
            }
            
            if (pos <= 0)  // non-positive chessboard position
                return false;

            board_size = Math.max(board_size, pos); // update board_size if pos is larger than current estimate
            if (i%2 == 0) //even entry of args, so this is column
                column.add(pos);
            else // odd entry of args, so this is row
                row.add(pos);
        }
        return true;  // successfully parse line as sequence of queen positions

    }

    // Method to populate the isFilled array so that the chessboard can be drawn
    // Input: no arguments
    // Output: 2D boolean array (or chessboard) with queens placed successfully

    private static boolean[][] populateIsFilledArray() {
        boolean[][] isFilled = new boolean[board_size+1][board_size+1]; // initialize the 2D array (or chessboard)

        // loop and initialize the chessboard
        for(int col_ctr = 1; col_ctr <= board_size; col_ctr++) {
            for(int row_ctr = 1; row_ctr <= board_size; row_ctr++) {
                isFilled[row_ctr][col_ctr] = false;
            }
        }

        // loop and fill the chessboard based on the positions read from solution.txt
        for(int col_ctr = 1; col_ctr <= board_size; col_ctr++) {
            isFilled[row.get(col_ctr-1)][column.get(col_ctr-1)] = true;
        }

        // return it to print the board
        return isFilled;
    }

    // Main method
    // Input: filename as command line argument
    // Output: void

    public static void main(String[] args) {

        try{

            BufferedReader reader = new BufferedReader(new FileReader(args[0]));
            // call the respective methods to read from file and display the chessboard

            String line; // store each line in input file
            int line_no = -1;

            while ((line = reader.readLine()) != null) { // reading in line, and checking if file has ended
                line_no++;  //increment line number
                System.out.println("Line "+line_no);
                if(readFromSolutionFile(line)) // this parses line. it returns true and populates the data structures/fields of class, if line was sequence of queen positions
                    printSolution(populateIsFilledArray()); // this does the actual printing
                else  // line is not sequence of queen positions
                    System.out.println("not sequence of queens");
            }
            reader.close();
        }
        catch(Exception e) {
            errExit("Error in reading input file, or no input file provided.");
        }

    }

}

// End
