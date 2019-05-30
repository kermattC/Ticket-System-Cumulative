printf "\nReomving old weekly transaction file...\n"
rm weekly_transactions_merged.data

cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day1
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day1
cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day2
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day2
cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day3
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day3
cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day4
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day4
cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day5
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day5
cd Front\ End/Daily\ Transaction\ Files/Day1
rm transaction_stream.output
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.output
#mv transaction_stream.output ../../../Weekly-Transactions/Day1
cd ../Day2
rm transaction_stream.output
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
#mv transaction_stream.output ../../../Weekly-Transactions/Day2
cd ../Day3
rm transaction_stream.output
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
#mv transaction_stream.output ../../../Weekly-Transactions/Day3
cd ../Day4
rm transaction_stream.output
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
#mv transaction_stream.output ../../../Weekly-Transactions/Day4
cd ../Day5
rm transaction_stream.output
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
#mv transaction_stream.output ../../../Weekly-Transactions/Day5

# combine transactions
cd ../

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

cd ../../
printf "\ncompiling Back end...\n"

# copy files into back end folder
cp current_user_accounts.data Back\ End
cp weekly_transactions_merged.data Back\ End
cp available_tickets.data Back\ End
cd Back\ End
mv "weekly_transactions_merged.data" "daily_transactions.data"
# run the back end code
javac BackEnd.java
java BackEnd
# move new files into new folder
mv "new_ticket_file.data" "../New data files"
mv "new_user_accounts.data" "../New data files"






