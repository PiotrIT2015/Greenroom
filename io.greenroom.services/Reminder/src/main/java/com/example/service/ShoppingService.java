package com.example.service;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;


/**
 *
 * @author Piotr
 */
public class ShoppingService {

    ShoppingService(){

    }


    public String odczyt(){



        String csvFile = ".//data";
        BufferedReader br = null;
        String line = "";
        String cvsSplitBy = ",";
        ArrayList<Integer> cash1 = new ArrayList<Integer>();
        ArrayList<Integer> cash2 = new ArrayList<Integer>();
        ArrayList<Integer> cash3 = new ArrayList<Integer>();
        ArrayList<Integer> cash4 = new ArrayList<Integer>();

        try {

            br = new BufferedReader(new FileReader(csvFile));
            while ((line = br.readLine()) != null) {

                // use comma as separator
                String[] money = line.split(cvsSplitBy);

                System.out.println(" [id= " + money[0] + " , type=" + money[1] + " , price=" + money[2] + " , commission=" + money[3] + " , currency=" + money[4] + "is paid=" + money[5] + "]");

                if(money[1].equals("trip") && money[4].equals("EUR"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("EUR"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }
                }else if(money[1].equals("transfer") && money[4].equals("EUR"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }
                }else if(money[1].equals("trip") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }

                }else if(money[1].equals("transfer") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int price2 = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash1.add(price2);
                    }
                }












                if(money[1].equals("trip") && money[4].equals("EUR"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int commission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(commission);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("EUR"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int comission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(comission);
                    }
                }else if(money[1].equals("transfer") && money[4].equals("EUR"))
                {

                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int comission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(comission);
                    }
                }else if(money[1].equals("trip") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int comission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(comission);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int comission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(comission);
                    }

                }else if(money[1].equals("transfer") && money[4].equals("PLN"))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[3].split(cvsSplitBy);
                        int comission = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash2.add(comission);
                    }
                }









                if(money[1].equals("trip") && money[4].equals("EUR") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("EUR") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }
                }else if(money[1].equals("transfer") && money[4].equals("EUR") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }
                }else if(money[1].equals("trip") && money[4].equals("PLN") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }
                }else if(money[1].equals("ticket") && money[4].equals("PLN") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }

                }else if(money[1].equals("transfer") && money[4].equals("PLN") && money[5].equals(false))
                {
                    for(int i=0;i<=money.length-1;i++)
                    {
                        String price[] = money[2].split(cvsSplitBy);
                        int chargevalue = Integer.parseInt(price[i]) + Integer.parseInt(price[i+1]);
                        cash3.add(chargevalue);
                    }
                }


                Iterator itr1 = cash1.iterator();
                Iterator itr2 = cash2.iterator();
                Iterator itr3 = cash3.iterator();

                while(itr1.hasNext()) {
                    Object price = itr2.next();
                    int prices = (int)price;
                    Object comission = itr2.next();
                    int comissions = (int)comission;
                    Object chargevalue = itr2.next();
                    int chargevalues = (int)chargevalue;
                    int settlmentvalue = prices - comissions - chargevalues;
                    System.out.println(prices+comissions+chargevalues+settlmentvalue);
                }


            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        return "data";
    }

    public String InsertQuery() {
        String connectionString =
                "jdbc:sqlserver://sqlserverapp.database.windows.net:1433;"
                        + "database=database1;"
                        + "user=Gekon@sqlserverapp.database.windows.net;"
                        + "password=pass;"
                        + "encrypt=true;"
                        + "trustServerCertificate=false;"
                        + "hostNameInCertificate=*.database.windows.net;"
                        + "loginTimeout=30;";

        // Declare the JDBC objects.
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        PreparedStatement prepsInsertProduct = null;

        try {
            connection = DriverManager.getConnection(connectionString);

            // Create and execute an INSERT SQL prepared statement.
            String insertSql = odczyt();

            prepsInsertProduct = connection.prepareStatement(
                    insertSql,
                    Statement.RETURN_GENERATED_KEYS);
            prepsInsertProduct.execute();

            // Retrieve the generated key from the insert.
            resultSet = prepsInsertProduct.getGeneratedKeys();

            // Print the ID of the inserted row.
            while (resultSet.next()) {
                System.out.println("Generated: " + resultSet.getString(1));
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Close the connections after the data has been handled.
            if (prepsInsertProduct != null) try {
                prepsInsertProduct.close();
            } catch (Exception e) {
            }
            if (resultSet != null) try {
                resultSet.close();
            } catch (Exception e) {
            }
            if (statement != null) try {
                statement.close();
            } catch (Exception e) {
            }
            if (connection != null) try {
                connection.close();
            } catch (Exception e) {
            }
        }

        return "database";
    }



}
