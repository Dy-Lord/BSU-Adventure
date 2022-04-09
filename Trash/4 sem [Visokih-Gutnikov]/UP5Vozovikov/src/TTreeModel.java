
import javax.swing.tree.DefaultTreeModel;

public class TTreeModel extends DefaultTreeModel {

    private static final long serialVersionUID = 1L;
    private TTreeNode root;

    TTreeModel(TTreeNode root) {
        super(root);
        this.root = root;
    }

    public TTreeNode getRoot() {
        return root;
    }

    void insertNodeInto(TTreeNode child, TTreeNode parent, int i, boolean flag) {
        insertNodeInto(child, parent, i);
        parent.addNode(child);
    }

}