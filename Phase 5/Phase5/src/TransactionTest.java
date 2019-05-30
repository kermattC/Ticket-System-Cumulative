import org.junit.Test;
import junit.framework.JUnit4TestAdapter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.io.IOException;

import static org.junit.Assert.*;

public class TransactionTest {

    //do not make these static
    public ArrayList<String> actualUserData = new ArrayList<String>() {{
        add("admin           AA 543278.23");
        add("newseller       SS 005201.25");
        add("event host      FS 020850.00");
    }};
    public ArrayList<String> actualTicketData = new ArrayList<String>() {{
        add("Test Event                event host      015 012.45");
    }};


    // ------------------ TEST CASES FOR ACCOUNT TRANSACTION CLASS --------------------------


    //initialize AccountTransaction for testing class methods
    public AccountTransaction TestCaseAT = new AccountTransaction();

    @Test
    public void runUpdateAddCreditTest() {

        //AccountTransaction TestCase1 = new AccountTransaction();
        //the "expected" user data ArrayList for the test case after execution
        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("newseller       SS 005301.25");
            add("event host      FS 020850.00");
        }};
        //run add credit test
        String addCreditLog = "06 newseller       SS 000100.00";
        TestCaseAT.updateAddCredit(addCreditLog, actualUserData);
        assertEquals(expectedUserData, actualUserData);
    }

    @Test
    public void runUpdateRefundTest() {

        // AccountTransaction TestCase1 = new AccountTransaction();
        //the "expected" user data ArrayList for the test case after execution
        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("newseller       SS 005101.25");
            add("event host      FS 020850.00");
            add("newbuyer        BS 000600.00");
        }};
        //add a new user to actualUserData arrayList inorder to run test for refund
        //this requires both seller and buyer (NOTE: newbuyer has 500 credits orginially as
        //opposed to expectedUserData arrayList which should be 600 credits after running refund test)

        actualUserData.add("newbuyer        BS 000500.00");

        //run refund test
        String refundCreditLog = "05 newbuyer        newseller       000100.00";
        TestCaseAT.updateRefund(refundCreditLog, actualUserData);
        assertEquals(expectedUserData, actualUserData);

    }

    @Test
    public void runUpdateCreateTest() {
        //initialize AccountTransaction for testing updateCreate
        //AccountTransaction TestCase1 = new AccountTransaction();
        //the expected user data ArrayList for the test case
        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("newseller       SS 005201.25");
            add("event host      FS 020850.00");
            add("standard        FS 000000.00");
        }};
        //running test
        String createLog = "01 standard        FS 000000.00";
        TestCaseAT.updateCreate(createLog, actualUserData);
        assertEquals(expectedUserData, actualUserData);
    }


    // ------------------ TEST CASES FOR TICKET TRANSACTION CLASS --------------------------

    //initialize TicketTransaction for testing class methods
    public TicketTransaction TestCaseTT = new TicketTransaction();


    @Test
    public void runUpdateDeleteTest1() {

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("event host      FS 020850.00");
        }};

        ArrayList<String> expectedTicketData = new ArrayList<String>() {{
            add("Test Event                event host      015 012.45");
        }};

        //running test
        String deleteLog = "02 newseller       SS 005201.25";
        TestCaseTT.updateDelete(deleteLog, actualUserData, actualTicketData);

        //compare expected vs actual user data arrayList & Ticket arrayList
        assertEquals(expectedUserData, actualUserData);
        assertEquals(expectedTicketData, actualTicketData);
    }

    @Test
    public void runUpdateDeleteTest2() {

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("event host      FS 020850.00");
        }};

        // add a ticket belonging to the seller and and relevant to the test case
        actualTicketData.add("NymH Event                newseller       055 019.99");

        // the recently added ticket will be removed after execution
        ArrayList<String> expectedTicketData = new ArrayList<String>() {{
            add("Test Event                event host      015 012.45");
        }};

        //running test
        String deleteLog = "02 newseller       SS 005201.25";
        TestCaseTT.updateDelete(deleteLog, actualUserData, actualTicketData);

        //compare expected vs actual user data arrayList & Ticket arrayList
        assertEquals(expectedUserData, actualUserData);
        assertEquals(expectedTicketData, actualTicketData);
    }


    @Test
    public void runUpdateSellTest() {

        ArrayList<String> expectedTicketData = new ArrayList<String>() {{
            add("Test Event                event host      015 012.45");
            add("admin event title         admin           012 005.00");
        }};

        //running test
        String sellLog = "03 admin event title         admin           012 005.00";
        TestCaseTT.updateSell(sellLog, actualTicketData);
        assertEquals(expectedTicketData, actualTicketData);
    }

    // non-existent event/ticket
    @Test
    public void runUpdateBuyTest1() {

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("newseller       SS 005201.25");
            add("event host      FS 020850.00");
        }};

        ArrayList<String> expectedTicketData = new ArrayList<String>() {{
            add("Test Event                event host      015 012.45");
        }};

        ArrayList<String> transactionData = new ArrayList<String>() {{
            add("04 LCS Series              newseller         002 032.95");
            add("00 admin           AA 543278.23");
        }};

        //running test
        String buyLog = "04 LCS Series              newseller         002 032.95";
        TestCaseTT.updateBuy(buyLog, actualUserData, actualTicketData, transactionData);
        assertEquals(expectedUserData, actualUserData);
        assertEquals(expectedTicketData, actualTicketData);
    }

    // Event exists
    @Test
    public void runUpdateBuyTest2() {

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543240.88");
            add("newseller       SS 005201.25");
            add("event host      FS 020887.35");
        }};

        ArrayList<String> expectedTicketData = new ArrayList<String>() {{
            add("Test Event                event host      012 012.45");
        }};

        ArrayList<String> transactionData = new ArrayList<String>() {{
            add("04 Test Event                event host      012 012.45");
            add("00 admin           AA 543278.23");
        }};

        //running testketDa
        String buyLog = "04 Test Event                event host      012 012.45";
        TestCaseTT.updateBuy(buyLog, actualUserData, actualTicketData, transactionData);
        assertEquals(expectedTicketData, actualTicketData);
        assertEquals(expectedUserData, actualUserData);
    }

    public static junit.framework.Test suite(){
        return new JUnit4TestAdapter(TransactionTest.class);
    }


    // ------------------ TEST CASES FOR BACKEND CLASS --------------------------

    public BackEnd TestCaseB = new BackEnd();

    @Test
    public void testGetData(){
        ArrayList<String> expectedUserData = new ArrayList<String>(){{
            add("admin           AA 543278.23");
            add("standard        FS 000000.00");
            add("buyer           BS 999999.99");
            add("seller          SS 000000.00");
            add("newseller       BS 999201.25");
            add("event host      SS 003292.05");
            add("newbuyer        BS 000500.00");
        }};
        ArrayList<String> expectedTicketData = new ArrayList<String>(){{
            add("Test Event                event host      015 012.45");
            add("My Awesome Event          standard        029 032.95");
            add("Another Event             creative        001 092.12");
        }};

        ArrayList<String> expectedTransactionData = new ArrayList<String>(){{
            add("06 newseller       SS 000100.00");
            add("02 event host      SS 000000.00");
            add("00 admin           AA 000000.00");
            add("00 standard        FS 000000.00");
            add("00 buyer           BS 999999.99");
            add("00 seller          SS 000000.00");
            add("03 admin event title         admin           001 000001.00");
            add("00 admin           AA 000000.00");
            add("03 standard event title      standard        001 000001.00");
            add("00 standard        FS 000000.00");
            add("00 buyer           BS 999999.99");
            add("03 seller event title        seller          001 000001.00");
            add("00 seller          SS 000000.00");
            add("01 Jude            AA 000000.00");
            add("04 My Awesome Event          standard        002 000032.95");
            add("00 buyer           BS 999999.99");
            add("05 newbuyer        newseller       000100.00");
        }};

        ArrayList<String> userResult = TestCaseB.getUsersData();
        ArrayList<String> ticketResult = TestCaseB.getTicketData();
        ArrayList<String> transactionResult = TestCaseB.getTransactionData();

        assertEquals(userResult, expectedUserData);
        assertEquals(ticketResult, expectedTicketData);
        assertEquals(transactionResult, expectedTransactionData);
    }

    @Test
    public void testFindUserIndex(){

        // TestCase #1 - User Exists
        int expected = 0;
        String target = "admin          ";
        int result = TestCaseB.findUserIndex(target, actualUserData);

        assertEquals(expected, result);

        // TestCase #2 - User Not Found
        expected = -1;
        target = "Tyler1         ";
        result = TestCaseB.findUserIndex(target, actualUserData);

        assertEquals(expected, result);
    }

    @Test
    public void testFindBuyer(){

        // TestCase #1 - Buyer Exists
        ArrayList<String> userData1 = new ArrayList<String>(){{
            add("00 buyer           BS 999999.99");
            add("02 event host      SS 000000.00");
        }};

        // TestCase #2 - Buyer Not Found
        ArrayList<String> userData2 = new ArrayList<String>(){{
            add("01 Jude            AA 000000.00");
            add("02 event host      SS 000000.00");
        }};

        String result = "buyer          ";
        String expected1 = TestCaseB.findBuyer(userData1, 0);
        String expected2 = TestCaseB.findBuyer(userData2, 0);

        assertEquals(expected1, result);
        assertEquals(expected2, null);
    }

    @Test
    public void saveToOutputTest(){

        ArrayList<String> expectedTicketData = new ArrayList<String>(){{
            add("Test Event                event host      015 012.45");
        }};

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("newseller       SS 005201.25");
            add("event host      FS 020850.00");
        }};

        TestCaseB.saveToOutput(actualUserData, actualTicketData);

        ArrayList<String> actualUserFileData = fileToArrayList("new_user_accounts.data");
        ArrayList<String> actualTicketFileData = fileToArrayList("new_ticket_file.data");

        assertEquals(expectedUserData, actualUserFileData);
        assertEquals(expectedTicketData, actualTicketFileData);

    }

    @Test
    public void testMainFunction() {


        ArrayList<String> expectedTicketData = new ArrayList<String>(){{
            add("My Awesome Event          standard        002 032.95");
            add("Another Event             creative        001 092.12");
            add("admin event title         admin           001 000001");
            add("standard event title      standard        001 000001");
            add("seller event title        seller          001 000001");
        }};

        ArrayList<String> expectedUserData = new ArrayList<String>() {{
            add("admin           AA 543278.23");
            add("standard        FS 000864.00");
            add("buyer           BS 999135.99");
            add("seller          SS 000000.00");
            add("newseller       BS 999201.25");
            add("newbuyer        BS 000600.00");
            add("Jude            AA 000000.00");
        }};

        // our main file reads from transactions.data file and runs tests for all transaction cases

        TestCaseB.main(null);

        ArrayList<String> actualUserFileData = fileToArrayList("new_user_accounts.data");
        ArrayList<String> actualTicketFileData = fileToArrayList("new_ticket_file.data");

        assertEquals(expectedUserData, actualUserFileData);
        assertEquals(expectedTicketData, actualTicketFileData);

    }

    public ArrayList<String> fileToArrayList(String path) {

        ArrayList<String> arr = new ArrayList<String>();
        try (BufferedReader br = new BufferedReader(new FileReader(path))){

            String sCurrentLine;
            while ((sCurrentLine = br.readLine()) != null) {
                arr.add(sCurrentLine);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return arr;
    }

    // ---------------------  TESTING LOOP / DECISION COVERAGE ----------------------------------------------------
    // for fuction findBuyer()

    @Test
    public void testLoopAndDecisionFindBuyer(){
        ArrayList<String> userData1 = new ArrayList<String>(){{
            add("00 buyer           BS 999999.99");
            add("02 event host      SS 000000.00");
        }};

        ArrayList<String> userData2 = new ArrayList<String>(){{
            add("01 Jude            AA 000000.00");
            add("02 event host      SS 000000.00");
        }};

        ArrayList<String> userData3 = new ArrayList<String>(){{
        }};

        ArrayList<String> userData4 = new ArrayList<String>(){{
            add("00 buyer           BS 999999.99");
            add("02 event host      SS 000000.00");
            add("01 Jude            AA 000000.00");
            add("01 Matt            AA 000000.00");
        }};

        ArrayList<String> userData5 = new ArrayList<String>(){{
            add("00 buyer           BS 999999.99");
        }};


        String result = "buyer          ";
        String expected1 = TestCaseB.findBuyer(userData1, 0); // loop 2 times
        String expected2 = TestCaseB.findBuyer(userData2, 0);
        String expected3 = TestCaseB.findBuyer(userData3, 0); // loop 0 times
        String expected4 = TestCaseB.findBuyer(userData4, 0); // loop many times
        String expected5 = TestCaseB.findBuyer(userData5, 0); // loop once

        assertEquals(expected1, result);
        assertEquals(expected2, null);
        assertEquals(expected3, null);
        assertEquals(expected4, result);
        assertEquals(expected5, result);
    }
}
