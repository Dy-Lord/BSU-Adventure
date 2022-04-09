import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddRecipe extends JFrame {
    private MainFrame cookingBook;

    private JLabel recName = new JLabel("Recipe");
    private JLabel description = new JLabel("Description");
    private JLabel cookingTime = new JLabel("Cooking time");
    private JLabel igCount = new JLabel("Ingredients count");

    private JTextField nameModel = new JTextField();
    private JTextField descModel = new JTextField();
    private JTextField timeModel = new JTextField();
    private JTextField countModel = new JTextField();
    private JButton okButton = new JButton("OK");

    public AddRecipe(MainFrame cBook) throws HeadlessException {
        Container c = getContentPane();
        this.cookingBook = cBook;
        okButton.addActionListener(new ok_Listner());
        this.setTitle("New recipe");
        this.setBounds(400, 200, 400, 150);
        this.setSize(350, 250);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        panel.add(recName);
        panel.add(nameModel);

        panel.add(description);
        panel.add(descModel);

        panel.add(igCount);
        panel.add(countModel);

        panel.add(cookingTime);
        panel.add(timeModel);

        panel.add(okButton);
        c.add(panel);

        setDefaultCloseOperation(HIDE_ON_CLOSE);
    }

    private class ok_Listner implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e) {
            if(nameModel.getText().equals("") || timeModel.getText().equals("") || countModel.getText().equals("") || descModel.getText().equals("")){
                JOptionPane.showMessageDialog(null, "Void field!", "Attention", JOptionPane.WARNING_MESSAGE);
            }else{
                try {
                    TNode lp = new TNode(nameModel.getText(), descModel.getText(), timeModel.getText(), countModel.getText());
                    MainFrame.addResult = lp;
                    cookingBook.addNewItem();
                } catch (NumberFormatException x){
                    JOptionPane.showMessageDialog(null, "Wrong ingredient count!", "Attention", JOptionPane.WARNING_MESSAGE);
                }
            }
            dispose();
        }
    }
}
