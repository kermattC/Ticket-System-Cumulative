# Author : Zehan Song, Matt Chan, Jude Antony
# Version 1.0

# Entire directory containing test files
#cd ".."
cd "Front End/Daily Transaction Files"

# Run Inputs
printf "\nProcessing Inputs..\n"
# Since each day case is in it's own directory,
# Go through all of them.
for dir in */ ; do
    # Enter the directory to run the test case
    cd $dir
        # Delete previous output file
        rm transaction_stream.output
        # Run the front_end program with test files, using the input file to automate the work
        ../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
    # Exit out of the directory to go to the next one
    cd ..
done
