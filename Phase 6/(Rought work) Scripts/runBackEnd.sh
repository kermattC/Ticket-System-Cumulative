printf "\ncompiling Back end...\n"


cp current_user_accounts.data Back\ End
cp daily_transactions.data Back\ End
cp available_tickets.data Back\ End
cd Back\ End
javac BackEnd.java
java BackEnd
mv "new_ticket_file.data" "../New data files"
mv "new_user_accounts.data" "../New data files"

