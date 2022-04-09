
import javax.swing.tree.DefaultMutableTreeNode;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;

public class TTreeNode extends DefaultMutableTreeNode {

    private static final long serialVersionUID = 1L;
    private String nodeName;
    private ArrayList<TTreeNode> nodes = new ArrayList<TTreeNode>();
    boolean isLeafNode = false;

    public TTreeNode() {
        nodeName = "-";
    }

    TTreeNode(String name) {
        nodeName = name;
    }

    TTreeNode(String name, boolean LeafNode) {
        nodeName = name;
        isLeafNode = LeafNode;
    }

    void addNode(TTreeNode node) {
        nodes.add(node);
    }

    boolean deleteNode(TTreeNode node) {
        boolean isExist = false;
        for (int i = 0; i < nodes.size(); ++i)
            if (nodes.get(i).toString().compareToIgnoreCase(node.toString()) == 0) {
                nodes.remove(i);
                isExist = true;
            }
        return isExist;
    }

    ArrayList<TNode> getAllLeaves(boolean aim) {
        ArrayList<TNode> leaves = new ArrayList<TNode>();
        Deque<TTreeNode> deque = new ArrayDeque<TTreeNode>();
        deque.push(this);
        TTreeNode temp;
        while (!deque.isEmpty()) {
            temp = deque.removeFirst();
            if (temp.isLeafNode) {
                int i = 0;
                String info[] = new String[4];
                while (temp.getParent() != null) {
                    info[i++] = temp.nodeName;
                    temp = (TTreeNode) temp.getParent();
                }
                if(aim)
                leaves.add(new TNode(info[1], info[2], info[3], info[0]));
                else
                    leaves.add(new TNode(info[3], info[2], info[1], info[0]));
            } else
                for (int i = 0; i < temp.nodes.size(); ++i)
                    deque.push(temp.nodes.get(i));
        }
        return leaves;
    }

    public String toString() {
        return nodeName;
    }

}