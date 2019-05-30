# Author : Zehan Song, Matt Chan, Jude Antony
# Version 1.0

# Entire directory containing test files
#cd ".."

#$acc='cat current_user_accounts.data' # store file name
#$tic='cat available_tickets.data'  # store file name

<<<<<<< HEAD
cd "Daily Transaction Files"
=======
cd "Front End/Daily Transaction Files"
>>>>>>> 0af6eacaa9ce13dad1bbdfa1b880a890ef7aa2e4

# Run Inputs
printf "\nProcessing Inputs..\n"
# Since each day case is in it's own directory,
# Go through all of them.
for dir in */ ; do
    # Enter the directory to run the test case
    cd $dir
        printf "\nlog for $dir\n"
        # Delete previous output file
<<<<<<< HEAD
        #rm transaction_stream.output
=======
        rm transaction_stream.output
>>>>>>> 0af6eacaa9ce13dad1bbdfa1b880a890ef7aa2e4
        # Run the front_end program with test files, using the input file to automate the work
        ../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
        #../../front_end acc tic < transaction_stream.input  # stored file names

    # Exit out of the directory to go to the next one
    cd ..
done
