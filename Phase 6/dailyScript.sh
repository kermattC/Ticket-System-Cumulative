#Day 1

cp current_user_accounts.data Front\ End/Daily\ Transaction\ Files/Day1
cp available_tickets.data Front\ End/Daily\ Transaction\ Files/Day1
cd Front\ End/Daily\ Transaction\ Files/Day1
../../front_end current_user_accounts.data available_tickets.data < transaction_stream.input
mv transaction_stream.output ../../../Back\ End
rm transaction_stream.input
cd ../../../
cp current_user_accounts.data Back\ End
cp available_tickets.data Back\ End
cd Back\ End
mv "transaction_stream.output" "daily_transactions.data"
javac BackEnd.java
java BackEnd
mv "new_ticket_file.data" "../New data files"
mv "new_user_accounts.data" "../New data files"




