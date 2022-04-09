import javafx.beans.property.SimpleStringProperty;

public class Chef {
    private SimpleStringProperty chef;
    private SimpleStringProperty rate;
    private SimpleStringProperty description;

    Chef(String chef, String rate, String description) throws Exception {
        if (chef == null || chef.isEmpty()) {
            throw new Exception("Field 'Chef' is empty");
        }
        if (rate == null || rate.isEmpty()) {
            throw new Exception("Field 'Rate' is empty");
        }
        if (description == null || description.isEmpty()) {
            throw new Exception("Field 'Description' is empty");
        }

        this.chef = new SimpleStringProperty(chef);
        this.rate = new SimpleStringProperty(rate);
        this.description = new SimpleStringProperty(description);
    }

    SimpleStringProperty getFieldFromDerby(String fieldName) {
        SimpleStringProperty res;
        switch (fieldName) {
            case "chef":
                res = this.chef;
                break;
            case "rate":
                res = this.rate;
                break;
            case "description":
                res = this.description;
                break;
            default:
                res = null;
        }
        return res;
    }

    public String getChef() { return chef.get(); }
    public SimpleStringProperty chefProperty() {
        return chef;
    }

    public String getRate() {
        return rate.get();
    }
    public SimpleStringProperty rateProperty() {
        return rate;
    }

    public String getDescription() {
        return description.get();
    }
    public SimpleStringProperty descriptionProperty() {
        return description;
    }
}
