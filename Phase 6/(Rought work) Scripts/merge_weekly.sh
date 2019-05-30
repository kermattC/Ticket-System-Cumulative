
printf "\nReomving old weekly transaction file...\n"
rm weekly_transactions_merged.data

# Entire directory containing test files
cd "Front End/Daily Transaction Files"

# Run tests
printf "\ncombining Transactions...\n"

for dir in */ ; do
	# enter each directory
    cd $dir
        printf "\nRetrieving Transactions from $dir\n"
		# adds a new line to each data files
		sed -i -e '$a\' *.output
		# combines all data files into one / appends to one file
        	cat *.output >> ../../../weekly_transactions_merged.data
    # Exit out of the directory to go to the next one
    cd ..

done

printf "\nSuccessfully combined to weekly_transactions_merged.data!\n"

