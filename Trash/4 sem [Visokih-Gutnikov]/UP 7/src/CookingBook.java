
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.control.Alert;

import java.sql.*;

public class CookingBook extends Application {

    private static Connection connection;
    private static Statement statement;
    private static ResultSet resultSet;

    private TableView<Recipe> recipesTable = new TableView<>();
    private TableView<Chef> chefsTable = new TableView<>();

    private static ObservableList<Recipe> recipesData = FXCollections.observableArrayList();
    private static ObservableList<Chef> chefsData = FXCollections.observableArrayList();

    private final HBox addBox = new HBox(15);
    private final HBox addChefBox = new HBox(15);
    final ComboBox<String> chefsBox = new ComboBox<>();

    private int preferNameColumnWidth = 200;
    private int preferIngredientsColumnWidth = 300;
    private int preferComplexityColumnWidth = 150;
    private int preferCookingTimeColumnWidth = 100;
    static boolean notCreated = false;

    public static void main(String[] args) {
        connectionDB();

        if(notCreated)
            createDB();

        launch(args);
        closeConnectionDB();
    }

    static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    static String connect = "jdbc:derby:cookDB;create=true";

    private static void connectionDB() {

        System.setProperty("derby.system.home", "C:\\Users\\User01\\Desktop\\Labs\\LabsFour\\UP 7\\cookDB");

        try {
            connection = null;
            Class.forName(driver);
            connection = DriverManager.getConnection(connect);

            statement = connection.createStatement();
            String select = "SELECT * FROM recipes";
            resultSet = statement.executeQuery(select);

            while (resultSet.next()) {
                Recipe recipe = new Recipe(resultSet.getString("name"),
                        resultSet.getString("ingredients"),
                        resultSet.getString("description"),
                        resultSet.getString("chef"),
                        resultSet.getString("weight"));
                recipesData.add(recipe);
            }

            select = "SELECT * FROM chefs";
            resultSet = statement.executeQuery(select);

            while (resultSet.next()) {
                Chef chef = new Chef(
                        resultSet.getString("chef"),
                        resultSet.getString("rate"),
                        resultSet.getString("description")
                );
                chefsData.add(chef);
            }


        } catch (Exception e) {
            notCreated = true;
            System.err.println(e.getStackTrace());
        }
    }

    private static void createDB() {
        try {

            statement.execute("CREATE TABLE chefs " +
                    "(rate VARCHAR(32),  " +
                    "chef VARCHAR(32) PRIMARY KEY, " +
                    "description VARCHAR(32))");

            statement.execute(
                    "CREATE TABLE recipes " +
                            "(name VARCHAR(32)," +
                            "ingredients VARCHAR(32), " +
                            "description VARCHAR(32), " +
                            "weight VARCHAR(32)," +
                            "chef VARCHAR(32) REFERENCES chefs(chef))");

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static void closeConnectionDB() {
        try {
            resultSet.close();
            connection.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        Scene scene = new Scene(new Group());
        primaryStage.setTitle("Recipes");

        createRecipesTable();
        createChefsTable();
        createAddBox();
        createAddChefBox();

        VBox allBox = new VBox(10);
        allBox.setPadding(new Insets(10, 10, 10, 10));
        allBox.getChildren().addAll(new Label("Recipes table"), recipesTable, addBox, chefsTable, addChefBox);

        ((Group) scene.getRoot()).getChildren().addAll(allBox);

        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void createAddBox() {
        final TextField addedRecipe = new TextField();
        addedRecipe.setMaxWidth(preferNameColumnWidth);
        addedRecipe.setPromptText("Recipe");

        final TextField addedIngredients = new TextField();
        addedIngredients.setMaxWidth(preferIngredientsColumnWidth);
        addedIngredients.setPromptText("Ingredients");

        final TextField addedDescription = new TextField();
        addedDescription.setMaxWidth(preferCookingTimeColumnWidth);
        addedDescription.setPromptText("Description");

        final TextField addedWeight = new TextField();
        addedWeight.setMaxWidth(preferCookingTimeColumnWidth);
        addedWeight.setPromptText("Weight");

        ObservableList<String> options = FXCollections.observableArrayList();
        for (Chef chef : chefsData) {
           options.add(chef.getChef());
        }

        chefsBox.setItems(options);
        chefsBox.setPrefWidth(preferComplexityColumnWidth + 25);
        chefsBox.setPromptText("Chef");

        final Button add_recipe = new Button("Add recipe");
        add_recipe.setOnAction((ActionEvent e) -> {
            String recipeName = addedRecipe.getText();
            String ingredientsText = addedIngredients.getText();
            String descriptionText = addedDescription.getText();
            String chef = chefsBox.getSelectionModel().getSelectedItem();;
            String weightText = addedWeight.getText();

            try {
                if(chefExists(chef)) {
                    Recipe recipe = new Recipe(recipeName, ingredientsText, descriptionText, chef, weightText);

                    recipesData.add(recipe);
                    addRecipeToDatabase(recipeName, ingredientsText, descriptionText, chef, weightText);

                    addedRecipe.clear();
                    addedIngredients.clear();
                    addedDescription.clear();
                    addedWeight.clear();
                }
                else
                    showAddingError("Chef don't exist!");

            } catch (Exception exc) {
                showAddingError(exc.getMessage());
            }
        });

        addBox.getChildren().addAll(addedRecipe, addedIngredients, addedDescription, chefsBox, addedWeight,
                add_recipe);
    }

    private void createAddChefBox() {
        final TextField addedChef = new TextField();
        addedChef.setMaxWidth(preferNameColumnWidth);
        addedChef.setPromptText("Chef");

        final TextField addedRate = new TextField();
        addedRate.setMaxWidth(preferIngredientsColumnWidth);
        addedRate.setPromptText("Rate");

        final TextField addedDescription = new TextField();
        addedDescription.setMaxWidth(preferCookingTimeColumnWidth);
        addedDescription.setPromptText("Description");

        final Button add_chef = new Button("Add chef");
        add_chef.setOnAction((ActionEvent e) -> {
            try{
            if(!chefExists(addedChef.getText())){
                Chef newChef = new Chef(addedChef.getText(), addedRate.getText(), addedDescription.getText());
                addChefToDataBase(newChef);
                chefsData.add(newChef);

                ObservableList<String> options = FXCollections.observableArrayList();
                for (Chef chef : chefsData) {
                    options.add(chef.getChef());
                }
                chefsBox.setItems(options);

                addedChef.clear();
                addedRate.clear();
                addedDescription.clear();
            }
            else
               showAddingError("Chef already exist!");
            } catch (Exception exc) {
                showAddingError(exc.getMessage());
            }
        });


        addChefBox.getChildren().addAll(addedChef, addedRate, addedDescription, add_chef);
    }

    private void showAddingError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Adding error");
        alert.setHeaderText("Can't add new recipe");
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void addChefToDataBase(Chef newChef) {
        String sql = "INSERT INTO chefs(rate, chef, description) VALUES(?,?,?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, newChef.getRate());
            statement.setString(2, newChef.getChef());
            statement.setString(3, newChef.getDescription());

            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private boolean chefExists(String newChef) {
        for (Chef chef : chefsData) {
            if (chef.getChef().equals(newChef)) {
                return true;
            }
        }
        return false;
    }

    private void createChefsTable() {
        TableColumn<Chef, String> nameColumn = new TableColumn<>("Chef");
        TableColumn<Chef, String> rateColumn = new TableColumn<>("Rate");
        TableColumn<Chef, String> descriptionColumn = new TableColumn<>("Description");

        setTypeColumnValues(nameColumn, 70, "chef");
        setTypeColumnValues(rateColumn, 70, "rate");
        setTypeColumnValues(descriptionColumn, 500, "description");

        chefsTable.setItems(chefsData);
        chefsTable.getColumns().addAll(nameColumn, rateColumn, descriptionColumn);
        chefsTable.setMaxHeight(200);
    }

    private void createRecipesTable() {
        TableColumn<Recipe, String> nameColumn = new TableColumn<>("Name");
        TableColumn<Recipe, String> ingredientsColumn = new TableColumn<>("Ingredients");
        TableColumn<Recipe, String> descriptionColumn = new TableColumn<>("Description");
        TableColumn<Recipe, String> chefColumn = new TableColumn<>("Chef");
        TableColumn<Recipe, String> weightColumn = new TableColumn<>("Weight");

        setRecipeColumnValues(nameColumn, preferNameColumnWidth, "name");
        setRecipeColumnValues(ingredientsColumn, preferIngredientsColumnWidth, "ingredients");
        setRecipeColumnValues(descriptionColumn, preferComplexityColumnWidth, "description");
        setRecipeColumnValues(chefColumn, preferCookingTimeColumnWidth, "chef");
        setRecipeColumnValues(weightColumn, preferCookingTimeColumnWidth, "weight");


        recipesTable.setItems(recipesData);
        recipesTable.getColumns().addAll(nameColumn, ingredientsColumn, descriptionColumn, chefColumn, weightColumn);
        recipesTable.setMaxHeight(300);

    }

    private void setTypeColumnValues(TableColumn<Chef, String> column, int width, String sqlName) {
        column.setPrefWidth(width);
        column.setCellValueFactory(param -> param.getValue().getFieldFromDerby(sqlName));
    }

    private void setRecipeColumnValues(TableColumn<Recipe, String> column, int width, String sqlName) {
        column.setPrefWidth(width);
        column.setCellValueFactory(param -> param.getValue().getFieldFromDerby(sqlName));
    }

    private void addRecipeToDatabase(String recipeName, String ingredients,String description, String chef, String weight) {
        String sql = "INSERT INTO recipes(name, ingredients, description, weight, chef) VALUES(?,?,?,?,?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, recipeName);
            statement.setString(2, ingredients);
            statement.setString(3, description);
            statement.setString(4, weight);
            statement.setString(5, chef);

            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}