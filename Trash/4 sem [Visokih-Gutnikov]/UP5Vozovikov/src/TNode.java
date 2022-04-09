
public class TNode {

    private String cookingTime, description, recName;
    private int igCount;

    TNode(String cookingTime, String description, String recName, String igCount) {
        this.cookingTime = cookingTime;
        this.description = description;
        this.recName = recName;
        try {
            this.igCount = Integer.parseInt(igCount);
        } catch (Exception e) {
            this.igCount = 0;
        }
    }

    public String getCookingTime() {
        return cookingTime;
    }

    public String getDescription() {
        return description;
    }

    public String getRecName() {
        return recName;
    }

    public int getIgCount() {
        return igCount;
    }

}