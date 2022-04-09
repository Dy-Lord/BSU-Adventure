
import javax.swing.*;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Enumeration;

public class MainFrame extends JFrame {

    public static String CANCELFLAG = "CANCEL_FLAG_5h23ng8b9234fevaa9uoh284";

    private static final long serialVersionUID = 1L;
    public static TNode addResult = null;
    public TTreeNode root;
    public static String path = null;

    JTable infoPanel;
    JTree notebooksTree;
    JMenu fileMenu, optionMenu;
    JMenuItem mSave, mImport, addMenu, deleteMenu;

    static TTableModel TTableModel = null;
    static TTreeModel TTreeModel = null;

    public MainFrame() throws HeadlessException {

        JMenuBar mb = new JMenuBar();
        fileMenu = new JMenu("File");
        optionMenu = new JMenu("Options");

        addMenu = new JMenuItem("Add");
        deleteMenu = new JMenuItem("Delete");

        mSave = new JMenuItem("Save");
        mImport = new JMenuItem("Import");

        fileMenu.add(mSave);
        fileMenu.add(mImport);
        optionMenu.add(addMenu);
        optionMenu.add(deleteMenu);

        mb.add(fileMenu);
        mb.add(optionMenu);
        setJMenuBar(mb);

        mSave.addActionListener(e -> saveData());
        mImport.addActionListener(e -> importData());

        addMenu.addActionListener(e -> openAddDialog());
        deleteMenu.addActionListener(e -> removeItem());

        TTableModel = new TTableModel();
        infoPanel = new JTable(TTableModel);
        TTreeModel = new TTreeModel(new TTreeNode("Cooking Book"));
        notebooksTree = new JTree(TTreeModel);

        notebooksTree.addTreeSelectionListener(e -> {
            TTreeNode node = (TTreeNode) notebooksTree.getLastSelectedPathComponent();
            if (node == null) {
                return;
            }
            ArrayList<TNode> array = node.getAllLeaves(true);
            TTableModel = new TTableModel(array);
            infoPanel.setModel(TTableModel);
        });

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, true, new JScrollPane(notebooksTree), new JScrollPane(infoPanel));
        splitPane.setDividerLocation(150);

        getContentPane().add(splitPane);

        setBounds(100, 100, 600, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }


    private void openAddDialog() {
        AddRecipe addForm = new AddRecipe(this);
        addForm.setVisible(true);
    }

    void addNewItem() {
        TTreeNode temp;
        root = TTreeModel.getRoot();

        if (addResult != null) {
            try {
                    TTreeModel.insertNodeInto(new TTreeNode(addResult.getCookingTime()), root, root.getChildCount(), true);
                    TTreeModel.insertNodeInto(new TTreeNode(addResult.getDescription()), temp = findNode(root, addResult.getCookingTime()), temp.getChildCount(), true);
                    TTreeModel.insertNodeInto(new TTreeNode(addResult.getRecName()), temp = findNode(temp, addResult.getDescription()), temp.getChildCount(), true);
                    TTreeModel.insertNodeInto(new TTreeNode(Integer.toString(addResult.getIgCount()), true), temp = findNode(temp, addResult.getRecName()), temp.getChildCount(), true);

            } catch (Exception e) {
                path = null;
                addResult = null;
                return;
            }
        }

        addResult = null;
    }

    public void saveData() {
        String path = folderDialog(true);
        if (!path.equals(CANCELFLAG))
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(path))) {
                oos.writeObject(root);
            } catch (Exception ex) {
            }
    }

    public void importData() {
        String path = folderDialog(false);
        if (!path.equals(CANCELFLAG))
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(path))) {
                root = (TTreeNode) ois.readObject();

                ArrayList<TNode> array = root.getAllLeaves(false);
                TTableModel = new TTableModel(array);
                TTreeModel.reload();

                for (TNode node : array) {
                    addResult = node;
                    addNewItem();
                }
                infoPanel.setModel(TTableModel);
            } catch (Exception ex) {
            }
    }

    public String folderDialog(boolean save) {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        int option;

        if (save)
            option = fileChooser.showSaveDialog(this);
        else
            option = fileChooser.showOpenDialog(this);

        if (option == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            return file.getAbsolutePath();
        }
        return CANCELFLAG;
    }

    public void removeItem() {
        TreePath currentSelection = notebooksTree.getSelectionPath();
        if (currentSelection != null) {
            TTreeNode currentNode = (TTreeNode) (currentSelection.getLastPathComponent());
            TTreeNode parent = (TTreeNode) (currentNode.getParent());
            if (parent != null) {
                TTreeModel.removeNodeFromParent(currentNode);
                parent.deleteNode(currentNode);
                ArrayList<TNode> array = parent.getAllLeaves(true);
                TTableModel = new TTableModel(array);
                infoPanel.setModel(TTableModel);
            }
        }
    }

    private static TTreeNode findNode(TTreeNode root, String s) {
        Enumeration<TreeNode> e = root.depthFirstEnumeration();
        while (e.hasMoreElements()) {
            TTreeNode node = (TTreeNode) e.nextElement();
            if (node.toString().equalsIgnoreCase(s)) {
                return node;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
            System.err.println(e.getMessage());
        }
        MainFrame mainClass = new MainFrame();
    }
}