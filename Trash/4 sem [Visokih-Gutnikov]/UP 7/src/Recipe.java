import javafx.beans.property.SimpleStringProperty;

public class Recipe {
    private SimpleStringProperty recipeName;
    private SimpleStringProperty ingredients;
    private SimpleStringProperty description;
    private SimpleStringProperty chef;
    private SimpleStringProperty weight;

    Recipe(String recipeName, String ingredients, String description, String chef,
           String weight) throws Exception {

        if (recipeName == null || recipeName.isEmpty()) {
            throw new Exception("Field 'Recipe' is empty");
        }
        if (description == null || description.isEmpty()) {
            throw new Exception("Field 'Description' is empty");
        }
        if (ingredients == null || ingredients.isEmpty()) {
            throw new Exception("Field 'Ingredients' is empty");
        }
        if (chef == null || chef.isEmpty()) {
            throw new Exception("Field 'Chef' is empty");
        }
        if (weight == null || weight.isEmpty()) {
            throw new Exception("Field 'Weight' is empty");
        }

        this.recipeName = new SimpleStringProperty(recipeName);
        this.chef = new SimpleStringProperty(chef);
        this.description= new SimpleStringProperty(description);
        this.weight = new SimpleStringProperty(weight);
        this.ingredients = new SimpleStringProperty(ingredients);
    }

    SimpleStringProperty getFieldFromDerby(String fieldName) {
        SimpleStringProperty res;
        switch (fieldName) {
            case "name":
                res = this.recipeName;
                break;
            case "chef":
                res = this.chef;
                break;
            case "description":
                res = this.description;
                break;
            case "weight":
                res = this.weight;
                break;
            case "ingredients":
                res = this.ingredients;
                break;
            default:
                res = null;
        }
        return res;
    }

    public String getRecipeName() {
        return recipeName.get();
    }
    public SimpleStringProperty recipeNameProperty() {
        return recipeName;
    }

    public String getIngredients() {
        return ingredients.get();
    }
    public SimpleStringProperty ingredientsProperty() {
        return ingredients;
    }

    public String getDescription() {
        return description.get();
    }
    public SimpleStringProperty descriptionProperty() {
        return description;
    }

    public String getChef() {
        return chef.get();
    }
    public SimpleStringProperty chefProperty() {
        return chef;
    }

    public String getWeight() {
        return weight.get();
    }
    public SimpleStringProperty weightProperty() {
        return weight;
    }
}
