
import javax.swing.event.TableModelListener;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;

public class TTableModel implements javax.swing.table.TableModel {

    private Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<TNode> infoTNodes = new ArrayList<TNode>();
    static final String[] columnNames = new String[]{"Recipe", "Description", "Cooking time", "Ingredients count"};
    static final Class<?>[] columnTypes = new Class[]{String.class, String.class, String.class, Integer.class};

    public TTableModel() {
    }

    public TTableModel(ArrayList<TNode> al) {
        setInfoNodes(al);
    }

    public void setInfoNodes(ArrayList<TNode> al) {
        infoTNodes = al;
    }

    @Override
    public void addTableModelListener(TableModelListener l) {
        listeners.add(l);
    }

    @Override
    public Class<?> getColumnClass(int columnIndex) {
        return columnTypes[columnIndex];
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public String getColumnName(int columnIndex) {
        return columnNames[columnIndex];
    }

    @Override
    public int getRowCount() {
        return infoTNodes.size();
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        TNode an = infoTNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return an.getRecName();
            case 1:
                return an.getDescription();
            case 2:
                return an.getCookingTime();
            case 3:
                return an.getIgCount();
        }
        return "";
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return false;
    }

    @Override
    public void removeTableModelListener(TableModelListener l) {
        listeners.remove(l);
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
    }

}