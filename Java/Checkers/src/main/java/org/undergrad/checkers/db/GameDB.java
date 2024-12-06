package org.undergrad.checkers.db;

import java.sql.*;


public class GameDB {

    // Connect
    // Establish connection to database
    static Connection connect() throws ClassNotFoundException {
        Class.forName("org.sqlite.JDBC");
        String url = "jdbc:sqlite:src/main/resources/org/undergrad/checkers/checkersdata.sqlite";
        try {
            Connection conn = DriverManager.getConnection(url);
            System.out.println("Connection to SQLite has been established.");
            return conn;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return null;
        }
    }

    // saveBoard
    // Saves board string to database of corresponding userID
    public static void saveBoard(int userID, String boardSave) {
        try (Connection c = connect();){
            System.out.println("test");
            Statement stmt = c.createStatement();
            String sql = "UPDATE USERS SET BOARD = '" + boardSave + "' WHERE USERID = " + userID;
            stmt.executeUpdate(sql);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    // loadBoard
    // Returns string of board save from corresponding userID
    public static String loadBoard(int userID) {
        try (Connection c = connect();) {
            ResultSet rs = c.createStatement().executeQuery("SELECT * FROM USERS WHERE USERID = " + userID);
            String save = rs.getString("BOARD");
            return save;
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }
    }

    // savePlayerScore
    // Saves player score to database with corresponding userID
    public static void savePlayerScore(int userID, int playerScore) {
        try (Connection c = connect();) {
            Statement stmt = c.createStatement();
            String sql = "UPDATE USERS SET PLAYERSCORE = '" + playerScore + "' WHERE USERID = " + userID;
            stmt.executeUpdate(sql);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    // loadPlayerScore
    // Loads player score from database with corresponding userID
    public static int loadPlayerScore(int userID) {
        try (Connection c = connect();) {
            ResultSet rs = c.createStatement().executeQuery("SELECT * FROM USERS WHERE USERID = " + userID);
            int playerScore = rs.getInt("PLAYERSCORE");
            return playerScore;
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            return 0;
        }
    }

    // saveBotScore
    // Saves bot score from database with corresponding userID
    public static void saveBotScore(int userID, int botScore) {
        try (Connection c = connect();) {
            Statement stmt = c.createStatement();
            String sql = "UPDATE USERS SET BOTSCORE = '" + botScore + "' WHERE USERID = " + userID;
            stmt.executeUpdate(sql);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    // loadBotScore
    // Loads bot score from database with corresponding userID
    public static int loadBotScore(int userID) {
        try (Connection c = connect();) {
            ResultSet rs = c.createStatement().executeQuery("SELECT * FROM USERS WHERE USERID = " + userID);
            int botScore = rs.getInt("BOTSCORE");
            return botScore;
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            return 0;
        }
    }

    // createUser
    // Inserts new user into database and creates appropriate records
    public static void createUser(String username, String password) {
        try (Connection c = connect();) {
            Statement stmt = c.createStatement();
            String sql = ("INSERT INTO USERS (USERNAME, PASSWORD) "
                    + "VALUES ('" + username + "', '" + password + "');");

            stmt.executeUpdate(sql);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    // findUser
    public static int findUser(String username, String password) {
        try (Connection c = connect();) {
            String sql = ("SELECT * FROM USERS WHERE USERNAME = '" + username + "'");
            ResultSet rs = c.createStatement().executeQuery(sql);
            // Return 0 is username not in system
            if (!rs.isBeforeFirst()) {
                return 0;
            }
            else if (rs.getString("PASSWORD").equals(password)) {
                return rs.getInt("USERID");
            // Return -1 if password incorrect for given username
            } else
                return -1;
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            return -2;
        }
    }

}