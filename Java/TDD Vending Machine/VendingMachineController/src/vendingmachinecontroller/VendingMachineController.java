package vendingmachinecontroller;

import java.util.Scanner;
import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.text.NumberFormat;

public class VendingMachineController {

    private static double balance = 0.00;
    private static double maxPrice = 0.00;
    private static int dollarcoins = 0;
    private static int quarters = 0;
    private static int dimes = 0;
    private static int nickels = 0;
    
    
    public static void main(String[] args) {
        // Initialize scanner and hashmap objects
        Scanner sc = new Scanner(System.in); 
        Map<String, Double> items = new HashMap<>();
        
        NumberFormat nf = NumberFormat.getInstance();
        nf.setMaximumFractionDigits(2);
        nf.setMinimumFractionDigits(2);
        
        // Intialize variables
        String codeLetter = "";
        String codeNum;
        String code;
        double price;
        
        // Get input
        while (true) {
            System.out.print("> ");
            String choice = sc.nextLine();
            
            // Iteration 0
            // Read config file
            if (choice.equals("R")) {
                System.out.print("Enter file name: ");
                String fileName = sc.nextLine();
                items = readConfig(fileName, items);
                // Iteration 5 set change
                dollarcoins = (int) Math.round(items.get("D"));
                quarters = (int) Math.round(items.get("Q"));
                dimes = (int) Math.round(items.get("M"));
                nickels = (int) Math.round(items.get("N"));
            } 
            
            // Iteration 0
            // Print loaded item configuration
            if (choice.equals("P")) {
               printConfig(items);
            }
            
            // Iteration 1
            // Set code letter
            if (choice.matches("[A-E]")) {
                codeLetter = choice;
                System.out.println("Display: " + codeLetter);
            }
            
            // Iteration 1
            // Set code number
            if (choice.matches("[0-9]")) {
                codeNum = choice;
                if (codeLetter.isBlank()) {
                    continue;
                }
                code = codeLetter + codeNum;
                price = items.get(code);
                if (price == -1) {
                    System.out.println("Display: INVALID CODE");
                } else {
                    // Iteration 3
                    if (balance >= price) {
                        
                        System.out.println("[Turn " + code + " Crank]");
                        System.out.println("Display: VENDING " + code);
                        System.out.println("[Stop " + code + " Crank]");
                        
                        balance -= price;
                        System.out.println("Display: BAL = " + nf.format(balance));
                        
                        if (balance > 0) {
                            getChange();
                        }
                    } else {
                        System.out.println("Display: " + code + " = " + nf.format(price));
                    }
                }
                codeLetter = "";
            }
            
            // Iteration 2
            // Input valid currency
            if (choice.matches("[N,M,Q,$,I,V]")) {
                
                //Iteration 6
                if (balance > maxPrice) {
                    System.out.println("[Currency rejected]");
                    System.out.println("Display: BAL LIMIT REACHED");
                    System.out.println("Display: BAL = " + nf.format(balance));
                    continue;
                }
                
                double newBalance = 0.00;
                
                switch (choice) {
                    case "N" -> newBalance = balance + 0.05;
                    case "M" -> newBalance = balance + 0.10;
                    case "Q" -> newBalance = balance + 0.25;
                    case "$" -> newBalance = balance + 1.00;
                    case "I" -> newBalance = balance + 1.00;
                    case "V" -> newBalance = balance + 5.00;
                }
                

                // Iteration 6
                if (checkChange(choice, newBalance) == true) {
                    balance = newBalance;
                } else {
                    System.out.println("[Currency rejected]");
                    System.out.println("Display: INSUFFICIENT CHANGE");
                }
                    
                System.out.println("Display: BAL = " + nf.format(balance));
                
            }
            
            // Iteration 2
            // Input invalid coin
            if (choice.equals("?")) {
                System.out.println("[Coin falls to coin return]");
                System.out.println("Display: BAL = " + nf.format(balance));
            }
            
            // Iteration 2
            // Input invalid bill
            if (choice.equals("!")) {
                System.out.println("[Bill rejected]");
                System.out.println("Display: BAL = " + nf.format(balance));
            }
            
            if (choice.equals("X")) {
                getChange();
            }
            
            if (choice.equals("S")) {
                System.out.println("Dollars = " + dollarcoins);
                System.out.println("Quarters = " + quarters);
                System.out.println("Dimes = " + dimes);
                System.out.println("Nickels = " + nickels);
            }
            
            // Quit
            if (choice.equals("Z")) {
                System.exit(0);
            }
            
        }
    }
    
    // Iteration 0
    public static Map<String, Double> readConfig(String fileName, Map<String, Double> items) {
        // Read file
        try (BufferedReader in = new BufferedReader(new FileReader(fileName))) {
            // Read line
            String line = in.readLine();
            // For each line, split at space and assign to hashmap
            while(line != null) {
                String[] splitLine = line.split(" ", 2);
                
                String itemID = splitLine[0];
                double price = Double.parseDouble(splitLine[1]);
                
                // Iteration 6
                if (price > maxPrice && itemID.length() == 2) {
                    maxPrice = price;
                }
                
                items.put(itemID, price);
                line = in.readLine();
            }
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " not found.");
        } catch (IOException e) {
            System.out.println(e);
        }
        
        return items;
    }
    
    // Iteration 0
    public static void printConfig(Map<String, Double> items) {
         // Convert map values to array for easier printing
        ArrayList<String> itemIDs = new ArrayList<>();
        ArrayList<String> prices = new ArrayList<>();
        
        // For loop to accumulate IDs and prices into indexed array 
        for (int i = 0; i < 5; i++) {
            String letter = "";
            switch (i) {
                case 0 -> letter = "A";
                case 1 -> letter = "B";
                case 2 -> letter = "C";
                case 3 -> letter = "D";
                case 4 -> letter = "E";
            }
            for (int n = 0; n < 10; n++) {
                String code = letter + Integer.toString(n);
                itemIDs.add(code);
                if (items.get(code) == -1.00) {
                    prices.add(" -1");
                } else {
                prices.add(String.format("%.2f", items.get(code)));
                }
            }
        }
        
        // Print to 5x10 table format
        for (int i = 0; i < itemIDs.size(); i += 10) {
            for (int n = 0; n < 10; n++) {
                System.out.print(" " + itemIDs.get(i+n) + "\t");
            }
            System.out.println();
            for (int n = 0; n < 10; n++) {
                System.out.print(prices.get(i+n) + "\t");
            }
            System.out.println("\n");
        }
    }
    
    // Iteration 4
    public static void getChange() {
        
        NumberFormat nf = NumberFormat.getInstance();
        nf.setMinimumFractionDigits(2);
        nf.setMaximumFractionDigits(2);
        
        while (balance > 0) {
            if (balance - 1 >= 0 && dollarcoins != 0) {
                balance -= 1;
                dollarcoins -= 1;
                System.out.println("[Dispense $1 coin]");
                System.out.println("Display: BAL = " + nf.format(balance));
            } else if (balance - 0.25 >= 0 && quarters != 0) {
                balance -= 0.25;
                quarters -= 1;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 25¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
            } else if (balance - 0.25 >= 0 && quarters == 0 && dimes >= 2 
                    && nickels >= 1) {
                dimes -= 2;
                nickels -= 1;
                balance -= 0.1;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 10¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
                
                balance -= 0.1;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 10¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
                
                balance -= 0.05;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 5¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
            } else if (balance - 0.1 >= 0 && dimes != 0) {
                balance -= 0.1;
                dimes -= 1;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 10¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
            } else if (balance - 0.05 >= 0 && nickels != 0) {
                balance -= 0.05;
                nickels -= 1;
                balance = Math.round(balance * 100.0) / 100.0;
                System.out.println("[Dispense 5¢]");
                System.out.println("Display: BAL = " + nf.format(balance));
            } else {
                balance = 0.00;
            }
        }
    }
    
    // Iteration 6
    public static boolean checkChange(String choice, double newBalance) {
        
        double totalChange = (dollarcoins) + (quarters * 0.25) + (dimes * 0.1)
                + (nickels * 0.05);
        
        // $5 bill check
        if (choice.equals("V")) {
            if ((totalChange >= (maxPrice + 4.95)) && ((totalChange - dollarcoins) >= 0.95)) {
                if ((dimes >= 1 && nickels >= 2) || (dimes >= 2 && nickels >= 1) 
                        || (nickels >= 4)) {
                    return true;    
                }
            }
        }
        // Non $5 bill check
        else if (totalChange >= newBalance) {
            if ((totalChange - dollarcoins) >= 1) {
                if ((dimes >= 1 && nickels >= 2) || (dimes >= 2 && nickels >= 1) 
                        || (nickels >= 4)) {
                    return true;
                }
            }
        }
        
        return false;
        
    }
}
